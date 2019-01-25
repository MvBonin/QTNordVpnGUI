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
    std::cout << "Status: " + line << std::endl;

    if (std::regex_search(line, m, reg)){
       return m[0];
    }

    return line;

}
