//-----本文件是对于NewType.h中定义的新类型的成员函数的实现部分-----
#include "widget.h"

//重载图元类
void MyPixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(fun==NULL || event->button()!=Qt::LeftButton)//检测图元是否是按钮、按下的是否是左键
    {return;}
    this->setPixmap(down);
}

void MyPixmap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
VideoPlayer::VideoPlayer(QString Path,int Volume,int x,int y,int width,int heigh,bool cycle,QString signfun,QGraphicsScene *scene,QWidget *parent)
    : QWidget(parent)
{
    mediaPlayer=new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVolume(Volume);
    videoItem=new QGraphicsVideoItem;
    videoItem->setSize(QSizeF(width,heigh));
    scene->addItem(videoItem);
    mediaPlayer->setVideoOutput(videoItem);
    videoItem->setPos(x,y);//设置视频位置，默认为窗口左上角
    this->cycle=cycle;
    this->Path=Path;
    this->signfun=signfun;
}

void VideoPlayer::start()
{
mediaPlayer->setMedia(QUrl::fromLocalFile(Path));
mediaPlayer->play();
QObject::connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playover(QMediaPlayer::State)));
}

void VideoPlayer::playover(QMediaPlayer::State state)
{
    if(state!=QMediaPlayer::StoppedState)
    {return;}
    if(!cycle)
    {
        if(signfun!=NULL)
        {
         QByteArray ba = signfun.toLatin1();
         const char *function = ba.data();
         QMetaObject::invokeMethod(lfevent,function);
        }
    delete this;
    }
    else
    {mediaPlayer->play();}
}

VideoPlayer::~VideoPlayer()
{
    delete mediaPlayer;
    delete videoItem;
}

//视图类
void GraphicsView::Scale(float sx,float sy)
{scale(sx,sy);}

void GraphicsView::Rotate(float set)
{rotate(set);}

//线程类
void EasyThread::run()
{
    QByteArray ba = fun.toLatin1();
    const char *function = ba.data();
    if(par!=NULL)
    {QMetaObject::invokeMethod(thob,function,Qt::DirectConnection,Q_ARG(ParametersStru,*par));}
    else
    {QMetaObject::invokeMethod(thob,function,Qt::DirectConnection);}
}
