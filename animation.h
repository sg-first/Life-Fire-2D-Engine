#pragma once
#include "reimplemen.h"

struct SCCurrentModulus
{
    float CurrentModulus;
    float CurrentModulus2;
    float CurrentModulus3;
};

typedef std::function<SCCurrentModulus(int)> SCFun;//SC系数获取函数使用的函数指针

class SC : public QObject//渐变使用的工具类
{
    Q_OBJECT
public:
    SC(float CurrentModulus,float TargetModulus,int times,Item* item,String signfun,Widget *s)
        :CurrentModulus(CurrentModulus),
          TargetModulus(TargetModulus),
          times(times),item(item),signfun(signfun),s(s){}
    SC(float CurrentModulus,float CurrentModulus2,float TargetModulus,float TargetModulus2,int times,Item* item,String signfun,Widget *s)
        :CurrentModulus(CurrentModulus),CurrentModulus2(CurrentModulus2),
        TargetModulus(TargetModulus),TargetModulus2(TargetModulus2),
        times(times),item(item),signfun(signfun),s(s){}
    SC(float CurrentModulus,float CurrentModulus2,float TargetModulus,float TargetModulus2,int times,GraphicsView *gv,String signfun,Widget *s)
        :CurrentModulus(CurrentModulus),CurrentModulus2(CurrentModulus2),
        TargetModulus(TargetModulus),TargetModulus2(TargetModulus2),
        times(times),gv(gv),signfun(signfun),s(s){} //另一个双系数，处理镜头动画
    SC(float CurrentModulus,float CurrentModulus2,float CurrentModulus3,
       float TargetModulus,float TargetModulus2,float TargetModulus3,int times,Item* item,String signfun,Widget *s)
        :CurrentModulus(CurrentModulus),CurrentModulus2(CurrentModulus2),CurrentModulus3(CurrentModulus3),
         TargetModulus(TargetModulus),TargetModulus2(TargetModulus2),TargetModulus3(TargetModulus3),
         times(times),item(item),signfun(signfun),s(s){}
    void UesSCFun(SCFun scfun);

    QVector<QPixmap> pixmap;
    ParametersStru par;
    bool over;//结束标志
    void start(int choose);
    bool cycle;//连续播图是否循环播放
    int choose;//start()函数的参数

protected:
    float CurrentModulus;//当前系数
    float CurrentModulus2;//当前系数2（处理多系数变化,下同）
    float CurrentModulus3;//当前系数3
    float TargetModulus;//目标系数1
    float TargetModulus2;//目标系数2
    float TargetModulus3;//目标系数3
    int times;//变化所需总时间

    Item* item;
    GraphicsView *gv;
    String signfun;
    Widget *s;

    Timer *timer;//计时器
    float temp;//临时变量，在某些特殊情况下用于各个函数之间通信使用
    float temp1;//临时变量，在某些特殊情况下用于各个函数之间通信使用
    float temp2;//临时变量，在某些特殊情况下用于各个函数之间通信使用
    float temp3;//临时变量，在某些特殊情况下用于各个函数之间通信使用

    void changepixmap();//Gif改变图元  choose==7
    void isend();//判断动画是否结束
    QVector<QPixmap>::iterator iter;

    //使用函数获取系数的部分
    bool isfunction=false;//是否使用函数获取渐变系数
    SCFun scfun;

private slots:
    void SlowChange();
};
