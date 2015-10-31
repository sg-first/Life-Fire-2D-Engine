//-----本文件是游戏中的一些函数调用的实现，引擎的三层封装-----
#pragma once
#include "library.h"

class maincall : public library
{
Q_OBJECT
public:
    //关于JS操作
    Q_INVOKABLE QScriptValue CallJSFile(String path,String functionname=NULL,ParametersStru *Parame=nullptr,String ParameName=NULL,String *mistake=nullptr);
    Q_INVOKABLE QScriptValue CallJSCode(String code,String functionname=NULL,ParametersStru *Parame=nullptr,String ParameName=NULL,String *mistake=nullptr);
    //入口函数
    void StartGame();
    //在此继续添加
	
	
public slots:
    //此处容纳事件处理与线程函数


};
