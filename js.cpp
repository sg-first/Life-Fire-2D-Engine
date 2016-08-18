//-----本文件是关于maincall类中JS操作的实现-----
#include "maincall.h"

void maincall::InitJSSlot()
{MainJSVM=AddJSVM();}

JSVM* maincall::AddJSVM()
{
    JSVM *VM=new JSVM;
    QScriptValue lib=VM->newQObject(thob);
    VM->globalObject().setProperty("lib",lib);
    QScriptValue lfvar=VM->newQObject(lfevent);
    VM->globalObject().setProperty("lfvar",lfvar);
    return VM;
}

Variant maincall::JSEval(String code,String functionname,String *mistake,JSVM *VM)
{
    QScriptValue ret;
    if(code!=NULL_String)
    {ret=VM->evaluate(code);}
    if(functionname!=NULL_String)
    {
        ret=VM->globalObject().property(functionname);
        ret.call(QScriptValue());
    }
    if(ret.isError())
    {
        if(mistake!=nullptr)
        {*mistake=String::number(ret.property("lineNumber").toInt32())+" line:"+ret.toString();}
        return NULL;
    }
    return ret.toVariant();
}

void maincall::JSSendPar(ParametersStru Parame,String ParameName,JSVM *VM)
{
    QScriptValue para=VM->newQObject(&Parame);
    VM->globalObject().setProperty(ParameName,para);
}

void maincall::JSSendJSPar(JSParStru Parame,JSVM *VM)
{
    for(int i=0;i<Parame.pointerVec.length();i++)
    {
        QScriptValue para=VM->newQObject(Parame.pointerVec[i]);
        VM->globalObject().setProperty(Parame.nameVec[i],para);
    }
}

Variant maincall::JSEvalFile(String path,String functionname,String *mistake,JSVM *VM)
{return JSEval(ReadTXT(path),functionname,mistake,VM);}

Variant maincall::JSCallFun(String functionname,String *mistake,JSVM *VM)
{return JSEval(NULL_String,functionname,mistake,VM);}
