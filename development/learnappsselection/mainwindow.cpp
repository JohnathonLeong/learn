
#include "mainwindow.h"
#include "learnappsselection.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  mpLearnApps = new learnappsselection(this);
  mpLearnApps->setGeometry(0, 0, mpLearnApps->width(), mpLearnApps->height());
  this->setWindowTitle("LEARN");
  this->setMinimumSize(mpLearnApps->width(), mpLearnApps->height());
  this->setMaximumSize(mpLearnApps->width(), mpLearnApps->height());

  connect(mpLearnApps, SIGNAL(signal_Resize(int, int)), this, SLOT(slot_mpLearnAppsResize(int, int)));
}

MainWindow::~MainWindow() {
  delete ui;
  delete mpLearnApps;
}

void MainWindow::slot_mpLearnAppsResize(int width, int height) {
  this->setMinimumSize(width, height);
  this->setMaximumSize(width, height);
}

