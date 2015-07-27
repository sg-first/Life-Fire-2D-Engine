//-----本文件是SC类成员函数的实现部分-----
#include "widget.h"

void SC::changepixmap()
{
    if(iter==pixmap.end())
    {
        if(cycle)
        {iter=pixmap.begin();}//若需循环，就重播
        else//若不循环，发信号退出一切
        {
            this->over=1;
            if(signfun!=NULL)
            {RunFun(signfun,par);}
            return;
        }
    }
    //若未播完，正常换图
    pi->setPixmap(*iter);
    ++iter;
}

void SC::start(int choose)
{
    this->choose=choose;
    timer=new QTimer(this);
    over=0;
    switch(choose)
    {
        case 0:
        {
            temp=0;
            temp1=2*TargetModulus/times;
            timer->start(2);
            break;
        }
        case 1:
        {
            temp=0;
            temp1=2*(TargetModulus-CurrentModulus)/times;
            timer->start(2);
            break;
        }
        case 2:
        {
            temp=0;
            temp1=2*TargetModulus/times;
            temp2=2*TargetModulus2/times;
            timer->start(2);
            break;
        }
        case 3:
        {
            temp=0;
            temp1=2*TargetModulus/times;
            timer->start(3);
            break;
        }
        case 4:
        {
            temp=0;
            temp1=2*(TargetModulus-CurrentModulus)/times;
            timer->start(2);
            break;
        }
        case 5:
        {
            temp=0;
            temp1=2*(TargetModulus-CurrentModulus)/times;
            temp2=2*(TargetModulus2-CurrentModulus2)/times;
            temp3=2*(TargetModulus3-CurrentModulus3)/times;
            timer->start(2);
            break;
        }
        case 6:
        {
            iter=pixmap.begin();//将装满连帧图元的迭代器调到头元素
            temp1=times/pixmap.size();//计算出播放每一帧需要的时间
            timer->start(int(temp1));//根据此时间开始播放
            break;
        }
        case 7:
        {
            temp=0;
            temp1=2*(TargetModulus-CurrentModulus)/times;
            temp2=2*(TargetModulus2-CurrentModulus2)/times;
            timer->start(2);
            break;
        }

    }
    connect(timer,SIGNAL(timeout()),this,SLOT(SlowChange()));
}

void SC::SlowChange()
{
    if(!over)
    {
        switch(choose)
        {
        case 0:
        {
            temp+=2;
            gr->setRotation(CurrentModulus+=temp1);
            gr->rotation();
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 1:
        {
            temp+=2;
            gr->setScale(CurrentModulus+=temp1);
            gr->scale();
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
           break;
        }
        case 2:
        {
            temp+=2;
            gr->moveBy(temp1,temp2);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 3:
        {
            temp+=3;
            Effect->setBlurRadius(CurrentModulus+=temp1);
            gr->setGraphicsEffect(Effect);
            if(temp==times || temp==times+1 || temp==times-1 || temp==times+2 || temp==times-2)
                over=1;
            break;
        }
        case 4:
        {
            temp+=2;
            gr->setOpacity(CurrentModulus+=temp1);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 5:
        {
            temp+=2;
            co->setColor(QColor(CurrentModulus+=temp1,CurrentModulus2+=temp2,CurrentModulus3+=temp3));
            gr->setGraphicsEffect(co);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 6:
        {
            changepixmap();
            break;
        }
        case 7:
        {
            temp+=2;
            tf=new QTransform;
            tf->shear(CurrentModulus+=temp1,CurrentModulus2+=temp2);
            gr->setTransform(*tf);
            delete tf;
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        }
    }
    if(over)
    {
       if(signfun!=NULL)
       {
         QByteArray ba = signfun.toLatin1();
         const char *function = ba.data();
         QMetaObject::invokeMethod(lfevent,function);
       }
       delete timer;
       delete this;
    }
}
