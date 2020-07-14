#include "../../inc/mylog4cpp.hpp"

mylog* mylog::_pinst=nullptr;
mylog::autorelease mylog::ar;

mylog * mylog::getInst()
{
    if(nullptr==_pinst)
        _pinst=new mylog();
    return _pinst;
}
void mylog::destroyInst()
{
    if(_pinst)
    {
        delete _pinst;
        _pinst=nullptr;
    }
}
void initlog(Category &r)
{
    PatternLayout *ppl1=new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2=new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");
    OstreamAppender *poa=new OstreamAppender("OstreamAppender",&cout);
    poa->setLayout(ppl1);

    RollingFileAppender *prfa=new RollingFileAppender("FileAppender1",
                                                      "../log/mylog",5*1024,10);
    prfa->setLayout(ppl2);
    
    r.addAppender(poa);
    r.addAppender(prfa);
    r.setPriority(Priority::DEBUG);

}


mylog::mylog()
:root(Category::getRoot().getInstance("h3rwau"))
{
    initlog(root);
    // cout<<"mylog()"<<endl;
}
mylog::~mylog()
{
    // cout << "~mylog()" << endl;
}
void mylog::warn(const  char * msg)
{
    root.warn(msg);
}
void mylog::error(const  char * msg)
{
    root.error(msg);
}
void mylog::debug(const  char * msg)
{
    root.debug(msg);
}
void mylog::info(const  char * msg)
{
    root.info(msg);
}


