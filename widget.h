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

    QList<Item*> AllItem;
    //引擎行为（实现于enginebeh）
    Q_INVOKABLE MyPixmap* NewMyPixmap(QString PicPath, QString signfun=NULL, QString down=NULL, ParametersStru *par=nullptr);
    Q_INVOKABLE Item* AddPixmapItem(QString PicPath,float X,float Y,QString signfun=NULL,QString down=NULL,ParametersStru *par=nullptr,QGraphicsScene *scene=scene);
    Q_INVOKABLE Item* AddPixmapItem(MyPixmap *pixmap, float X, float Y, QGraphicsScene *scene=scene);
    Q_INVOKABLE Item* AddTextItem(QString Text,QString Font,int Size,int CR,int CG,int CB,float X,float Y,QGraphicsScene *scene=scene);
    Q_INVOKABLE Item* AddRectItem(float x,float y,float width,float height,QGraphicsScene *scene=scene);
    Q_INVOKABLE Item* AddEllipseItem(float x,float y,float width,float height,QGraphicsScene *scene=scene);
    Q_INVOKABLE Item* AddLineItem(float x,float y,float fx,float fy,QGraphicsScene *scene=scene);
    Q_INVOKABLE void RotationItem(Item* item, float set);
    Q_INVOKABLE void ScaleItem(Item* item, float set);
    Q_INVOKABLE void MoveItem(Item* item, float X, float Y);
    Q_INVOKABLE void BlurRadiusItem(Item* item, float set);
    Q_INVOKABLE void SetOpacityItem(Item* item, float set);
    Q_INVOKABLE void SetColorItem(Item* item, float R, float G, float B);
    Q_INVOKABLE void ClearScene(QGraphicsScene *scene=scene);
    Q_INVOKABLE void DeleteItem(Item* item);
    Q_INVOKABLE QString GetPath(QString str);
    Q_INVOKABLE void SetVisibleItem(Item* item,bool Enabled);
    Q_INVOKABLE QMediaPlayer* PlayMusic(QString name, int volume, bool cycle=false);
    Q_INVOKABLE void SetBackground(QString PicturePath,QGraphicsScene *scene=scene);
    Q_INVOKABLE void SetBackground(int R, int G, int B);
    Q_INVOKABLE void PauseMusic(QMediaPlayer *player);
    Q_INVOKABLE void ContinueMusic(QMediaPlayer *player);
    Q_INVOKABLE VideoPlayer* PlayVideo(QString path, int Volume, int x=-1, int y=-1,int width=WindowsWidth,int heigh=WindowsHeigh,bool cycle=false,QString signfun=NULL,ParametersStru *par=NULL,QGraphicsScene *scene=scene);
    Q_INVOKABLE void PauseVideo(VideoPlayer *video);
    Q_INVOKABLE void ContinueVideo(VideoPlayer *video);
    Q_INVOKABLE void StopVideo(VideoPlayer *video);
    Q_INVOKABLE EasyThread* StartThread(QString signfun, ParametersStru *par=nullptr, bool track=true);
    Q_INVOKABLE void StopThread(EasyThread *thread);
    Q_INVOKABLE bool ItemColliding(Item* item1, Item* item2);
    Q_INVOKABLE void AnimationRotationItem(Item* item, float set,int times,QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE void AnimationScaleItem(Item* item, float set,int times,QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE void AnimationBlurRadiusItem(Item* item, float set,int times,QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE void AnimationSetOpacityItem(Item* item, float set,int times,QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE void AnimationSetColorItem(Item* item, float R, float G, float B,int times,QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE void AnimationMoveItem(Item* item,float X,float Y,int time,QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE float GetItemX(Item* item);
    Q_INVOKABLE float GetItemY(Item* item);
    Q_INVOKABLE float GetItemR(Item* item);
    Q_INVOKABLE float GetItemG(Item* item);
    Q_INVOKABLE float GetItemB(Item* item);
    Q_INVOKABLE float GetItemBlur(Item* item);
    Q_INVOKABLE float GetItemOpacity(Item* item);
    Q_INVOKABLE float GetItemRotation(Item* item);
    Q_INVOKABLE float GetItemScale(Item* item);
    Q_INVOKABLE Item* AddPicAnimation(QVector<QString> address,int x,int y,int time,QString signfun=NULL,ParametersStru *par=nullptr,bool cycle=true,QGraphicsScene *scene=scene);
    Q_INVOKABLE Item* AddPicAnimation(QVector<MyPixmap*> allpixmap, int x, int y, int time, QString signfun=NULL, ParametersStru *par=nullptr, bool cycle=true, QGraphicsScene *scene=scene);
    Q_INVOKABLE void EndAnimation(Item* item, AnimationType choose);
    Q_INVOKABLE void EndAllAnimation(Item* item);
    Q_INVOKABLE void SetViewCenter(float x, float y, GraphicsView *gview=MainView);
    Q_INVOKABLE void SetViewItemCenter(Item* item,GraphicsView *gview=MainView);
    Q_INVOKABLE float GetMainViewX();
    Q_INVOKABLE float GetMainViewY();
    Q_INVOKABLE GraphicsView* AddView(float x,float y,float width,float height);
    Q_INVOKABLE void SetViewSize(float x,float y,float width=WindowsWidth,float height=WindowsHeigh,GraphicsView *gview=MainView);
    Q_INVOKABLE int GetScreenWidth();
    Q_INVOKABLE int GetScreenHeigh();
    Q_INVOKABLE QGraphicsScene* AddScene(int width,int height);
    Q_INVOKABLE void SetScene(GraphicsView *view=MainView,QGraphicsScene *scene=scene);
    Q_INVOKABLE void SafeSleep(int time);
    Q_INVOKABLE void SetItemLayer(Item* item, int Layer);
    //collidingItems(QGraphicsItem *item)，返回一个与item碰撞的item的表，可以留着做物理引擎用
    Q_INVOKABLE void SetItemOrder(Item* Belowitem, Item* Aboveitem);
    Q_INVOKABLE void ScaleView(float sx,float sy,GraphicsView *view=MainView);
    Q_INVOKABLE void RotateView(float set,GraphicsView *view=MainView);
    Q_INVOKABLE QString ReadTXT(QString path, int line=-1);
    Q_INVOKABLE void WriteTXT(QString path,QString text);
    Q_INVOKABLE void WriteINI(QString path,QString section,QString var,QString value);
    Q_INVOKABLE QString ReadINI(QString path,QString section,QString var);
    Q_INVOKABLE QString AESEncrypt(QString str,QString key);
    Q_INVOKABLE QString AESUncrypt(QString str,QString key);
    Q_INVOKABLE void ChangePixmapItem(QString path,Item* item);
    Q_INVOKABLE void ChangePixmapItem(MyPixmap* pixmap,Item* item);
    Q_INVOKABLE void ChangePicAnimationItem(QVector<QString> address,Item* item,int time,QString signfun=NULL,ParametersStru *par=nullptr,bool cycle=true);
    Q_INVOKABLE void ChangePicAnimationItem(QVector<MyPixmap*> allpixmap, Item* item, int time, QString signfun=NULL, ParametersStru *par=nullptr, bool cycle=true);
    Q_INVOKABLE void DeleteFile(QString path);
    Q_INVOKABLE void SetShearItem(Item* item,float x,float y);
    Q_INVOKABLE float GetItemShearX(Item* item);
    Q_INVOKABLE float GetItemShearY(Item* item);
    Q_INVOKABLE void AnimationShearItem(Item* item, float fx, float fy, int time, QString signfun=NULL,ParametersStru *par=nullptr);
    Q_INVOKABLE void SetKeyEvent(Qt::Key key,QString signfun,ParametersStru *par=nullptr);
    Q_INVOKABLE void DeleteKeyEvent(Qt::Key key);
    Q_INVOKABLE void SetMouseEvent(float MouseX,float MouseY,float fMouseX,float fMouseY,QString signfun,ParametersStru *par=nullptr);
    Q_INVOKABLE void DeleteKeyEvent(float MouseX,float MouseY);
    Q_INVOKABLE void DeleteAllEvent();

protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::Widget *ui;
    void Initialization();//初始化函数
    float viewX;
    float viewY;
    Q_INVOKABLE bool isColliding(QGraphicsItem* Ritem1,QGraphicsItem* Ritem2);
    //关于输入事件
    QList<InputEvent*> AllEvent;
};
