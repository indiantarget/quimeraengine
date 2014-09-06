//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __QLIST__
#define __QLIST__

#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"
#include "Assertions.h"
#include "QPoolAllocator.h"
#include "QAlignment.h"
#include "QComparatorDefault.h"
#include "AllocationOperators.h"
#include "EQIterationDirection.h"


using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a double linked list of elements that can be accessed either sequentally or arbitrarily, using a zero-based index.
/// </summary>
/// <remarks>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T"> The type of the list elements.</typeparam>
/// <typeparam name="AllocatorT"> The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="ComparatorT"> The comparator. The default type is QComparatorDefault.</typeparam>
template <class T, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class ComparatorT = QComparatorDefault<T> >
class QList
{

    // INTERNAL CLASSES
    // -----------------

protected:

    /// <summary>
    /// Class intended to store the information needed to link one element of the list to another.
    /// </summary>
    class QLink
    {
        // CONSTRUCTORS
        // ---------------

    public:

        /// <summary>
        /// Constructor with the positions in the allocated memory chunk to the previous and next elements,
        /// passed by parameter.
        /// </summary>
        /// <param name="uPrevious"> [IN] Position of the previous element.</param>
        /// <param name="uNext"> [IN] Position of the next element.</param>
        QLink(const pointer_uint_q uPrevious, const pointer_uint_q uNext) :
                m_uPrevious(uPrevious),
                m_uNext(uNext)
        {
        }


        // PROPERTIES
        // ---------------

        /// <summary>
        /// Returns the index of the next element in the list.
        /// </summary>
        /// <returns>
        /// The index of the next element in the list. Returns QList::END_POSITION_FORWARD constant if there is no previous element.
        /// </returns>
        pointer_uint_q GetNext() const
        {
            return m_uNext;
        }

        /// <summary>
        /// Returns the index of the previous element in the list.
        /// </summary>
        /// <returns>
        /// The index of the previous element in the list. Returns QList::END_POSITION_BACKWARD constant if there is no previous element.
        /// </returns>
        pointer_uint_q GetPrevious() const
        {
            return m_uPrevious;
        }

        /// <summary>
        /// Sets the index of the next element in the list.
        /// </summary>
        /// <param name="uNext"> [IN] The index of the next element in the list. If there is no next element, you must pass QList::END_POSITION_FORWARD constant.</param>
        void SetNext(const pointer_uint_q uNext)
        {
            m_uNext = uNext;
        }

        /// <summary>
        /// Sets the index of the previous element in the list.
        /// </summary>
        /// <param name="uPrevious"> [IN] The index of the previous element in the list. If there is no previous element, you must pass QList::END_POSITION_BACKWARD constant.</param>
        void SetPrevious(const pointer_uint_q uPrevious)
        {
            m_uPrevious = uPrevious;
        }

    public:

        // ATTRIBUTES
        // ---------------

    protected:

        /// <summary>
        /// The index of the next element in the list. QList::END_POSITION_FORWARD must be used when there is no next element.
        /// </summary>
        pointer_uint_q m_uNext;

        /// <summary>
        /// The index of the previous element in the list. QList::END_POSITION_BACKWARD must be used when there is no previous element.
        /// </summary>
        pointer_uint_q m_uPrevious;

    };

public:

    /// <summary>
    /// Iterator that steps once per element of a list.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a list, it cannot point to another list ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the list.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QListIterator
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the list to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetConstIterator and GetIterator methods instead.
        /// </summary>
        /// <remarks>
        /// If the list is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pList">[IN] The list to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of list elements, but the physical.
        /// It must be lower than the capacity of the list.</param>
        QListIterator(const QList* pList, const unsigned int uPosition) : m_pList(pList), m_uPosition(uPosition)
        {
            QE_ASSERT_ERROR(pList != null_q, "Invalid argument: The pointer to the list cannot be null");
            QE_ASSERT_WARNING(pList->GetCapacity() > uPosition, "Invalid argument: The position must be lower than the capacity of the list");

            if(pList == null_q || pList->GetCapacity() <= uPosition || pList->IsEmpty())
                m_uPosition = QList::END_POSITION_FORWARD;
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same list as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QListIterator& operator=(const QListIterator &iterator)
        {
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "The input iterator points to a different list");

            if(m_pList == iterator.m_pList)
                m_uPosition = iterator.m_uPosition;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the list element");

            QE_ASSERT_ERROR(m_uPosition != QList::END_POSITION_FORWARD && m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return *(((T*)m_pList->m_elementAllocator.GetPointer()) + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the list element");

            QE_ASSERT_ERROR(m_uPosition != QList::END_POSITION_FORWARD && m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return ((T*)m_pList->m_elementAllocator.GetPointer()) + m_uPosition;
        }

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QListIterator operator++(int)
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = QList::END_POSITION_FORWARD;
            else if(m_uPosition == QList::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != QList::END_POSITION_FORWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetNext();

            return iteratorCopy;
        }

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QListIterator operator--(int)
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = QList::END_POSITION_BACKWARD;
            else if(m_uPosition == QList::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != QList::END_POSITION_BACKWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetPrevious();

            return iteratorCopy;
        }

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QListIterator& operator++()
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = QList::END_POSITION_FORWARD;
            else if(m_uPosition == QList::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != QList::END_POSITION_FORWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetNext();

            return *this;
        }

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QListIterator& operator--()
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = QList::END_POSITION_BACKWARD;
            else if(m_uPosition == QList::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != QList::END_POSITION_BACKWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetPrevious();

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same list to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same list; False otherwise.
        /// </returns>
        bool operator==(const QListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            return m_uPosition == iterator.m_uPosition && m_pList == iterator.m_pList;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different list is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different list; False otherwise.
        /// </returns>
        bool operator!=(const QListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            return m_uPosition != iterator.m_uPosition || m_pList != iterator.m_pList;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QList::END_POSITION_FORWARD &&
               m_uPosition != QList::END_POSITION_BACKWARD)
            {
                QList::QListIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator does not equal the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QList::END_POSITION_BACKWARD &&
               m_uPosition != QList::END_POSITION_FORWARD)
            {
                QList::QListIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator equals the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QList::QListIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator does not equal the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QList::QListIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator equals the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the list.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <returns>
        /// True if the iterator is pointing to an end position; False otherwise.
        /// </returns>
        bool IsEnd() const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return m_uPosition == QList::END_POSITION_BACKWARD || m_uPosition == QList::END_POSITION_FORWARD;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the list, distinguishing which of them.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <param name="eIterationDirection">[IN] The iteration direction used to identify which of the end positions is checked.</param>
        /// <returns>
        /// True if the iterator is pointing to the position after the last element when iterating forward or if it is
        /// pointing to the position immediately before the first position when iterating backward; False otherwise.
        /// </returns>
        bool IsEnd(const EQIterationDirection &eIterationDirection) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return (eIterationDirection == EQIterationDirection::E_Backward && m_uPosition == QList::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EQIterationDirection::E_Forward  && m_uPosition == QList::END_POSITION_FORWARD);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            m_uPosition = m_pList->m_uFirst == QList::END_POSITION_BACKWARD ? QList::END_POSITION_FORWARD : m_pList->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            m_uPosition = m_pList->m_uLast;
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a list may have been shortened while the iterator
        /// was pointing to its last position). If the list to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pList != null_q && 
                   (m_uPosition < m_pList->m_linkAllocator.GetPoolSize() / sizeof(QList::QLink) ||
                    m_uPosition == QList::END_POSITION_BACKWARD ||
                    m_uPosition == QList::END_POSITION_FORWARD);
        }


        // ATTRIBUTES
        // ---------------
    private:

        /// <summary>
        /// The list the iterator points to.
        /// </summary>
        const QList* m_pList;

        /// <summary>
        /// The current iteration position regarding the base position of the buffer (zero). It is zero-based.
        /// </summary>
        pointer_uint_q m_uPosition;

    }; // QListIterator


       // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Number of elements for which to reserve memory in the default constructor.
    /// </summary>
    static const pointer_uint_q DEFAULT_NUMBER_OF_ELEMENTS = 1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the last element.
    /// </summary>
    static const pointer_uint_q END_POSITION_FORWARD = -1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first element.
    /// </summary>
    static const pointer_uint_q END_POSITION_BACKWARD = -2;

    // CONSTRUCTORS
    // ---------------

public:

    /// <summary>
    /// Default constructor. It reserves memory for the number of elements indicated at DEFAULT_NUMBER_OF_ELEMENTS constants.
    /// </summary>
    QList() :
            m_uFirst(QList::END_POSITION_BACKWARD),
            m_uLast(QList::END_POSITION_FORWARD),
            m_elementAllocator(QList::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
            m_linkAllocator(QList::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
    }

    /// <summary>
    /// Constructor that reserves space to store the number of elements passed by parameter.
    /// </summary>
    /// <param name="uInitialCapacity"> [IN] Number of elements for wich to reserve space. It must be greater than zero.</param>
    QList(const pointer_uint_q uInitialCapacity) :
            m_uFirst(QList::END_POSITION_BACKWARD),
            m_uLast(QList::END_POSITION_FORWARD),
            m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
            m_linkAllocator(uInitialCapacity * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
        QE_ASSERT_ERROR( uInitialCapacity > 0, "Initial capacity must be greater than zero" );
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every element is called.
    /// </remarks>
    /// <param name="list">[IN] Source list to copy.</param>
    QList(const QList& list) : m_elementAllocator(list.m_elementAllocator.GetPoolSize(), sizeof(T), QAlignment(alignof_q(T))),
                               m_linkAllocator(list.m_linkAllocator.GetPoolSize(), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
        if(list.m_uFirst == QList::END_POSITION_BACKWARD)
        {
            m_uFirst = QList::END_POSITION_BACKWARD;
            m_uLast = QList::END_POSITION_FORWARD;
        }
        else
        {
            list.m_linkAllocator.CopyTo(m_linkAllocator);
            list.m_elementAllocator.CopyTo(m_elementAllocator);

            m_uFirst = list.m_uFirst;
            m_uLast = list.m_uLast;

            QList::QListIterator iteratorOrigin = list.GetFirst();
            QList::QListIterator iteratorDestination = this->GetFirst();

            for(; !iteratorOrigin.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
            {
                new(&(*iteratorDestination)) T(*iteratorOrigin);
            }
        }
    }
    
protected:

    // DESTRUCTOR
    // ---------------

public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element is called in the same order they appear in the list.
    /// </remarks>
    ~QList()
    {
        if(m_uFirst != QList::END_POSITION_BACKWARD)
        {
            // Iterates the list in an orderly manner, calling the destructor for each element.
            pointer_uint_q uIndex = m_uFirst;
            pointer_uint_q uNextIndex;
            QList::QLink* pLink = null_q;
            T* pElement = null_q;
            bool bDestroyed = false;

            while(!bDestroyed)
            {
                pLink = (QList::QLink*)m_linkAllocator.GetPointer() + uIndex * sizeof(QList::QLink);
                uNextIndex = pLink->GetNext();

                pElement = (T*)m_elementAllocator.GetPointer() + uIndex * sizeof(T);
                pElement->~T();

                if(uIndex == m_uLast)
                    bDestroyed = true;
                else
                    uIndex = uNextIndex;
            }
        }
    }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignment operator that copies one list to another.
    /// </summary>
    /// <remarks>
    /// Assignment operator will be called for every element of the list.
    /// </remarks>
    /// <param name="list">[IN] List to copy in the current list.</param>
    /// <returns>
    /// A reference to the current list.
    /// </returns>
    QList& operator= (const QList& list)
    {
        if(this != &list)
        {
            if(list.GetCount() == this->GetCount())
            {
                QListIterator iteratorOrigin = QListIterator(&list);
                QListIterator iteratorDestination = QListIterator(this);

                for(iteratorOrigin.MoveFirst(), iteratorDestination.MoveFirst();
                    !iteratorOrigin.IsEnd();
                    ++iteratorOrigin, ++iteratorDestination)
                {
                    *iteratorDestination = *iteratorOrigin;
                }
            }
            else if(list.GetCount() < this->GetCount())
            {
                pointer_uint_q uFirstIndexToDestroy;
                pointer_uint_q uOldLast = m_uLast;

                if(list.GetCount() == 0)
                {
                    uFirstIndexToDestroy = m_uFirst;
                    m_uFirst = QList::END_POSITION_BACKWARD;
                    m_uLast = QList::END_POSITION_FORWARD;
                }
                else
                {
                    // Makes the copy calling assignment operator with existing elements.

                    T* pElementOrigin = null_q;
                    T* pElementDestination = null_q;
                    QList::QLink* pLinkOrigin = null_q;
                    QList::QLink* pLinkDestination = null_q;

                    pointer_uint_q uIndexOrigin = list.m_uFirst;
                    pointer_uint_q uIndexDestination = m_uFirst;

                    bool bCopied = false;

                    while(!bCopied)
                    {
                        pElementOrigin = (T*)list.m_elementAllocator.GetPointer() + uIndexOrigin * sizeof(T);
                        pElementDestination = (T*)m_elementAllocator.GetPointer() + uIndexDestination * sizeof(T);

                        *pElementDestination = *pElementOrigin;

                        bCopied = (uIndexOrigin == list.m_uLast);
                        m_uLast = uIndexDestination;

                        pLinkOrigin = (QList::QLink*)list.m_linkAllocator.GetPointer() + uIndexOrigin * sizeof(QList::QLink);
                        uIndexOrigin = pLinkOrigin->GetNext();

                        pLinkDestination = (QList::QLink*)m_linkAllocator.GetPointer() + uIndexDestination * sizeof(QList::QLink);
                        uIndexDestination = pLinkDestination->GetNext();
                    }
                    uFirstIndexToDestroy = uIndexDestination;
                }

                // Destroys the rest of the destination list

                pointer_uint_q uIndex = uFirstIndexToDestroy;
                pointer_uint_q uNextIndex;

                bool bDestroyed = false;

                while(!bDestroyed && uIndex != QList::END_POSITION_FORWARD)
                {
                    QList::QLink* pLink = (QList::QLink*)m_linkAllocator.GetPointer() + uIndex * sizeof(QList::QLink);
                    uNextIndex = pLink->GetNext();
                    m_linkAllocator.Deallocate(pLink);

                    T* pElement = (T*)m_elementAllocator.GetPointer() + uIndex * sizeof(T);
                    pElement->~T();
                    m_elementAllocator.Deallocate(pElement);

                    bDestroyed = (uIndex == uOldLast);
                    uIndex = uNextIndex;
                }
            }
            else
            {
                if(list.GetCapacity() > this->GetCapacity())
                {
                    AllocatorT *pOldElementAllocator = m_elementAllocator;
                    AllocatorT *pOldLinkAllocator = m_linkAllocator;

                    // Creates new allocators

                    m_elementAllocator.Reallocate(list.GetCapacity() * sizeof(T));
                    m_linkAllocator.Reallocate(list.GetCapacity() * sizeof(QList::QLink));

                    pOldElementAllocator->CopyTo(*m_linkAllocator);
                    pOldLinkAllocator->CopyTo(*m_elementAllocator);

                    delete pOldElementAllocator;
                    delete pOldLinkAllocator;
                }

                QListIterator iteratorOrigin = QListIterator(&list);
                QListIterator iteratorDestination = QListIterator(this);

                // Copies as many elements as it has the destination list.

                for(iteratorOrigin.MoveFirst(), iteratorDestination.MoveFirst();
                    !iteratorDestination.IsEnd();
                    ++iteratorOrigin, ++iteratorDestination)
                {
                    *iteratorDestination = *iteratorOrigin;
                }

                // Adds the rest of elements if needed.

                while(!iteratorOrigin.IsEnd())
                {
                    this->Add(*iteratorOrigin);
                    ++iteratorOrigin;
                }
            }
        }
        
        return *this;
    }

    /// <summary>
    /// Performs a fast shallow copy of the list elements.
    /// </summary>
    /// <remarks>
    /// Neither elements' constructor nor element's assignment operator are called.
    /// </remarks>
    /// <param name="destinationList"> [OUT] Destination list where to copy the list elements. If the destination list's capacity is lower
    /// than the resident list's capacity, it will be increased.</param>
    void Clone(QList &destinationList) const
    {
        // Uncomment when reserve method is implemented
        //if ( destinationList.GetCapacity() < this->GetCapacity())
            // destinationList.Reserve(this->GetCapacity());
        m_elementAllocator->CopyTo(*destinationList.m_elementAllocator);
        m_linkAllocator->CopyTo(*destinationList.m_linkAllocator);
        destinationList.m_uFirst = m_uFirst;
        destinationList.m_uLast = m_uLast;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex"> [IN] Position of the element to access. It must be less than the list's size. Note that indexes are zero-based.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& GetValue(const pointer_uint_q uIndex) const
    {
        // [TODO] raul. When unit tests get done, check if the program crashes in case the index is not lower than the number of elements.
        // [TODO] raul. If so a remark must be added in the documentation.

        QE_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );
        QList::QListIterator iterator = QList::QListIterator(this, 0); // [TODO] Thund: Replace with QList::GetIterator when it exists
        pointer_uint_q uCurrentIndex = 0;

        for(iterator.MoveFirst(); !iterator.IsEnd(); ++iterator, ++uCurrentIndex)
        {
            if (uCurrentIndex == uIndex)
                break;
        }
        return (*iterator);

        T t;
        return t; // [TODO] Thund: Remove this line when the above block is uncommented
    }

    /// <summary>
    /// Sets the value in the index passed as parameter.
    /// </summary>
    /// <param name="uIndex"> [IN] Position of the element to set. It must be less than the list's size. Note that indexes are zero-based.</param>
    void SetValue(const pointer_uint_q uIndex, const T& value)
    {
        // [TODO] raul. When unit tests get done, check if the program crashes in case the index is not lower than the number of elements.
        // [TODO] raul. If so a remark must be added in the documentation.

        QE_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );
        QList::QListIterator iterator = QList::QListIterator(this, 0); // [TODO] Thund: Replace with QList::GetIterator when it exists
        pointer_uint_q uCurrentIndex = 0;
        iterator.MoveFirst();

        while ( (uCurrentIndex <= uIndex) && (!iterator.IsEnd()) )
        {
            if (uCurrentIndex == uIndex)
                *iterator = value;
            ++iterator;
            ++uCurrentIndex;
        }

    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position. Indexes are zero-based.
    /// </summary>
    /// <param name="uIndex"> [IN] Position of the element to access. It must be less than the list's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& operator[] (const pointer_uint_q uIndex) const
    {
        // [TODO] raul. When unit tests get done, check if the program crashes in case the index is not lower than the number of elements.
        // [TODO] raul. If so a remark must be added in the documentation.
        return this->GetValue(uIndex);
    }
    
    /// <summary>
    /// Gets an iterator that points to a given position in the list.
    /// </summary>
    /// <param name="uIndex">[IN] Position in the list, starting at zero, to which the iterator will point. If it is out of bounds, the returned iterator will point 
    /// to the end position.</param>
    /// <returns>
    /// An iterator that points to the position of the element.
    /// </returns>
    QListIterator GetIterator(const pointer_uint_q uIndex) const 
    {
        QE_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );

        QList::QListIterator iterator(this, m_uFirst);

        if(!this->IsEmpty())
            for(pointer_uint_q i = 0; i < uIndex; ++i)
                ++iterator;

        return iterator;
    }

    /// <summary>
    /// Gets an iterator that points to the first position in the list.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the first element. If the list is empty, the iterator will point to the end position.
    /// </returns>
    QListIterator GetFirst() const
    {
        QE_ASSERT_WARNING( !this->IsEmpty(), "The list is empty, there is no first position." );

        return QList::QListIterator(this, m_uFirst);
        
    }

    /// <summary>
    /// Gets an iterator that points to the last position in the list.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the last element. If the list is empty, the iterator will point to the end position.
    /// </returns>
    QListIterator GetLast() const
    {
        QE_ASSERT_WARNING( !this->IsEmpty(), "The list is empty, there is no last position." );

        return QList::QListIterator(this, m_uLast);
    }
    
    /// <summary>
    /// Increases the capacity of the list, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means:<br/>
    /// - Iterators pointing to elements of this list may become invalid.<br/>
    /// - Any pointer to elements of this list will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const pointer_uint_q uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
        {
            m_elementAllocator.Reallocate(uNumberOfElements * sizeof(T));
            m_linkAllocator.Reallocate(uNumberOfElements * sizeof(QList::QLink));
        }
    }


    // PROPERTIES
    // ---------------

public:

    /// <summary>
    /// Returns a constant pointer to the element allocator.
    /// </summary>
    /// <returns>
    /// Constant pointer to the element allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return &m_elementAllocator;
    }

    /// <summary>
    /// Returns the number of elements in the list.
    /// </summary>
    /// <returns>
    /// The number of elements in the list.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_elementAllocator.GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
    /// Returns the number of elements that can be stored in the list without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of elements that can be stored in the list without a reallocation.
    /// </returns>
    pointer_uint_q GetCapacity() const
    {
        return m_elementAllocator.GetPoolSize() / sizeof(T);
    }

    /// <summary>
    /// Checks whether the list is empty or not.
    /// </summary>
    /// <returns>
    /// True if the list is empty.
    /// </returns>
    bool IsEmpty() const
    {
        return (GetCount() == 0);
    }

    // ATTRIBUTES
    // ---------------

protected:

    /// <summary>
    /// The comparator used to compare elements.
    /// </summary>
    ComparatorT m_comparator;

    /// <summary>
    /// Index of the first element in the sequence. If there is no first element, its value is END_POSITION_BACKWARD constant.
    /// </summary>
    pointer_uint_q m_uFirst;

       /// <summary>
    /// Index of the last element in the sequence. If there is no last element, its value is END_POSITION_FORWARD constant.
    /// </summary>
    pointer_uint_q m_uLast;

    /// <summary>
    /// The allocator which stores the list elements.
    /// </summary>
    AllocatorT m_elementAllocator;

      /// <summary>
    /// The allocator which stores the double linked list for internals.
    /// </summary>
    AllocatorT m_linkAllocator;
};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLIST__
