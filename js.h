//-----引擎对JS相关函数的定义-----
#pragma once
#include "head.h"
#include "macro.h"

enum JSResultType {
    Ok, Error
};

typedef struct JSResult {
    enum JSResultType result;
    QVariant v;
    QString mistake;
} JSResult;

#define JS_FUNCTION Q_INVOKABLE JSVM* AddJSVM();\
                    Q_INVOKABLE JSResult JSEval(String code,String functionname=NULL_String,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE void JSSendPar(ParametersStru *Parame,String ParameName,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE void JSSendJSPar(JSParStru Parame,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE JSResult JSEvalFile(String path,String functionname=NULL_String,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE JSResult JSCallFun(String functionname,JSVM *VM=MainJSVM);\
                    Q_INVOKABLE void DeleteJSVM(JSVM *VM) {delete VM;}\
                    void InitJSSlot();
