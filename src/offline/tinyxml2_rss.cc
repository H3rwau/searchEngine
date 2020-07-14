#include "../../inc/tinyxml2_rss.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

using namespace tinyxml2;
using std::cerr;
using std::cout;
using std::endl;
using std::ofstream;
using std::ostringstream;
using std::regex;
using std::regex_replace;

namespace SE
{
    RssReader::RssReader(vector<string> &files)
        : _files(files)
    {
       
    }

    void RssReader::loadfiles()
    {
        for(auto &s:_files)
        {
            loadonefile(s);
        }
    }
    void RssReader::loadonefile(const string &filename)
    {
        XMLDocument doc;
        doc.LoadFile(filename.c_str());
        //LogDebug("load %s file",filename.c_str());
        XMLError errorID=doc.ErrorID();
        if(errorID)
        {
            //LogError("XMLDocument  load file error");
            perror("XMLdocument load file error");
            exit(1);
        }else
        {
            parseRss(doc);
        }
        
        
    }
    void RssReader::parseRss(XMLDocument &doc) //解析
    {
        XMLElement *root = doc.RootElement();
        XMLElement *channel = root->FirstChildElement("channel");

        if (nullptr == channel)
        {
            cout << "get channel failed" << endl;
            return;
        }

        XMLElement *item = channel->FirstChildElement("item");
        while (item)
        {
            struct RssItem oneItem;

            const char * title=item->FirstChildElement("title")->GetText();
            const char * link=item->FirstChildElement("link")->GetText();
            const char * description=item->FirstChildElement("description")->GetText();
            const char * content=nullptr;
            XMLElement * contentEncoded=item->FirstChildElement("content:encoded");
            if(contentEncoded)
                content=contentEncoded->GetText();
            else
            {
                content=description;
            }

            regex e("<[^>]+>");
            string newcontent=regex_replace(string(content),e,"");

            oneItem.title=title?title:string("");
            oneItem.link=link?link:string("");
            oneItem.description=description?description:string("");
            oneItem.content=newcontent;
            _rss.push_back(oneItem);

            item = item->NextSiblingElement();
        }
    }
    void RssReader::makePages(vector<string> &pages)
    {
        for(auto it=0;it!=_rss.size();++it)
        {
            ostringstream oss;
            oss <<"<doc>\n"
                <<"\t<docid>"<<(it+1)<<"</docid>\n"
                <<"\t<title>"<<_rss[it].title<<"</title>\n"
                <<"\t<link>"<<_rss[it].link<<"</link>\n"
                <<"\t<content>"<<_rss[it].content<<"</content>\n"
                <<"</doc>\n";

            string page=oss.str();
            pages.push_back(page);
        }
    }
    void RssReader::dump(const string &filename) //输出
    {
        //输出_rss的内容到pagelib.txt
        ofstream ofsm(filename);
        if (!ofsm.good())
        {
            cerr << "ofstream broken!" << endl;
            return;
        }

        auto it = _rss.begin();
        int num = 1;
        while (it != _rss.end())
        {
            ofsm << "<doc>" << endl;
            ofsm << "    "
                 << "<docid>" << num++ << "</docid>" << endl;
            ofsm << "    "
                 << "<title>" << it->title << "</title>" << endl;
            ofsm << "    "
                 << "<link>" << it->link << "</link>" << endl;
            ofsm << "    "
                 << "<description>" << it->description << "</description>" << endl;
            regex e("<[^>]+>");
            // string content=regex_replace(it->content,e," ");
            ofsm << "    "
                 << "<content>" << regex_replace(it->content, e, " ") << "</content>" << endl;
            ofsm << "</doc>" << endl;
            ++it;
        }
    }

} // namespace SE
