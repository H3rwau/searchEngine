#include "../../inc/pagelibpreprocessor.hpp"

#include <errno.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::log;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::make_pair;
using std::sort;

using std::stringstream;
namespace SE
{
    
    PageLibPreProcessor::PageLibPreProcessor(Configuration &conf)
    :_conf(conf)
    ,_jieba(_conf)
    ,_simhash(getsimhash())
    {

    }
    simhash::Simhasher PageLibPreProcessor::getsimhash()
    {

        map<string,string> pathMap= _conf.getConfContent();
        const char* const DICT_PATH = pathMap["DICT_PATH"].c_str();
        const char* const HMM_PATH = pathMap["HMM_PATH"].c_str();
        const char* const IDF_PATH = pathMap["IDF_PATH"].c_str();
        const char* const STOP_WORD_PATH = pathMap["STOP_WORD_PATH"].c_str();

        simhash::Simhasher simhasher(
            DICT_PATH,
            HMM_PATH,
            IDF_PATH,
            STOP_WORD_PATH
        );
        return simhasher;
    }
    void PageLibPreProcessor::doProcess()
    {
        readInfoFromFile();
        time_t t1=time(nullptr);
        cutRedundantPages();
        buildInvertIndex();
        time_t t2=time(nullptr);
        cout<<"preprocess time :"<<t2-t1<<" seconds"<<endl;
        store();
        time_t t3=time(nullptr);
        cout<<"store time :"<<t3-t2<<" seconds"<<endl;


    }
    void PageLibPreProcessor::readInfoFromFile()  //读取网页库和偏移库的内容
    {
        map<string,string> &confMap=_conf.getConfContent();
        string pageLibPath=confMap["ripepage"];
        string offsetPath=confMap["offset"];

        ifstream pageIfsm(pageLibPath.c_str());
        ifstream offsetIfsm(offsetPath.c_str());
        if((!pageIfsm.good())||(!offsetIfsm.good()))
        {
           perror("page or offset open error\n");
        }

        string line;
        int docId,docOffset,docLen;

        while(getline(offsetIfsm,line))
        {
            stringstream ss(line);
            ss>>docId>>docOffset>>docLen;
            string doc;
            doc.resize(docLen,' ');
            pageIfsm.seekg(docOffset,pageIfsm.beg);
            pageIfsm.read(&*doc.begin(),docLen);

            WebPage webpage(doc,_conf,_jieba,_simhash);
            _pageLib.push_back(webpage);
            _offsetLib.insert(make_pair(docId,make_pair(docOffset,docLen)));
        }
    }
    void PageLibPreProcessor::cutRedundantPages() //对网页去重
    {
        for(int i=0;i!=_pageLib.size()-1;++i)
        {
            for(int j=i+1;j!=_pageLib.size();++j)
            {
                if(_pageLib[i]==_pageLib[j])
                {
                    _pageLib[j]=_pageLib[_pageLib.size()-1];
                    _pageLib.pop_back();
                    --j;
                }
            }
        }
    }
    void PageLibPreProcessor::buildInvertIndex()  //创建倒排索引
    {
        for(auto page:_pageLib)
        {
            map<string,int> &wordsFreqMap=page.getWordsFreqMap();
            for(auto wf:wordsFreqMap)
            {
                _invertIndex[wf.first].push_back(make_pair(page.getDocId(),wf.second));
            }
        }
        //计算每篇文档中的词权重，并归一化
        map<int,double> weightsum;//每一篇文档中所有词的权重平方和 id-Wn
        int totalPageNum=_pageLib.size();
        for(auto &it:_invertIndex)
        {
            int df=it.second.size();//df代表某个词在所有文章中出现次数
            //逆文档频率
            double idf=log(totalPageNum/(df+1))/log(2);

            for(auto &sit:it.second)
            {
                double w=sit.second*idf;
                weightsum[sit.first]+=pow(w,2);
                sit.second=w;
            }
        }
        //归一化
        for(auto &it:_invertIndex)
        {
            for(auto &sit:it.second)
            {
                sit.second=sit.second/sqrt(weightsum[sit.first]);
            }
        }
    }
    void PageLibPreProcessor::store()            //将处理过的网页库、偏移库、倒排索引保存到文件中
    {
        sort(_pageLib.begin(),_pageLib.end());
        map<string,string> confMap=_conf.getConfContent();
        string newPageLibPath=confMap["newripepage"];
        string newOffsetPath=confMap["newoffset"];

        ofstream ofsmPageLib(newPageLibPath.c_str());
        ofstream ofsmOffset(newOffsetPath.c_str());

        if(!ofsmOffset.good()||!ofsmPageLib.good())
        {
            perror("new page or offset ofstream open error");
        }

        for(auto &page:_pageLib)
        {
            int id=page.getDocId();
            int length =page.getDoc().size();

            ofstream::pos_type offset=ofsmPageLib.tellp();
            ofsmPageLib<<page.getDoc();
            ofsmOffset<<id<<'\t'<<offset<<'\t'<<length<<'\n';
        }

        ofsmOffset.close();
        ofsmPageLib.close();

        //存储倒排索引
        string invertIndexPath=confMap["invertindex"];
        ofstream ofsminverIndex(invertIndexPath.c_str());

        if(!ofsminverIndex.good())
        {
            perror("invertindex ofsm error");
        }

        for(auto it:_invertIndex)
        {
            ofsminverIndex<<it.first<<"\t";
            for(auto sit:it.second)
            {
                ofsminverIndex<<sit.first<<"\t"<<sit.second<<"\t";
            }
            ofsminverIndex<<endl;
        }
        ofsminverIndex.close();
    }
} // namespace SE
