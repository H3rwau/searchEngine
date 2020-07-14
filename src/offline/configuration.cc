#include "../../inc/configuration.hpp"
#include "../../inc/mylog4cpp.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;


namespace SE
{

    Configuration::Configuration(const string &confPath)
        : _confPath(confPath)
    {
        cout<<_confPath<<endl;
        confInit();
    }
    map<string, string> &Configuration::getConfContent()
    {
        return _confContent;
    }

    void Configuration::confInit()
    {
        string oneLine;
        ifstream ifsm(_confPath);
        if (!ifsm.good())
        {
            //使用log4cpp
            LogError("config ifsm broken...");
            exit(1);
        }
        while (getline(ifsm, oneLine))
        {
            string attr;
            string cont;
            stringstream ss(oneLine);
            while (ss >> attr)
            {
                ss >> cont;
                _confContent.insert({attr, cont});
            }
        }
        ifsm.close();
    }

    set<string> &Configuration::getStopWordSet()
    {
        if(_stopWordSet.size()>0)
            return _stopWordSet;
        string stopWordFile= _confContent["stopword"];
        ifstream ifsm(stopWordFile.c_str());
        if(!ifsm.good())
        {
            LogError("get stopwordset failed!");
            exit(1);
        }

        string word;
        while(getline(ifsm,word))
        {
            _stopWordSet.insert(word);
        }
        return _stopWordSet;
    }
} // namespace SE
