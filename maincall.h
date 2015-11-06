//-----本文件是游戏中的一些函数调用的实现，引擎的三层封装-----
#pragma once
#include "library.h"
#include "js.h"

class maincall : public library
{
Q_OBJECT
public:
    JS_FUNCTION//关于JS操作
    //入口函数
    void StartGame();
    //在此继续添加
	
	
public slots:
    //此处容纳事件处理与线程函数


};
