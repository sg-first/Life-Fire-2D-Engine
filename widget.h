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
    Q_INVOKABLE Pixmap* NewPixmap(String PicPath);
    Q_INVOKABLE RGBColor NewRGBColor(int R,int G,int B);
    Q_INVOKABLE float GetPixmapWidth(Pixmap *pixmap);
    Q_INVOKABLE float GetPixmapHeight(Pixmap *pixmap);
    Q_INVOKABLE Item* AddPixmapItem(String PicPath,float X,float Y,String PressSlotfun=NULL_String,ParametersStru PressPar=NULL_ParametersStru,String ReleaseSlotfun=NULL_String,ParametersStru ReleasePar=NULL_ParametersStru,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddPixmapItem(Pixmap *pixmap, float X, float Y,String PressSlotfun=NULL_String,ParametersStru PressPar=NULL_ParametersStru,String ReleaseSlotfun=NULL_String,ParametersStru ReleasePar=NULL_ParametersStru,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddButtonItem(String PicPath, float X, float Y, String ReleaseSlotfun, String PressPic=NULL_String, String PressMusic=NULL_String,int volume=100, ParametersStru ReleasePar=NULL_ParametersStru, GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddButtonItem(Pixmap *pixmap, float X, float Y, String ReleaseSlotfun, Pixmap *PressPic=nullptr, String PressMusic=NULL_String,int volume=100, ParametersStru ReleasePar=NULL_ParametersStru, GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddTextItem(String Text,String Font,int Size,int CR,int CG,int CB,float X,float Y,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddTextItem(String Text,String Font,int Size,RGBColor color,float X,float Y,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddRectItem(float x,float y,float width,float height,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddEllipseItem(float x,float y,float width,float height,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddLineItem(float x,float y,float fx,float fy,GraphicsScene *scene=MainScene);
    Q_INVOKABLE void RotationItem(Item* item, float set);
    Q_INVOKABLE void ScaleItem(Item* item, float set);
    Q_INVOKABLE void MoveItem(Item* item, float X, float Y);
    Q_INVOKABLE void BlurRadiusItem(Item* item, float set);
    Q_INVOKABLE void DropShadowItem(Item* item, float shadowX,float shadowY);
    Q_INVOKABLE void SetOpacityItem(Item* item, float set);
    Q_INVOKABLE void SetRGBColorItem(Item* item, float R, float G, float B);
    Q_INVOKABLE void ClearScene(GraphicsScene *scene=MainScene);
    Q_INVOKABLE void DeleteItem(Item* item);
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
    Q_INVOKABLE void DeleteMusic(MusicPlayer *player);
    Q_INVOKABLE void StopMusic(MusicPlayer *player);
    Q_INVOKABLE VideoPlayer* AddVideo(String path, int Volume, int x=-1, int y=-1,int width=WindowsWidth,int heigh=WindowsHeigh,bool cycle=false,String signfun=NULL_String,GraphicsScene *scene=MainScene);
    Q_INVOKABLE void SetVideoVolume(VideoPlayer *video,int volume);
    Q_INVOKABLE int GetVideoVolume(VideoPlayer *video);
    Q_INVOKABLE void PauseVideo(VideoPlayer *video);
    Q_INVOKABLE void PlayVideo(VideoPlayer *video);
    Q_INVOKABLE void DeleteVideo(VideoPlayer *video);
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
    Q_INVOKABLE void AnimationMoveItem(Item* item,float X,float Y,int time,String signfun=NULL_String);
    Q_INVOKABLE void AnimationMoveItem(Item* item,SCFun scfun,int time,String signfu=NULL_String);
    Q_INVOKABLE void AnimationSetViewCenter(GraphicsView* view,float X,float Y,int time,String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetViewCenter(GraphicsView* view,SCFun scfun,int time,String signfun=NULL_String);
    Q_INVOKABLE void AnimationShearItem(Item* item, float fx, float fy, int time, String signfun=NULL_String);
    Q_INVOKABLE void AnimationShearItem(Item* item,SCFun scfun,int time, String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetRGBColorItem(Item* item, float R, float G, float B,int times,String signfun=NULL_String);
    Q_INVOKABLE void AnimationSetRGBColorItem(Item* item,SCFun scfun,int times,String signfun=NULL_String);
    Q_INVOKABLE float GetItemX(Item* item);
    Q_INVOKABLE float GetItemY(Item* item);
    Q_INVOKABLE float GetItemR(Item* item);
    Q_INVOKABLE float GetItemG(Item* item);
    Q_INVOKABLE float GetItemB(Item* item);
    Q_INVOKABLE float GetItemBlur(Item* item);
    Q_INVOKABLE float GetItemOpacity(Item* item);
    Q_INVOKABLE float GetItemRotation(Item* item);
    Q_INVOKABLE float GetItemScale(Item* item);
    Q_INVOKABLE Item* AddPicAnimation(QVector<String> address,int x,int y,int time,String signfun=NULL_String,bool cycle=true,GraphicsScene *scene=MainScene);
    Q_INVOKABLE Item* AddPicAnimation(QVector<Pixmap*> allpixmap, int x, int y, int time, String signfun=NULL_String, bool cycle=true, GraphicsScene *scene=MainScene);
    Q_INVOKABLE void EndAnimation(Item* item, AnimationType choose);
    Q_INVOKABLE bool IsAnimation(Item* item,AnimationType choose);
    Q_INVOKABLE void EndAllAnimation(Item* item);
    Q_INVOKABLE void SetViewCenter(float x, float y, GraphicsView *gview=MainView);
    Q_INVOKABLE void SetViewCenter(Item* item,GraphicsView *gview=MainView);
    Q_INVOKABLE float GetViewX(GraphicsView *gview=MainView);
    Q_INVOKABLE float GetViewY(GraphicsView *gview=MainView);
    Q_INVOKABLE GraphicsView* AddView(float x,float y,float width,float height);
    Q_INVOKABLE void SetViewSize(float x,float y,float width=WindowsWidth,float height=WindowsHeigh,GraphicsView *gview=MainView);
    Q_INVOKABLE float GetScreenWidth();
    Q_INVOKABLE float GetScreenHeigh();
    Q_INVOKABLE GraphicsScene* AddScene(int width,int height);
    Q_INVOKABLE void SetScene(GraphicsView *view=MainView, GraphicsScene *scene=MainScene, float viewX=-1, float viewY=-1);
    Q_INVOKABLE void SafeSleep(int time);
    Q_INVOKABLE void SetItemLayer(Item* item, int Layer);
    //collidingItems(QGraphicsItem *item)，返回一个与item碰撞的item的表，可以留着做物理引擎用
    Q_INVOKABLE void SetItemOrder(Item* Belowitem, Item* Aboveitem);
    Q_INVOKABLE void ScaleView(float sx,float sy,GraphicsView *view=MainView);
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
    Q_INVOKABLE void DeleteFile(String path);
    Q_INVOKABLE void ShearItem(Item* item,float x,float y);
    Q_INVOKABLE float GetItemShearX(Item* item);
    Q_INVOKABLE float GetItemShearY(Item* item);
    Q_INVOKABLE void AddKeyEvent(Qt::Key key, String PressSlotfun=NULL_String, ParametersStru PressPar=NULL_ParametersStru, String ReleaseSlotfun=NULL_String, ParametersStru ReleasePar=NULL_ParametersStru);
    Q_INVOKABLE void DeleteKeyEvent(Qt::Key key);
    Q_INVOKABLE void AddMouseEvent(float MouseX, float MouseY, float fMouseX, float fMouseY, String PressSlotfun=NULL_String, ParametersStru PressPar=NULL_ParametersStru, String ReleaseSlotfun=NULL_String, ParametersStru ReleasePar=NULL_ParametersStru);
    Q_INVOKABLE void DeleteMouseEvent(float MouseX, float MouseY,float fMouseX,float fMouseY);
    Q_INVOKABLE void DeleteAllEvent();
    Q_INVOKABLE void WaitSign(String signfun);
    Q_INVOKABLE void HorizontallyFlip(Item *item);
    Q_INVOKABLE Pixmap* HorizontallyFlip(Pixmap *pixmap);
    Q_INVOKABLE void VerticalFlip(Item *item);
    Q_INVOKABLE Pixmap* VerticalFlip(Pixmap *pixmap);
    Q_INVOKABLE QTimer* StartMultipleTimer(String slotfun,int time);
    Q_INVOKABLE void StartSingleTimer(String slotfun,int time);
    Q_INVOKABLE void DeleteTimer(QTimer* timer);

    void PassMousePressEvent(QPointF point);
    void PassMouseReleaseEvent(QPointF point);

protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


private:
    Ui::Widget *ui;
    //引擎行为函数
    void Initialization();
    bool isColliding(QGraphicsItem* Ritem1,QGraphicsItem* Ritem2);
    Pixmap* mirrorAndChange(Pixmap *pixmap, bool mirrorMode);
    //关于输入事件
    QList<InputEvent> AllEvent;
    //关于IO优化
    QFile *PreQFile=nullptr;
    String PreQFileName;
    QSettings *PreQSet=nullptr;
    String PreQSetName;
};

