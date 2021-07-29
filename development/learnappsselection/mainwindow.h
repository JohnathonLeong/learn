#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class learnappsselection;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;


public:
  learnappsselection * mpLearnApps;

private slots:
  void slot_mpLearnAppsResize(int width, int height);
};
#endif // MAINWINDOW_H

