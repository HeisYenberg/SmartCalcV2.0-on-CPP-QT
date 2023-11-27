#include "model.h"

#include <cmath>
#include <cstring>
#include <locale>

namespace s21 {

int Model::SmartCalc() {
  setlocale(LC_ALL, "C");
  std::string temp(expression_);
  int status = ParseExpression();
  while (status == kOk && !operations_.empty()) {
    status = Calculate();
  }
  if (status == kOk && !numbers_.empty()) {
    result_ = numbers_.top().value;
    numbers_.pop();
    if (!numbers_.empty()) {
      status = kIncorrectExpression;
    }
  }
  expression_ = std::move(temp);
  return status;
}

void Model::SetExpression(std::string &expression) {
  CleanStacks();
  expression_ = std::move(expression);
}

std::string Model::GetExpression() const { return expression_; }

void Model::SetXValue(double x) {
  CleanStacks();
  x_ = x;
}

double Model::GetResult() const { return result_; }

void Model::CleanStacks() {
  while (!numbers_.empty()) {
    numbers_.pop();
  }
  while (!operations_.empty()) {
    operations_.pop();
  }
}

int Model::ParseExpression() {
  int status = kOk;
  char last_read = 0;
  std::size_t expression_length = expression_.size();
  for (std::size_t i = 0; i < expression_length && status == kOk; ++i) {
    if (isspace(expression_[i])) {
      continue;
    } else if (strchr("acstl", expression_[i])) {
      last_read = expression_[i];
      std::size_t read = ReadFunction(expression_.substr(i));
      if (read != 0) {
        i += read;
      } else {
        status = kIncorrectExpression;
      }
    } else if (isdigit(expression_[i]) || expression_[i] == 'x') {
      if (isdigit(last_read) || last_read == 'x') {
        status = kIncorrectExpression;
      }
      i += ReadDigit(expression_.substr(i));
      last_read = expression_[i];
    } else if (expression_[i] == 'm') {
      status = ReadMod(&i);
    } else if (strchr("+-*%/^", expression_[i])) {
      char type = HandleUnarySign(expression_[i], last_read);
      status = ReadBinaryOperation(type, &last_read, &i);
    } else if (expression_[i] == '(' || expression_[i] == ')') {
      last_read = expression_[i];
      status = ReadBrackets(expression_[i]);
    } else {
      status = kIncorrectExpression;
    }
  }
  return status;
}

char Model::HandleUnarySign(char type, char last_read) {
  if (!isdigit(last_read) && last_read != 'x' && last_read != ')' &&
      (type == '-' || type == '+')) {
    if (type == '+')
      type = '#';
    else
      type = '~';
  }
  return type;
}

int Model::ReadMod(std::size_t *pos) {
  int status = kIncorrectExpression;
  if (!expression_.compare(*pos, 3, "mod")) {
    expression_[*pos + 2] = '%';
    ++(*pos);
    status = kOk;
  }
  return status;
}

std::size_t Model::ReadDigit(const std::string &expression) {
  std::size_t read = 0;
  double value = x_;
  if (expression[0] != 'x') {
    value = std::stod(expression, &read);
    --read;
  }
  numbers_.push({0, value});
  return read;
}

int Model::ReadBinaryOperation(char type, char *last_read, std::size_t *pos) {
  int status = kOk;
  int previous_rank =
      (operations_.empty()) ? 0 : CheckRank(operations_.top().type);
  if (previous_rank && CheckRank(type) != 3 &&
      CheckRank(type) <= previous_rank) {
    status = Calculate();
    --(*pos);
  } else {
    *last_read = type;
    operations_.push({type, 0});
  }
  return status;
}

int Model::ReadBrackets(char type) {
  int status = kOk;
  if (type == '(') {
    operations_.push({type, 0});
  } else {
    if (operations_.empty()) return kIncorrectExpression;
    while (operations_.top().type != '(' && !status) {
      status = Calculate();
      if (operations_.empty()) {
        status = kIncorrectExpression;
      }
    }
    if (!operations_.empty()) {
      operations_.pop();
    }
  }
  return status;
}

std::size_t Model::ReadFunction(const std::string &expression) {
  std::size_t read = 0;
  char type = 0;
  if (!expression.compare(0, 5, "asin(")) {
    read += 3;
    type = 'S';
  } else if (!expression.compare(0, 5, "acos(")) {
    read += 3;
    type = 'C';
  } else if (!expression.compare(0, 5, "atan(")) {
    read += 3;
    type = 'T';
  } else if (!expression.compare(0, 4, "sin(")) {
    read += 2;
    type = 's';
  } else if (!expression.compare(0, 4, "cos(")) {
    read += 2;
    type = 'c';
  } else if (!expression.compare(0, 4, "tan(")) {
    read += 2;
    type = 't';
  } else if (!expression.compare(0, 4, "log(")) {
    read += 2;
    type = 'L';
  } else if (!expression.compare(0, 3, "ln(")) {
    read += 1;
    type = 'l';
  } else if (!expression.compare(0, 5, "sqrt(")) {
    read += 3;
    type = 'q';
  }
  operations_.push({type, 0});
  return read;
}

int Model::CheckRank(char type) {
  int rang = 0;
  if (type == '-' || type == '+')
    rang = 1;
  else if (type == '/' || type == '*' || type == '%')
    rang = 2;
  else if (type == '^')
    rang = 3;
  else if (type == '~' || type == '#')
    rang = 4;
  else if (type == 's' || type == 'c' || type == 't' || type == 'S' ||
           type == 'C' || type == 'T' || type == 'L' || type == 'l' ||
           type == 'q') {
    rang = 5;
  }
  return rang;
}

int Model::Calculate() {
  int status = kIncorrectExpression;
  char type = operations_.top().type;
  if (strchr("+-*/%^", type)) {
    status = BinaryCalculation();
  } else if (strchr("~#sctSCTLlq", type)) {
    status = FunctionCalculation();
  }
  return status;
}

int Model::BinaryCalculation() {
  int status = kOk;
  char type = operations_.top().type;
  double a = numbers_.top().value;
  numbers_.pop();
  if (numbers_.empty()) {
    status = kIncorrectExpression;
  } else {
    double b = numbers_.top().value;
    numbers_.pop();
    double c = 0;
    if (type == '-') {
      c = b - a;
    } else if (type == '+') {
      c = b + a;
    } else if (type == '*') {
      c = b * a;
    } else if (type == '/') {
      if (a)
        c = b / a;
      else
        status = kDivisionByZero;
    } else if (type == '%') {
      if (a)
        c = fmod(b, a);
      else
        status = kDivisionByZero;
    } else if (type == '^') {
      c = pow(b, a);
    }
    if (std::isnan(c))
      status = kCalculationError;
    else {
      numbers_.push({0, c});
      operations_.pop();
    }
  }
  return status;
}

int Model::FunctionCalculation() {
  int status = kOk;
  char type = operations_.top().type;
  if (numbers_.empty()) {
    status = kIncorrectExpression;
  } else {
    double a = numbers_.top().value;
    numbers_.pop();
    operations_.pop();
    double c = 0;
    if (type == '#') {
      c = a;
    } else if (type == '~') {
      c = -a;
    } else if (type == 's') {
      c = sin(a);
    } else if (type == 'c') {
      c = cos(a);
    } else if (type == 't') {
      c = tan(a);
    } else if (type == 'S') {
      c = asin(a);
    } else if (type == 'C') {
      c = acos(a);
    } else if (type == 'T') {
      c = atan(a);
    } else if (type == 'L') {
      c = log10(a);
    } else if (type == 'l') {
      c = log(a);
    } else if (type == 'q') {
      c = sqrt(a);
    }
    if (std::isnan(c))
      status = kCalculationError;
    else {
      numbers_.push({0, c});
    }
  }
  return status;
}

}  // namespace s21