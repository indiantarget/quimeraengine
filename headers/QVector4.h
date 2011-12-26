// [TERMS&CONDITIONS]

#ifndef __QVECTOR4__
#define __QVECTOR4__

#include "MathDefinitions.h"
#include "QBaseVector3.h"
#include "QBaseVector4.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
class QBaseMatrix3x3;
class QBaseMatrix3x4;
class QBaseMatrix4x3;
class QBaseMatrix4x4;
class QMatrix4x3;
class QMatrix4x4;
template<class MatrixType> class QTranslationMatrix;
class QQuaternion;
class QDualQuaternion;
template<class MatrixType> class QTransformationMatrix;
class QSpaceConversionMatrix;
class QRotationMatrix3x3;
class QScaleMatrix3x3;


/// <summary>
/// This class implements a four components vector functionality. It inherits from QBaseVector4.
/// A vector is a geometric object that has both a magnitude (or length) and direction.
/// It is frequently represented by a line segment with a definite direction, or graphically as an arrow,
/// connecting an initial point A with a terminal point B. The vector is then denoted by AB with an arrow hat.
/// The fourth component may be a 0, if the vector represents a vector in 3D space, or a 1, if vector represents a point.
/// </summary>
class QDllExport QVector4 : public QBaseVector4
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Product by a scalar: all components are multiplied by the floating point value provided.
    /// Shortcut to multiply on the left.
    /// </summary>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <param name="v">[IN] Vector to be multiplied.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    friend QVector4 operator * (const float_q &fValue, const QBaseVector4 &v);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QVector4() { }

    /// <summary>
    /// Constructor from a QBaseVector4.
    /// </summary>
    /// <param name="v">[IN] The vector in which we want resident vector to be based.</param>
    inline explicit QVector4(const QBaseVector4 &v) : QBaseVector4(v) { }

    /// <summary>
    /// Constructor from a QBaseVector3. It's initialized as vector (w = 0).
    /// </summary>
    /// <param name="v">[IN] The 3D vector in which we want resident vector to be based.</param>
    inline explicit QVector4(const QBaseVector3 &v) : QBaseVector4(v.x, v.y, v.z, SQFloat::_0) { }

    /// <summary>
    /// Constructor from four floating point values for each component x, y, z and w.
    /// </summary>
    /// <param name="fValueX">[IN] Floating point value for x component.</param>
    /// <param name="fValueY">[IN] Floating point value for y component.</param>
    /// <param name="fValueZ">[IN] Floating point value for z component.</param>
    /// <param name="fValueW">[IN] Floating point value for w component.</param>
    inline QVector4(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ, const float_q &fValueW) :
        QBaseVector4(fValueX, fValueY, fValueZ, fValueW) { }

    /// <summary>
    /// Constructor from a single floating point value for all components.
    /// </summary>
    /// <param name="fValue">[IN] Floating point value for all components.</param>
    inline explicit QVector4(const float_q &fValue) : QBaseVector4(fValue) { }

    /// <summary>
    /// Constructor from a four component array of floating point values.
    /// </summary>
    /// <param name="pValue">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
    inline explicit QVector4(const float_q *pValue) : QBaseVector4(pValue) { }

    /// <summary>
    /// Constructor from a 4x32 packed floating point value.
    /// </summary>
    /// <param name="vfValue">[IN] 4x32 packed floating point value containing the four components.</param>
    inline explicit QVector4(const vf32_q vfValue) : QBaseVector4 (vfValue) { }

    /// <summary>
    /// Constructor from a translation matrix. The x, y, z components are filled with the
    /// \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ elements of the matrix, and the w component is set to 1.
    /// </summary>
    /// <param name="m">[IN] A 4x4 or 4x3 translation matrix, depending on the constructor template parameter.</param>
    explicit QVector4(const QTranslationMatrix<QMatrix4x3> &m);

    /// <summary>
    /// Constructor from a translation matrix. The x, y, z components are filled with the
    /// \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ elements of the matrix, and the w component is set to 1.
    /// </summary>
    /// <param name="m">[IN] A 4x4 or 4x3 translation matrix, depending on the constructor template parameter.</param>
    explicit QVector4(const QTranslationMatrix<QMatrix4x4> &m);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a point with all components set to 0 (but W, which equals 1).
    /// </summary>
    /// <returns>
    /// A point placed in coordinate origin.
    /// </returns>
    inline static const QVector4& GetZeroPoint()
    {
        static const QVector4 ZEROPOINT(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
        return ZEROPOINT;
    }

    /// <summary>
    /// Gets a vector with all components set to 0.
    /// </summary>
    /// <returns>
    /// A null vector.
    /// </returns>
    inline static const QVector4& GetZeroVector()
    {
        static const QVector4 ZEROVECTOR(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
        return ZEROVECTOR;
    }

    /// <summary>
    /// Gets a vector with all components set to 1.
    /// </summary>
    /// <returns>
    /// A vector of ones.
    /// </returns>
    inline static const QVector4& GetVectorOfOnes()
    {
        static const QVector4 VECTOROFONES(SQFloat::_1,  SQFloat::_1,  SQFloat::_1, SQFloat::_1);
        return VECTOROFONES;
    }

    /// <summary>
    /// Gets a unit vector that points to X positive direction.
    /// </summary>
    /// <returns>
    /// A unit vector that points to X positive direction.
    /// </returns>
    inline static const QVector4& GetUnitVectorX()
    {
        static const QVector4 UNITVECTORX(SQFloat::_1,  SQFloat::_0,  SQFloat::_0, SQFloat::_0);
        return UNITVECTORX;
    }

    /// <summary>
    /// Gets a unit vector that points to Y positive direction.
    /// </summary>
    /// <returns>
    /// A unit vector that points to Y positive direction.
    /// </returns>
    inline static const QVector4& GetUnitVectorY()
    {
        static const QVector4 UNITVECTORY(SQFloat::_0,  SQFloat::_1,  SQFloat::_0, SQFloat::_0);
        return UNITVECTORY;
    }

    /// <summary>
    /// Gets a unit vector that points to Z positive direction.
    /// </summary>
    /// <returns>
    /// A unit vector that points to Z positive direction.
    /// </returns>
    inline static const QVector4& GetUnitVectorZ()
    {
        static const QVector4 UNITVECTORZ(SQFloat::_0,  SQFloat::_0,  SQFloat::_1, SQFloat::_0);
        return UNITVECTORZ;
    }

    /// <summary>
    /// Gets a unit vector that points to X negative direction.
    /// </summary>
    /// <returns>
    /// A unit vector that points to X negative direction.
    /// </returns>
    inline static const QVector4& GetUnitVectorInvX()
    {
        static const QVector4 UNITVECTORINVX(-SQFloat::_1,  SQFloat::_0,  SQFloat::_0, SQFloat::_0);
        return UNITVECTORINVX;
    }

    /// <summary>
    /// Gets a unit vector that points to Y negative direction.
    /// </summary>
    /// <returns>
    /// A unit vector that points to Y negative direction.
    /// </returns>
    inline static const QVector4& GetUnitVectorInvY()
    {
        static const QVector4 UNITVECTORINVY(SQFloat::_0,  -SQFloat::_1,  SQFloat::_0, SQFloat::_0);
        return UNITVECTORINVY;
    }

    /// <summary>
    /// Gets a unit vector that points to Z negative direction.
    /// </summary>
    /// <returns>
    /// A unit vector that points to Z positive direction.
    /// </returns>
    inline static const QVector4& GetUnitVectorInvZ()
    {
        static const QVector4 UNITVECTORINVZ(SQFloat::_0,  SQFloat::_0,  -SQFloat::_1, SQFloat::_0);
        return UNITVECTORINVZ;
    }


    // METHODS
    // ---------------
public:

    // binary operators

    /// <summary>
    /// Vectors addition: it's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Adding vector.</param>
    /// <returns>
    /// A vector that is the result of the addition.
    /// </returns>
    QVector4 operator + (const QBaseVector4 &v) const;

    /// <summary>
    /// Vectors addition: it's performed component by component, keeping constant the w component.
    /// </summary>
    /// <param name="v">[IN] Adding vector.</param>
    /// <returns>
    /// A vector that is the result of the addition.
    /// </returns>
    QVector4 operator + (const QBaseVector3 &v) const;

    /// <summary>
    /// Vectors subtraction: it's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Subtracting vector.</param>
    /// <returns>
    /// A vector that is the result of the subtraction.
    /// </returns>
    QVector4 operator - (const QBaseVector4 &v) const;

    /// <summary>
    /// Vectors subtraction: it's performed component by component, keeping constant the w component.
    /// </summary>
    /// <param name="v">[IN] Subtracting vector.</param>
    /// <returns>
    /// A vector that is the result of the subtraction.
    /// </returns>
    QVector4 operator - (const QBaseVector3 &v) const;

    /// <summary>
    /// Product by a scalar: all components are multiplied by the floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector4 operator * (const float_q &fValue) const;

    /// <summary>
    /// Product by a vector: it's performed component by component. It's not dot product or cross product!
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector4 operator * (const QBaseVector4 &v) const;

    /// <summary>
    /// Product by a [4x4] matrix: it's performed as a matrix product between m[1x4] and n[4x4]
    /// resulting a [1x4] matrix
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector4 operator * (const QBaseMatrix4x4 &m) const;

    /// <summary>
    /// Product by a matrix with 4 rows and 3 columns: it's performed as a matrix product between m[1x4] and n[4x3]
    /// resulting a [1x3] matrix.
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A 3D vector that is the result of the product.
    /// </returns>
    QBaseVector3 operator * (const QBaseMatrix4x3 &m) const;

    /// <summary>
    /// Division by a scalar: all components are divided by the floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    QVector4 operator / (const float_q &fValue) const;

    /// <summary>
    /// Division by a vector: it's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Dividing vector.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    QVector4 operator / (const QBaseVector4 &v) const;

    // assignment operators

    /// <summary>
    /// Adds a vector provided to current vector. It's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Adding vector.</param>
    /// <returns>
    /// A reference to vector result of the addition.
    /// </returns>
    inline QVector4& operator += (const QBaseVector4 &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;

        return *this;
    }

    /// <summary>
    /// Adds a vector provided to current vector. It's performed component by component,
    /// keeping constant the w component.
    /// </summary>
    /// <param name="v">[IN] Adding vector.</param>
    /// <returns>
    /// A reference to vector result of the addition.
    /// </returns>
    inline QVector4& operator += (const QBaseVector3 &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;

        return *this;
    }

    /// <summary>
    /// Subtracts a vector provided to current vector. It's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Subtracting vector.</param>
    /// <returns>
    /// A reference to vector result of the subtraction.
    /// </returns>
    inline QVector4& operator -= (const QBaseVector4 &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;

        return *this;
    }

    /// <summary>
    /// Subtracts a vector provided to current vector. It's performed component by component,
    /// keeping constant the w component.
    /// </summary>
    /// <param name="v">[IN] Subtracting vector.</param>
    /// <returns>
    /// A reference to vector result of the subtraction.
    /// </returns>
    inline QVector4& operator -= (const QBaseVector3 &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;

        return *this;
    }

    /// <summary>
    /// Multiplies current vector by a floating point value provided. It's performed component by component.
    /// </summary>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    inline QVector4& operator *= (const float_q &fValue)
    {
        this->x *= fValue;
        this->y *= fValue;
        this->z *= fValue;
        this->w *= fValue;

        return *this;
    }

    /// <summary>
    /// Multiplies current vector by a vector provided. It's performed component by component.
    /// It's not dot product or cross product!
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    inline QVector4& operator *= (const QBaseVector4 &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;

        return *this;
    }

    /// <summary>
    /// Product by a [4x4] matrix: it's performed as a matrix product between m[1x4] and n[4x4]
    /// resulting a [1x4] matrix
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    QVector4& operator *= (const QBaseMatrix4x4 &m);

    /// <summary>
    /// Divides current vector by a floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A reference to vector result of the division.
    /// </returns>
    inline QVector4& operator /= (const float_q &fValue)
    {
        // Checkout to avoid division by 0
        QE_ASSERT(fValue != SQFloat::_0);

        this->x /= fValue;
        this->y /= fValue;
        this->z /= fValue;
        this->w /= fValue;

        return *this;
    }

    /// <summary>
    /// Divides current vector by a vector provided. It's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Dividing vector.</param>
    /// <returns>
    /// A reference to vector result of the division.
    /// </returns>
    inline QVector4& operator /= (const QBaseVector4 &v)
    {
        // Checkout to avoid division by 0
        QE_ASSERT (v.x != SQFloat::_0 && v.y != SQFloat::_0 && v.z != SQFloat::_0 && v.w != SQFloat::_0);

        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;

        return *this;
    }

    // Unary operators

    /// <summary>
    /// Assign operator. Assigns the provided vector to the resident vector.
    /// </summary>
    /// <param name="v">[IN] The vector to be assigned.</param>
    /// <returns>
    /// A reference to the modified vector.
    /// </returns>
    inline QVector4& operator=(const QBaseVector4 &v)
    {
        QBaseVector4::operator=(v);
        return *this;
    }

    /// <summary>
    /// Opposite vector: multiplies each component by -1.
    /// </summary>
    /// <returns>
    /// A vector that is the opposite of the resident vector.
    /// </returns>
    QVector4 operator- () const;

    //Methods

    /// <summary>
    /// Calculates the length of current vector.
    /// </summary>
    /// <returns>
    /// A floating point value which is the length of the vector.
    /// </returns>
    inline float_q GetLength() const
    {
        return sqrt_q(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
    }

    /// <summary>
    /// Calculates the squared length of resident vector.
    /// </summary>
    /// <returns>
    /// A floating point value which is the squared length of the vector.
    /// </returns>
    inline float_q GetSquaredLength() const
    {
        return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
    }

    /// <summary>
    /// Makes current vector unitary.
    /// </summary>
    inline void Normalize()
    {
        // Gets vector length
        float_q fLength = this->GetLength();

        // Checkout to avoid division by 0
        QE_ASSERT(fLength != SQFloat::_0);

        //Normalize
        this->x /= fLength;
        this->y /= fLength;
        this->z /= fLength;
        this->w /= fLength;
    }

    /// <summary>
    /// Calculates a normalized vector from the resident one and stores it in an output vector provided.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where we want to store the normalized vector.</param>
    inline void Normalize(QBaseVector4 &vOut) const
    {
        vOut = * this;
        vOut.As<QVector4>().Normalize();
    }

    /// <summary>
    /// Convert current vector in its opposite vector.
    /// </summary>
    inline void Reverse()
    {
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
        this->w = -this->w;
    }

    /// <summary>
    /// Calculates the opposite to resident vector and stores it in an output vector provided.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where we want store the opposite vector.</param>
    inline void Reverse(QBaseVector4 &vOut) const
    {
        vOut = *this;
        vOut.As<QVector4>().Reverse();
    }

    /// <summary>
    /// Resets all components of current vector to 1.
    /// </summary>
    inline void ResetToOne()
    {
        this->x = SQFloat::_1;
        this->y = SQFloat::_1;
        this->z = SQFloat::_1;
        this->w = SQFloat::_1;
    }

    /// <summary>
    /// Resets all components of current vector to 0, except fourth component which is set to 1.
    /// </summary>
    inline void ResetToZeroPoint()
    {
        this->x = SQFloat::_0;
        this->y = SQFloat::_0;
        this->z = SQFloat::_0;
        this->w = SQFloat::_1;
    }

    /// <summary>
    /// Resets all components of current vector to 0.
    /// </summary>
    inline void ResetToZeroDirection()
    {
        this->x = SQFloat::_0;
        this->y = SQFloat::_0;
        this->z = SQFloat::_0;
        this->w = SQFloat::_0;
    }

    /// <summary>
    /// Check if all components of current vector are 0.
    /// </summary>
    /// <returns>
    /// True if all components are 0. False otherwise.
    /// </returns>
    inline bool IsZero() const
    {
        return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y) &&
               SQFloat::IsZero(this->z) && SQFloat::IsZero(this->w);
    }

    /// <summary>
    /// Check if all components of current vector are 1.
    /// </summary>
    /// <returns>
    /// True if all components are 1. False otherwise.
    /// </returns>
    inline bool IsVectorOfOnes() const
    {
        return SQFloat::AreEquals(this->x, SQFloat::_1) && SQFloat::AreEquals(this->y, SQFloat::_1) &&
               SQFloat::AreEquals(this->z, SQFloat::_1) && SQFloat::AreEquals(this->w, SQFloat::_1);
    }

    /// <summary>
    /// Calculates Dot Product by a vector provided.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A floating point value which is the result of Dot Product.
    /// </returns>
    inline float_q DotProduct(const QBaseVector4 &v) const
    {
        return(this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w);
    }

    /// <summary>
    /// Calculates the angle between resident vector and the provided vector, via dot product.
    /// Both vectors are treated as 3D vectors, ignoring W component.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A floating point value which is the smaller angle between vectors (less or equal to 180�).
    /// </returns>
    inline float_q DotProductAngle(const QBaseVector4 &v) const
    {
        float_q fLength = sqrt_q( (this->x*this->x + this->y*this->y + this->z*this->z) * (v.x*v.x + v.y*v.y + v.z*v.z) );

        // Checkout to avoid division by zero.
        QE_ASSERT(fLength != SQFloat::_0);

        float_q fDot = (this->x*v.x + this->y*v.y + this->z*v.z)/fLength;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1);

        float_q fAngle = acos_q(fDot);

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            SQAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

        return fAngle;
    }

    /// <summary>
    /// Calculates cross product by a vector provided (left handed rules), and stores it in current vector.
    /// Due to cross product between two 4D vectors isn't defined (is a ternary operation in 4D space),
    /// we treat it as a cross product between two 3D vectors, maintaining the W component of the resident vector.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    void CrossProduct(const QBaseVector4 &v);

    /// <summary>
    /// Calculates cross product by a vector provided (left handed rules), and stores it in a vector provided.
    /// Due to cross product between two 4D vectors isn't defined (is a ternary operation in 4D space),
    /// we treat it as a cross product between two 3D vectors, maintaining the W component of the resident vector.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <param name="vOut">[OUT] Vector where resultant product is stored.</param>
    /// <remarks>
    /// Cross Product is noncommutative, please note the resident vector is the first operator, set to the left
    /// of the Cross Product operator sign, and the input vector is the second operator (set to the right).
    /// </remarks>
    inline void CrossProduct(const QBaseVector4 &v, QBaseVector4 &vOut) const
    {
        vOut = *this;
        vOut.As<QVector4>().CrossProduct(v);
    }

    /// <summary>
    /// Makes a Linear Interpolation between current vector and other vector provided. It stores result in current vector.
    /// </summary>
    /// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the current vector (per one).</param>
    /// <param name="v">[IN] Vector with which to interpolate.</param>
    inline void Lerp(const float_q &fFactor, const QBaseVector4 &v)
    {
        float_q fDiff = SQFloat::_1 - fFactor;

        this->x = this->x * fFactor + v.x * fDiff;
        this->y = this->y * fFactor + v.y * fDiff;
        this->z = this->z * fFactor + v.z * fDiff;
        this->w = this->w * fFactor + v.w * fDiff;
    }

    /// <summary>
    /// Makes a Linear Interpolation between current vector and other vector provided. It stores result in current vector.
    /// </summary>
    /// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the current vector (per one).</param>
    /// <param name="v">[IN] Vector with which to interpolate.</param>
    /// <param name="vOut">[OUT] Vector where to store interpolation.</param>
    inline void Lerp(const float_q &fFactor, const QBaseVector4 &v, QBaseVector4 &vOut) const
    {
        vOut = *this;
        vOut.As<QVector4>().Lerp(fFactor, v);
    }

    /// <summary>
    /// Calculates the distance between two vector heads (or two points). It computes the difference of two vectors and returns its length.
    /// </summary>
    /// <param name="v">[IN] Vector we want to calculate the distance from current vector.</param>
    /// <returns>
    /// A positive floating point value containing the distance between both vectors.
    /// </returns>
    inline float_q Distance(const QBaseVector4 &v) const
    {
        return sqrt_q( (this->x-v.x)*(this->x-v.x) + (this->y-v.y)*(this->y-v.y) +
                     (this->z-v.z)*(this->z-v.z) + (this->w-v.w)*(this->w-v.w) );
    }

    /// <summary>
    /// Applies a rotation quaternion to resident vector. The rotation applied is following left-handed rules.
    /// It's made by multiplying resident vector by the quaternion provided, as follows:
    /// \f$ v' = Q \cdot v \cdot Q^*\f$,
    /// where v is the resident vector, Q the quaternion and \f$ Q^*\f$ the conjugate of the quaternion.
    /// The w component of original vector is not transformed.
    /// [TODO] jwladi: probably it will be necessary verify if rotation follows left-handed rules or not.
    /// </summary>
    /// <param name="qR">[IN] The rotation quaternion.</param>
    void Transform(const QQuaternion &qR);

    /// <summary>
    /// Applies a rotation quaternion to resident vector, storing results in an out vector provided.
    /// The rotation applied is following left-handed rules.
    /// It's made by multiplying resident vector by the quaternion provided, as follows:
    /// \f$ v' = Q \cdot v \cdot Q^*\f$,
    /// where v is the resident vector, Q the quaternion and \f$ Q^*\f$ the conjugate of the quaternion.
    /// The w component of original vector is not transformed.
    /// [TODO] jwladi: probably it will be necessary verify if rotation follows left-handed rules or not.
    /// </summary>
    /// <param name="qR">[IN] The rotation quaternion.</param>
    /// <param name="vOut">[OUT] The vector where the result of rotation is stored.</param>
    inline void Transform(const QQuaternion &qR, QBaseVector4 &vOut) const
    {
        vOut = *this;
        vOut.As<QVector4>().Transform(qR);
    }

    /// <summary>
    /// Applies a rigid transformation dual quaternion to resident vector.
    /// It's made by multiplying resident vector by the dual quaternion provided, as follows:
    /// \f$ v' = \hat{Q} \cdot v \cdot \hat{Q}^*\f$,
    /// where v is the resident vector, \f$\hat{Q}\f$ the dual quaternion and \f$\hat{Q}^*\f$ the double conjugate of the dual quaternion.
    /// The w component of original vector is not transformed.
    /// </summary>
    /// <param name="dqTransf">[IN] The dual quaternion which wears the transformation.</param>
    void Transform(const QDualQuaternion &dqTransf);

    /// <summary>
    /// Applies a rigid transformation dual quaternion to resident vector, storing results in an out vector provided.
    /// It's made by multiplying resident vector by the dual quaternion provided, as follows:
    /// \f$ v' = \hat{Q} \cdot v \cdot \hat{Q}^*\f$,
    /// where v is the resident vector, \f$\hat{Q}\f$ the dual quaternion and \f$\hat{Q}^*\f$ the double conjugate of the dual quaternion.
    /// The w component of original vector is not transformed.
    /// </summary>
    /// <param name="dqTransf">[IN] The dual quaternion which wears the transformation..</param>
    /// <param name="vOut">[OUT] The vector where the result of rotation is stored.</param>
    inline void Transform(const QDualQuaternion &dqTransf, QBaseVector4 &vOut) const
    {
        vOut = *this;
        vOut.As<QVector4>().Transform(dqTransf);
    }

    /// <summary>
    /// Divides all componentes by the w component to ensure the vector is in homogeneus coordinates.
    /// If w component is 0 it does nothing.
    /// </summary>
    inline void Homogenize()
    {
        if (SQFloat::IsNotZero(this->w))
        {
            const float_q &fInvW = SQFloat::_1/this->w;

            this->x *= fInvW;
            this->y *= fInvW;
            this->z *= fInvW;
        }
    }

    /// <summary>
    /// Divides all componentes by the w component to ensure the vector is in homogeneus coordinates.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where to store the homogenized vector.</param>
    inline void Homogenize(QBaseVector4 &vOut) const
    {
        vOut = *this;
        vOut.As<QVector4>().Homogenize();
    }

    /// <summary>
    /// Applies a rotation to resident vector, multiplying the vector by a rotation matrix
    /// to transform it. The w component remains unchanged.
    /// </summary>
    /// <param name="mRot">[IN] The rotation matrix.</param>
	void Transform(const QRotationMatrix3x3 &mRot);

    /// <summary>
    /// Applies a rotation to resident vector, multiplying the vector by a rotation matrix
    /// to transform it. The w component remains unchanged. The rotated vector is stored into the provided one.
    /// </summary>
    /// <param name="mRot">[IN] The rotation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of rotation.</param>
	void Transform(const QRotationMatrix3x3 &mRot, QBaseVector4 &vOut) const;

    /// <summary>
    /// Applies a scale transformation to resident vector, multiplying the vector by a scale matrix
    /// to transform it.
    /// </summary>
    /// <param name="mScale">[IN] The scale matrix.</param>
	void Transform(const QScaleMatrix3x3 &mScale);

    /// <summary>
    /// Applies a scale transformation to resident vector, multiplying the vector by a scale matrix
    /// to transform it. The scaled vector is stored into the provided one.
    /// </summary>
    /// <param name="mScale">[IN] The scale matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of scale.</param>
	void Transform(const QScaleMatrix3x3 &mScale, QBaseVector4 &vOut) const;

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	void Transform(const QTranslationMatrix<QMatrix4x3> &mDisp);

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	void Transform(const QTranslationMatrix<QMatrix4x4> &mDisp);

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it.The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The translated vector is stored into the provided one.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of translation.</param>
	void Transform(const QTranslationMatrix<QMatrix4x3> &mDisp, QBaseVector4 &vOut) const;

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it.The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The translated vector is stored into the provided one.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of translation.</param>
	void Transform(const QTranslationMatrix<QMatrix4x4> &mDisp, QBaseVector4 &vOut) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	void Transform(const QTransformationMatrix<QMatrix4x3> &mTransf);

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	void Transform(const QTransformationMatrix<QMatrix4x4> &mTransf);

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The transformed vector is stored into the provided one.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QTransformationMatrix<QMatrix4x3> &mTransf, QBaseVector4 &vOut) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The transformed vector is stored into the provided one.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QTransformationMatrix<QMatrix4x4> &mTransf, QBaseVector4 &vOut) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a space conversion matrix
	/// to refer it to another coordinate system.
    /// The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The space conversion matrix.</param>
	void Transform(const QSpaceConversionMatrix &mTransf);

	/// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a space conversion matrix
	/// to refer it to another coordinate system.
    /// The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The transformed vector is stored into the provided one.
    /// </summary>
    /// <param name="mTransf">[IN] The space conversion matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QSpaceConversionMatrix &mTransf, QBaseVector4 &vOut) const;

    /// <summary>
    /// Converts vector into a string with the following format:
    /// "V4(x, y, z, w)".
    /// </summary>
    /// <returns>The string with the format specified.</returns>
    inline string_q ToString() const
    {
        return QE_L("V4(") + SQFloat::ToString(this->x) +
               QE_L(", ")  + SQFloat::ToString(this->y) +
               QE_L(", ")  + SQFloat::ToString(this->z) +
               QE_L(", ")  + SQFloat::ToString(this->w) + QE_L(")");
    }

protected:

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix. It must be a 4x3 or a 4x4 translation matrix.</param>
	template <class MatrixType>
	void TransformImp(const QTranslationMatrix<MatrixType> &mDisp);

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix. It must be a 4x3 or a 4x4 matrix.</param>
    template <class MatrixType>
	void TransformImp(const QTransformationMatrix<MatrixType> &mTransf);

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR4__
