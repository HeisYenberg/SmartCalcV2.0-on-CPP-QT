#include "smartcalc.h"

#include "../credit/credit.h"
#include "../deposit/deposit.h"
#include "../graph/graph.h"
#include "ui_smartcalc.h"

namespace s21 {

SmartCalc::SmartCalc(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new ::Ui::SmartCalc), controller_(controller) {
  ui_->setupUi(this);
  ConnectButtons();
}

SmartCalc::~SmartCalc() { delete ui_; }

void SmartCalc::ConnectButtons() {
  buttons_map_[ui_->button0] = "0";
  buttons_map_[ui_->button1] = "1";
  buttons_map_[ui_->button2] = "2";
  buttons_map_[ui_->button3] = "3";
  buttons_map_[ui_->button4] = "4";
  buttons_map_[ui_->button5] = "5";
  buttons_map_[ui_->button6] = "6";
  buttons_map_[ui_->button7] = "7";
  buttons_map_[ui_->button8] = "8";
  buttons_map_[ui_->button9] = "9";
  buttons_map_[ui_->buttonE] = "e";
  buttons_map_[ui_->buttonX] = "x";
  buttons_map_[ui_->buttonBracketOpen] = "(";
  buttons_map_[ui_->buttonBracketClose] = ")";
  buttons_map_[ui_->buttonDivide] = "/";
  buttons_map_[ui_->buttonMultiply] = "*";
  buttons_map_[ui_->buttonAdd] = "+";
  buttons_map_[ui_->buttonSubstruct] = "-";
  buttons_map_[ui_->buttonDot] = ".";
  buttons_map_[ui_->buttonPower] = "^";
  buttons_map_[ui_->buttonMod] = "mod";
  buttons_map_[ui_->buttonLn] = "ln(";
  buttons_map_[ui_->buttonLog] = "log(";
  buttons_map_[ui_->buttonSqrt] = "sqrt(";
  buttons_map_[ui_->buttonAcos] = "acos(";
  buttons_map_[ui_->buttonAsin] = "asin(";
  buttons_map_[ui_->buttonAtan] = "atan(";
  buttons_map_[ui_->buttonCos] = "cos(";
  buttons_map_[ui_->buttonSin] = "sin(";
  buttons_map_[ui_->buttonTan] = "tan(";
  for (auto it = buttons_map_.begin(); it != buttons_map_.end(); ++it) {
    connect(it.key(), &QPushButton::clicked, this,
            &SmartCalc::OnButtonsClicked);
  }
  connect(ui_->buttonC, SIGNAL(clicked(bool)), this, SLOT(OnButtonCClicked()));
  connect(ui_->buttonEqual, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonEqualClicked()));
  connect(ui_->buttonDel, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonDelClicked()));
  connect(ui_->input, SIGNAL(editingFinished()), this,
          SLOT(OnButtonEqualClicked()));
  connect(ui_->buttonGraph, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonGraphClicked()));
  connect(ui_->buttonCredit, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonCreditClicked()));
  connect(ui_->buttonDeposit, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonDepositClicked()));
}

void SmartCalc::OnButtonsClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (!button) {
    return;
  }
  QString append = buttons_map_[button];
  QString input = ui_->input->text();
  input.append(append);
  ui_->input->setText(input);
}

void SmartCalc::OnButtonCreditClicked() {
  CreditModel model;
  CreditController controller(model);
  Credit *credit = new Credit(controller);
  credit->setAttribute(Qt::WA_DeleteOnClose);
  credit->show();
}

void SmartCalc::OnButtonDepositClicked() {
  DepositModel model;
  DepositController controller(model);
  Deposit *deposit = new Deposit(controller);
  deposit->setAttribute(Qt::WA_DeleteOnClose);
  deposit->show();
}

void SmartCalc::OnButtonGraphClicked() {
  Graph *graph = new Graph(controller_);
  QString input = ui_->input->text();
  std::string expression = input.toStdString();
  graph->controller_->SetExpression(expression);
  graph->setAttribute(Qt::WA_DeleteOnClose);
  graph->show();
}

void SmartCalc::OnButtonEqualClicked() {
  QString input = ui_->input->text();
  std::string expression = input.toStdString();
  controller_->SetExpression(expression);
  controller_->SetXValue(ui_->xValue->value());
  int status = controller_->Calculate();
  if (!status) {
    ui_->output->setText(QString::number(controller_->GetResult(), 'g', 7));
  } else if (status == s21::Model::kIncorrectExpression) {
    ui_->output->setText("INCORRECT EXPRESSION");
  } else if (status == s21::Model::kCalculationError) {
    ui_->output->setText("CALCULATION ERROR");
  } else if (status == s21::Model::kDivisionByZero) {
    ui_->output->setText("DIVISION BY ZERO");
  }
}

void SmartCalc::OnButtonCClicked() {
  ui_->input->clear();
  ui_->output->setText("0");
}

void SmartCalc::OnButtonDelClicked() {
  QString append = ui_->input->text();
  append.chop(1);
  ui_->input->setText(append);
}

}  // namespace s21
