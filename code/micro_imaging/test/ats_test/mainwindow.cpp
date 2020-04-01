#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ats = NULL;
    config = NULL;
}

void MainWindow::on_btnStart_clicked()
{
    //MI_RESULTS code = MIAtsStart(ats, config);
    //qDebug("MIAtsStart: [%d]", code);
}

void MainWindow::on_btnStop_clicked()
{
    //MI_RESULTS code = MIAtsStop(ats);
    //qDebug("MIAtsStart: [%d]", code);
}

void MainWindow::on_btnOpen_clicked()
{
    qDebug() << "open ats device.";
    config = MICfgGetConfiguration();

    //ats = MIAtsOpen();
    //ATS_INFO info;
    //MI_RESULTS code = MIAtsGetInfo(ats, &info);
    //qDebug("MIAstGetInfo: [%d]", code);

    //code = MIAtsSetConfiguration(ats, config);
    //qDebug("MIAtsSetConfiguration: [%d]", code);
}

void MainWindow::on_btnClose_clicked()
{
    //MIAtsClose();
}
