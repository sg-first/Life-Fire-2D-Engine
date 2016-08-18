//-----本文件是键盘事件的响应-----
#include "widget.h"
#include "configure.h"

void Widget::PassMousePressEvent(Pos point)
{
    QMouseEvent e(QEvent::Type::MouseButtonPress,point,Qt::MouseButton::LeftButton,nullptr,nullptr);
    this->mousePressEvent(&e);
}

void Widget::PassMouseReleaseEvent(Pos point)
{
    QMouseEvent e(QEvent::Type::MouseButtonRelease,point,Qt::MouseButton::LeftButton,nullptr,nullptr);
    this->mouseReleaseEvent(&e);
}

void Widget::PassMouseMoveEvent(QMouseEvent *e)
{this->mouseMoveEvent(e);}

void Widget::keyPressEvent(QKeyEvent *e)//键盘事件响应
{
    for(InputEvent &i:AllEvent)
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
    for(InputEvent &i:AllEvent)
    {
        if(i.mouseX<=e->x()&&i.mouseY<=e->y()&&i.fmouseY>=e->y()&&i.fmouseX>=e->x())
        {RunFun(i.PressFun,i.PressPar);}
    }
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    for(InputEvent &i:AllEvent)
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
    for(InputEvent &i:AllEvent)
    {
        if(i.mouseX<=e->x()&&i.mouseY<=e->y()&&i.fmouseY>=e->y()&&i.fmouseX>=e->x())
        {RunFun(i.ReleaseFun,i.ReleasePar);}
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    for(GestureArea* gesarea:AllGestureArea)
    {
        for(Gesture* ges:gesarea->allGesture)
        {ges->match(e->pos());}
    }
}

#ifdef AutoIsColliding
void Widget::itemMoveEvent()
{
    for(Collision &co:AllAutoCollision)
    {
        if(ItemColliding(co.item1,co.item2))
        {RunFun(co.slot,co.par);}
    }
}
#endif
