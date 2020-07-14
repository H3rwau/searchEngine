#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__


#include <string>
#include <map>
#include <set>

using std::set;
using std::map;
using std::string;

namespace SE
{
    class Configuration
    {
    public:
        Configuration(const string &confPath);
        map<string, string> &getConfContent();
        set<string> &getStopWordSet();

    private:
        void confInit();

    private:
        string _confPath;
        map<string, string> _confContent;
        set<string> _stopWordSet;
    };
} // namespace SE
#endif // !__CONFIGURATION_HPP__
