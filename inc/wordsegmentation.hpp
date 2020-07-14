#ifndef __WORDSEGMENTATION_HPP__
#define __WORDSEGMENTATION_HPP__

#include "simhash/cppjieba/Jieba.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;
namespace SE
{
    class Configuration;
    class WordSegmentation
    {
    public:
        WordSegmentation(Configuration & conf);
        cppjieba::Jieba setPath(); 
        vector<string> operator()(const char *src)
        {
            vector<string> words;
            _jieba.CutAll(src,words);
            return words;
        }
    private:
        Configuration & _conf;
        cppjieba::Jieba _jieba;
    };
    
} // namespace SE



#endif // !__WORDSEGMENTATION_HPP__