#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <math.h>
#include <QMainWindow>
#include  <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    double Re;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_run_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
