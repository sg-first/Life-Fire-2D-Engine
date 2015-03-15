//-----本文件十分重要，它是窗口类、引擎API以及其它自定义类（类型）的声明区域-----
#pragma once
#include "head.h"
#include "GlobalVar.h"
#include "NewType.h"
#include "AES.h"

namespace Ui {class Widget;}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //程序基础（实现于widget）
    void Initialization();//初始化函数
    //图元管理器
    QList<QGraphicsItem*> AllItem;
    QList<myPixmap*> AllPixmapItem;
    QList<int> ItemNumber;
    int ItemNowNumber;
    //效果管理器
    QList<QGraphicsBlurEffect*>Blur;
    QList<QGraphicsColorizeEffect*>Color;
    //SC类管理器
    QList<QPair<int,SC *> > scPointer;
    //引擎行为（实现于enginebeh）
    Q_INVOKABLE int AddPixmapItem(QString PicPath,float X,float Y,QString fun=NULL,QString down=NULL,QGraphicsScene *scene=scene);
    Q_INVOKABLE int AddTextItem(QString Text,QString Font,int Size,int CR,int CG,int CB,float X,float Y,QGraphicsScene *scene=scene);
    Q_INVOKABLE int AddRectItem(float x,float y,float width,float height,QGraphicsScene *scene=scene);
    Q_INVOKABLE int AddEllipseItem(float x,float y,float width,float height,QGraphicsScene *scene=scene);
    Q_INVOKABLE int AddLineItem(float x,float y,float fx,float fy,QGraphicsScene *scene=scene);
    Q_INVOKABLE void RotationItem(int item, float set,bool LastIndex=false);
    Q_INVOKABLE void ScaleItem(int item, float set,bool LastIndexx=false);
    Q_INVOKABLE void MoveItem(int item, float X, float Y,bool LastIndex=false);
    Q_INVOKABLE void BlurRadiusItem(int item, float set,bool LastIndex=false);
    Q_INVOKABLE void SetOpacityItem(int item, float set,bool LastIndex=false);
    Q_INVOKABLE void SetColorItem(int item, float R, float G, float B,bool LastIndex=false);
    Q_INVOKABLE void ClearScene(QGraphicsScene *scene=scene);
    Q_INVOKABLE void DeleteItem(int item,bool LastIndex=false);
    Q_INVOKABLE QString GetPath(QString str);
    Q_INVOKABLE int QListFindItem(bool LastIndex, int item);
    Q_INVOKABLE void SetVisibleItem(int item,bool Enabled,bool LastIndex=false);
    Q_INVOKABLE QMediaPlayer* PlayMusic(QString name, int volume, bool cycle=false);
    Q_INVOKABLE void SetBackground(QString PicturePath,QGraphicsScene *scene=scene);
    Q_INVOKABLE void SetBackground(int R, int G, int B);
    Q_INVOKABLE void PauseMusic(QMediaPlayer *player);
    Q_INVOKABLE void ContinueMusic(QMediaPlayer *player);
    Q_INVOKABLE VideoPlayer* PlayVideo(QString path, int Volume, int x=-1, int y=-1,int width=WindowsWidth,int heigh=WindowsHeigh,bool cycle=false,QString signfun=NULL,QGraphicsScene *scene=scene);
    Q_INVOKABLE void PauseVideo(VideoPlayer *video);
    Q_INVOKABLE void ContinueVideo(VideoPlayer *video);
    Q_INVOKABLE void StopVideo(VideoPlayer *video);
    Q_INVOKABLE easythread* StartThread(QString Fun,bool track=true);
    Q_INVOKABLE void StopThread(easythread *thread);
    Q_INVOKABLE bool IsColliding(QGraphicsItem* Ritem1,QGraphicsItem* Ritem2);
    Q_INVOKABLE bool ItemColliding(int item1,int item2);
    Q_INVOKABLE void AnimationRotationItem(int item, float set,int times,QString signfun=NULL,bool LastIndex=false);//旋转
    Q_INVOKABLE void AnimationScaleItem(int item, float set,int times,QString signfun=NULL,bool LastIndexx=false);//缩放
    Q_INVOKABLE void AnimationBlurRadiusItem(int item, float set,int times,QString signfun=NULL,bool LastIndex=false);//将一个图元变模糊
    Q_INVOKABLE void AnimationSetOpacityItem(int item, float set,int times,QString signfun=NULL,bool LastIndex=false);//设置一个图元的透明度
    Q_INVOKABLE void AnimationSetColorItem(int item, float R, float G, float B,int times,QString signfun=NULL,bool LastIndex=false);//在一个图元基础上进行着色
    Q_INVOKABLE void AnimationMoveItem(int item,float X,float Y,int time,QString signfun=NULL,bool LastIndex=false);
    Q_INVOKABLE float GetItemX(int item,bool LastIndex=false);
    Q_INVOKABLE float GetItemY(int item,bool LastIndex=false);
    Q_INVOKABLE float GetItemR(int item,bool LastIndex=false);
    Q_INVOKABLE float GetItemG(int item,bool LastIndex=false);
    Q_INVOKABLE float GetItemB(int item,bool LastIndex=false);
    Q_INVOKABLE float GetItemBlur(int item,bool LastIndex);
    Q_INVOKABLE float GetItemOpacity(int item,bool LastIndex);
    Q_INVOKABLE float GetItemRotation(int item,bool LastIndex);
    Q_INVOKABLE float GetItemScale(int item,bool LastIndex);
    Q_INVOKABLE int AddPicAnimation(QVector<QString> address,int x,int y,int time,QString signfun=NULL,bool cycle=true,QGraphicsScene *scene=scene);
    Q_INVOKABLE void endAnimation(int item, animationtype choose);
    Q_INVOKABLE void SetViewCenter(float x, float y, graphicsview *gview=MainView);
    Q_INVOKABLE void SetViewItemCenter(int item,graphicsview *gview=MainView,bool LastIndex=false);
    Q_INVOKABLE float GetMainViewX();
    Q_INVOKABLE float GetMainViewY();
    Q_INVOKABLE graphicsview* AddView(float x,float y,float width,float height);
    Q_INVOKABLE void SetViewSize(float x,float y,float width=WindowsWidth,float height=WindowsHeigh,graphicsview *gview=MainView);
    Q_INVOKABLE int GetScreenWidth();
    Q_INVOKABLE int GetScreenHeigh();
    Q_INVOKABLE QGraphicsScene* AddScene(int width,int height);
    Q_INVOKABLE void SetScene(graphicsview *view=MainView,QGraphicsScene *scene=scene);
    Q_INVOKABLE void SafeSleep(int time);
    Q_INVOKABLE void SetItemLayer(int item, int Layer, bool LastIndex=false);
    //collidingItems(QGraphicsItem *item)，返回一个与item碰撞的item的表，可以留着做物理引擎用
    Q_INVOKABLE void SetItemOrder(int Belowitem,int Aboveitem,bool LastIndex=false);
    Q_INVOKABLE void ScaleView(float sx,float sy,graphicsview *view=MainView);
    Q_INVOKABLE void RotateView(float set,graphicsview *view=MainView);
    Q_INVOKABLE QString ReadTXT(QString path, int line=-1);
    Q_INVOKABLE void WriteTXT(QString path,QString text);
    Q_INVOKABLE void WriteINI(QString path,QString section,QString var,QString value);
    Q_INVOKABLE QString ReadINI(QString path,QString section,QString var);
    Q_INVOKABLE QString AESEncrypt(QString str,QString key);
    Q_INVOKABLE QString AESUncrypt(QString str,QString key);
    Q_INVOKABLE void ChangePixmapItem(QString path,int item,bool LastIndex=false);
    Q_INVOKABLE void ChangePicAnimationItem(QVector<QString> address,int item,int time,QString signfun=NULL,bool cycle=true,bool LastIndex=false);
    Q_INVOKABLE void DeleteFile(QString path);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::Widget *ui;
    float viewX;
    float viewY;
};
