//-----本文件是关于maincall类中JS操作的实现-----
#include "maincall.h"

QScriptEngine* CreatEngine()
{
    QScriptEngine *myengine=new QScriptEngine;
    QScriptValue lib=myengine->newQObject(this);
    myengine->globalObject().setProperty("lib",lib);
    QScriptValue lfvar=myengine->newQObject(lfevent);
    myengine->globalObject().setProperty("lfvar",lfvar);
    return myengine;
}

QScriptValue eval(String functionname,QScriptEngine *myengine,String code)
{
    QScriptValue ret=myengine->evaluate(code);
    if(functionname!=NULL)
    {
        ret=myengine->globalObject().property(functionname);//准备调用JS函数
        ret.call(QScriptValue());//调用JS函数
    }
    delete myengine;
    return ret;
}

QScriptValue maincall::CallJSFile(String path,String functionname,ParametersStru Parame,String ParameName,String *mistake)
{
    /*QFile scripfile(path);
    scripfile.open(QIODevice::ReadOnly);
    QTextStream text(&scripfile);
    String concert=text.readAll();
    scripfile.close();*/
    String concert=ReadTXT(path);
    return CallJSCode(concert,functionname,Parame,ParameName,mistake);
}

QScriptValue maincall::CallJSFile(String path,String functionname,JSParStru Parame,String *mistake)
{
    String concert=ReadTXT(path);
    return CallJSCode(concert,functionname,Parame,mistake);
}

QScriptValue maincall::CallJSCode(String code, String functionname,ParametersStru Parame,String ParameName,String *mistake)
{
    QScriptEngine* myengine=CreatEngine();
    if(Parame!=NULLpar&&ParameName!=NULL)
    {
        QScriptValue para=myengine->newQObject(&Parame);
        myengine->globalObject().setProperty(ParameName,para);
    }
    /*if(mistake!=nullptr&&ret.isError())
    {
        *mistake=String::number(ret.property("lineNumber").toInt32())+" line:"+ret.toString();
        return NULL;
    }*/
    return eval(functionname,myengine,code);
}

QScriptValue maincall::CallJSCode(String code, String functionname,JSParStru Parame,String *mistake)
{
    QScriptEngine* myengine=CreatEngine();
    if(Parame!=NULLJSpar)
    {
        for(int i=0;i<pointerVec.length();i++)
        {
            QScriptValue para=myengine->newQObject(pointerVec[i]);
            myengine.globalObject().setProperty(nameVec[i],para);
        }
    }
    return eval(functionname,myengine,code);
}
