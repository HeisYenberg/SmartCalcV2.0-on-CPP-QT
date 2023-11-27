#ifndef CPP3_SMARTCALC_V2_0_VIEW_DEPOSIT_DEPOSIT_H_
#define CPP3_SMARTCALC_V2_0_VIEW_DEPOSIT_DEPOSIT_H_

#include <QWidget>

#include "../../controller/deposit/deposit_controller.h"

namespace Ui {
class Deposit;
}

namespace s21 {

class Deposit : public QWidget {
  Q_OBJECT

 public:
  Deposit(DepositController &controller, QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void OnReplenishmentAddButtonClicked();
  void OnWithdrawalsAddButtonClicked();
  void OnCalculateButtonClicked();
  void OnDepositAmountValueChanged(double arg1);
  void OnMothlyTermValueChanged(int arg1);
  void OnPereodicetyComboBoxCurrentIndexChanged(int index);
  void OnCapitatlizationCheckBoxStateChanged(int arg1);
  void OnResetButtonClicked();

 private:
  Ui::Deposit *ui_;
  DepositController controller_;
  s21::DepositData data_{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_VIEW_DEPOSIT_DEPOSIT_H_
