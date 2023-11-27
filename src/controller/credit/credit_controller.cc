#include "credit_controller.h"

namespace s21 {

CreditController::CreditController(CreditModel &model) : model_(model) {}

void CreditController::Calculate(CreditData data) {
  model_.CalculateCredit(data);
}

double CreditController::GetOverpayment() const {
  return model_.GetOverpayment();
}

double CreditController::GetTotalPayment() const {
  return model_.GetTotalPayment();
}

std::vector<double> CreditController::GetMonthlyPayments() const {
  return model_.GetMonthlyPayments();
}

}  // namespace s21