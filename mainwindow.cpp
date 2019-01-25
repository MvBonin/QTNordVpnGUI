#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nvpn = new nVPN();

    ui->label->setText(QString(nvpn->getStatus().c_str()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



