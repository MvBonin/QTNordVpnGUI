#ifndef NVPN_H
#define NVPN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QStringList>
#include <vector>
#include <string>

class nVPN
{
public:
    nVPN();
    std::string getStatus();
    std::string ssystem( const char *command);
    QStringList getCountries();
    QStringList getCities(std::string country);
};

#endif // NVPN_H
