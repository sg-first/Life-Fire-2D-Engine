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
    item->PixmapItemPoniter->setPixmap(*iter);
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
    if(times!=-1)
    {
        if(temp==times || temp==times+1 || temp==times-1) //temp实际上是记录目前时间的
        {over=1;}
    }
}

void SC::SlowChange()
{
    if(!over)
    {
        switch(choose)
        {
        case Rotation:
        {
            temp+=2;

            if(!isfunction)
            {item->ItemPointer->setRotation(CurrentModulus+=temp1);}
            else
            {item->ItemPointer->setRotation(scfun(temp).CurrentModulus);}
            isend();
            break;
        }
        case Scale:
        {
            temp+=2;
            if(!isfunction)
            {item->ItemPointer->setScale(CurrentModulus+=temp1);}
            else
            {
                #ifdef AdaptionScale
                item->ItemPointer->setScale((scfun(temp).CurrentModulus)*adaptiveRatioX);
                #else
                item->ItemPointer->setScale(scfun(temp).CurrentModulus);
                #endif
            }
            isend();
            break;
        }
        case Move:
        {
            temp+=2;
            if(!isfunction)
            {item->ItemPointer->moveBy(temp1,temp2);}
            else
            {
                SCCurrentModulus scc=scfun(temp);
                #ifdef SelfAdaption
                scc.CurrentModulus*=adaptiveRatioX;
                scc.CurrentModulus2*=adaptiveRatioY;
                #endif
                item->ItemPointer->setPos(scc.CurrentModulus,scc.CurrentModulus2);
            }
            #ifdef AutoIsColliding
            s->itemMoveEvent();
            #endif
            isend();
            break;
        }
        case BlurRadius:
        {
            temp+=3;
            if(!isfunction)
            {s->BlurRadiusItem(item,CurrentModulus+=temp1);}
            else
            {s->BlurRadiusItem(item,scfun(temp).CurrentModulus);}
            isend();
            break;
        }
        case Opacity:
        {
            temp+=2;
            if(!isfunction)
            {item->ItemPointer->setOpacity(CurrentModulus+=temp1);}
            else
            {item->ItemPointer->setOpacity(scfun(temp).CurrentModulus);}
            isend();
            break;
        }
        case Color:
        {
            temp+=2;
            if(!isfunction)
            {s->SetRGBColorItem(item,CurrentModulus+=temp1,CurrentModulus2+=temp2,CurrentModulus3+=temp3);}
            else
            {
                SCCurrentModulus scc=scfun(temp);
                s->SetRGBColorItem(item,scc.CurrentModulus,scc.CurrentModulus2,scc.CurrentModulus3);
            }
            isend();
            break;
        }
        case Picture:
        {
            changepixmap();
            break;
        }
        case Shear:
        {
            temp+=2;
            if(!isfunction)
            {s->ShearItem(item,CurrentModulus+=temp1,CurrentModulus2+=temp2);}
            else
            {
                SCCurrentModulus scc=scfun(temp);
                s->ShearItem(item,scc.CurrentModulus,scc.CurrentModulus2);
            }
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
        {item->scPointer[choose]=nullptr;}
        delete timer;
        delete this;
    }
}
