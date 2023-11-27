#include "deposit_controller.h"

namespace s21 {

DepositController::DepositController(DepositModel &model) : model_(model) {}

int DepositController::Calculate(DepositData *data) {
  return model_.CalculateDeposit(data);
}

double DepositController::GetDepositAmount() const {
  return model_.GetDepositAmount();
}

double DepositController::GetInterest() const { return model_.GetInterest(); }

double DepositController::GetTaxes() const { return model_.GetTaxes(); }

}  // namespace s21