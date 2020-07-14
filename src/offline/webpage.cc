#include "../../inc/webpage.hpp"
#include "../../inc/simhash/Simhasher.hpp"
#include "../../inc/configuration.hpp"
#include "../../inc/wordsegmentation.hpp"
#include "../../inc/mylog4cpp.hpp"

#include <utility>
#include <vector>
#include <set>

using std::set;
using std::vector;
using std::pair;
namespace SE
{
    struct WordFreqCompare
    {
        bool operator()(const pair<string,int> &left,const pair<string,int> &right)
        {
            if(left.second<right.second)
            {
                return true;
            }else if(left.second==right.second &&left.first>right.first)
            {
                return true;
            }else
            {
                return false;
            }
        }
    };
    
    bool operator==(const WebPage &lhs, const WebPage &rhs)
    {
        if(simhash::Simhasher::isEqual(lhs._simhash,rhs._simhash))
        {
            return true;
        }
        return false;
    }
    bool operator<(const WebPage &lhs, const WebPage &rhs)
    {
        if(lhs._docId<rhs._docId)
            return true;
        return false;
    }
    WebPage::WebPage(string &doc, Configuration &conf, WordSegmentation &jieba,simhash::Simhasher &hash)
    :_doc(doc)
    {
        processDoc(doc,conf,jieba,hash);
    }
    void WebPage::processDoc(const string &doc, Configuration &conf, WordSegmentation &jieba,simhash::Simhasher &hash)
    {
        string docIdHead = "<docid>";
        string docIdTail = "</docid>";
        string docUrlHead = "<link>";
        string docUrlTail = "</link>";
        string docTitleHead = "<title>";
        string docTitleTail = "</title>";
        string docContentHead = "<content>";
        string docContentTail = "</content>";

        //提取文档的docid
        int bpos = doc.find(docIdHead);
        int epos = doc.find(docIdTail);
        string docId = doc.substr(bpos + docIdHead.size(),
                                  epos - bpos - docIdHead.size());
        _docId = atoi(docId.c_str());

        //title
        bpos = doc.find(docTitleHead);
        epos = doc.find(docTitleTail);
        _docTitle = doc.substr(bpos + docTitleHead.size(),
                               epos - bpos - docTitleHead.size());

        //content
        bpos = doc.find(docContentHead);
        epos = doc.find(docContentTail);
        _docContent = doc.substr(bpos + docContentHead.size(),
                                 epos - bpos - docContentHead.size());

        //统计词频
        vector<string> wordsVec=jieba(_docContent.c_str());
        set<string> & stopWordSet=conf.getStopWordSet();
        for(auto it=wordsVec.begin();it!=wordsVec.end();++it)
        {
            auto obit=stopWordSet.find(*it);
            if(obit==stopWordSet.end())
            {
                ++_wordsFreqMap[*it];
            }
        }
        //计算simhash
        calcSimhash(hash);
    }
    void WebPage::calcSimhash(simhash::Simhasher &simhasher)
    {
        simhasher.make(_docContent,5,_simhash);
    }
} // namespace SE
