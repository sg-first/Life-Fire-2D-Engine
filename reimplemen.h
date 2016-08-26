//-----本文件所声明用于引擎的其它类型-----
#pragma once
#include "basics.h"
#include "gesture.h"
#include "configure.h"

class Widget;
class SC;

const Pos defaultPos(0,0);

class JSParStru
{
public:
    void add(QObject *pointer,QString name);
    QVector<QObject*>pointerVec;
    QVector<QString>nameVec;

    bool operator !=(const JSParStru &par);
};
const JSParStru _NULLJSParStru;


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
    GraphicsView(QWidget *parent,Widget *s,int x,int y,int width,int height);
    void Scale(int sX, int sY);
    void Rotate(float set);
    void SetCenter(int x,int y);
    void SetCenter(QGraphicsItem *item);
    int viewX;
    int viewY;

protected:
    Widget *s;
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
    int mouseX;
    int mouseY;
    int fmouseX;
    int fmouseY;
    ParametersStru PressPar;
    String PressFun;
    ParametersStru ReleasePar;
    String ReleaseFun;
};


#ifdef AutoIsColliding
struct Collision
{
    Item *item1;
    Item *item2;
    String slot;
    ParametersStru par;
};
#endif
