#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget * parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow * ui;
  QWidget * mpLearnApps;

private slots:
  void slot_mpLearnAppsResize(int width, int height);

};
#endif
