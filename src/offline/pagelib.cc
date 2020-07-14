#include "../../inc/pagelib.hpp"
#include "../../inc/dirscanner.hpp"
#include "../../inc/tinyxml2_rss.hpp"
#include "../../inc/configuration.hpp"
#include "../../inc/mylog4cpp.hpp"

#include <fstream>
using std::ofstream;
namespace SE
{
    PageLib::PageLib(Configuration &conf,DirScanner &dscanner)
    :_conf(conf)
    ,_dScanner(dscanner)
    {

    }
    void PageLib::create()
    {
        vector<string> & rssFileVec=_dScanner.getFilePathVec();
        RssReader reader(rssFileVec);
        reader.loadfiles();
        reader.makePages(_pageFileVec);
    }
    void PageLib::store()
    {
        map<string,string> &confMap=_conf.getConfContent();

        string pageLibPath=confMap["ripepage"];
        string offsetPath=confMap["offset"];

        ofstream ofsPage(pageLibPath.c_str());
        ofstream ofsOffset(offsetPath.c_str());

        if(!(ofsPage.good()&&ofsOffset.good()))
        {
            LogError("ofstream error");
            exit(1);
        }

        for(auto it=0;it!=_pageFileVec.size();++it)
        {
            int id=it+1;
            int length=_pageFileVec[it].size();
            ofstream::pos_type offset=ofsPage.tellp();
            ofsPage<<_pageFileVec[it];
            ofsOffset<<id<<"\t"<<offset<<"\t"<<length<<endl;
        }

        ofsOffset.close();
        ofsPage.close();
    }
    
} // namespace SE
