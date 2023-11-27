#ifndef CPP3_SMARTCALC_V2_0_MODEL_CREDIT_MODEL_H_
#define CPP3_SMARTCALC_V2_0_MODEL_CREDIT_MODEL_H_

#include <vector>

namespace s21 {

struct CreditData {
  double credit_amount, interest_rate;
  int term;
  bool differentiated;
};

class CreditModel {
 public:
  CreditModel() = default;
  ~CreditModel() = default;

  void CalculateCredit(CreditData data);
  double GetOverpayment() const;
  double GetTotalPayment() const;
  std::vector<double> GetMonthlyPayments() const;

 private:
  double overpayment_{};
  double total_payment_{};
  std::vector<double> monthly_payments_;

  void CalculateDifferentiated(CreditData data);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_MODEL_CREDIT_MODEL_H_