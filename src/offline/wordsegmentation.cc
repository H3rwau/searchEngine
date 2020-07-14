#include "../../inc/wordsegmentation.hpp"
#include "../../inc/configuration.hpp"
#include "../../inc/simhash/cppjieba/Jieba.hpp"
namespace SE
{
    
    WordSegmentation::WordSegmentation(Configuration & conf)
    :_conf(conf)
    ,_jieba(setPath())
    {

    }
        
    cppjieba::Jieba WordSegmentation::setPath()
    {

        map<string,string> pathMap= _conf.getConfContent();
        const char* const DICT_PATH = pathMap["DICT_PATH"].c_str();
        const char* const HMM_PATH = pathMap["HMM_PATH"].c_str();
        const char* const USER_DICT_PATH = pathMap["USER_DICT_PATH"].c_str();


        cppjieba::Jieba jieba(
        DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH
        );
        return jieba;
    }
} // namespace SE
