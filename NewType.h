//-----本文件所声明用于引擎的其它类型-----
#pragma once
#include "head.h"

#define FIRST1 QTimer*
//t
#define OVER1 =new QTimer;
#define FIRST2 QEventLoop*
//q
#define OVER2 =new QEventLoop;
//t
#define FIRSTOVER3 ->setSingleShot(true);
//connect(lfevent,SIGNAL(ff()),q,SLOT(quit()));
//connect(t,SIGNAL(timeout()),q,SLOT(quit()));

//t
#define FFIRSTOVER1 ->start();
//q
#define FFIRSTOVER2 ->exec();
//t
#define FDelFITST delete
//t/q
#define FDelOVER ;

//t
#define TFFIRST1 ->start(
//MS
#define TFOVER1 );


class Widget;
class SC : public QObject//渐变使用的工具类
{
    Q_OBJECT
public:
    SC(float CurrentModulus,float TargetModulus,int times,
       QMutableListIterator<QPair<int,SC *> > p
       ):CurrentModulus(CurrentModulus),
        TargetModulus(TargetModulus),times(times),p(p){}//这个构造方法处理单渐变系数
    SC(float CurrentModulus,float CurrentModulus2,float TargetModulus,float TargetModulus2,
       int times,
       QMutableListIterator<QPair<int,SC *> > p
       ):CurrentModulus(CurrentModulus),CurrentModulus2(CurrentModulus2),
        TargetModulus(TargetModulus),TargetModulus2(TargetModulus2),times(times),p(p){}//这个构造方法处理双渐变系数
    SC(float CurrentModulus,float CurrentModulus2,float CurrentModulus3,float TargetModulus,
       float TargetModulus2,float TargetModulus3,int times,
       QMutableListIterator<QPair<int,SC *> > p
       ):CurrentModulus(CurrentModulus),
        CurrentModulus2(CurrentModulus2),CurrentModulus3(CurrentModulus3),TargetModulus(TargetModulus),
        TargetModulus2(TargetModulus2),TargetModulus3(TargetModulus3),times(times),p(p){}//这个构造方法处理三渐变系数

    QGraphicsItem* gr;
    QGraphicsBlurEffect *Effect;
    QGraphicsColorizeEffect *co;
    QGraphicsPixmapItem *pi;
    QVector<QPixmap> pixmap;
    QString signfun;
    int over;//结束标志
    void start(int choose);
    bool cycle;//连续播图是否循环播放
    int num;//动画在图元管理器中的序号

protected:
    float CurrentModulus;//当前系数
    float CurrentModulus2;//当前系数2（处理多系数变化,下同）
    float CurrentModulus3;//当前系数3
    float TargetModulus;//目标系数1
    float TargetModulus2;//目标系数2
    float TargetModulus3;//目标系数3
    int times;//变化所需【总】时间,单位：毫秒
    QTimer *timer;//计时器
    QMutableListIterator<QPair<int,SC *> > p;
    int choose;//start()函数的参数
    float temp;//临时变量，在某些特殊情况下用于各个函数之间通信使用
    float temp1;//临时变量，在某些特殊情况下用于各个函数之间通信使用
    float temp2;//临时变量，在某些特殊情况下用于各个函数之间通信使用
    float temp3;//临时变量，在某些特殊情况下用于各个函数之间通信使用

    //旋转                         choose==1
    //缩放                          choose==2
    //相对移动一个图元                 chose==3
    //将一个图元变模糊                 choose==4
    //设置一个图元的透明度              choose==5
    //在一个图元基础上进行着色           choose==6
    void changepixmap();//Gif改变图元  choose==7
    QVector<QPixmap>::iterator iter;

private slots:
    void SlowChange();
};


class myPixmap : public QGraphicsPixmapItem//重载图元类
{
public:
    myPixmap(QGraphicsItem *parent = 0):QGraphicsPixmapItem::QGraphicsPixmapItem(parent){}
    myPixmap(const QPixmap &pixmap, QGraphicsItem *parent = 0)
        :QGraphicsPixmapItem::QGraphicsPixmapItem(pixmap,parent){}
    QPixmap up;
    QString fun;
    QPixmap down;
    Widget *s;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //允许在此添加更多类型的事件，或许你需要添加一些公有成员变量来记录其所对应的槽函数
};


class VideoPlayer : public QWidget //视频类
{
    Q_OBJECT
public:
    VideoPlayer(QString Path,int Volume, int x, int y,int width,int heigh,bool cycle,QString signfun,QGraphicsScene *scene,QWidget *parent = 0);
    ~VideoPlayer();
    void start();
    QMediaPlayer *mediaPlayer;
    QString signfun;

private:
    QGraphicsVideoItem *videoItem;
    bool cycle;
    QString Path;

private slots:
    void playover(QMediaPlayer::State state);
};


class graphicsview : public QGraphicsView//重载视图类
{
public:
    graphicsview(QWidget *parent):QGraphicsView(parent){}
    void Scale(float sx, float sy);
    void Rotate(float set);

protected:
    void wheelEvent(QWheelEvent *event){}
};
