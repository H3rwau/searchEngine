#include "../../inc/dirscanner.hpp"
#include "../../inc/configuration.hpp"
#include "../../inc/mylog4cpp.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include <map>
#include <string>

using std::map;
using std::string;
namespace SE
{
    
    DirScanner::DirScanner(Configuration & conf)
    :_conf(conf)
    {

    }
    void DirScanner::operator()()
    {
        map<string,string> confMap=_conf.getConfContent();
        string path=confMap["rss"];
        traverse(path);
    }
    vector<string> &DirScanner::getFilePathVec()
    {
        return _filePathVec;
    }
    void DirScanner::traverse(const string & dirname)
    {
        DIR *dir=opendir(dirname.c_str());
        if(nullptr==dir)
        {
            LogError("opendir failed!");
            exit(1);
        }
        struct dirent *pDirent;
        
        while (pDirent = readdir(dir))
        {
            if (strcmp(pDirent->d_name, ".") == 0 || 0 == strcmp(pDirent->d_name, ".."))
            {
                continue;
            }
            //将文件名和路径拼接
            string path = dirname;
            string onetext;
            onetext = path.append("/").append(pDirent->d_name);
            LogDebug(onetext.c_str());
            _filePathVec.push_back(onetext);
        }

        closedir(dir);

    }
} // namespace SE
