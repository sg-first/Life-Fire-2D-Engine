//-----本文件是键盘事件的响应-----
#include "widget.h"

void Widget::keyPressEvent(QKeyEvent *e)//键盘事件响应
{
    for(int i;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==e->key())
        {RunSignFun(AllEvent[i]->signfun,AllEvent[i]->par);}
    }
}

void Widget::mousePressEvent(QMouseEvent *e)//鼠标事件响应
{
    for(int i;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->MouseX==e->x()&&AllEvent[i]->MouseY==e->y())
        {RunSignFun(AllEvent[i]->signfun,AllEvent[i]->par);}
    }
}
