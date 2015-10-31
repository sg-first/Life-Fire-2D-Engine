//-----本文件是关于maincall类中JS操作的实现-----
#include "maincall.h"

QScriptValue maincall::CallJSFile(String path,String functionname,ParametersStru *Parame,String ParameName,String *mistake)
{
    QFile scripfile(path);
    scripfile.open(QIODevice::ReadOnly);
    QTextStream text(&scripfile);
    String concert=text.readAll();
    scripfile.close();
    return CallJSCode(concert,functionname,Parame,ParameName,mistake);
}


QScriptValue maincall::CallJSCode(String code, String functionname,ParametersStru *Parame,String ParameName,String *mistake)
{
    QScriptEngine myengine;
    QScriptValue lib=myengine.newQObject(this);
    myengine.globalObject().setProperty("lib",lib);
    QScriptValue lfvar=myengine.newQObject(lfevent);
    myengine.globalObject().setProperty("lfvar",lfvar);

    if(Parame!=nullptr&&ParameName!=nullptr)
    {
        QScriptValue para=myengine.newQObject(Parame);
        myengine.globalObject().setProperty(ParameName,para);
    }

    QScriptValue ret=myengine.evaluate(code);
    if(functionname!=NULL)
    {
        ret=myengine.globalObject().property(functionname);//准备调用JS函数
        ret.call(QScriptValue());//调用JS函数
    }

    /*if(mistake!=nullptr&&ret.isError())
    {
        *mistake=String::number(ret.property("lineNumber").toInt32())+" line:"+ret.toString();
        return NULL;
    }*/
    return ret;
}
