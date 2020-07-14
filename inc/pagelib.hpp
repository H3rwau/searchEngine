#ifndef __PAGELIB_HPP__
#define __PAGELIB_HPP__

#include <vector>
#include <map>
#include <utility>
#include <string>

using std::map;
using std::pair;
using std::string;
using std::vector;

namespace SE
{
    class Configuration;
    class DirScanner;
    class PageLib
    {
    public:
        PageLib(Configuration &conf,DirScanner &dscanner);
        void create();//创建网页库
        void store();//存储网页库和偏移库到文件中

    private:
        Configuration &_conf;
        DirScanner &_dScanner;
        vector<string> _pageFileVec;//存储每篇网页的格式化string的容器
        map<int, pair<long, long>> _offsetLib;//每篇网页的docid---(position,length)
    };

} // namespace SE

#endif // !__PAGELIB_HPP__