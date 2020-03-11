#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nvpn = new nVPN();

    ui->label->setText("Status: " + QString(nvpn->getStatus().c_str()));

    QStringList countriesList = nvpn->getCountries();
    QStringListModel *countriesModel = new QStringListModel();
    countriesModel->setStringList(countriesList);

    ui->listView->setModel(countriesModel);

    QStringList out = nvpn->getCities("Germany");

}

MainWindow::~MainWindow()
{
    delete ui;
}



