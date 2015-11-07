//-----本文件是关于maincall类中JS操作的实现-----
#include "maincall.h"
#include "NewType.h"

QScriptEngine* CreatEngine()
{
    QScriptEngine *myengine=new QScriptEngine;
    QScriptValue lib=myengine->newQObject(thob);
    myengine->globalObject().setProperty("lib",lib);
    QScriptValue lfvar=myengine->newQObject(lfevent);
    myengine->globalObject().setProperty("lfvar",lfvar);
    return myengine;
}

QVariant eval(String functionname,QScriptEngine *myengine,String code,String *mistake)
{
    QScriptValue ret=myengine->evaluate(code);
    if(functionname!=NULL)
    {
        ret=myengine->globalObject().property(functionname);//准备调用JS函数
        ret.call(QScriptValue());//调用JS函数
    }
    if(ret.isError())
    {
        if(mistake!=nullptr)
        {*mistake=String::number(ret.property("lineNumber").toInt32())+" line:"+ret.toString();}
        delete myengine;
        return NULL;
    }
    QVariant variant=ret.toVariant();
    delete myengine;
    return variant;
}

QVariant maincall::ParCallJSFile(String path,ParametersStru Parame,String ParameName,String functionname,String *mistake)
{
    String concert=ReadTXT(path);
    return ParCallJSCode(concert,Parame,ParameName,functionname,mistake);
}

QVariant maincall::JSParCallJSFile(String path,JSParStru Parame,String functionname,String *mistake)
{
    String concert=ReadTXT(path);
    return JSParCallJSCode(concert,Parame,functionname,mistake);
}

QVariant maincall::ParCallJSCode(String code,ParametersStru Parame,String ParameName,String functionname,String *mistake)
{
    QScriptEngine* myengine=CreatEngine();
    QScriptValue para=myengine->newQObject(&Parame);
    myengine->globalObject().setProperty(ParameName,para);
    return eval(functionname,myengine,code,mistake);
}

QVariant maincall::JSParCallJSCode(String code,JSParStru Parame,String functionname,String *mistake)
{
    QScriptEngine* myengine=CreatEngine();
    for(int i=0;i<Parame.pointerVec.length();i++)
    {
        QScriptValue para=myengine->newQObject(Parame.pointerVec[i]);
        myengine->globalObject().setProperty(Parame.nameVec[i],para);
    }
    return eval(functionname,myengine,code,mistake);
}

QVariant maincall::CallJSCode(String code, String functionname,String *mistake)
{
    QScriptEngine* myengine=CreatEngine();
    return eval(functionname,myengine,code,mistake);
}

QVariant maincall::CallJSFile(String path, String functionname,String *mistake)
{
    String concert=ReadTXT(path);
    return CallJSCode(concert,functionname,mistake);
}
