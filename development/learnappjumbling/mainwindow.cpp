#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "learnappjumbling.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  mpSelectedApp = new learnappjumbling(this);
  mpSelectedApp->show();
  this->resize(mpSelectedApp->width(), mpSelectedApp->height());
  emit signal_Resize(mpSelectedApp->width(), mpSelectedApp->height());
}

MainWindow::~MainWindow()
{
  delete ui;
}

