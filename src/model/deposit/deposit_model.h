#ifndef CPP3_SMARTCALC_V2_0_MODEL_DEPOSIT_MODEL_H_
#define CPP3_SMARTCALC_V2_0_MODEL_DEPOSIT_MODEL_H_

#include <map>

namespace s21 {

struct DepositData {
  std::map<int, double> replenishment;
  std::map<int, double> withdrawals;
  double deposit_amount, interest_rate, tax_rate;
  int month_term, capitalisation, capitalisation_periodicity;
};

class DepositModel {
 public:
  DepositModel() = default;
  ~DepositModel() = default;

  int CalculateDeposit(DepositData *data);
  double GetDepositAmount() const;
  double GetInterest() const;
  double GetTaxes() const;

 private:
  double deposit_amount_;
  double interest_;
  double taxes_;

  void DepositCapitalization(DepositData *data, double *capitalized,
                             double monthly_interest, int month);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_MODEL_DEPOSIT_MODEL_H_