#ifndef NVPN_H
#define NVPN_H
#define STATE_CONNECTION 0
#define STATE_SERVER 1
#define STATE_COUNTRY 2
#define STATE_CITY 3
#define STATE_IP 4
#define STATE_TECHNOLOGY 5
#define STATE_PROTOCOL 6
#define STATE_TRANSFER 7
#define STATE_UPTIME 8


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
class nVPN
{
public:
    nVPN();
    std::string getStatusString();
    bool connect(std::string country = "");
    bool disconnect();
    bool getStatus();
    std::string getCurrentServer();
    std::string getCurrentCity();
    std::string getCurrentIP();
    std::string getCurrentCountry();
    std::vector<std::string> getDataList(std::string in);
private:
    std::string getStateData(int index);
    std::string ssystem( std::string inputCommand );
    std::vector<std::string> split_str(const std::string& str,
                                       const std::string& trenner);

};

#endif // NVPN_H
