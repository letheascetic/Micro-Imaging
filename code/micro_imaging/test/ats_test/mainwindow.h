#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "miats.h"
#include "midef.h"
#include "micfg.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void init();

private slots:
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void on_btnOpen_clicked();
    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
    ATS ats;
    CONFIG config;
};
#endif // MAINWINDOW_H
