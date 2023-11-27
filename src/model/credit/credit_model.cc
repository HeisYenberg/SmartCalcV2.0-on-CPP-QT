#include "credit_model.h"

#include <cmath>

namespace s21 {

double CreditModel::GetOverpayment() const { return overpayment_; }

double CreditModel::GetTotalPayment() const { return total_payment_; }

std::vector<double> CreditModel::GetMonthlyPayments() const {
  return monthly_payments_;
}

void CreditModel::CalculateCredit(CreditData data) {
  if (!data.differentiated) {
    double coefficient =
        (data.interest_rate * pow(1 + data.interest_rate, data.term)) /
        (pow(1 + data.interest_rate, data.term) - 1);
    monthly_payments_.push_back(data.credit_amount * coefficient);
    total_payment_ = monthly_payments_.back() * data.term;
    overpayment_ = total_payment_ - data.credit_amount;
  } else {
    CalculateDifferentiated(data);
  }
}

void CreditModel::CalculateDifferentiated(CreditData data) {
  total_payment_ = 0;
  double monthly_payment = data.credit_amount / data.term;
  double payment_left = data.credit_amount;
  for (int i = 0; i < data.term; ++i) {
    monthly_payments_.push_back(monthly_payment +
                                payment_left * data.interest_rate);
    payment_left -= monthly_payment;
    total_payment_ += monthly_payments_.back();
  }
  overpayment_ = total_payment_ - data.credit_amount;
}

}  // namespace s21