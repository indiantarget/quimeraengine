﻿// [TERMS&CONDITIONS]

#ifndef __QLINESEGMENT2D__
#define __QLINESEGMENT2D__

#include "QLineSegment.h"

#include "QBaseOrb.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward Declarations
//-----------------------
class QVector2;
template<class VectorType> class QBaseTriangle;
typedef QBaseTriangle<QVector2> QBaseTriangle2;
class QBaseQuadrilateral;

/// <summary>
/// This class represents a chunk (segment) of straight line into 2D space, defined by two
/// endpoints, A and B.
/// These points will always be expressed as 2D points or vectors.
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below). However, some transforming methods will rotate the segment using A
/// by default as the pivot point.
/// </summary>
class QDllExport QLineSegment2D : public QLineSegment<QVector2>
{

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
	static const QLineSegment2D UnitLine;

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints
	/// both equals to (0,0) and it's length equals 0.
    /// </summary>
	static const QLineSegment2D LineZero;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QLineSegment2D() { };

	/// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] 2D vector to define endpoint A.</param>
    /// <param name="vB">[IN] 2D vector to define endpoint B.</param>
	inline QLineSegment2D (const QVector2& vA, const QVector2& vB) : QLineSegment<QVector2>(vA,vB) { }

	/// <summary>
    /// Constructor from a 2D line segment.
    /// </summary>
    /// <param name="segmt">[IN] 2D line segment containing the two endpoints.</param>
	inline explicit QLineSegment2D (const QLineSegment<QVector2>& segmt) : QLineSegment<QVector2>(segmt.A, segmt.B)  { }


	// METHODS
	// ---------------
public:
	/// <summary>
	/// Assigning operator.
	/// </summary>
	/// <param name="segmt">[IN] The 2D segment to be copied from.</param>
	/// <returns>
	/// A reference to the modified line segment.
	/// </returns>
    inline QLineSegment2D& operator=(const QBaseLineSegment2& segmt)
    {
		// [TODO] It must be done via QLineSegment assign operator,
		//		  when it's implemented on QLineSegment.
        //reinterpret_cast<QBaseLineSegment2&>(*this) = segmt;   
        //return *this;
    }

	/// <summary>
	/// This method receives a 2D cirle, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="circle">[IN] The 2D circle to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the circle (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns> 
	inline bool Intersection (const QBaseOrb<QVector2>& circle) const
	{
		// An intersection between the segment and the circle is considered if the minimum
		// distance between "the whole segment" and the center of the circle (this is, the
		// minimum distance between the center of the circle and the closest point inside
		// the segment) is either lesser or equal than the radius of the circle.
		return QFloat::IsLowerOrEquals(this->MinDistance(circle.P), circle.Radius);
	};

	/// <summary>
	/// This method receives a 2D triangle, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="triangl">[IN] The 2D triangle to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the triangle (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection (const QBaseTriangle2& triangl) const; 

	/// <summary>
	/// This method receives a 2D quadrilateral, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="quadrl">[IN] The 2D quadrilateral to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the quadrilateral (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection (const QBaseQuadrilateral& quadrl) const;

	/// <summary>
	/// This method receives another line segment, and computes wheter they intersect each other or not.
	/// This method calls base class' implementation.
	/// </summary>
	/// <param name="vBaseLineSegment">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection (const QBaseLineSegment<QVector2>& vBaseLineSegment) const
	{
		return QLineSegment<QVector2>::Intersection(vBaseLineSegment);
	}

	/// <summary>
	/// This method transforms the 2D segment by rotating an amount defined by a rotation angle. 
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <remarks>
	/// The rotation will be performed using endpoint A as the pivot point for the rotation.
	/// </remarks>
	void Transform (const float_q& fRotationAngle);

	/// <summary>
	/// This method performs a rotation of the 2D segment by rotating an amount defined by a rotation angle
	/// and then storing the resulting segment in the output parameter.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="segmt">[OUT] It receives the resulting rotated 2D segment.</param>
	/// <returns>
	/// The resulting rotated 2D segment.
	/// </returns>
	/// <remarks>
	/// -The rotation will be performed using endpoint A as the pivot point for the rotation.
	/// -The segment is NOT modified, it stays the same.
	/// </remarks>
	void Transform (const float_q& fRotationAngle, QBaseLineSegment2& segmt) const;

	/// <summary>
	/// This method transforms the 2D segment by rotating an amount defined by a rotation angle. 
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <remarks>
	/// The rotation will be performed using the centre point of the segment as the pivot
	/// point for the rotation.
	/// </remarks>
	void TransformFromCenter (const float_q& fRotationAngle);

	/// <summary>
	/// This method performs a rotation of the 2D segment by rotating an amount defined by a rotation angle
	/// and then storing the resulting segment in the output parameter.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="segmt">[OUT] It receives the resulting rotated 2D segment.</param>
	/// <returns>
	/// The resulting rotated 2D segment.
	/// </returns>
	/// <remarks>
	/// -The rotation will be performed using the centre point of the segment as the pivot point for the rotation.
	/// -The segment is NOT modified, it stays the same.
	/// </remarks>
	void TransformFromCenter (const float_q& fRotationAngle, QBaseLineSegment2& segmt) const;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT2D__