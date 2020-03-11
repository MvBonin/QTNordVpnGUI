#include "nvpn.h"
#include <regex>
#include <iostream>
#include <string>
nVPN::nVPN()
{

}

std::string nVPN::ssystem( const char *command){
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


std::string nVPN::getStatus(){
    std::regex reg("([A-Za-z][A-Za-z])\\D+");
    std::smatch m;

    std::string bash = "nordvpn status";
    std::string in;
    std::string s = ssystem(bash.c_str());
    std::istringstream iss(s);
    std::string line;
    std::getline(iss, line);
    std::getline(iss, line); //Show current connected server
    std::cout << "Connected: " + line << std::endl;

    /*if (std::regex_search(line, m, reg)){
       return m[0];
    }*/

    return line;

}

QStringList nVPN::getCountries(){
    QStringList countries;
    std::string bash = "nordvpn countries";
    std::string in;
    std::string s = ssystem(bash.c_str());
    std::istringstream iss(s);
    std::string line;
    std::getline(iss, line);

    //std::cout << line << std::endl;
    std::regex reg("[^,\\s][A-z][^\\,][^,\\s]*");
    std::smatch m;

    //std::regex_search (line ,m,reg);

    std::string::const_iterator searchStart( line.cbegin() );
        while ( regex_search( searchStart, line.cend(), m, reg ) )
        {
            std::cout << ( searchStart == line.cbegin() ? "" : " " ) << m[0];
            //countries.push_back(m[0]);
            countries.append( std::string(m[0]).c_str() ) ;
            searchStart = m.suffix().first;
        }


    return countries;
}

QStringList nVPN::getCities(std::string country){
    QStringList cities;
    std::string bash = "nordvpn cities " + country;
    std::string in;
    std::string s = ssystem(bash.c_str());
    std::istringstream iss(s);
    std::string line;
    std::getline(iss, line);

    //std::cout << line << std::endl;
    std::regex reg("[^,\\s][A-z][^\\,][^,\\s]*");
    std::smatch m;

    //std::regex_search (line ,m,reg);

    std::string::const_iterator searchStart( line.cbegin() );
        while ( regex_search( searchStart, line.cend(), m, reg ) )
        {
            std::cout << ( searchStart == line.cbegin() ? "" : " " ) << m[0];
            //cities.push_back(m[0]);
            cities.append(std::string(m[0]).c_str());
            searchStart = m.suffix().first;
        }


    return cities;
}

