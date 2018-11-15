//-----引擎对JS相关函数的定义-----
#pragma once
#include "macro.h"

#define JS_FUNCTION Q_INVOKABLE JSVM* AddJSVM();\
                    Q_INVOKABLE Variant JSEval(String code,String functionname=NULL_String,String *mistake=nullptr,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE void JSSendPar(ParametersStru *Parame,String ParameName,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE void JSSendJSPar(JSParStru Parame,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE Variant JSEvalFile(String path,String functionname=NULL_String,String *mistake=nullptr,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE Variant JSCallFun(String functionname,String *mistake=nullptr,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE void DeleteJSVM(JSVM *VM) {delete VM;}\
                    void InitJSSlot();
