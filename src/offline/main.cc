#include "../../inc/configuration.hpp"
#include "../../inc/dirscanner.hpp"
#include "../../inc/pagelib.hpp"
#include "../../inc/webpage.hpp"
#include "../../inc/pagelibpreprocessor.hpp"

#include <time.h>

#include <iostream>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::map;
int main(int argc,char **argv)
{
    SE::Configuration conf("../conf/config.txt");
    auto confmap=conf.getConfContent();

    SE::DirScanner dirscanner(conf);
    dirscanner();

    SE::PageLib pagelib(conf,dirscanner);

    time_t start=time(nullptr);
    pagelib.create();
    pagelib.store();
    time_t end=time(nullptr);
    cout<<"the lib building takes "<<end-start<<" second"<<endl;

    SE::PageLibPreProcessor libPreprocessor(conf);
    libPreprocessor.doProcess();
    
    cout<<"离线阶段完毕"<<endl;
    return 0;
}
