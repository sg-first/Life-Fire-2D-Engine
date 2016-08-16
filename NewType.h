//-----本文件所声明用于引擎的其它类型-----
#pragma once
#include "head.h"
#include "macro.h"

class Widget;
class Item;
class GraphicsView;
class VideoPlayer;
class CaluThread;
class ParametersStru;
class JSParStru;
class MusicPlayer;

typedef QPixmap Pixmap;
typedef QColor RGBColor;
typedef QString String;
typedef QGraphicsScene GraphicsScene;
typedef QVariant Variant;
typedef QTimer Timer;
typedef std::function<void(ParametersStru)> ParSlot;
typedef std::function<void()> VoidSlot;
typedef Qt::ConnectionType ExecutionMode;

enum AnimationType{Rotation,Scale,Move,BlurRadius,Opacity,Color,Picture,Shear};

class ParametersStru : public QObject
{
    Q_OBJECT
public:
    ParametersStru(const ParametersStru&);
    ParametersStru(){}

    QVector<int> intVar;
    QVector<float> floatVar;
    QVector<String> StringVar;
    QVector<bool> boolVar;
    QVector<VideoPlayer*> VideoPlayerVar;
    QVector<GraphicsView*> GraphicsViewVar;
    QVector<CaluThread*> CaluThreadVar;
    QVector<AnimationType> AnimationTypeVar;
    QVector<Pixmap*> PixmapVar;
    QVector<Item*> ItemVar;
    QVector<MusicPlayer*> MusicPlayerVar;
    QVector<GraphicsScene*> GraphicsSceneVar;

    QVector<Variant> VariantVar;
    QVector<Qt::Key> QtKeyVar;

    bool operator !=(const ParametersStru &par);
    ParametersStru& operator =(const ParametersStru &par);
};
const ParametersStru _NULLParametersStru;


class ExpansionSlot
{
private:
    ParSlot parslot=nullptr;
    VoidSlot voidslot=nullptr;
    String slotname;

public:
    ExpansionSlot(ParSlot parslot,String slotname):parslot(parslot),slotname(slotname){}
    ExpansionSlot(VoidSlot voidslot,String slotname):voidslot(voidslot),slotname(slotname){}
    ExpansionSlot(){} //创建空实例，用于查找不到可用的槽时返回

    void call(ParametersStru par=NULL_ParametersStru);
    String getslotname(){return this->slotname;}
    bool isEmpty();
};


struct SCCurrentModulus
{
    float CurrentModulus;
    float CurrentModulus2;
    float CurrentModulus3;
};


class JSParStru
{
public:
    void add(QObject *pointer,QString name);
    QVector<QObject*>pointerVec;
    QVector<QString>nameVec;

    bool operator !=(const JSParStru &par);
};
const JSParStru _NULLJSParStru;


typedef std::function<SCCurrentModulus(int)> SCFun;//SC系数获取函数使用的函数指针

class SC : public QObject//渐变使用的工具类
{
    Q_OBJECT
public:
    SC(float CurrentModulus,float TargetModulus,int times)
        :CurrentModulus(CurrentModulus),TargetModulus(TargetModulus),times(times){}//这个构造方法处理单渐变系数
    SC(float CurrentModulus,float CurrentModulus2,float TargetModulus,float TargetModulus2,
       int times)
        :CurrentModulus(CurrentModulus),CurrentModulus2(CurrentModulus2),
        TargetModulus(TargetModulus),TargetModulus2(TargetModulus2),times(times){}//这个构造方法处理双渐变系数
    SC(float CurrentModulus,float CurrentModulus2,float CurrentModulus3,float TargetModulus,
       float TargetModulus2,float TargetModulus3,int times)
        :CurrentModulus(CurrentModulus),
        CurrentModulus2(CurrentModulus2),CurrentModulus3(CurrentModulus3),TargetModulus(TargetModulus),
        TargetModulus2(TargetModulus2),TargetModulus3(TargetModulus3),times(times){}//这个构造方法处理三渐变系数
    void UesSCFun(SCFun scfun);

    QGraphicsItem* gr;
    QGraphicsBlurEffect *Effect;
    QGraphicsColorizeEffect *co;
    QGraphicsPixmapItem *pi;
    GraphicsView *gv;
    QVector<QPixmap> pixmap;
    QString signfun;
    ParametersStru par;
    bool over;//结束标志
    void start(int choose);
    bool cycle;//连续播图是否循环播放
    Item* num;//动画的图元指针
    int choose;//start()函数的参数

protected:
    float CurrentModulus;//当前系数
    float CurrentModulus2;//当前系数2（处理多系数变化,下同）
    float CurrentModulus3;//当前系数3
    float TargetModulus;//目标系数1
    float TargetModulus2;//目标系数2
    float TargetModulus3;//目标系数3
    int times;//变化所需【总】时间,单位：毫秒
    QTimer *timer;//计时器
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


class MyItem : public QGraphicsPixmapItem//真正的图元类
{
public:
    MyItem(const QPixmap &pixmap,Widget *s=nullptr, QGraphicsItem *parent=nullptr)
        :QGraphicsPixmapItem::QGraphicsPixmapItem(pixmap,parent),s(s){}
    void SetButton(Pixmap up, Pixmap down, String Music, int volume);
    void SetEvent(String PressFun, ParametersStru PressPar, String ReleaseFun, ParametersStru ReleasePar);

protected:
    Widget *s;
    //Button
    bool isbutton=false;
    Pixmap up;
    Pixmap down;
    String Music;
    int volume;
    //slotfun
    String PressFun;
    ParametersStru PressPar;
    String ReleaseFun;
    ParametersStru ReleasePar;
    //Event
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    //允许在此添加更多类型的事件，或许你需要添加一些公有成员变量来记录其所对应的槽函数

    bool IsRegion();
};


class VideoPlayer : public QWidget //视频类
{
    Q_OBJECT
public:
    VideoPlayer(String Path,int Volume, int x, int y,int width,int heigh,bool cycle,String signfun,ParametersStru par,GraphicsScene *scene);
    ~VideoPlayer();
    void start();
    QMediaPlayer *mediaPlayer;

private:
    QGraphicsVideoItem *videoItem;
    bool cycle;
    String Path;
    String signfun;
    ParametersStru par;

private slots:
    void playFinished(QMediaPlayer::State state);
};

class MusicPlayer : public QMediaPlayer//音乐类
{
    Q_OBJECT
public:
    void singleplay(String name,int volume);
    void multipleplay(String name,int volume);
    QMediaPlaylist *cyclelist=nullptr;
    ~MusicPlayer();

private slots:
    void playFinished(QMediaPlayer::State state);
};


class GraphicsView : public QGraphicsView//视图类
{
public:
    GraphicsView(QWidget *parent,Widget *s):QGraphicsView(parent),s(s){}
    void Scale(int sX, int sY);
    void Rotate(float set);
    void SetCenter(int x,int y);
    void SetCenter(QGraphicsItem *item);
    int viewX;
    int viewY;

protected:
    void wheelEvent(QWheelEvent *e)
    {
        e->ignore();
        //不对滚轮事件做任何处理，防止滚动view（如果忽略还会向下层机制传递消息）
    }
    void keyPressEvent(QKeyEvent *e)
    {
        switch(e->key())
        {
            //防止未定义按键滚动view
            case Qt::Key_Left:{}
            case Qt::Key_Right:{}
            case Qt::Key_Down:{}
            case Qt::Key_Up:{}
            default:
            {e->ignore();}
        }
    }
    //void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    Widget *s;
};


class CaluThread : public QThread//线程类
{
    Q_OBJECT
private:
    //调用扩展槽才可能追踪
    ExpansionSlot exfun;
    //非扩展槽
    String fun=NULL_String; //如果通过函数名调用，肯定不是扩展槽
    ParametersStru par;
    //追踪
    bool track;

public:
    CaluThread(String fun,ParametersStru par=NULL_ParametersStru):fun(fun),par(par),track(false){}
    CaluThread(ExpansionSlot exfun,ParametersStru par=NULL_ParametersStru,bool track=false):exfun(exfun),par(par),track(track){}
    void run();

public slots:
    void playFinished();
};


class Item//图元信息记录类
{
public:
    Item(MyItem* pixmapitem=nullptr,QGraphicsItem *graphicsitem=nullptr);
    ~Item();

    QGraphicsItem *ItemPointer;
    MyItem *PixmapItemPoniter;
    QGraphicsBlurEffect *Blur=nullptr;
    QGraphicsColorizeEffect *Color=nullptr;
    float ShearX=0;
    float ShearY=0;
    SC* scPointer[8];
};

struct InputEvent
{
    Qt::Key key;
    int MouseX;
    int MouseY;
    int fMouseX;
    int fMouseY;
    ParametersStru PressPar;
    String PressFun;
    ParametersStru ReleasePar;
    String ReleaseFun;
};

//独立函数
ExpansionSlot FindExpansionSlot(String slotfun);
void RunFun(String slotfun, ParametersStru par=NULL_ParametersStru, ExecutionMode CT=synchronization, bool expansion=true);
