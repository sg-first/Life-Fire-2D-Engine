//-----本文件是关于maincall类中JS操作的实现-----
#include "maincall.h"

QScriptValue maincall::CallJSFile(QString path,QString functionname,ParametersStru *Parame,QString ParameName,QString mistake)
{
    QScriptEngine myengine;
    QScriptValue lib=myengine.newQObject(this);
    myengine.globalObject().setProperty("lib",lib);
    QScriptValue lfvar=myengine.newQObject(lfevent);
    myengine.globalObject().setProperty("lfvar",lfvar);

    if(Parame==NULL&&ParameName==NULL)
    {
        QScriptValue para=myengine.newQObject(Parame);
        myengine.globalObject().setProperty(ParameName,para);
    }

    /*如果想要在js中使用QT中的变量，请事先修改globalvar.h中的lfevent类，
    从其中添加您的变量，并在调用本函数前将其赋值，即可在js中使用lfvar.XX的方式使用*/

    QFile scripfile(path);
    scripfile.open(QIODevice::ReadOnly);
    QTextStream text(&scripfile);
    QString concert=text.readAll();
    scripfile.close();

    if(mistake==NULL)
    {myengine.evaluate(concert);}
    else
    {myengine.evaluate(concert,mistake);}

    if(functionname==NULL)
    {return NULL;}
    else
    {
        QScriptValue ret=myengine.globalObject().property(functionname);//准备调用JS函数
        ret.call(QScriptValue());//调用JS函数
        return ret;
    }
}


QScriptValue maincall::CallJSCode(QString code, QString functionname,ParametersStru *Parame,QString ParameName,QString mistake)
{
    QScriptEngine myengine;
    QScriptValue lib=myengine.newQObject(this);
    myengine.globalObject().setProperty("lib",lib);
    QScriptValue lfvar=myengine.newQObject(lfevent);
    myengine.globalObject().setProperty("lfvar",lfvar);

    if(Parame==NULL&&ParameName==NULL)
    {
        QScriptValue para=myengine.newQObject(Parame);
        myengine.globalObject().setProperty(ParameName,para);
    }

    /*如果想要在js中使用QT中的变量，请事先修改globalvar.h中的lfevent类，
    从其中添加您的变量，并在调用本函数前将其赋值，即可在js中使用lfvar.XX的方式使用*/

    if(mistake==NULL)
    {myengine.evaluate(code);}
    else
    {myengine.evaluate(code,mistake);}

    if(functionname==NULL)
    {return NULL;}
    else
    {
        QScriptValue ret=myengine.globalObject().property(functionname);//准备调用JS函数
        ret.call(QScriptValue());//调用JS函数
        return ret;
    }
}
