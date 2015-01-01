//-----本文件是游戏中的一些函数调用的实现，引擎的三层封装-----
#pragma once
#include "library.h"

class maincall : public library
{
Q_OBJECT

public:
    //对js的处理函数
    Q_INVOKABLE void CallJs(QString path);
    Q_INVOKABLE void CallJsFunction(QString path,QString functionss);
	void StartGame();
	//在此继续添加
	
	
public slots:
    //此处容纳事件处理与线程函数

};
