#pragma once
#include "head.h"
#include "macro.h"

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
};

class CaluThread : public QThread//线程类
{
    Q_OBJECT
private:
    //调用扩展槽才可能追踪
    ExpansionSlot *exfun;
    //非扩展槽
    String fun=NULL_String; //如果通过函数名调用，肯定不是扩展槽
    ParametersStru par;
    //追踪
    bool track;

public:
    CaluThread(String fun,ParametersStru par=NULL_ParametersStru):fun(fun),par(par),track(false){}
    CaluThread(ExpansionSlot *exfun,ParametersStru par=NULL_ParametersStru,bool track=false):exfun(exfun),par(par),track(track){}
    void run();

public slots:
    void playFinished();
};

//独立函数
ExpansionSlot* FindExpansionSlot(String slotfun);
void RunFun(String slotfun, ParametersStru par=NULL_ParametersStru, ExecutionMode CT=synchronization, bool expansion=true);

