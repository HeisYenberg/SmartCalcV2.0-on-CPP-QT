#include "deposit_model.h"

#include "../smart_calc/model.h"

namespace s21 {

double DepositModel::GetDepositAmount() const { return deposit_amount_; }

double DepositModel::GetInterest() const { return interest_; }

double DepositModel::GetTaxes() const { return taxes_; }

int DepositModel::CalculateDeposit(DepositData *data) {
  int status = Model::kOk;
  double capitalized = 0;
  interest_ = 0;
  for (int i = 0; i < data->month_term && !status; ++i) {
    data->deposit_amount += data->replenishment[i];
    if (data->deposit_amount > data->withdrawals[i]) {
      data->deposit_amount -= data->withdrawals[i];
    } else {
      status = Model::kIncorrectExpression;
    }
    double monthly_interest =
        data->deposit_amount * data->interest_rate / 12 / 100;
    if (data->capitalisation) {
      DepositCapitalization(data, &capitalized, monthly_interest, i);
    }
    interest_ += monthly_interest;
  }
  if (!data->capitalisation) {
    data->deposit_amount += interest_;
  }
  data->deposit_amount += capitalized;
  taxes_ = interest_ * data->tax_rate / 100;
  data->deposit_amount -= taxes_;
  deposit_amount_ = data->deposit_amount;
  return status;
}

void DepositModel::DepositCapitalization(DepositData *data, double *capitalized,
                                         double monthly_interest, int month) {
  *capitalized += monthly_interest;
  if (!data->capitalisation_periodicity) {
    data->deposit_amount += *capitalized;
    *capitalized = 0;
  } else if (data->capitalisation_periodicity == 1) {
    if (!(month % 4)) {
      data->deposit_amount += *capitalized;
      *capitalized = 0;
    }
  } else if (data->capitalisation_periodicity == 2) {
    if (!(month % 6)) {
      data->deposit_amount += *capitalized;
      *capitalized = 0;
    }
  } else {
    if (!(month % 12)) {
      data->deposit_amount += *capitalized;
      *capitalized = 0;
    }
  }
}

}  // namespace s21