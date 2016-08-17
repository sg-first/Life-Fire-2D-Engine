//-----本文件为手势类-----
#pragma once
#include "basics.h"

typedef QPoint Pos;
typedef float(*LocusFunc)(int);
enum ProgressStand{XPos,YPos}; //如果使用函数表示手势，指定手势进程判定标准

class Gesture
{
private:
    //序列
    QList<Pos> posSeq;
    int progress=-1;
    //方程
    LocusFunc locus=nullptr;
    ProgressStand standard;
    int maxProgress;
    //通用
    int tolerance;
    String event;
    bool ownership;
    //运行时
    Pos firstPos;

    void matchSuccess();
    void callEvent(int progress);

public:
    Gesture(QList<Pos> posSeq,int tolerance,String event,bool ownership):posSeq(posSeq),tolerance(tolerance),event(event),ownership(ownership){}
    Gesture(LocusFunc locus,ProgressStand standard,int maxProgress,int tolerance,String event,bool ownership):
        locus(locus),standard(standard),maxProgress(maxProgress),tolerance(tolerance),event(event),ownership(ownership){}
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
