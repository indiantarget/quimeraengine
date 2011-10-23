// [TERMS&CONDITIONS]

#ifndef __QORB__
#define __QORB__

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

/// <summary>
/// Class which represents an orb in the space, defined by its centre point and radius.
/// Centre point may be expressed as 2D or 3D point or vector, depending on the parameter of the template,
/// which may be 2D vector, 3D vector or 4D vector.
/// Radius is expressed as a floating point value which is always nonnegative.
/// Remember that an orb is the sum of equidistant points from a given one.
/// </summary>
template <class VectorType>
class QDllExport QOrb : public QBaseOrb<VectorType>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QBaseOrb<VectorType>::P;
    using QBaseOrb<VectorType>::Radius;


    // CONSTANTS
    // ---------------
public:

	/// <summary>
    /// Unit orb placed in the center of coordinates and whose radius equals to 1.
	/// </summary>
    static const QOrb<VectorType> UnitOrb;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QOrb() { }

    /// <summary>
    /// Constructor from a vector which defines the centre point and a floating point value which
    /// defines the radius for the orb.
    /// </summary>
    /// <param name="vP">[IN] Vector to define the center of the orb.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    inline QOrb (const VectorType& vP, const float_q& fRadius) : QBaseOrb<VectorType>(vP, fRadius) { }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assigning operator.
	/// </summary>
    /// <param name="orb">[IN] The orb to be copied from.</param>
    /// <returns>
	/// A reference to the modified orb.
	/// </returns>
    inline QOrb& operator=(const QBaseOrb<VectorType>& orb)
    {
        QBaseOrb<VectorType>::operator=(orb);
        return *this;
    }

	/// <summary>
	/// This method receives a point and determines if the point is contained into the orb.
	/// </summary>
    /// <param name="vP">[IN] The point to be tested.</param>
	/// <returns>
	/// True if the point is inside the orb (or if it belongs to its bounds). Otherwise returns false.
	/// </returns>
    inline bool Contains (const VectorType& vP)
    {
        // The point is inside the orb whenever the minimum squared distance the point and
        // the centre point of the orb is lower or equals the whole square radius of the orb.
        VectorType vDistance(vP - P);
        return QFloat::IsLowerOrEquals(vDistance.GetSquaredLength(), Radius * Radius);
    }

	/// <summary>
	/// This method receives another orb and computes whether this orb intersects the resident one or not.
	/// </summary>
    /// <param name="orb">[IN] The orb to be checked for intersections.</param>
	/// <returns>
	/// True if they intersect to each other (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
    inline bool Intersection (const QBaseOrb<VectorType>& orb)
    {
        // An intersection between the two orbs is considered if the minimum squared distance
		// between their centre points is lower or equals the square sum of their radius.
        VectorType vDistance(orb.P - P);
        float_q    fRadiusSum = Radius + orb.Radius;
        return QFloat::IsLowerOrEquals(vDistance.GetSquaredLength(), fRadiusSum * fRadiusSum);
    }

	/// <summary>
	/// Converts the orb into a string with the following format:
	/// O:P(VectorType::ToString),R(Radius)
	/// </summary>
	/// <returns>
	/// The string with the specified format.
	/// </returns>
	string_q ToString()
	{
		return QE_L("O:P(") + P.ToString() + QE_L("),R(") + QFloat::ToString(Radius) + QE_L(")");
	}

};


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |    CONSTANTS DEFINITIONS	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

template <class VectorType>
const QOrb<VectorType> QOrb<VectorType>::UnitOrb(VectorType::ZeroVector, QFloat::_1);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QORB__