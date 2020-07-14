#ifndef __WEBPAGE_HPP__
#define __WEBPAGE_HPP__

#include "simhash/Simhasher.hpp"
#include <string>
#include <map>

using std::map;
using std::string;
namespace SE
{
    class Configuration;
    class WordSegmentation;
    class WebPage
    {

        friend bool operator==(const WebPage &lhs, const WebPage &rhs);
        friend bool operator<(const WebPage &lhs, const WebPage &rhs);

    public:
        WebPage(string &doc, Configuration &conf, WordSegmentation& jieba,simhash::Simhasher &hash);

        int getDocId()
        {
            return _docId;
        }
        string getDoc()
        {
            return _doc;
        }
        map<string, int> &getWordsFreqMap() //获取词频统计map
        {
            return _wordsFreqMap;
        }

    private:
        void processDoc(const string &doc, Configuration &conf,WordSegmentation& jieba, simhash::Simhasher &hash);
        void calcSimhash(simhash::Simhasher &hash);

    private:
        string _doc;                    //网页库内容
        int _docId;                     //一篇网页id
        string _docTitle;               //一篇网页标题
        string _docUrl;                 //一篇网页URL；
        string _docContent;             //一篇网页内容
        string _docSummary;             //一篇网页摘要
        uint64_t _simhash;              //simhash值
        map<string, int> _wordsFreqMap; //保存每篇网页的所有词语和词频，不包括停用词
    };

} // namespace SE

#endif // !__WEBPAGE_HPP__