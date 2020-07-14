#ifndef __PAGELIBPREPROCESSOR_HPP__
#define __PAGELIBPREPROCESSOR_HPP__

#include "wordsegmentation.hpp"
#include "webpage.hpp"
#include "configuration.hpp"
#include "simhash/Simhasher.hpp"

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <set>

using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;
namespace SE
{
    class PageLibPreProcessor
    {
    public:
        PageLibPreProcessor(Configuration &conf);
        void doProcess();

    private:
        simhash::Simhasher getsimhash();
        void readInfoFromFile();  //读取网页库和偏移库的内容
        void cutRedundantPages(); //对网页去重
        void buildInvertIndex();  //创建倒排索引
        void store();             //将处理过的网页库、偏移库、倒排索引保存到文件中
    private:
        Configuration &_conf;
        WordSegmentation _jieba;
        simhash::Simhasher _simhash;
        vector<WebPage> _pageLib;                                   //网页库的容器
        unordered_map<int, pair<long, long>> _offsetLib;            //偏移库的容器
        unordered_map<string, vector<pair<int, double>>> _invertIndex; //倒排索引
        //倒排索引对应格式  词--set(docid,w)
        //w=TF*IDF
    };

} // namespace SE

#endif // !__PAGELIBPREPROCESSOR_HPP__