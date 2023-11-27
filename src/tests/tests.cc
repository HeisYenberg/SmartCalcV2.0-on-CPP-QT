#include "tests.h"

#include <gtest/gtest.h>

#include "../controller/credit/credit_controller.h"
#include "../controller/deposit/deposit_controller.h"
#include "../controller/smart_calc/controller.h"

TEST(TestSmartCalc, TestBinaryCalculations) {
  double result = 0;
  s21::Controller controller;
  for (int i = 0; i < 10; ++i) {
    controller.SetExpression(kBinaryCalculations[i]);
    controller.SetXValue(0);
    int status = controller.Calculate(&result);
    EXPECT_EQ(status, s21::Model::kOk);
    EXPECT_NEAR(result, kBinaryCalculationsResults[i], kPrecision);
  }
}

TEST(TestSmartCalc, TestFunctionsCalculations) {
  double result = 0;
  s21::Controller controller;
  for (int i = 0; i < 10; ++i) {
    controller.SetExpression(kFunctionCalculations[i]);
    controller.SetXValue(0);
    int status = controller.Calculate(&result);
    EXPECT_EQ(status, s21::Model::kOk);
    EXPECT_NEAR(result, kFunctionCalculationsResults[i], kPrecision);
  }
}

TEST(TestSmartCalc, TestIncorrectExpressions) {
  double result = 0;
  s21::Controller controller;
  for (int i = 0; i < 10; ++i) {
    controller.SetExpression(kIncorrectExpressions[i]);
    controller.SetXValue(0);
    int status = controller.Calculate(&result);
    EXPECT_EQ(status, s21::Model::kIncorrectExpression);
  }
}

TEST(TestSmartCalc, TestCalculationErrors) {
  double result = 0;
  s21::Controller controller;
  for (int i = 0; i < 10; ++i) {
    controller.SetExpression(kCalculationErrors[i]);
    controller.SetXValue(0);
    int status = controller.Calculate(&result);
    EXPECT_EQ(status, s21::Model::kCalculationError);
  }
}

TEST(TestSmartCalc, TestDivisionByZero) {
  double result = 0;
  s21::Controller controller;
  controller.SetExpression("12/0");
  controller.SetXValue(0);
  int status = controller.Calculate(&result);
  EXPECT_EQ(status, s21::Model::kDivisionByZero);
  controller.SetExpression("12%0");
  status = controller.Calculate(&result);
  EXPECT_EQ(status, s21::Model::kDivisionByZero);
}

TEST(TestSmartCalc, TestGetExpression) {
  s21::Controller controller;
  for (int i = 0; i < 10; ++i) {
    controller.SetExpression(kBinaryCalculations[i]);
    EXPECT_EQ(controller.GetExpression(), kBinaryCalculations[i]);
  }
}

TEST(TestCreditCalc, TestCreditAnnuity) {
  s21::CreditData data = {1000, 10.0 / 12 / 100, 3, 0};
  s21::CreditController controller;
  controller.Calculate(data);
  EXPECT_NEAR(controller.GetMonthlyPayments().back(), 338.904257, kPrecision);
  EXPECT_NEAR(controller.GetOverpayment(), 16.712771, kPrecision);
  EXPECT_NEAR(controller.GetTotalPayment(), 1016.712771, kPrecision);
}

TEST(TestCreditCalc, TestCreditDifferentiated) {
  s21::CreditData data = {1000, 10.0 / 12 / 100, 3, 1};
  s21::CreditController controller;
  controller.Calculate(data);
  std::vector<double> payments = {341.666667, 338.888889, 336.111111};
  std::vector<double> my_payments = controller.GetMonthlyPayments();
  for (int i = 0; i < 3; ++i) {
    EXPECT_NEAR(payments[i], my_payments[i], kPrecision);
  }
  EXPECT_NEAR(controller.GetOverpayment(), 16.666667, kPrecision);
  EXPECT_NEAR(controller.GetTotalPayment(), 1016.666667, kPrecision);
}

TEST(TestDepositCalc, TestDepositNotCapitalized) {
  s21::DepositData data = {{}, {}, 75000, 5, 13, 24, 0, 0};
  s21::DepositController controller;
  controller.Calculate(&data);
  EXPECT_NEAR(controller.GetDepositAmount(), 81525.00, kPrecision);
  EXPECT_NEAR(controller.GetInterest(), 7500.00, kPrecision);
  EXPECT_NEAR(controller.GetTaxes(), 975.00, kPrecision);
}

TEST(TestDepositCalc, TestDepositCapitalizedMontly) {
  s21::DepositData data = {{}, {}, 75000, 5, 13, 24, 1, 0};
  s21::DepositController controller;
  controller.Calculate(&data);
  EXPECT_NEAR(controller.GetDepositAmount(), 81847.422145, kPrecision);
  EXPECT_NEAR(controller.GetInterest(), 7870.600167, kPrecision);
  EXPECT_NEAR(controller.GetTaxes(), 1023.178022, kPrecision);
}

TEST(TestDepositCalc, TestDepositCapitalizedQuaterly) {
  s21::DepositData data = {{}, {}, 75000, 5, 13, 24, 1, 1};
  s21::DepositController controller;
  controller.Calculate(&data);
  EXPECT_NEAR(controller.GetDepositAmount(), 81806.683932, kPrecision);
  EXPECT_NEAR(controller.GetInterest(), 7823.774634, kPrecision);
  EXPECT_NEAR(controller.GetTaxes(), 1017.090702, kPrecision);
}

TEST(TestDepositCalc, TestDepositCapitalizedHalfYearly) {
  s21::DepositData data = {{}, {}, 75000, 5, 13, 24, 1, 2};
  s21::DepositController controller;
  controller.Calculate(&data);
  EXPECT_NEAR(controller.GetDepositAmount(), 81779.890689, kPrecision);
  EXPECT_NEAR(controller.GetInterest(), 7792.977804, kPrecision);
  EXPECT_NEAR(controller.GetTaxes(), 1013.087114, kPrecision);
}

TEST(TestDepositCalc, TestDepositCapitalizedYearly) {
  s21::DepositData data = {{}, {}, 75000, 5, 13, 24, 1, 3};
  s21::DepositController controller;
  controller.Calculate(&data);
  EXPECT_NEAR(controller.GetDepositAmount(), 81701.208984, kPrecision);
  EXPECT_NEAR(controller.GetInterest(), 7702.539062, kPrecision);
  EXPECT_NEAR(controller.GetTaxes(), 1001.330078, kPrecision);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}