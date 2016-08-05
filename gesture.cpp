#include "gesture.h"

#define isLocusFunc this->locus!=nullptr

void Gesture::setEvent(String event)
{this->event=event;}

bool Gesture::isOwn()
{return this->ownership;}

void Gesture::callEvent(int progress)
{
    ParametersStru par;
    par.intVar<<progress;
    RunFun(this->event,par);
}

void Gesture::matchSuccess()
{
    this->callEvent(progress);
    if(progress==this->posSeq.length()-1)
    {progress=0;}
    else
    {progress++;}
    return;
}

bool Gesture::match(Pos pos)
{
    if(isLocusFunc)
    {
        if(this->standard==XPos) //以X作为进程判定标准，则X是准的
        {
            if(pos.x()>=0&&pos.x()<=maxProgress) //先看X出没出规定的边界
            {
                float y=this->locus(pos.x());
                if(pos.y()<=y+tolerance&&pos.y()>=y-tolerance) //看看Y是不是在可以容忍的错误范围内
                {
                    this->callEvent(progress);
                    return true;
                }
            }
        }
        if(this->standard==YPos) //以Y作为进程判定标准，则Y是准的
        {
            if(pos.y()>=0&&pos.y()<=maxProgress) //先看Y出没出规定的边界
            {
                float x=this->locus(pos.y()); //注意，如果以Y为判定标准传入的函数应当计算X
                if(pos.x()<=x+tolerance&&pos.x()>=x-tolerance) //看看X是不是在可以容忍的错误范围内
                {
                    this->callEvent(progress);
                    return true;
                }
            }
        }
    }
    else
    {
        if(pos.x()<=this->posSeq[progress].x()+tolerance
                && pos.y()<=this->posSeq[progress].y()+tolerance
                && pos.y()>=this->posSeq[progress].y()-tolerance
                && pos.x()>=this->posSeq[progress].x()-tolerance)
        {
            matchSuccess();
            return true;
        }

    }
    //两个都不在范围内，匹配失败
    progress=0;
    return false;
}


GestureArea::~GestureArea()
{
    for(Gesture* i:this->allGesture)
    {
        if(i->isOwn())
        {delete i;}
    }
}
