// [TERMS&CONDITIONS]

#ifndef __QBASERAY__
#define __QBASERAY__

#include "SQFloat.h"
#include "QConvertible.h"

using Kinesis::QuimeraEngine::Core::QConvertible;
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
/// Implements the funcionality of a ray, which is a vector located at a point.
/// </summary>
template<class VectorTypeOrigin, class VectorTypeDirection>
class QDllExport QBaseRay : public QConvertible
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QBaseRay() : Origin(SQFloat::_0), Direction(SQFloat::_0)
    {
    }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="ray">[IN] The ray from which we want to create a copy in the resident ray.</param>
	inline QBaseRay(const QBaseRay &ray) : Origin(ray.Origin), Direction(ray.Direction)
	{
	}

	/// <summary>
	/// Constructor from a point and a vector.
	/// </summary>
	/// <param name="vOrigin">[IN] Point where the vector is located.</param>
	/// <param name="vDirection">[IN] A vector which defines the direction of the ray.</param>
	/// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
	inline QBaseRay (const VectorTypeOrigin &vOrigin, const VectorTypeDirection &vDirection) :
                        Origin(vOrigin), Direction(vDirection)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two rays.
    /// </summary>
    /// <param name="ray">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are the same, false otherwise.
    /// </returns>
    /// <remarks>
    /// Both rays must be normalized to obtain a correct result.
    /// </remarks>
    inline bool operator==(const QBaseRay<VectorTypeOrigin, VectorTypeDirection> &ray) const
    {
        return ( this->Origin == ray.Origin && this->Direction == ray.Direction );
    }

    /// <summary>
    /// Inequality operator. Compares two rays.
    /// </summary>
    /// <param name="ray">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are not the same, false otherwise.
    /// </returns>
    /// <remarks>
    /// Both rays must be normalized to obtain a correct result.
    /// </remarks>
    inline bool operator!=(const QBaseRay<VectorTypeOrigin, VectorTypeDirection> &ray) const
    {
        return !(*this == ray);
    }

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Point where the vector is located.
	/// </summary>
	VectorTypeOrigin Origin;

	/// <summary>
	/// Vector which defines the direction of the ray.
	/// </summary>
	VectorTypeDirection Direction;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASERAY__
