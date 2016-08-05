//-----本文件是键盘事件的响应-----
#include "widget.h"

void Widget::keyPressEvent(QKeyEvent *e)//键盘事件响应
{
    for(auto i:AllEvent)
    {
        if(i.key==e->key())
        {
            RunFun(i.PressFun,i.PressPar);
            return;
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *e)//鼠标事件响应
{
    for(auto i:AllEvent)
    {
        if(i.MouseX<=e->x()&&i.MouseY<=e->y()&&i.fMouseY>=e->y()&&i.fMouseX>=e->x())
        {RunFun(i.PressFun,i.PressPar);}
    }
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    for(auto i:AllEvent)
    {
        if(i.key==e->key())
        {
            RunFun(i.ReleaseFun,i.ReleasePar);
            return;
        }
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    for(auto i:AllEvent)
    {
        if(i.MouseX<=e->x()&&i.MouseY<=e->y()&&i.fMouseY>=e->y()&&i.fMouseX>=e->x())
        {RunFun(i.ReleaseFun,i.ReleasePar);}
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{

}
