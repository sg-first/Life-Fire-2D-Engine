//-----本文件是关于maincall类中JS操作的实现-----
#include "maincall.h"

void maincall::InitJSSlot()
{MainJSVM=AddJSVM();}

JSVM* maincall::AddJSVM()
{
    JSVM *VM=new JSVM;
    QJSValue lib=VM->newQObject(thob);
    VM->globalObject().setProperty("lib",lib);
    QJSValue lfvar=VM->newQObject(lfevent);
    VM->globalObject().setProperty("lfvar",lfvar);
    return VM;
}

JSResult maincall::JSEval(String code,String functionname,JSVM *VM)
{
    JSResult result;
    result.result = Ok;
    QJSValue ret;
    if(code!=NULL_String)
    {
        ret=VM->evaluate(code);
    }
    if(functionname!=NULL_String)
    {
        ret=VM->globalObject().property(functionname);
        ret=ret.call(QJSValueList());
    }
    if(ret.isError())
    {
        result.result = Error;
        result.mistake = ret.property("lineNumber").toString()+" line:"+ret.toString();
        return result;
    }
    result.v = ret.toVariant();
    return result;
}

void maincall::JSSendPar(ParametersStru *Parame,String ParameName,JSVM *VM) //注意，使用指针仅因迫不得已，实际创建请不要new
{
    QJSValue para=VM->newQObject(Parame);
    VM->globalObject().setProperty(ParameName,para);
}

void maincall::JSSendJSPar(JSParStru Parame,JSVM *VM)
{
    for(int i=0;i<Parame.pointerVec.length();i++)
    {
        QJSValue para=VM->newQObject(Parame.pointerVec[i]);
        VM->globalObject().setProperty(Parame.nameVec[i],para);
    }
}

JSResult maincall::JSEvalFile(String path,String functionname,JSVM *VM)
{return JSEval(ReadTXT(path),functionname,VM);}

JSResult maincall::JSCallFun(String functionname,JSVM *VM)
{return JSEval(NULL_String,functionname,VM);}
