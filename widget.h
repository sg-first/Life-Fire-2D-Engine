//-----本文件十分重要，它是窗口类、引擎API以及其它自定义类（类型）的声明区域-----
#pragma once
#include "head.h"
#include "GlobalVar.h"
#include "NewType.h"
#include "AES.h"
#include "gesture.h"

namespace Ui {class Widget;}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QList<Item*> AllItem;
    //引擎行为（实现于enginebeh）
    Q_INVOKABLE Pixmap* LoadPixmap(String PicPath);
    Q_INVOKABLE RGBColor LoadRGBColor(int R,int G,int B);
    Q_INVOKABLE int GetPixmapWidth(Pixmap *pixmap);
    Q_INVOKABLE int GetPixmapHeight(Pixmap *pixmap);
    Q_INVOKABLE Item* AddPixmapItem(String PicPath,int x,int y,String PressSlotfun=NULL_String,ParametersStru PressPar=NULL_ParametersStru,String ReleaseSlotfun=NULL_String,ParametersStru ReleasePar=NULL_ParametersStru,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddPixmapItem(Pixmap *pixmap,int x,int y,String PressSlotfun=NULL_String,ParametersStru PressPar=NULL_ParametersStru,String ReleaseSlotfun=NULL_String,ParametersStru ReleasePar=NULL_ParametersStru,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddButtonItem(String PicPath,int x,int y,String ReleaseSlotfun, String PressPic=NULL_String, String PressMusic=NULL_String,int volume=100, ParametersStru ReleasePar=NULL_ParametersStru, GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddButtonItem(Pixmap *pixmap,int x,int y,String ReleaseSlotfun, Pixmap *PressPic=nullptr, String PressMusic=NULL_String,int volume=100, ParametersStru ReleasePar=NULL_ParametersStru, GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddTextItem(String Text,String Font,int Size,int CR,int CG,int CB,int x,int y,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddTextItem(String Text,String Font,int Size,RGBColor color,int x,int y,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddRectItem(int x,int y,int width,int height,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddEllipseItem(int x,int y,int width,int height,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddLineItem(int x,int y,int fx,int fy,GraphicsScene *scene=MainScene);
    Q_INVOKABLE void RotationItem(Item* item, float set);
    Q_INVOKABLE void ScaleItem(Item* item, float set);
    Q_INVOKABLE void MoveItem(Item* item, int x, int y);
    Q_INVOKABLE void BlurRadiusItem(Item* item, float set);
    Q_INVOKABLE void DropShadowItem(Item* item, float shadowX,float shadowY);
    Q_INVOKABLE void SetOpacityItem(Item* item, float set);
    Q_INVOKABLE void SetRGBColorItem(Item* item, int R, int G, int B);
    Q_INVOKABLE void ClearScene(GraphicsScene *scene=MainScene);
    Q_INVOKABLE void RemoveItem(Item* item);
    Q_INVOKABLE String GetPath(String str);
    Q_INVOKABLE void SetVisibleItem(Item* item,bool Enabled);
    Q_INVOKABLE MusicPlayer* AddMusic(String name, int volume, bool cycle=false);
    Q_INVOKABLE void SetMusicVolume(MusicPlayer *player,int volume);
    Q_INVOKABLE int GetMusicVolume(MusicPlayer *player);
    Q_INVOKABLE void SetBackground(String PicturePath,GraphicsScene *scene=MainScene);
    Q_INVOKABLE void SetBackground(int R, int G, int B);
    Q_INVOKABLE void SetBackground(RGBColor color);
    Q_INVOKABLE void PauseMusic(MusicPlayer *player);
    Q_INVOKABLE void PlayMusic(MusicPlayer *player);
    Q_INVOKABLE void RemoveMusic(MusicPlayer *player);
    Q_INVOKABLE void StopMusic(MusicPlayer *player);
    Q_INVOKABLE VideoPlayer* AddVideo(String path, int Volume, int x=-1, int y=-1,int width=WindowsWidth,int heigh=WindowsHeigh,bool cycle=false,String signfun=NULL_String,GraphicsScene *scene=MainScene);
    Q_INVOKABLE void SetVideoVolume(VideoPlayer *video,int volume);
    Q_INVOKABLE int GetVideoVolume(VideoPlayer *video);
    Q_INVOKABLE void PauseVideo(VideoPlayer *video);
    Q_INVOKABLE void PlayVideo(VideoPlayer *video);
    Q_INVOKABLE void RemoveVideo(VideoPlayer *video);
    Q_INVOKABLE void StopVideo(VideoPlayer *video);
    Q_INVOKABLE EasyThread* StartThread(String slotfun, ParametersStru par=NULL_ParametersStru, bool track=true);
    Q_INVOKABLE void StopThread(EasyThread *thread);
    Q_INVOKABLE bool ItemColliding(Item* item1, Item* item2);
    Q_INVOKABLE void AnimationRotationItem(Item* item, float set,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationRotationItem(Item* item,SCFun scfun,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationScaleItem(Item* item, float set,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationScaleItem(Item* item,SCFun scfun,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationBlurRadiusItem(Item* item, float set,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationBlurRadiusItem(Item* item,SCFun scfun,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetOpacityItem(Item* item, float set,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetOpacityItem(Item* item,SCFun scfun,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationMoveItem(Item* item,int x,int y,int time,String signfun=NULL_String);
    Q_INVOKABLE void AnimationMoveItem(Item* item,SCFun scfun,int time,String signfu=NULL_String);
    Q_INVOKABLE void AnimationSetViewCenter(GraphicsView* view,int x,int y,int time,String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetViewCenter(GraphicsView* view,SCFun scfun,int time,String signfun=NULL_String);
    Q_INVOKABLE void AnimationShearItem(Item* item, float fx, float fy, int time, String signfun=NULL_String);
    Q_INVOKABLE void AnimationShearItem(Item* item,SCFun scfun,int time, String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetRGBColorItem(Item* item, int R, int G, int B,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetRGBColorItem(Item* item,SCFun scfun,int times,String signfun=NULL_String);
    Q_INVOKABLE int GetItemX(Item* item);
    Q_INVOKABLE int GetItemY(Item* item);
    Q_INVOKABLE int GetItemR(Item* item);
    Q_INVOKABLE int GetItemG(Item* item);
    Q_INVOKABLE int GetItemB(Item* item);
    Q_INVOKABLE float GetItemBlur(Item* item);
    Q_INVOKABLE float GetItemOpacity(Item* item);
    Q_INVOKABLE float GetItemRotation(Item* item);
    Q_INVOKABLE float GetItemScale(Item* item);
    Q_INVOKABLE Item* AddPicAnimation(QVector<String> address,int x,int y,int time,String signfun=NULL_String,bool cycle=true,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddPicAnimation(QVector<Pixmap*> allpixmap, int x, int y, int time, String signfun=NULL_String, bool cycle=true, GraphicsScene *scene=MainScene);
    Q_INVOKABLE void EndAnimation(Item* item, AnimationType choose);
    Q_INVOKABLE bool IsAnimation(Item* item,AnimationType choose);
    Q_INVOKABLE void EndAllAnimation(Item* item);
    Q_INVOKABLE void SetViewCenter(int x, int y, GraphicsView *gview=MainView);
    Q_INVOKABLE void SetViewCenter(Item* item,GraphicsView *gview=MainView);
    Q_INVOKABLE int GetViewX(GraphicsView *gview=MainView);
    Q_INVOKABLE int GetViewY(GraphicsView *gview=MainView);
    Q_INVOKABLE GraphicsView* AddView(int x,int y,int width,int height);
    Q_INVOKABLE void DeleteView(GraphicsView* view){delete view;}
    Q_INVOKABLE void SetViewSize(int x,int y,int width=WindowsWidth,int height=WindowsHeigh,GraphicsView *gview=MainView);
    Q_INVOKABLE int GetScreenWidth();
    Q_INVOKABLE int GetScreenHeigh();
    Q_INVOKABLE GraphicsScene* AddScene(int width,int height);
    Q_INVOKABLE void DeleteScene(GraphicsScene* scene){delete scene;}
    Q_INVOKABLE void SetScene(GraphicsView *view=MainView, GraphicsScene *scene=MainScene, int viewX=-1, int viewY=-1);
    Q_INVOKABLE void SafeSleep(int time);
    Q_INVOKABLE void SetItemLayer(Item* item, int Layer);
    //collidingItems(QGraphicsItem *item)，返回一个与item碰撞的item的表，可以留着做物理引擎用
    Q_INVOKABLE void SetItemOrder(Item* Belowitem, Item* Aboveitem);
    Q_INVOKABLE void ScaleView(float sX,float sY,GraphicsView *view=MainView);
    Q_INVOKABLE void RotateView(float set,GraphicsView *view=MainView);
    Q_INVOKABLE String ReadTXT(String path, int line=-1);
    Q_INVOKABLE void WriteTXT(String path,String text);
    Q_INVOKABLE void WriteINI(String path,String section,String var,String value);
    Q_INVOKABLE String ReadINI(String path,String section,String var);
    Q_INVOKABLE String AESEncrypt(String str,String key);
    Q_INVOKABLE String AESUncrypt(String str,String key);
    Q_INVOKABLE void ChangePixmapItem(String path, Item* item);
    Q_INVOKABLE void ChangePixmapItem(Pixmap* pixmap,Item* item);
    Q_INVOKABLE void ChangePicAnimationItem(QVector<String> allpixmap, Item* item, int time, String signfun=NULL_String, bool cycle=true);
    Q_INVOKABLE void ChangePicAnimationItem(QVector<Pixmap*> allpixmap, Item* item, int time, String signfun=NULL_String, bool cycle=true);
    Q_INVOKABLE void SetItemEvent(Item *item, String PressSlotfun=NULL_String, ParametersStru PressPar=NULL_ParametersStru, String ReleaseSlotfun=NULL_String, ParametersStru ReleasePar=NULL_ParametersStru);
    Q_INVOKABLE void RemoveFile(String path);
    Q_INVOKABLE void ShearItem(Item* item,float X,float Y);
    Q_INVOKABLE float GetItemShearX(Item* item);
    Q_INVOKABLE float GetItemShearY(Item* item);
    Q_INVOKABLE void AddKeyEvent(Qt::Key key, String PressSlotfun=NULL_String, ParametersStru PressPar=NULL_ParametersStru, String ReleaseSlotfun=NULL_String, ParametersStru ReleasePar=NULL_ParametersStru);
    Q_INVOKABLE void RemoveKeyEvent(Qt::Key key);
    Q_INVOKABLE void AddMouseEvent(int MouseX, int MouseY, int fMouseX, int fMouseY, String PressSlotfun=NULL_String, ParametersStru PressPar=NULL_ParametersStru, String ReleaseSlotfun=NULL_String, ParametersStru ReleasePar=NULL_ParametersStru);
    Q_INVOKABLE void RemoveMouseEvent(int MouseX, int MouseY,int fMouseX,int fMouseY);
    Q_INVOKABLE void RemoveAllEvent();
    Q_INVOKABLE void WaitSign(String signfun);
    Q_INVOKABLE void HorizontallyFlip(Item *item);
    Q_INVOKABLE Pixmap* HorizontallyFlip(Pixmap *pixmap);
    Q_INVOKABLE void VerticalFlip(Item *item);
    Q_INVOKABLE Pixmap* VerticalFlip(Pixmap *pixmap);
    Q_INVOKABLE Timer* StartMultipleTimer(String slotfun,int time);
    Q_INVOKABLE void StartSingleTimer(String slotfun,int time);
    Q_INVOKABLE void DeleteTimer(Timer* timer){delete timer;}
    Q_INVOKABLE Gesture* LoadGesture(QList<Pos> posSeq,int tolerance,String event);
    Q_INVOKABLE Gesture* LoadGesture(LocusFunc locus,int tolerance,ProgressStand standard,int maxProgress,String event);
    Q_INVOKABLE void AddGesture(int mouseX,int mouseY,int fmouseX,int fmouseY,QList<Pos> posSeq,int tolerance,String event);
    Q_INVOKABLE void AddGesture(int mouseX,int mouseY,int fmouseX,int fmouseY,LocusFunc locus,int tolerance,ProgressStand standard,int maxProgress,String event);
    Q_INVOKABLE void AddGesture(int mouseX,int mouseY,int fmouseX,int fmouseY,Gesture* gesture);
    Q_INVOKABLE void RemoveGesture(Gesture* gesture);
    Q_INVOKABLE void RemoveGestureArea(int mouseX,int mouseY,int fmouseX,int fmouseY);
    Q_INVOKABLE void RemoveAllGestureArea();

    void PassMousePressEvent(QPointF point);
    void PassMouseReleaseEvent(QPointF point);
    void PassMouseReleaseEvent(QMouseEvent *e);
    void PassMouseMoveEvent(QMouseEvent *e);

protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    Ui::Widget *ui;
    //引擎行为函数
    void Initialization();
    bool isColliding(QGraphicsItem* RItem1,QGraphicsItem* RItem2);
    Pixmap* mirrorAndChange(Pixmap *pixmap, bool mirrorMode);
    //关于输入事件
    QList<InputEvent> AllEvent;
    QList<GestureArea*> AllGestureArea;
    //关于IO优化
    QFile *PreQFile=nullptr;
    String PreQFileName;
    QSettings *PreQSet=nullptr;
    String PreQSetName;
};

