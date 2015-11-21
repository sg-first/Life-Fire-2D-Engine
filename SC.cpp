//-----本文件是SC类成员函数的实现部分-----
#include "widget.h"

void SC::UesSCFun(SCFun scfun)
{
    this->scfun=scfun;
    this->isfunction=true;
}

void SC::changepixmap()
{
    if(iter==pixmap.end())
    {
        if(cycle)
        {iter=pixmap.begin();}//若需循环，就重播
        else//若不循环，发信号退出一切
        {
            this->over=1;
            if(signfun!=NULL_String)
            {
              QByteArray ba = signfun.toLatin1();
              const char *function = ba.data();
              QMetaObject::invokeMethod(lfevent,function);
            }
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
            temp1=2*(TargetModulus-CurrentModulus)/times;
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
            temp1=2*(TargetModulus-CurrentModulus)/times;
            temp2=2*(TargetModulus2-CurrentModulus2)/times;
            timer->start(2);
            break;
        }
        case 3:
        {
            temp=0;
            temp1=3*(TargetModulus-CurrentModulus)/times;
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
        case 20:
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

void SC::isend()
{
    if(temp==times || temp==times+1 || temp==times-1)
        over=1;
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
            if(!isfunction)
            {gr->setRotation(CurrentModulus+=temp1);}
            else
            {gr->setRotation(scfun(temp).CurrentModulus);}
            gr->rotation();
            isend();
            break;
        }
        case 1:
        {
            temp+=2;
            if(!isfunction)
            {gr->setScale(CurrentModulus+=temp1);}
            else
            {gr->setScale(scfun(temp).CurrentModulus);}
            gr->scale();
            isend();
            break;
        }
        case 2:
        {
            temp+=2;
            if(!isfunction)
            {gr->moveBy(temp1,temp2);}
            else
            {
                SCCurrentModulus scc=scfun(temp);
                gr->setPos(scc.CurrentModulus,scc.CurrentModulus2);
            }
            isend();
            break;
        }
        case 3:
        {
            temp+=3;
            if(!isfunction)
            {Effect->setBlurRadius(CurrentModulus+=temp1);}
            else
            {Effect->setBlurRadius(scfun(temp).CurrentModulus);}
            gr->setGraphicsEffect(Effect);
            isend();
            break;
        }
        case 4:
        {
            temp+=2;
            if(!isfunction)
            {gr->setOpacity(CurrentModulus+=temp1);}
            else
            {gr->setOpacity(scfun(temp).CurrentModulus);}
            isend();
            break;
        }
        case 5:
        {
            temp+=2;
            if(!isfunction)
            {co->setColor(QColor(CurrentModulus+=temp1,CurrentModulus2+=temp2,CurrentModulus3+=temp3));}
            else
            {
                SCCurrentModulus scc=scfun(temp);
                co->setColor(QColor(scc.CurrentModulus,scc.CurrentModulus2,scc.CurrentModulus3));
            }
            gr->setGraphicsEffect(co);
            isend();
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
            float shearX;
            float shearY;
            if(!isfunction)
            {
                shearX=CurrentModulus+=temp1;
                shearY=CurrentModulus2+=temp2;
                tf->shear(shearX,shearY);
                num->ShearX=shearX;
                num->ShearY=shearY;
            }
            else
            {
                SCCurrentModulus scc=scfun(temp);
                tf->shear(scc.CurrentModulus,scc.CurrentModulus2);
                num->ShearX=scc.CurrentModulus;
                num->ShearY=scc.CurrentModulus2;
            }
            gr->setTransform(*tf);
            delete tf;
            isend();
            break;
        }
        case 20:
        {
            temp+=2;
            if(!isfunction)
            {gv->SetCenter(CurrentModulus+=temp1,CurrentModulus2+=temp2);}
            else
            {
                SCCurrentModulus scc=scfun(temp);
                gv->SetCenter(scc.CurrentModulus,scc.CurrentModulus2);
            }
            isend();
            break;
        }
        }
    }
    if(over)
    {
       if(signfun!=NULL_String)
       {
         QByteArray ba = signfun.toLatin1();
         const char *function = ba.data();
         QMetaObject::invokeMethod(lfevent,function);
       }
       if(choose!=20)
       {num->scPointer[choose]=nullptr;}
       delete timer;
       delete this;
    }
}
