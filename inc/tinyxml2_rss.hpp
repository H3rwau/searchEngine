#ifndef __TINY2XML2_RSS_HPP__
#define __TINY2XML2_RSS_HPP__

#include <string>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;
using std::string;
using std::vector;

namespace SE
{
    struct RssItem
    {
        string title;
        string link;
        string description;
        string content;
    };

    class RssReader
    {
    public:
        RssReader(vector<string> &files);

        void loadonefile(const string & filename);
        void loadfiles();

        void makePages(vector<string> &pages);
        void parseRss(XMLDocument &doc);                   //解析
        void dump(const string &filename); //输出
    private:
        vector<RssItem> _rss;
        vector<string> &_files;
    };

} // namespace SE

#endif // !__TINY2XML2_RSS_HPP__