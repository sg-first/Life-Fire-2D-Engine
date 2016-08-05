//-----本文件为手势类-----
#pragma once
#include "NewType.h"

typedef QPoint Pos;
typedef float(*LocusFunc)(int);
enum ProgressStand{XPos,YPos}; //如果使用函数表示手势，手势进程判定标准

class Gesture
{
private:
    //通用
    bool ownership;
    int tolerance;
    String event;
    //序列
    QList<Pos> posSeq;
    int progress=0;
    //方程
    LocusFunc locus=nullptr;
    ProgressStand standard;
    int maxProgress;

    void matchSuccess();
    void callEvent(int progress);

public:
    Gesture(QList<Pos> posSeq,int tolerance,String event,bool ownership):posSeq(posSeq),tolerance(tolerance),event(event),ownership(ownership){}
    Gesture(LocusFunc locus,int tolerance,ProgressStand standard,int maxProgress,String event,bool ownership):
        locus(locus),tolerance(tolerance),standard(standard),maxProgress(maxProgress),event(event),ownership(ownership){}
    bool match(Pos pos);
    bool isOwn();
    void setEvent(String event);
};

class GestureArea
{
public:
    GestureArea(int mouseX,int mouseY,int fmouseX,int fmouseY,String directDeal=NULL_String):
        mouseX(mouseX),mouseY(mouseY),fmouseX(fmouseX),fmouseY(fmouseY),directDeal(directDeal){}
    ~GestureArea();
    QList<Gesture*> allGesture;

    int mouseX;
    int mouseY;
    int fmouseX;
    int fmouseY;
    String directDeal;
};
