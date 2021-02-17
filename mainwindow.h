#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "nvpn.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    nVPN *nvpn;
    ~MainWindow();
    void setUIState();
    void populateCountriesList();
    void populateCitiesList(std::string country);

private slots:
    void on_connectButton_clicked();

    void on_debugButton_clicked();

    void on_countriesList_clicked(const QModelIndex &index);

    void on_countriesList_doubleClicked(const QModelIndex &index);

    void on_citiesList_doubleClicked(const QModelIndex &index);

    void on_countriesList_activated(const QModelIndex &index);

    void on_actionBeenden_triggered();

private:
    Ui::MainWindow *ui;
    QStringListModel *countriesModel;
    QStringList countriesList;

    QStringListModel *citiesModel;
    QStringList citiesList;
    QStringList toStringList(std::vector<std::string> s);
    void tryConnectUIMsg(std::string str);

};

#endif // MAINWINDOW_H
