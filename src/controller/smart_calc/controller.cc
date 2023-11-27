#include "controller.h"

namespace s21 {

Controller::Controller(Model *model) : model_(model) {}

void Controller::SetExpression(std::string &expression) {
  model_->SetExpression(expression);
}

std::string Controller::GetExpression() const {
  return model_->GetExpression();
}

double Controller::GetResult() const { return model_->GetResult(); }

void Controller::SetXValue(double x) { model_->SetXValue(x); }

int Controller::Calculate() { return model_->SmartCalc(); }

}  // namespace s21