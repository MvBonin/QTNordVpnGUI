#ifndef NVPN_H
#define NVPN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

class nVPN
{
public:
    nVPN();
    std::string getStatus();
    std::string ssystem( const char *command);
};

#endif // NVPN_H
