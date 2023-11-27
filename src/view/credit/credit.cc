#include "credit.h"

#include "../../controller/credit/credit_controller.h"
#include "ui_credit.h"

namespace s21 {

Credit::Credit(CreditController &controller, QWidget *parent)
    : QWidget(parent), ui_(new Ui::Credit), controller_(controller) {
  ui_->setupUi(this);
  this->setWindowTitle("Credit Calculator");
  ui_->annuity->setChecked(true);
  connect(ui_->buttonCalculate, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonCalculateClicked()));
}

Credit::~Credit() { delete ui_; }

void Credit::OnButtonCalculateClicked() {
  double loanAmount = ui_->creditAmountValue->value();
  double monthlyRate = (double)ui_->interestRateValue->value() / 12 / 100;
  int loanTerm = ui_->monthTermValue->value();
  if (loanAmount && monthlyRate && loanTerm) {
    s21::CreditData data = {loanAmount, monthlyRate, loanTerm,
                            ui_->differentiated->isChecked()};
    controller_.Calculate(data);
    ui_->overpaymentValue->setText(
        QString::number(controller_.GetOverpayment(), 'f', 2));
    ui_->totalPaymentValue->setText(
        QString::number(controller_.GetTotalPayment(), 'f', 2));
    std::vector<double> monthly_payments = controller_.GetMonthlyPayments();
    QString result;
    for (int i = 0; i < (int)monthly_payments.size(); ++i) {
      result = result + QString::number(i + 1) + ") " +
               QString::number(monthly_payments[i], 'f', 2) + '\n';
    }
    ui_->monthlyPaymentValue->setText(result);
  } else {
    ui_->monthlyPaymentValue->setText("Incorrect input");
  }
}

}  // namespace s21
