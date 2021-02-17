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


    setUIState();
    populateCountriesList();
    ui->debugButton->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUIState()
{
    //Update Status of Connection in Window

    if(nvpn->getStatus() == true){
        std::string server = nvpn->getCurrentServer();
        std::string city = nvpn->getCurrentCity();
        std::string country = nvpn->getCurrentCountry();

        QString conn = QString("Connected to ");
        conn.append(server.c_str());
        if(!city.empty()){
        conn.append(" ( ").append(city.c_str());
        if(!country.empty()){
            conn.append(", ").append(country.c_str());
        }
        conn.append(" )");
        }
        ui->label->setText(conn);
        ui->connectButton->setText("Disconnect");
    }else{
        ui->label->setText(QString("Disconnected. Double-Click to Connect."));
        ui->connectButton->setText("Auto Connect");
    }
}

void MainWindow::populateCountriesList()
{   //Populate Countries list
    std::vector<std::string> countries = nvpn->getDataList("nordvpn countries");
    countriesModel = new QStringListModel(this);
    countriesList = toStringList(countries);

    countriesModel->setStringList(countriesList);
    ui->countriesList->setModel(countriesModel);
}

void MainWindow::populateCitiesList(std::string country)
{
    if(country.empty()){
        country = ui->countriesList->currentIndex().data(Qt::DisplayRole).toString().toStdString();
    }
    std::string in = std::string("nordvpn cities ") + country;

    std::vector<std::string> cities = nvpn->getDataList( in.c_str() );
    std::cout << "cities: " << cities.size() << std::endl;
    citiesModel = new QStringListModel(this);
    citiesList = toStringList(cities);

    citiesModel->setStringList(citiesList);
    ui->citiesList->setModel(citiesModel);

}





void MainWindow::on_connectButton_clicked()
{
    //Connect/Disconnect Button is clicked

    if(nvpn->getStatus()){
        nvpn->disconnect();
    }else{
        tryConnectUIMsg("");
        nvpn->connect("");
    }
    setUIState();
}

void MainWindow::on_debugButton_clicked()
{

}

QStringList MainWindow::toStringList(std::vector<std::string> s)
{
    QStringList out;
    for(std::string i : s){
        out.append(QString(i.c_str()));
    }
    return out;

}

void MainWindow::tryConnectUIMsg(std::string str)
{

    if(str.c_str() == ""){
        std::cout << "autoConn" << std::endl;
        ui->label->setText("Connecting...");
    }else{
        std::cout << "Conn" << std::endl;
        std::string con = std::string("Connecting to ") + str + std::string(" ...");
        ui->label->setText(con.c_str());
    }
    ui->label->update();
    QApplication::instance()->processEvents();

}

void MainWindow::on_countriesList_clicked(const QModelIndex &index)
{
    //open Cities
    populateCitiesList(index.data(Qt::DisplayRole).toString().toStdString());
}

void MainWindow::on_countriesList_doubleClicked(const QModelIndex &index)
{
    //Connect to clicked Country
    tryConnectUIMsg(index.data(Qt::DisplayRole).toString().toStdString());
    nvpn->connect(index.data(Qt::DisplayRole).toString().toStdString());
    setUIState();
}

void MainWindow::on_citiesList_doubleClicked(const QModelIndex &index)
{
    //connect to clicked City

    tryConnectUIMsg(index.data(Qt::DisplayRole).toString().toStdString());
    nvpn->connect(index.data(Qt::DisplayRole).toString().toStdString());
    setUIState();
}

void MainWindow::on_countriesList_activated(const QModelIndex &index)
{
}

void MainWindow::on_actionBeenden_triggered()
{
    QApplication::quit();
}
