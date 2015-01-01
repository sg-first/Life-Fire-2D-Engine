//-----本文件是对于widget.h和NewType.h中定义的新类型的成员函数的实现部分-----
#include "widget.h"

//重载图元类
void myPixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(fun==NULL || event->button()!=Qt::LeftButton)//检测图元是否是按钮、按下的是否是左键
    {return;}
    this->setPixmap(down);
}

void myPixmap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(fun==NULL)
    {return;}

    int x=this->x();
    int width=this->pixmap().width();
    int y=this->y();
    int height=this->pixmap().height();

    int xmin,ymin,xmax,ymax;
    xmin=x;
    xmax=x+width;

    if(x<0)
    {xmin=0;}
    if(x+width>WindowsWidth)
    {xmax=WindowsWidth;}

    ymin=y;
    ymax=y+height;

    if(y<0)
        ymin=0;
    if(y+height>WindowsHeigh)
        ymax=WindowsHeigh;

    if(xmax<s->mapFromGlobal(QCursor::pos()).x() || xmin>s->mapFromGlobal(QCursor::pos()).x())
    {
        this->setPixmap(up);
        return;
    }

    if(ymax<s->mapFromGlobal(QCursor::pos()).y() || ymin>s->mapFromGlobal(QCursor::pos()).y())
    {
        this->setPixmap(up);
        return;
    }

     this->setPixmap(up);
     QByteArray ba = fun.toLatin1();
     const char *function = ba.data();
     QMetaObject::invokeMethod(thob,function);
}

//视频类
VideoPlayer::VideoPlayer(QString Path,int Volume,int time,int x,int y,int width,int heigh,bool cycle,QString signfun,QGraphicsScene *scene,QWidget *parent)
    : QWidget(parent)
{
    mediaPlayer=new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVolume(Volume);
    videoItem=new QGraphicsVideoItem;
    videoItem->setSize(QSizeF(width,heigh));
    scene->addItem(videoItem);
    mediaPlayer->setVideoOutput(videoItem);
    this->time=time;
    videoItem->setPos(x,y);//设置视频位置，默认为窗口左上角
    this->cycle=cycle;
    this->Path=Path;
    this->signfun=signfun;
}

void VideoPlayer::start()
{
mediaPlayer->setMedia(QUrl::fromLocalFile(Path));
mediaPlayer->play();
this->timer=new QTimer(this);
QObject::connect(timer,SIGNAL(timeout()),SLOT(playover()));
timer->start((time+1)*1000);
}

void VideoPlayer::playover()
{
    if(cycle==false)
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
    else
    {this->start();}//循环播放
}

//SC类
void SC::RotationItem(float set)//旋转
{
    gr->setRotation(set);
    gr->rotation();
}

void SC::ScaleItem(float set)//缩放
{
    gr->setScale(set);
    gr->scale();
}

void SC::BlurRadiusItem(float set)//将一个图元变模糊
{
    Effect->setBlurRadius(set);
    gr->setGraphicsEffect(Effect);
}

void SC::SetOpacityItem(float set)//设置一个图元的透明度
{
    gr->setOpacity(set);
}

void SC::SetColorItem(float R, float G, float B)//对一个图元进行着色
{
    co->setColor(QColor(R,G,B));
    gr->setGraphicsEffect(co);
}

void SC::MoveByItem(float X, float Y)//移动一个图元
{
    gr->moveBy(X,Y);
}

void SC::changepixmap()
{
    if(iter==pixmap.end())
        iter=pixmap.begin();
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
    case 1:
    {
        temp=0;
        temp1=2*TargetModulus/times;
        timer->start(2);
        break;
    }
    case 2:
    {
        temp=0;
        temp1=2*(TargetModulus-CurrentModulus)/times;
        timer->start(2);
        break;
    }
    case 3:
    {
        temp=0;
        temp1=2*TargetModulus/times;
        temp2=2*TargetModulus2/times;
        timer->start(2);
        break;
    }
    case 4:
    {
        temp=0;
        temp1=2*TargetModulus/times;
        timer->start(3);
        break;
    }
    case 5:
    {
        temp=0;
        temp1=2*(TargetModulus-CurrentModulus)/times;
        timer->start(2);
        break;
    }
    case 6:
    {
        temp=0;
        temp1=2*(TargetModulus-CurrentModulus)/times;
        temp2=2*(TargetModulus2-CurrentModulus2)/times;
        temp3=2*(TargetModulus3-CurrentModulus3)/times;
        timer->start(2);
        break;
    }

    case 7:
    {
        iter=pixmap.begin();
        temp1=times/pixmap.size();
        timer->start(int (temp1));
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
        case 1:
        {
            temp+=2;
            RotationItem(CurrentModulus+=temp1);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 2:
        {
            temp+=2;
            ScaleItem(CurrentModulus+=temp1);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
           break;
        }
        case 3:
        {
            temp+=2;
            MoveByItem(temp1,temp2);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 4:
        {
            temp+=3;
            BlurRadiusItem(CurrentModulus+=temp1);
            if(temp==times || temp==times+1 || temp==times-1 || temp==times+2 || temp==times-2)
                over=1;
            break;
        }
        case 5:
        {
            temp+=2;
            SetOpacityItem(CurrentModulus+=temp1);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 6:
        {
            temp+=2;
            SetColorItem(CurrentModulus+=temp1,CurrentModulus2+=temp2,CurrentModulus3+=temp3);
            if(temp==times || temp==times+1 || temp==times-1)
                over=1;
            break;
        }
        case 7:
        {
            changepixmap();
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
        p.toFront();
        while(p.hasNext())
        {
            if(p.next().second==this)
            {
                p.remove();
                break;
            }
        }
        delete timer;
        delete this;
    }
}

//视图类
void graphicsview::Scale(float sx,float sy)
{scale(sx,sy);}

void graphicsview::Rotate(float set)
{rotate(set);}
