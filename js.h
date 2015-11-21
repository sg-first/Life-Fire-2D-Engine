//-----引擎对JS相关函数的定义-----
#pragma once
#include "macro.h"

#define JS_FUNCTION Q_INVOKABLE QVariant ParCallJSFile(String path,ParametersStru Parame,String ParameName,String functionname=NULL_String,String *mistake=nullptr);\
                    Q_INVOKABLE QVariant ParCallJSCode(String code,ParametersStru Parame,String ParameName,String functionname=NULL_String,String *mistake=nullptr);\
                    Q_INVOKABLE QVariant JSParCallJSFile(String path,JSParStru Parame,String functionname=NULL_String,String *mistake=nullptr);\
                    Q_INVOKABLE QVariant JSParCallJSCode(String code,JSParStru Parame,String functionname=NULL_String,String *mistake=nullptr);\
                    Q_INVOKABLE QVariant CallJSCode(String code, String functionname=NULL_String,String *mistake=nullptr);\
                    Q_INVOKABLE QVariant CallJSFile(String path, String functionname=NULL_String,String *mistake=nullptr);
