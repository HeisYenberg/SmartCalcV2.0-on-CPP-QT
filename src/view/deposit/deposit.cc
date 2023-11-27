#include "deposit.h"

#include "ui_deposit.h"

namespace s21 {

Deposit::Deposit(DepositController &controller, QWidget *parent)
    : QWidget(parent), ui_(new Ui::Deposit), controller_(controller) {
  ui_->setupUi(this);
  this->setWindowTitle("Deposit Calculator");
  connect(ui_->replenishmentAddButton, SIGNAL(clicked(bool)), this,
          SLOT(OnReplenishmentAddButtonClicked()));
  connect(ui_->withdrawalsAddButton, SIGNAL(clicked(bool)), this,
          SLOT(OnWithdrawalsAddButtonClicked()));
  connect(ui_->depositAmount, SIGNAL(valueChanged(double)), this,
          SLOT(OnDepositAmountValueChanged(double)));
  connect(ui_->mothlyTerm, SIGNAL(valueChanged(int)), this,
          SLOT(OnMothlyTermValueChanged(int)));
  connect(ui_->pereodicetyComboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(OnPereodicetyComboBoxCurrentIndexChanged(int)));
  connect(ui_->capitatlizationCheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(OnCapitatlizationCheckBoxStateChanged(int)));
  connect(ui_->calculateButton, SIGNAL(clicked(bool)), this,
          SLOT(OnCalculateButtonClicked()));
  connect(ui_->resetButton, SIGNAL(clicked(bool)), this,
          SLOT(OnResetButtonClicked()));
}

Deposit::~Deposit() { delete ui_; }

void Deposit::OnReplenishmentAddButtonClicked() {
  double amount = ui_->replenishmentAmount->value();
  int mounth = ui_->replenishmentMonth->value();
  if (amount && mounth) {
    data_.replenishment[mounth] += amount;
    QString item = QString::number(mounth, 'd', 0) + ") " +
                   QString::number(amount, 'f', 2);
    ui_->replenishmentList->insertItem(ui_->replenishmentMonth->value(), item);
  }
}

void Deposit::OnWithdrawalsAddButtonClicked() {
  double amount = ui_->withdrawalAmount->value();
  int mounth = ui_->withdrawalMonth->value();
  if (amount && mounth) {
    data_.withdrawals[mounth] += amount;
    QString item = QString::number(mounth, 'd', 0) + ") " +
                   QString::number(amount, 'f', 2);
    ui_->withdrawalList->insertItem(mounth, item);
  }
}

void Deposit::OnDepositAmountValueChanged(double arg1) {
  ui_->withdrawalAmount->setMaximum(arg1);
}

void Deposit::OnMothlyTermValueChanged(int arg1) {
  if (arg1) {
    ui_->replenishmentMonth->setMaximum(arg1 - 1);
    ui_->withdrawalMonth->setMaximum(arg1 - 1);
  }
}

void Deposit::OnCalculateButtonClicked() {
  data_.deposit_amount = ui_->depositAmount->value();
  data_.interest_rate = ui_->interestRate->value();
  data_.tax_rate = ui_->taxRate->value();
  data_.month_term = ui_->mothlyTerm->value();
  if (!controller_.Calculate(&data_)) {
    ui_->accruedInterestValue->setText(
        QString::number(controller_.GetInterest(), 'f', 2));
    ui_->taxAmountValue->setText(
        QString::number(controller_.GetTaxes(), 'f', 2));
    ui_->endTermsAmountValue->setText(
        QString::number(controller_.GetDepositAmount(), 'f', 2));
  } else {
    ui_->accruedInterestValue->setText("Incorrect input");
  }
}

void Deposit::OnPereodicetyComboBoxCurrentIndexChanged(int index) {
  data_.capitalisation_periodicity = index;
}

void Deposit::OnCapitatlizationCheckBoxStateChanged(int arg1) {
  data_.capitalisation = arg1;
}

void Deposit::OnResetButtonClicked() {
  data_.replenishment.clear();
  ui_->replenishmentList->clear();
  data_.withdrawals.clear();
  ui_->withdrawalList->clear();
}

}  // namespace s21
