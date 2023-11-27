#ifndef CPP3_SMARTCALC_V2_0_CONTROLLER_SMART_CALC_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_CONTROLLER_SMART_CALC_CONTROLLER_H_

#include "../../model/smart_calc/model.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Model *model);
  ~Controller() = default;

  void SetExpression(std::string &expression);
  std::string GetExpression() const;
  double GetResult() const;
  void SetXValue(double x);
  int Calculate();

 private:
  Model *model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_CONTROLLER_SMART_CALC_CONTROLLER_H_