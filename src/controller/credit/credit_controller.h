#ifndef CPP3_SMARTCALC_V2_0_CONTROLLER_CREDIT_CREDIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_CONTROLLER_CREDIT_CREDIT_CONTROLLER_H_

#include "../../model/credit/credit_model.h"

namespace s21 {

class CreditController {
 public:
  explicit CreditController(CreditModel &model);
  ~CreditController() = default;

  void Calculate(CreditData data);
  double GetOverpayment() const;
  double GetTotalPayment() const;
  std::vector<double> GetMonthlyPayments() const;

 private:
  CreditModel model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_CONTROLLER_CREDIT_CREDIT_CONTROLLER_H_