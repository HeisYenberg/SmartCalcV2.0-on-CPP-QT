#ifndef CPP3_SMARTCALC_V2_0_MODEL_SMART_CALC_MODEL_H_
#define CPP3_SMARTCALC_V2_0_MODEL_SMART_CALC_MODEL_H_

#include <stack>
#include <string>

namespace s21 {

class Model {
 public:
  enum CalculationStatus {
    kOk,
    kIncorrectExpression,
    kCalculationError,
    kDivisionByZero
  };

  Model() = default;
  ~Model() = default;
  int SmartCalc();
  void SetExpression(std::string expression);
  void SetXValue(double x);
  std::string GetExpression() const;
  double GetResult() const;

 private:
  struct Lexeme {
    char type;
    double value;
  };

  std::string expression_;
  double x_{};
  double result_{};
  std::stack<Lexeme> numbers_;
  std::stack<Lexeme> operations_;

  void CleanStacks();
  int ParseExpression();
  char HandleUnarySign(char type, char last_read);
  int ReadMod(std::size_t *pos);
  std::size_t ReadDigit(const std::string &expression);
  int ReadBinaryOperation(char type, char *last_read, std::size_t *pos);
  int ReadBrackets(char type);
  std::size_t ReadFunction(const std::string &expression);
  int CheckRank(char type);

  int Calculate();
  int BinaryCalculation();
  int FunctionCalculation();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_MODEL_SMART_CALC_MODEL_H_