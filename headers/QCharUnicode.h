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

#ifndef __QCHARUNICODE__
#define __QCHARUNICODE__

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Represents a character in the Unicode code space.
/// </summary>
class QE_LAYER_COMMON_SYMBOLS QCharUnicode
{

	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a Unicode code point.
    /// </summary>
    /// <param name="codepoint">[IN] A code point that represents the character in the Unicode code space.</param>
	QCharUnicode(const codepoint_q &codepoint);

    /// <summary>
    /// Constructor that makes a copy of another character.
    /// </summary>
    /// <param name="character">[IN] The input character to be copied.</param>
    QCharUnicode(const QCharUnicode &character);


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignment operator that makes a copy of the input character.
    /// </summary>
    /// <param name="character">[IN] The input character to be copied.</param>
    QCharUnicode& operator=(const QCharUnicode &character);

    /// <summary>
    /// Equality operator that indicates whether Unicode characters are the same or not.
    /// </summary>
    /// <param name="character">[IN] The input character to be compared.</param>
    /// <returns>
    /// True if characters are equal; False otherwise.
    /// </returns>
    bool operator==(const QCharUnicode &character) const;

    /// <summary>
    /// Inequality operator that indicates whether Unicode characters are the same or not.
    /// </summary>
    /// <param name="character">[IN] The input character to be compared.</param>
    /// <returns>
    /// True if characters are not equal; False otherwise.
    /// </returns>
    bool operator!=(const QCharUnicode &character) const;


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the code point that corresponds to the character.
    /// </summary>
    /// <returns>
    /// A code point.
    /// </returns>
    codepoint_q GetCodePoint() const;


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// The code point that represents the character in the Unicode code space.
    /// </summary>
    codepoint_q m_value;


};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCHARUNICODE__
