//-----本文件是键盘事件的响应-----
#include "widget.h"

void Widget::keyPressEvent(QKeyEvent *e)//键盘事件响应
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==e->key())
        {
            RunFun(AllEvent[i]->slotfun,AllEvent[i]->par);
            return;
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *e)//鼠标事件响应
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->MouseX<=e->x()&&
           AllEvent[i]->MouseY<=e->y()&&
           AllEvent[i]->fMouseY>=e->y()&&
           AllEvent[i]->fMouseX>=e->x())
        {RunFun(AllEvent[i]->slotfun,AllEvent[i]->par);}
    }
}
