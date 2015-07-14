//-----本文件是键盘事件的响应-----
#include "widget.h"

void Widget::keyPressEvent(QKeyEvent *e)//键盘事件响应
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==e->key())
        {
            RunSignFun(AllEvent[i]->signfun,AllEvent[i]->par);
            return;
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *e)//鼠标事件响应
{
    vector <InputEvent*> event;
    for(int i=0;i<AllEvent.length();i++)
    {
        if(e->x()>=AllEvent[i]->MouseX&&
           e->y()>=AllEvent[i]->MouseY&&
           e->x()<=AllEvent[i]->fMouseX&&
           e->y()<=AllEvent[i]->fMouseY)
        {event.push_back(AllEvent[i]);}
    }
    if(!event.empty())
    {
        bool(*fun)(InputEvent*,InputEvent*)=[](InputEvent* a,InputEvent* b){return a->layout>b->layout;};
        sort(event.begin(),event.end(),fun);
        RunSignFun(event.at(0)->signfun,event.at(0)->par);
    }
}
