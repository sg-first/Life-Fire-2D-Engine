//-----引擎对JS相关函数的定义-----QScriptValue CallJSCode(String code,String functionname=NULL,ParametersStru *Parame=nullptr,String ParameName=NULL,String *mistake=nullptr);\


#define JS_FUNCTION Q_INVOKABLE QScriptValue CallJSFile(String path,String functionname=NULL,ParametersStru Parame=NULLpar,String ParameName=NULL,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue CallJSCode(String code,String functionname=NULL,ParametersStru Parame=NULLpar,String ParameName=NULL,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue CallJSFile(String path,String functionname=NULL,JSParStru Parame=NULLJSpar,String *mistake=nullptr);\
                    Q_INVOKABLE QScriptValue CallJSCode(String code, String functionname=NULL,JSParStru Parame=NULLJSpar,String *mistake=nullptr);