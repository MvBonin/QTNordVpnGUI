#include "nvpn.h"
#include <regex>
#include <iostream>
#include <string>
nVPN::nVPN()
{

}

std::string nVPN::ssystem( std::string inputCommand ){
    const char *command = inputCommand.c_str();
    char tmpname [L_tmpnam];
        std::tmpnam ( tmpname );
        std::string scommand = command;
        std::string cmd = scommand + " >> " + tmpname;
        std::system(cmd.c_str());
        std::ifstream file(tmpname, std::ios::in );
        std::string result;
        if (file) {
            while (!file.eof()) result.push_back(file.get())
                ;
            file.close();
        }
        remove(tmpname);
        return result;
}

std::vector<std::string> nVPN::split_str(const std::string &str, const std::string &trenner)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(trenner, prev)) != std::string::npos)
        {
            strings.push_back(str.substr(prev, pos - prev));
            prev = pos + 1;
        }

     // To get the last substring (or only, if delimiter is not found)
     strings.push_back(str.substr(prev));

    return strings;
}

bool nVPN::connect(std::string country){
    //Connect to Server and return if it worked
    std::string connectString = "nordvpn c ";
    connectString.append(country);
    std::string response = ssystem(connectString);
    //std::cout << "Connect response: " << response << std::endl;
    return getStatus();
}

bool nVPN::disconnect(){
    //Disconnect from Server
    std::string response = ssystem("nordvpn d");
    return getStatus();
}


bool nVPN::getStatus(){
    //Return Boolean of the current state of connection
    //For now we use the getStatusString for this.
    std::string str = getStatusString();
    if(strstr(str.c_str(), "Disconnected") ){
        //str contains "Disconnected"
        return false;
    }else{

        return true;
    }
}

std::string nVPN::getCurrentServer()
{    //Return Current connected Server
    std::string response = getStateData(STATE_SERVER);
    return response;
}

std::string nVPN::getCurrentCity()
{
    return getStateData(STATE_CITY);
}

std::string nVPN::getCurrentCountry()
{
    return getStateData(STATE_COUNTRY);
}

std::string nVPN::getCurrentIP()
{
    return getStateData(STATE_IP);
}

std::vector<std::string> nVPN::getDataList(std::string in)
{
    //return List of Countries: in = "nordvpn countries"
    std::string response = ssystem(in);
    response = split_str(response, "\n").at(0);
    response = response.substr(12, response.size()-1);
    std::vector<std::string> out;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ", ";
    while ((pos = response.find(delimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        out.push_back(token);
        response.erase(0, pos + delimiter.length());
    }

    out.push_back(response);
    return out;
}

std::string nVPN::getStateData(int index)
{
    //Index:
    //When Connected:
    // 0: connection
    // 1: current server
    // 2: country
    // 3: City
    // 4: New IP
    // 5: Technology
    // 6: protocol
    // 7: transfer
    // 8: uptime
    //When disconnected:
    // 0: status
    std::string stateResponse = ssystem("nordvpn status");
    std::vector<std::string> vec = split_str(stateResponse, "\n");
    if(vec.size() < index){
        return "";
    }

    //Now we got the whole line. Time to get the Attribute
    std::string line = vec.at(index);
    size_t pos = 0;
    pos = line.find(": ");
    if(pos != std::string::npos){
        line = line.substr(pos + 2, line.length()-1);
    }
    return line;
}



std::string nVPN::getStatusString(){
    return getStateData(0);
}
