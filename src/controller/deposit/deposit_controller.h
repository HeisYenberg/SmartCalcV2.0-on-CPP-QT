#ifndef CPP3_SMARTCALC_V2_0_CONTROLLER_DEPOSIT_DEPOSIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_CONTROLLER_DEPOSIT_DEPOSIT_CONTROLLER_H_

#include "../../model/deposit/deposit_model.h"

namespace s21 {

class DepositController {
 public:
  explicit DepositController(DepositModel &model);
  ~DepositController() = default;

  int Calculate(DepositData *data);
  double GetDepositAmount() const;
  double GetInterest() const;
  double GetTaxes() const;

 private:
  DepositModel model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_CONTROLLER_DEPOSIT_DEPOSIT_CONTROLLER_H_