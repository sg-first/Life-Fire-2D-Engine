//-----本文件是引擎行为层给用户提供的接口的实现-----
#include "widget.h"
#include "configure.h"

#ifdef SelfAdaption
void adaptive(int &x,int &y)
{
    x*=adaptiveRatioX;
    y*=adaptiveRatioY;
}
void adaptive(float &x,float &y)
{
    x*=adaptiveRatioX;
    y*=adaptiveRatioY;
}
#endif

Pixmap* Widget::LoadPixmap(String PicPath)
{return new Pixmap(PicPath);}

RGBColor Widget::LoadRGBColor(int R, int G, int B)
{return RGBColor(R,G,B);}

int Widget::GetPixmapWidth(Pixmap *pixmap)
{return pixmap->width();}

int Widget::GetPixmapHeight(Pixmap *pixmap)
{return pixmap->height();}

Item* Widget::AddPixmapItem(String PicPath,int x,int y,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar,GraphicsScene *scene)
{
    Pixmap mainpix(PicPath);
    MyItem *item=new MyItem(mainpix,this);
    item->SetEvent(PressSlotfun,PressPar,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(x,y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddPixmapItem(Pixmap *pixmap,int x,int y,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar,GraphicsScene *scene)
{
    MyItem *item=new MyItem(*pixmap,this);
    item->SetEvent(PressSlotfun,PressPar,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(x,y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddButtonItem(String PicPath,int x,int y,String ReleaseSlotfun, String PressPic, String PressMusic,int volume, ParametersStru ReleasePar, GraphicsScene *scene)
{
    Pixmap mainpix(PicPath);
    MyItem *item=new MyItem(mainpix,this);
    if(PressPic!=NULL_String)
    {item->SetButton(mainpix,Pixmap(PressPic),PressMusic,volume);}
    else
    {item->SetButton(mainpix,mainpix,PressMusic,volume);}
    item->SetEvent(NULL_String,NULL_ParametersStru,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(x,y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddButtonItem(Pixmap *pixmap,int x,int y,String ReleaseSlotfun, Pixmap *PressPic, String PressMusic,int volume, ParametersStru ReleasePar, GraphicsScene *scene)
{
    MyItem *item=new MyItem(*pixmap,this);
    if(PressPic!=nullptr)
    {item->SetButton(*pixmap,*PressPic,PressMusic,volume);}
    else
    {item->SetButton(*pixmap,*pixmap,PressMusic,volume);}
    item->SetEvent(NULL_String,NULL_ParametersStru,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(x,y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddTextItem(String Text,String Font,int Size,int CR,int CG,int CB,int x,int y,GraphicsScene *scene)
{return AddTextItem(Text,Font,Size,RGBColor(CR,CG,CB),x,y,scene);}

Item* Widget::AddTextItem(String Text, String Font, int Size, RGBColor color, int x, int y, GraphicsScene *scene)
{
    QGraphicsTextItem *text=new QGraphicsTextItem(Text);
    text->setFont(QFont(Font,Size));
    text->setDefaultTextColor(color);
    text->setPos(x,y);
    Item *item=new Item(nullptr,text);
    AllItem<<item;
    scene->addItem(text);
    return item;
}

Item* Widget::AddRectItem(int x,int y,int width,int height,GraphicsScene *scene)
{
    QGraphicsRectItem *rect=new QGraphicsRectItem(x,y,width,height);
    scene->addItem(rect);
    Item *item=new Item(nullptr,rect);
    AllItem<<item;
    return item;
}

Item* Widget::AddEllipseItem(int x,int y,int width,int height,GraphicsScene *scene)
{
    QGraphicsEllipseItem *Ellipse=new QGraphicsEllipseItem(x,y,width,height);
    scene->addItem(Ellipse);
    Item *item=new Item(nullptr,Ellipse);
    AllItem<<item;
    return item;
}

Item* Widget::AddLineItem(int x,int y,int fx,int fy,GraphicsScene *scene)
{
    QGraphicsLineItem *line=new QGraphicsLineItem(x,y,fx,fy);
    scene->addItem(line);
    Item *item=new Item(nullptr,line);
    AllItem<<item;
    return item;
}

void Widget::RotationItem(Item* item, float set,PosF originPos)
{
    item->ItemPointer->setTransformOriginPoint(originPos);
    item->ItemPointer->setRotation(set);
}

void Widget::ScaleItem(Item* item, float set,PosF originPos)
{
    item->ItemPointer->setTransformOriginPoint(originPos);
    item->ItemPointer->setScale(set);
}

void Widget::BlurRadiusItem(Item* item, float set)
{
   if(item->Blur==nullptr)
   {item->Blur=new QGraphicsBlurEffect(this);}
   item->Blur->setBlurRadius(set);
   item->ItemPointer->setGraphicsEffect(item->Blur);
}

/*void Widget::DropShadowItem(Item* item, float shadowX,float shadowY)//还没写完
{
    QGraphicsDropShadowEffect *e2 = new QGraphicsDropShadowEffect(this);
    e2->setOffset(shadowX,shadowY);
    item->ItemPointer->setGraphicsEffect(e2);
}*/

void Widget::MoveItem(Item* item, int x, int y)
{
    item->ItemPointer->setPos(x,y);
    #ifdef AutoIsColliding
    itemMoveEvent();
    #endif
}

void Widget::SetOpacityItem(Item* item, float set)
{item->ItemPointer->setOpacity(set);}

void Widget::SetRGBColorItem(Item* item,int R,int G,int B)
{
   if(item->Color==nullptr)
   {item->Color=new QGraphicsColorizeEffect(this);}
   item->Color->setColor(RGBColor(R,G,B));
   item->ItemPointer->setGraphicsEffect(item->Color);
}

void Widget::ClearScene(GraphicsScene *scene)
{
   for(Item* i:AllItem)
   {RemoveItem(i);}
   scene->clear();//这句目测没用
}

void Widget::RemoveItem(Item* item)
{
    EndAllAnimation(item);
    #ifdef SafetyPriority
    SafeSleep(2);//等待目前进行这帧完成
    #endif
    AllItem.removeAt(AllItem.indexOf(item));
    delete item;
}

String Widget::GetPath(String str)
{
   String path;
   QDir dir;
   path=dir.currentPath();
   path+="/"+str;
   return path;
}

void Widget::SetVisibleItem(Item* item,bool Enabled)
{item->ItemPointer->setVisible(Enabled);}

void Widget::SetBackground(String PicturePath,GraphicsScene *scene)
{scene->setBackgroundBrush(Pixmap(PicturePath));}

void Widget::SetBackground(int R,int G,int B)
{SetBackground(RGBColor(R,G,B));}

void Widget::SetBackground(RGBColor color)
{MainScene->setBackgroundBrush(color);}

MusicPlayer* Widget::AddMusic(String name,int volume,bool cycle)
{
   MusicPlayer *player=new MusicPlayer;
   if(!cycle)
   {player->singleplay(name,volume);}
   else
   {player->multipleplay(name,volume);}
   return player;
}

void Widget::SetMusicVolume(MusicPlayer *player,int volume)
{player->setVolume(volume);}

int Widget::GetMusicVolume(MusicPlayer *player)
{return player->volume();}

void Widget::PauseMusic(MusicPlayer *player)
{player->pause();}

void Widget::PlayMusic(MusicPlayer *player)
{player->play();}

void Widget::RemoveMusic(MusicPlayer *player)
{
    player->stop();
    delete player;
}

void Widget::StopMusic(MusicPlayer *player)
{player->stop();}

CaluThread* Widget::StartThread(String slotfun,ParametersStru par,bool track)
{
    ExpansionSlot *slot=FindExpansionSlot(slotfun);
    if(slot==nullptr)
    {
        //非扩展情况
        if(track)
        {
            CaluThread *thread=new CaluThread(slotfun,par);
            thread->start();
            return thread;
        }
        RunFun(slotfun,par);
        return nullptr;
    }
    //扩展情况
    //即使是非追踪，调用扩展槽还是需要CaluThread，区别只是是否自动回收
    CaluThread *thread=new CaluThread(slot,par,track);
    thread->start();
    if(track)
    {return thread;}
    return nullptr;
}

void Widget::RemoveThread(CaluThread *thread)
{
    thread->quit();
    thread->wait();
    thread->playFinished();
}

bool Widget::ItemColliding(Item* item1,Item* item2)
{return isColliding(item1->ItemPointer,item2->ItemPointer);}

VideoPlayer* Widget::AddVideo(String path,int Volume,int x,int y,int width,int heigh,bool cycle,String signfun,ParametersStru par,GraphicsScene *scene)
{
    if(x==-1)
    {x=MainView->viewX-(WindowsWidth/2);}
    if(y==-1)
    {y=MainView->viewY-(WindowsHeigh/2);}
    VideoPlayer* video=new VideoPlayer(path,Volume,x,y,width,heigh,cycle,signfun,par,scene);
    video->start();
    return video;
}

void Widget::SetVideoVolume(VideoPlayer *video,int volume)
{video->mediaPlayer->setVolume(volume);}

int Widget::GetVideoVolume(VideoPlayer *video)
{return video->mediaPlayer->volume();}

void Widget::PauseVideo(VideoPlayer *video)
{video->mediaPlayer->pause();}

void Widget::PlayVideo(VideoPlayer *video)
{video->mediaPlayer->play();}

void Widget::RemoveVideo(VideoPlayer *video)
{
    video->mediaPlayer->stop();
    delete video;
}

void Widget::StopVideo(VideoPlayer *video)
{video->mediaPlayer->stop();}

void Widget::AnimationRotationItem(Item* item, float set,int time,PosF originPos,String signfun)
{
   EndAnimation(item,Rotation);
   SC *sc=new SC(GetItemRotation(item),set,time,item,signfun,this);
   item->ItemPointer->setTransformOriginPoint(originPos);
   item->scPointer[Rotation]=sc;
   sc->start(Rotation);
}

void Widget::AnimationRotationItem(Item *item, SCFun scfun, int time,PosF originPos,String signfun)
{
    EndAnimation(item,Rotation);
    SC *sc=new SC(0,0,time,item,signfun,this);
    item->ItemPointer->setTransformOriginPoint(originPos);
    item->scPointer[Rotation]=sc;
    sc->UesSCFun(scfun);
    sc->start(Rotation);
}

void Widget::AnimationScaleItem(Item* item, float set,int time,PosF originPos,String signfun)
{
    EndAnimation(item,Scale);
    SC *sc=new SC(item->ItemPointer->scale(),set,time,item,signfun,this);
    item->ItemPointer->setTransformOriginPoint(originPos);
    item->scPointer[Scale]=sc;
    sc->start(Scale);
}

void Widget::AnimationScaleItem(Item *item, SCFun scfun, int time,PosF originPos,String signfun)
{
    EndAnimation(item,Scale);
    SC *sc=new SC(0,0,time,item,signfun,this);
    item->ItemPointer->setTransformOriginPoint(originPos);
    item->scPointer[Scale]=sc;
    sc->UesSCFun(scfun);
    sc->start(Scale);
}

void Widget::AnimationBlurRadiusItem(Item* item, float set, int time,String signfun)
{
   EndAnimation(item,BlurRadius);
   SC *sc=new SC(GetItemBlur(item),set,time,item,signfun,this);
   item->scPointer[BlurRadius]=sc;
   sc->start(BlurRadius);
}

void Widget::AnimationBlurRadiusItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,BlurRadius);
    if(item->Blur==nullptr)
    {item->Blur=new QGraphicsBlurEffect(this);}
    SC *sc=new SC(0,0,time,item,signfun,this);
    item->scPointer[BlurRadius]=sc;
    sc->UesSCFun(scfun);
    sc->start(BlurRadius);
}

void Widget::AnimationSetOpacityItem(Item* item, float set, int time,String signfun)
{
   EndAnimation(item,Opacity);
   SC *sc=new SC(GetItemOpacity(item),set,time,item,signfun,this);
   item->scPointer[Opacity]=sc;
   sc->start(Opacity);
}

void Widget::AnimationSetOpacityItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,Opacity);
    SC *sc=new SC(0,0,time,item,signfun,this);
    item->scPointer[Opacity]=sc;
    sc->UesSCFun(scfun);
    sc->start(Opacity);
}

void Widget::AnimationMoveItem(Item* item,int x,int y,int time,String signfun)
{
    EndAnimation(item,Move);
    SC *sc=new SC(item->ItemPointer->x(),item->ItemPointer->y(),x,y,time,item,signfun,this);
    item->scPointer[Move]=sc;
    sc->start(Move);
}

void Widget::AnimationMoveItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,Move);
    SC *sc=new SC(0,0,0,0,time,item,signfun,this);
    item->scPointer[Move]=sc;
    sc->UesSCFun(scfun);
    sc->start(Move);
}

void Widget::AnimationSetViewCenter(GraphicsView *view, int x, int y, int time, String signfun)
{
    SC *sc=new SC(view->viewX,view->viewY,x,y,time,view,signfun,this);
    sc->start(20);
}

void Widget::AnimationSetViewCenter(GraphicsView *view, SCFun scfun, int time, String signfun)
{
    SC *sc=new SC(0,0,0,0,time,view,signfun,this);
    sc->UesSCFun(scfun);
    sc->start(20);
}

void Widget::AnimationShearItem(Item* item, float fx, float fy, int time, String signfun)
{
   EndAnimation(item,Shear);
   SC *sc=new SC(item->ShearX,item->ShearY,fx,fy,time,item,signfun,this);
   item->scPointer[Shear]=sc;
   sc->start(Shear);
}

void Widget::AnimationShearItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,Shear);
    SC *sc=new SC(0,0,0,0,time,item,signfun,this);
    item->scPointer[Shear]=sc;
    sc->UesSCFun(scfun);
    sc->start(Shear);
}

void Widget::AnimationSetRGBColorItem(Item* item, int R, int G, int B, int time,String signfun)
{
   EndAnimation(item,Color);
   //当前系数
   float CurrentModulus;
   float CurrentModulus2;
   float CurrentModulus3;
   if(item->Color==nullptr)
   {
       //如果之前没有进行过着色,从0,0,0开始着色
       CurrentModulus=0;
       CurrentModulus2=0;
       CurrentModulus3=0;
       item->Color=new QGraphicsColorizeEffect(this);
   }
   else
   {
        RGBColor color=item->Color->color();
        CurrentModulus=color.red();
        CurrentModulus2=color.green();
        CurrentModulus3=color.blue();
   }
   SC *sc=new SC(CurrentModulus,CurrentModulus2,CurrentModulus3,R,G,B,time,item,signfun,this);
   item->scPointer[Color]=sc;
   sc->start(Color);
}

void Widget::AnimationSetRGBColorItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,Color);
    SC *sc=new SC(0,0,0,0,0,0,time,item,signfun,this);
    item->scPointer[Color]=sc;
    sc->UesSCFun(scfun);
    sc->start(Color);
}

Item* Widget::AddPicAnimation(QVector<String> address,int x,int y,int time,String signfun,bool cycle,GraphicsScene *scene)
{
    assert(!address.isEmpty()); //确认传入的图片容器不为空

    MyItem *temp=new MyItem(address.at(0));//将第一张图片变为图元
    scene->addItem(temp);//将第一张图片显示在场景中
    temp->setPos(x,y);
    Item *item=new Item(temp);
    AllItem<<item;

    SC *sc=new SC(0,0,time,item,signfun,this);//创建SC实例，这里直接套用双系数的构造函数
    item->scPointer[Picture]=sc;
    sc->cycle=cycle;//定义是否循环连续播图

    for(QVector<String>::iterator iter=address.begin();iter!=address.end();++iter)//遍历容器中的所有图片
    {sc->pixmap.push_back(Pixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
    return item;
}

Item* Widget::AddPicAnimation(QVector<Pixmap*> allpixmap, int x, int y, int time, String signfun, bool cycle, GraphicsScene *scene)
{
    assert(!allpixmap.isEmpty());

    MyItem *item=new MyItem(*allpixmap.at(0));
    Item *ritem=new Item(item);
    scene->addItem(item);
    item->setPos(x,y);
    AllItem<<ritem;

    SC *sc=new SC(0,0,time,ritem,signfun,this);
    ritem->scPointer[Picture]=sc;
    sc->cycle=cycle;

    for(Pixmap* i:allpixmap)
    {sc->pixmap.push_back(*i);}
    sc->start(Picture);
    return ritem;
}

void Widget::ChangePicAnimationItem(QVector<String>allpixmap,Item* item,int time,String signfun,bool cycle)
{
    assert(!allpixmap.isEmpty());//断言，确认传入的图片容器不为空
    EndAnimation(item,Picture);
    MyItem *temp=item->PixmapItemPoniter;
    temp->setPixmap(Pixmap(allpixmap.at(0)));//变更当前图片为图集的第一帧
    SC *sc=new SC(0,0,time,item,signfun,this);//创建SC实例
    item->scPointer[Picture]=sc;
    sc->cycle=cycle;//定义是否循环连续播图

    for(QVector<String>::iterator iter=allpixmap.begin();iter!=allpixmap.end();++iter)//遍历容器中的所有图片
    {sc->pixmap.push_back(Pixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
}

void Widget::ChangePicAnimationItem(QVector<Pixmap*> allpixmap, Item *item, int time, String signfun, bool cycle)
{
    assert(!allpixmap.isEmpty());//断言，确认传入的图片容器不为空
    EndAnimation(item,Picture);
    MyItem *temp=item->PixmapItemPoniter;
    temp->setPixmap(*allpixmap.at(0));//变更当前图片为图集的第一帧
    SC *sc=new SC(0,0,time,item,signfun,this);//创建SC实例
    item->scPointer[Picture]=sc;
    sc->cycle=cycle;//定义是否循环连续播图

    for(Pixmap* i:allpixmap)//遍历容器中的所有图片
    {sc->pixmap.push_back(*i);}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
}

//注意，开启自适应后这两个函数返回的是假坐标，即用户指定的
int Widget::GetItemX(Item* item)
{return item->ItemPointer->x();}

int Widget::GetItemY(Item* item)
{return item->ItemPointer->y();}

int Widget::GetItemR(Item* item)
{return (item->Color==nullptr)?-1:item->Color->color().red();}

int Widget::GetItemG(Item* item)
{return (item->Color==nullptr)?-1:item->Color->color().green();}

int Widget::GetItemB(Item* item)
{return (item->Color==nullptr)?-1:item->Color->color().blue();}

float Widget::GetItemBlur(Item* item)
{return (item->Blur==nullptr)?0:item->Blur->blurRadius();}

float Widget::GetItemOpacity(Item* item)
{return item->ItemPointer->opacity();}

float Widget::GetItemRotation(Item* item)
{return item->ItemPointer->rotation();}

float Widget::GetItemScale(Item* item)
{return item->ItemPointer->scale();}

void Widget::EndAnimation(Item* item,AnimationType choose)
{
    if(item->scPointer[choose]!=nullptr)
    {
        item->scPointer[choose]->over=2;
        item->scPointer[choose]=nullptr;
    }
}

bool Widget::IsAnimation(Item* item,AnimationType choose)
{return (item->scPointer[choose]!=nullptr)?true:false;}

void Widget::EndAllAnimation(Item* item)
{
   EndAnimation(item,Rotation);
   EndAnimation(item,Scale);
   EndAnimation(item,Move);
   EndAnimation(item,BlurRadius);
   EndAnimation(item,Opacity);
   EndAnimation(item,Color);
   EndAnimation(item,Picture);
   EndAnimation(item,Shear);
}

void Widget::SetViewCenter(int x, int y,GraphicsView *gview)
{gview->SetCenter(x,y);}

void Widget::SetViewCenter(Item* item,GraphicsView *gview)
{gview->SetCenter(item->ItemPointer);}

int Widget::GetViewX(GraphicsView *gview)
{return gview->viewX;}

int Widget::GetViewY(GraphicsView *gview)
{return gview->viewY;}

GraphicsView* Widget::AddView(int x, int y, int width, int height)
{
    #ifdef SelfAdaption
    adaptive(x,y);
    adaptive(width,height);
    #endif
    GraphicsView *view=new GraphicsView(this,this,x,y,width,height);
    view->show();
    #ifdef SelfAdaption
    view->scale(adaptiveRatioX,adaptiveRatioX);
    #endif
    return view;
}

void Widget::SetViewSize(int x, int y, int width, int height, GraphicsView *gview)
{
    #ifdef SelfAdaption
    adaptive(x,y);
    adaptive(width,height);
    #endif
    gview->setGeometry(x,y,width,height);
    gview->SetCenter(width/2,height/2);
}

int Widget::GetScreenWidth()
{return QApplication::desktop()->width();}

int Widget::GetScreenHeigh()
{return QApplication::desktop()->height();}

GraphicsScene* Widget::AddScene(int width, int height)
{return new GraphicsScene(0,0,width,height);}

void Widget::SetViewScene(GraphicsView *view, GraphicsScene *scene,int viewX,int viewY)
{
    view->setScene(scene);
    if(viewX==-1&&viewY==-1)
    {
        viewX=view->width()/adaptiveRatioX/2;
        viewY=view->height()/adaptiveRatioY/2;
    }
    SetViewCenter(viewX,viewY);
}

void Widget::SafeSleep(int time)
{
   QTimer T1;
   QEventLoop Q1;
   T1.setSingleShot(true);
   connect(&T1,SIGNAL(timeout()),&Q1,SLOT(quit()));
   T1.start(time);
   Q1.exec();
}

void Widget::SetItemLayer(Item* item,int Layer)
{
   //Qt默认都是0，如果在不手动排序的情况下将一个item设为顶层则设为1，底层-1
   item->ItemPointer->setZValue(Layer);
}

void Widget::SetItemOrder(Item* Belowitem, Item* Aboveitem)
{Belowitem->ItemPointer->stackBefore(Aboveitem->ItemPointer);}

void Widget::ScaleView(float sX, float sY, GraphicsView *view)
{
    #ifdef SelfAdaption
    adaptive(sX,sY);
    #endif
    view->Scale(sX,sY);
}

void Widget::RotateView(float set, GraphicsView *view)
{view->Rotate(set);}

String Widget::ReadTXT(String path,int line)
{
    if(path!=PreQFileName)
    {
        if(PreQFile!=nullptr)
        {delete PreQFile;}
        PreQFile=new QFile(path);
        PreQFileName=path;
    }
    PreQFile->open(QIODevice::ReadOnly);
    QTextStream text(PreQFile);
    String concert;
    if(line==-1)
    {concert=text.readAll();}
    else
    {concert=text.readLine(line);}
    PreQFile->close();
    return concert;
}

void Widget::WriteTXT(String path, String text)//这个函数等等再搞，问题超大
{
   if(path!=PreQFileName)
   {
       if(PreQFile!=nullptr)
       {delete PreQFile;}
       PreQFile=new QFile(path);
       PreQFileName=path;
   }
   PreQFile->open(QFile::Text|QFile::Append);
   QTextStream out(PreQFile);
   out<<text;
   PreQFile->close();
}

void Widget::WriteINI(String path, String section, String var, String value)
{
   if(path!=PreQSetName)
   {
       if(PreQSet!=nullptr)
       {delete PreQSet;}
       PreQSet=new QSettings(path,QSettings::IniFormat);
       PreQSetName=path;
   }
   PreQSet->setValue("/"+section+"/"+var,value);
}

String Widget::ReadINI(String path, String section, String var)
{
    if(path!=PreQSetName)
    {
        if(PreQSet!=nullptr)
        {delete PreQSet;}
        PreQSet=new QSettings(path,QSettings::IniFormat);
        PreQSetName=path;
    }
    String result=PreQSet->value("/"+section+"/"+var).toString();
    return result;
}

String Widget::AESEncrypt(String str,String key)
{
  AesHelper aes(key);
  return aes.aesEncrypt(str);
}

String Widget::AESUncrypt(String str,String key)
{
  AesHelper aes(key);
  return aes.aesUncrypt(str);
}

void Widget::ChangePixmapItem(String path,Item* item)
{item->PixmapItemPoniter->setPixmap(Pixmap(path));}

void Widget::ChangePixmapItem(Pixmap* pixmap,Item* item)
{item->PixmapItemPoniter->setPixmap(*pixmap);}

void Widget::SetItemEvent(Item *item,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar)
{
    assert(item->PixmapItemPoniter!=nullptr);
    item->PixmapItemPoniter->SetEvent(PressSlotfun,PressPar,ReleaseSlotfun,ReleasePar);
}

void Widget::RemoveFile(String path)
{QFile::remove(path);}

void Widget::ShearItem(Item* item,float X,float Y)
{
   QTransform tranform;
   tranform.shear(X,Y);
   item->ItemPointer->setTransform(tranform);
   item->ShearX=X;
   item->ShearY=Y;
}

float Widget::GetItemShearX(Item* item)
{return item->ShearX;}

float Widget::GetItemShearY(Item* item)
{return item->ShearY;}

void Widget::AddKeyEvent(Qt::Key key,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar)
{
    for(InputEvent &i:AllEvent)
    {
        if(i.key==key)
        {
            //如果已经有了，不能让空的给覆盖上
            if(PressSlotfun!=NULL_String)
            {i.PressFun=PressSlotfun;}
            if(PressPar!=NULL_ParametersStru)
            {i.PressPar=PressPar;}
            if(ReleaseSlotfun!=NULL_String)
            {i.ReleaseFun=ReleaseSlotfun;}
            if(ReleasePar!=NULL_ParametersStru)
            {i.ReleasePar=ReleasePar;}
            return;
        }
    }
    InputEvent event{key,-1,-1,-1,-1,PressPar,PressSlotfun,ReleasePar,ReleaseSlotfun,};
    AllEvent<<event;
}

void Widget::RemoveKeyEvent(Qt::Key key)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent.at(i).key==key)
        {
            AllEvent.removeAt(i);
            return;
        }
    }
}

void Widget::AddMouseEvent(int mouseX,int mouseY,int fmouseX,int fmouseY,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar)
{
    #ifdef SelfAdaption
    adaptive(mouseX,mouseY);
    adaptive(fmouseX,fmouseY);
    #endif
    for(InputEvent &i:AllEvent)
    {
        if(i.mouseX==mouseX&&i.mouseY==mouseY&&i.fmouseX==fmouseX&&i.fmouseY==fmouseY)
        {
            //如果已经有了，不能让空的给覆盖上
            if(PressSlotfun!=NULL_String)
            {i.PressFun=PressSlotfun;}
            if(PressPar!=NULL_ParametersStru)
            {i.PressPar=PressPar;}
            if(ReleaseSlotfun!=NULL_String)
            {i.ReleaseFun=ReleaseSlotfun;}
            if(ReleasePar!=NULL_ParametersStru)
            {i.ReleasePar=ReleasePar;}
            return;
        }
    }
    //没有就无所谓了
    InputEvent event;
    event.mouseX=mouseX;
    event.mouseY=mouseY;
    event.fmouseX=fmouseX;
    event.fmouseY=fmouseY;
    event.PressFun=PressSlotfun;
    event.PressPar=PressPar;
    event.ReleaseFun=ReleaseSlotfun;
    event.ReleasePar=ReleasePar;
    AllEvent<<event;
}

void Widget::RemoveMouseEvent(int mouseX, int mouseY,int fmouseX,int fmouseY)
{
    #ifdef SelfAdaption
    adaptive(mouseX,mouseY);
    adaptive(fmouseX,fmouseY);
    #endif
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent.at(i).mouseX==mouseX&&AllEvent.at(i).mouseY==mouseY&&AllEvent.at(i).fmouseX==fmouseX&&AllEvent.at(i).fmouseY==fmouseY)
        {
            AllEvent.removeAt(i);
            return;
        }
    }
}

void Widget::RemoveAllEvent()
{AllEvent.clear();}

void Widget::WaitSign(String signfun)
{
    QTimer t;
    QEventLoop q;
    t.setSingleShot(true);
    QByteArray ba = signfun.toLatin1();
    const char *function = ba.data();
    connect(lfevent,function,&q,SLOT(quit()));
    t.start();
    q.exec();
}

void Widget::HorizontallyFlip(Item *item)
{
    assert(item->PixmapItemPoniter!=nullptr);
    Pixmap pixmap=item->PixmapItemPoniter->pixmap();
    ChangePixmapItem(mirrorAndChange(&pixmap,true),item);
}

Pixmap* Widget::HorizontallyFlip(Pixmap *pixmap)
{return mirrorAndChange(pixmap,true);}

void Widget::VerticalFlip(Item *item)
{
    assert(item->PixmapItemPoniter!=nullptr);
    Pixmap pixmap=item->PixmapItemPoniter->pixmap();
    ChangePixmapItem(mirrorAndChange(&pixmap,false),item);
}

Pixmap* Widget::VerticalFlip(Pixmap *pixmap)
{return mirrorAndChange(pixmap,false);}

Timer* Widget::StartMultipleTimer(String slotfun,int time)
{
    QTimer *timer = new QTimer(this);
    QByteArray ba = slotfun.toLatin1();
    const char *ch=ba.data();
    QObject::connect(timer,SIGNAL(timeout()),this,ch);
    timer->start(time);
    return timer;
}

void Widget::StartSingleTimer(String slotfun,int time)
{
    QByteArray ba = slotfun.toLatin1();
    const char *ch=ba.data();
    QTimer::singleShot(time,this,ch);
}

Gesture* Widget::LoadGesture(QList<Pos> posSeq, int tolerance, String event)
{return new Gesture(posSeq,tolerance,event,false);}

Gesture* Widget::LoadGesture(LocusFunc locus, int tolerance, ProgressStand standard, int maxProgress, String event)
{return new Gesture(locus,standard,maxProgress,tolerance,event,false);}

void Widget::AddGesture(int mouseX,int mouseY,int fmouseX,int fmouseY,QList<Pos> posSeq,int tolerance,String event)
{AddGesture(mouseX,mouseY,fmouseX,fmouseY,new Gesture(posSeq,tolerance,event,true));}

void Widget::AddGesture(int mouseX, int mouseY, int fmouseX, int fmouseY, LocusFunc locus, int tolerance, ProgressStand standard, int maxProgress, String event)
{AddGesture(mouseX,mouseY,fmouseX,fmouseY,new Gesture(locus,standard,maxProgress,tolerance,event,true));}

void Widget::AddGesture(int mouseX, int mouseY, int fmouseX, int fmouseY, Gesture *gesture)
{
    #ifdef SelfAdaption
    adaptive(mouseX,mouseY);
    adaptive(fmouseX,fmouseY);
    #endif
    for(GestureArea* i:AllGestureArea)
    {
        if(i->mouseX==mouseX&&i->mouseY==mouseY&&i->fmouseX==fmouseX&&i->fmouseX==fmouseX)
        {
            i->allGesture<<gesture; //一个区域拥有很多手势
            return;
        }
    }
    GestureArea *ga=new GestureArea(mouseX,mouseY,fmouseX,fmouseY);
    ga->allGesture<<gesture;
    this->AllGestureArea<<ga;
    ga->allGesture<<gesture;
}

void Widget::RemoveGesture(Gesture *gesture)
{
    //注意，这个函数对比地址删除。仅在保存创建的手势指针时才管用，再实例化一个一样的手势删除没用
    for(GestureArea* i:AllGestureArea)
    {i->allGesture.removeAll(gesture);}
    delete gesture;
}

void Widget::RemoveGestureArea(int mouseX, int mouseY, int fmouseX, int fmouseY)
{
    #ifdef SelfAdaption
    adaptive(mouseX,mouseY);
    adaptive(fmouseX,fmouseY);
    #endif
    for(int i=0;i<AllGestureArea.length();i++)
    {
        if(AllGestureArea[i]->mouseX==mouseX&&
            AllGestureArea[i]->mouseY==mouseY&&
            AllGestureArea[i]->fmouseX==fmouseX&&
            AllGestureArea[i]->fmouseX==fmouseY)
        {
            delete AllGestureArea[i];
            AllGestureArea.removeAt(i);
            return;
        }
    }
}

void Widget::RemoveAllGestureArea()
{
    for(GestureArea* i:AllGestureArea)
    {delete i;}
    this->AllGestureArea.clear();
}

void Widget::AddExpansionSlot(String slotname, ParSlot slot)
{AllExpansionSlot<<new ExpansionSlot(slot,slotname);}

void Widget::AddExpansionSlot(String slotname, VoidSlot slot)
{AllExpansionSlot<<new ExpansionSlot(slot,slotname);}

void Widget::AddJSExpansionSlot(String JSFun)
{AllExpansionSlot<<new ExpansionSlot(JSFun);}

#ifdef AutoIsColliding
void Widget::AddAutoCollision(Item *item1, Item *item2, String slotfun, ParametersStru par)
{
    for(Collision &co:AllAutoCollision)
    {
        if(co.item1==item1&&co.item2==item2)
        {
            co.slot=slotfun;
            co.par=par;
            return;
        }
    }
    AllAutoCollision<<Collision{item1,item2,slotfun,par};
}

void Widget::RemoveAutoCollision(Item *item1, Item *item2)
{
    for(int i=0;i<AllAutoCollision.length();i++)
    {
        if(AllAutoCollision[i].item1==item1&&AllAutoCollision[i].item2==item2)
        {
            AllAutoCollision.removeAt(i);
            return;
        }
    }
}

void Widget::RemoveAllAutoCollision()
{AllAutoCollision.clear();}
#endif

PosF Widget::GetItemCenter(Item *item)
{
    assert(item->PixmapItemPoniter!=nullptr);
    return PosF(item->PixmapItemPoniter->pixmap().width()/2,item->PixmapItemPoniter->pixmap().height()/2);
}
