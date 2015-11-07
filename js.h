//-----引擎对JS相关函数的定义-----
#pragma once

#define JS_FUNCTION Q_INVOKABLE QScriptValue ParCallJSFile(String path,ParametersStru Parame,String ParameName,String functionname=NULL,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue ParCallJSCode(String code,ParametersStru Parame,String ParameName,String functionname=NULL,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue JSParCallJSFile(String path,JSParStru Parame,String functionname=NULL,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue JSParCallJSCode(String code,JSParStru Parame,String functionname=NULL,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue CallJSCode(String code, String functionname=NULL);\
                    Q_INVOKABLE QScriptValue CallJSFile(String path, String functionname=NULL);
