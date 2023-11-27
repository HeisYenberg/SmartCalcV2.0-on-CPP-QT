#include "graph.h"

#include "ui_graph.h"

namespace s21 {

Graph::Graph(Controller *controller, QWidget *parent)
    : QWidget(parent), ui_(new Ui::Graph), controller_(controller) {
  ui_->setupUi(this);
  this->setWindowTitle("Graph of function");
  connect(ui_->buttonGraph, SIGNAL(clicked(bool)), this,
          SLOT(OnButtonGraphClicked()));
}

Graph::~Graph() { delete ui_; }

void Graph::OnButtonGraphClicked() {
  QString result = QString::fromStdString(controller_->GetExpression());
  ui_->result->setText(result);
  double x_min = ui_->xMin->value();
  double x_max = ui_->xMax->value();
  double y_min = ui_->yMin->value();
  double y_max = ui_->yMax->value();
  double h = (x_max - x_min) / 1000000;
  QVector<double> x_vector, y_vector;
  ui_->widget->xAxis->setRange(x_min, x_max);
  ui_->widget->yAxis->setRange(y_min, y_max);
  for (double x = x_min; x <= x_max; x += h) {
    controller_->SetXValue(x);
    int res = controller_->Calculate();
    if (res == s21::Model::kIncorrectExpression) {
      ui_->result->setText("INCORRECT EXPRESSION");
      break;
    }
    if (res == s21::Model::kOk) {
      x_vector.push_back(x);
      y_vector.push_back(controller_->GetResult());
    }
  }
  ui_->widget->addGraph();
  ui_->widget->graph()->addData(x_vector, y_vector);
  ui_->widget->graph()->setLineStyle(QCPGraph::lsNone);
  QCPScatterStyle myScatter;
  myScatter.setShape(QCPScatterStyle::ssDisc);
  myScatter.setSize(2);
  ui_->widget->graph()->setScatterStyle(myScatter);
  ui_->widget->replot();
}

}  // namespace s21
