#ifndef __DIRSCANNER_HPP__
#define __DIRSCANNER_HPP__

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace SE
{
    class Configuration;
    class DirScanner
    {
    public:
        DirScanner(Configuration &conf);
        void operator()();
        vector<string>& getFilePathVec();

    private:
        void traverse(const string &dirname);

    private:
        vector<string> _filePathVec;
        Configuration &_conf;
    };

} // namespace SE

#endif // !__DIRSCANNER_HPP__