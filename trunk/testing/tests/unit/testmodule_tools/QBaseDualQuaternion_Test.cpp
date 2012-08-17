
// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QBaseDualQuaternion.h"

using Kinesis::QuimeraEngine::Tools::Math::QBaseDualQuaternion;

QTEST_SUITE_BEGIN( QBaseDualQuaternion_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHasNotChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;

    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

	// Execution
    QBaseDualQuaternion dualQuaternionUT;

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);

    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks if copy constructor sets dual quaternion components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QQuaternion EXPECTED_VALUE_D = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion EXPECTED_VALUE_R = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

    const QBaseDualQuaternion DQUAT_TO_COPY(EXPECTED_VALUE_R, EXPECTED_VALUE_D);

	// Execution
    QBaseDualQuaternion dualQuaternionUT = DQUAT_TO_COPY;

    // Verification
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_VALUE_D);
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_VALUE_R);
}

/// <summary>
/// Checks that every value is set to correct quaternion.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCorrectlySet_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QQuaternion EXPECTED_VALUE_D = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion EXPECTED_VALUE_R = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

	// Execution
    QBaseDualQuaternion dualQuaternionUT(EXPECTED_VALUE_R, EXPECTED_VALUE_D);

    // Verification
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_VALUE_D);
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_VALUE_R);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon),
                                           QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                           QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                           QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));
	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon),
                                           QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon),
                                            QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon));

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon),
                                           QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                           QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                           QQuaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseDualQuaternion LEFT_OPERAND(QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon),
                                           QQuaternion(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon));
    const QBaseDualQuaternion RIGHT_OPERAND(QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                            QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseDualQuaternion
QTEST_SUITE_END()