//-----本文件是引擎行为层给用户提供的接口的实现-----
#include "widget.h"

Pixmap* Widget::NewPixmap(String PicPath)
{return new Pixmap(PicPath);}

RGBColor Widget::NewRGBColor(int R, int G, int B)
{return RGBColor(R,G,B);}

float Widget::GetPixmapWidth(Pixmap *pixmap)
{return pixmap->width();}

float Widget::GetPixmapHeight(Pixmap *pixmap)
{return pixmap->height();}

Item* Widget::AddPixmapItem(String PicPath,float X,float Y,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar,GraphicsScene *scene)
{
    Pixmap mainpix(PicPath);
    MyItem *item=new MyItem(mainpix);
    item->s=this;
    item->SetEvent(PressSlotfun,PressPar,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(X,Y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddPixmapItem(Pixmap *pixmap,float X,float Y,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar,GraphicsScene *scene)
{
    MyItem *item=new MyItem(*pixmap);
    item->s=this;
    item->SetEvent(PressSlotfun,PressPar,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(X,Y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddButtonItem(String PicPath, float X, float Y, String ReleaseSlotfun, String PressPic, String PressMusic,int volume, ParametersStru ReleasePar, GraphicsScene *scene)
{
    Pixmap mainpix(PicPath);
    MyItem *item=new MyItem(mainpix);
    item->s=this;
    if(PressPic!=NULL_String)
    {item->SetButton(mainpix,Pixmap(PressPic),PressMusic,volume);}
    else
    {item->SetButton(mainpix,mainpix,PressMusic,volume);}
    item->SetEvent(NULL_String,NULL_ParametersStru,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(X,Y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddButtonItem(Pixmap *pixmap, float X, float Y, String ReleaseSlotfun, Pixmap *PressPic, String PressMusic,int volume, ParametersStru ReleasePar, GraphicsScene *scene)
{
    MyItem *item=new MyItem(*pixmap);
    item->s=this;
    if(PressPic!=nullptr)
    {item->SetButton(*pixmap,*PressPic,PressMusic,volume);}
    else
    {item->SetButton(*pixmap,*pixmap,PressMusic,volume);}
    item->SetEvent(NULL_String,NULL_ParametersStru,ReleaseSlotfun,ReleasePar);
    scene->addItem(item);
    item->setPos(X,Y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddTextItem(String Text,String Font,int Size,int CR,int CG,int CB,float X,float Y,GraphicsScene *scene)
{return AddTextItem(Text,Font,Size,RGBColor(CR,CG,CB),X,Y,scene);}

Item* Widget::AddTextItem(String Text, String Font, int Size, RGBColor color, float X, float Y, GraphicsScene *scene)
{
    QGraphicsTextItem *text=new QGraphicsTextItem(Text);
    text->setFont(QFont(Font,Size));
    text->setDefaultTextColor(color);
    scene->addItem(text);
    text->setPos(X,Y);
    Item *item=new Item(nullptr,text);
    AllItem<<item;
    return item;
}

Item* Widget::AddRectItem(float x,float y,float width,float height,GraphicsScene *scene)
{
   QGraphicsRectItem *rect=new QGraphicsRectItem(x,y,width,height);
   scene->addItem(rect);
   Item *item=new Item(nullptr,rect);
   AllItem<<item;
   return item;
}

Item* Widget::AddEllipseItem(float x,float y,float width,float height,GraphicsScene *scene)
{
   QGraphicsEllipseItem *Ellipse=new QGraphicsEllipseItem(x,y,width,height);
   scene->addItem(Ellipse);
   Item *item=new Item(nullptr,Ellipse);
   AllItem<<item;
   return item;
}

Item* Widget::AddLineItem(float x,float y,float fx,float fy,GraphicsScene *scene)
{
   QGraphicsLineItem *line=new QGraphicsLineItem(x,y,fx,fy);
   scene->addItem(line);
   Item *item=new Item(nullptr,line);
   AllItem<<item;
   return item;
}

void Widget::RotationItem(Item* item, float set)
{item->ItemPointer->setRotation(set);}

void Widget::ScaleItem(Item* item, float set)
{item->ItemPointer->setScale(set);}

void Widget::BlurRadiusItem(Item* item, float set)
{
   if(item->Blur==nullptr)
   {item->Blur=new QGraphicsBlurEffect(this);}
   item->Blur->setBlurRadius(set);
   item->ItemPointer->setGraphicsEffect(item->Blur);
}

void Widget::DropShadowItem(Item* item, float shadowX,float shadowY)//还没写完
{
    QGraphicsDropShadowEffect *e2 = new QGraphicsDropShadowEffect(this);
    e2->setOffset(shadowX,shadowY);
    item->ItemPointer->setGraphicsEffect(e2);
}

void Widget::MoveItem(Item* item, float X, float Y)
{item->ItemPointer->setPos(X,Y);}

void Widget::SetOpacityItem(Item* item, float set)
{item->ItemPointer->setOpacity(set);}

void Widget::SetRGBColorItem(Item* item,float R,float G,float B)
{
   if(item->Color==nullptr)
   {item->Color=new QGraphicsColorizeEffect(this);}
   item->Color->setColor(RGBColor(R,G,B));
   item->ItemPointer->setGraphicsEffect(item->Color);
}

void Widget::ClearScene(GraphicsScene *scene)
{
   for(auto i:AllItem)
   {DeleteItem(i);}
   scene->clear();//这句目测没用
}

void Widget::DeleteItem(Item* item)
{
   EndAllAnimation(item);
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

void Widget::DeleteMusic(MusicPlayer *player)
{
    player->stop();
    delete player;
}

void Widget::StopMusic(MusicPlayer *player)
{player->stop();}

EasyThread* Widget::StartThread(String slotfun,ParametersStru par,bool track)
{
    if(track)
    {
        EasyThread *thread=new EasyThread(slotfun,par);
        thread->start();
        return thread;
    }
    else
    {
        RunFun(slotfun,par);
        return nullptr;
    }
}

void Widget::StopThread(EasyThread *thread)
{thread->terminate();}

bool Widget::ItemColliding(Item* item1,Item* item2)
{return isColliding(item1->ItemPointer,item2->ItemPointer);}

VideoPlayer* Widget::AddVideo(String path,int Volume,int x,int y,int width,int heigh,bool cycle,String signfun,GraphicsScene *scene)
{
   if(x==-1)
   {x=MainView->viewX-(WindowsWidth/2);}
   if(y==-1)
   {y=MainView->viewY-(WindowsHeigh/2);}
   VideoPlayer* video=new VideoPlayer(path,Volume,x,y,width,heigh,cycle,signfun,scene);
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

void Widget::DeleteVideo(VideoPlayer *video)
{
    video->mediaPlayer->stop();
    delete video;
}

void Widget::StopVideo(VideoPlayer *video)
{video->mediaPlayer->stop();}

void Widget::AnimationRotationItem(Item* item, float set,int times,String signfun)
{
   EndAnimation(item,Rotation);
   QGraphicsItem* gr=item->ItemPointer;
   float CurrentModulus=gr->rotation();
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[Rotation]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->num=item;
   s->start(Rotation);
}

void Widget::AnimationRotationItem(Item *item, SCFun scfun, int times, String signfun)
{
    EndAnimation(item,Rotation);
    SC *s=new SC(0,0,times);
    item->scPointer[Rotation]=s;
    s->gr=item->ItemPointer;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(Rotation);
}

void Widget::AnimationScaleItem(Item* item, float set,int times,String signfun)
{
   EndAnimation(item,Scale);
   QGraphicsItem* gr=item->ItemPointer;
   float CurrentModulus=gr->scale();
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[Scale]=s;
   s->gr=item->ItemPointer;
   s->signfun=signfun;
   s->num=item;
   s->start(Scale);
}

void Widget::AnimationScaleItem(Item *item, SCFun scfun, int times, String signfun)
{
    EndAnimation(item,Scale);
    SC *s=new SC(0,0,times);
    item->scPointer[Scale]=s;
    s->gr=item->ItemPointer;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(Scale);
}

void Widget::AnimationBlurRadiusItem(Item* item, float set, int times,String signfun)
{
   EndAnimation(item,BlurRadius);
   float CurrentModulus;//当前系数
   if(item->Blur==nullptr)
   {
       CurrentModulus=0;
       item->Blur=new QGraphicsBlurEffect(this);
   }
   else
   {CurrentModulus=item->Blur->blurRadius();}
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[BlurRadius]=s;
   s->gr=item->ItemPointer;
   s->Effect=item->Blur;
   s->signfun=signfun;
   s->num=item;
   s->start(BlurRadius);
}

void Widget::AnimationBlurRadiusItem(Item *item, SCFun scfun, int times, String signfun)
{
    EndAnimation(item,BlurRadius);
    if(item->Blur==nullptr)
    {item->Blur=new QGraphicsBlurEffect(this);}
    SC *s=new SC(0,0,times);
    item->scPointer[BlurRadius]=s;
    s->gr=item->ItemPointer;
    s->Effect=item->Blur;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(BlurRadius);
}

void Widget::AnimationSetOpacityItem(Item* item, float set, int times,String signfun)
{
   EndAnimation(item,Opacity);
   QGraphicsItem* gr=item->ItemPointer;
   float CurrentModulus=gr->opacity();
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[Opacity]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->num=item;
   s->start(Opacity);
}

void Widget::AnimationSetOpacityItem(Item *item, SCFun scfun, int times, String signfun)
{
    EndAnimation(item,Opacity);
    SC *s=new SC(0,0,times);
    item->scPointer[Opacity]=s;
    s->gr=item->ItemPointer;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(Opacity);
}

void Widget::AnimationMoveItem(Item* item,float X,float Y,int time,String signfun)
{
   EndAnimation(item,Move);
   QGraphicsItem* gr=item->ItemPointer;
   SC *s=new SC(gr->x(),gr->y(),X,Y,time);
   item->scPointer[Move]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->num=item;
   s->start(Move);
}

void Widget::AnimationMoveItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,Move);
    SC *s=new SC(0,0,0,0,time);
    item->scPointer[Move]=s;
    s->gr=item->ItemPointer;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(Move);
}

void Widget::AnimationSetViewCenter(GraphicsView *view, float X, float Y, int time, String signfun)
{
    SC *s=new SC(view->viewX,view->viewY,X,Y,time);
    s->gv=view;
    s->signfun=signfun;
    s->start(20);
}

void Widget::AnimationSetViewCenter(GraphicsView *view, SCFun scfun, int time, String signfun)
{
    SC *s=new SC(0,0,0,0,time);
    s->gv=view;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->start(20);
}

void Widget::AnimationShearItem(Item* item, float fx, float fy, int time, String signfun)
{
   EndAnimation(item,Shear);
   SC *s=new SC(item->ShearX,item->ShearY,fx,fy,time);
   item->scPointer[Shear]=s;
   s->gr=item->ItemPointer;
   s->signfun=signfun;
   s->num=item;
   s->start(Shear);
}

void Widget::AnimationShearItem(Item *item, SCFun scfun, int time, String signfun)
{
    EndAnimation(item,Shear);
    SC *s=new SC(0,0,0,0,time);
    item->scPointer[Shear]=s;
    s->gr=item->ItemPointer;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(Shear);
}

void Widget::AnimationSetRGBColorItem(Item* item, float R, float G, float B, int times,String signfun)
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
   SC *s=new SC(CurrentModulus,CurrentModulus2,CurrentModulus3,R,G,B,times);
   item->scPointer[Color]=s;
   s->gr=item->ItemPointer;
   s->co=item->Color;
   s->signfun=signfun;
   s->num=item;
   s->start(Color);
}

void Widget::AnimationSetRGBColorItem(Item *item, SCFun scfun, int times, String signfun)
{
    EndAnimation(item,Color);
    SC *s=new SC(0,0,0,0,0,0,times);
    item->scPointer[Color]=s;
    s->gr=item->ItemPointer;
    s->co=item->Color;
    s->signfun=signfun;
    s->UesSCFun(scfun);
    s->num=item;
    s->start(Color);
}

Item* Widget::AddPicAnimation(QVector<String> address,int x,int y,int time,String signfun,bool cycle,GraphicsScene *scene)
{
   assert(!address.isEmpty());//断言，确认传入的图片容器不为空
   MyItem *temp=new MyItem(address.at(0));//将第一张图片变为图元
   scene->addItem(temp);//将第一张图片显示在场景中
   temp->setPos(x,y);//设置其位置
   Item *item=new Item(temp);
   AllItem<<item;

   SC *sc=new SC(0,0,time);//创建SC实例
   item->scPointer[Picture]=sc;
   sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
   sc->cycle=cycle;//定义是否循环连续播图

   if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
   {sc->signfun=signfun;}

   for(QVector<String>::iterator iter=address.begin();iter!=address.end();++iter)//遍历容器中的所有图片
   {sc->pixmap.push_back(Pixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
   sc->start(Picture);
   sc->num=item;
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

    SC *sc=new SC(0,0,time);
    ritem->scPointer[Picture]=sc;
    sc->pi=item;
    sc->cycle=cycle;

    if(!cycle)
    {sc->signfun=signfun;}

    for(auto i:allpixmap)
    {sc->pixmap.push_back(*i);}
    sc->start(Picture);
    sc->num=ritem;
    return ritem;
}

void Widget::ChangePicAnimationItem(QVector<String>allpixmap,Item* item,int time,String signfun,bool cycle)
{
    assert(!allpixmap.isEmpty());//断言，确认传入的图片容器不为空
    EndAnimation(item,Picture);
    MyItem *temp=item->PixmapItemPoniter;
    temp->setPixmap(Pixmap(allpixmap.at(0)));//变更当前图片为图集的第一帧
    SC *sc=new SC(0,0,time);//创建SC实例
    item->scPointer[Picture]=sc;
    sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
    sc->cycle=cycle;//定义是否循环连续播图

    if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
    {sc->signfun=signfun;}

    for(QVector<String>::iterator iter=allpixmap.begin();iter!=allpixmap.end();++iter)//遍历容器中的所有图片
    {sc->pixmap.push_back(Pixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
    sc->num=item;
}

void Widget::ChangePicAnimationItem(QVector<Pixmap*> allpixmap, Item *item, int time, String signfun, bool cycle)
{
    assert(!allpixmap.isEmpty());//断言，确认传入的图片容器不为空
    EndAnimation(item,Picture);
    MyItem *temp=item->PixmapItemPoniter;
    temp->setPixmap(*allpixmap.at(0));//变更当前图片为图集的第一帧
    SC *sc=new SC(0,0,time);//创建SC实例
    item->scPointer[Picture]=sc;
    sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
    sc->cycle=cycle;//定义是否循环连续播图

    if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
    {sc->signfun=signfun;}

    for(auto i:allpixmap)//遍历容器中的所有图片
    {sc->pixmap.push_back(*i);}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
    sc->num=item;
}

float Widget::GetItemX(Item* item)
{return item->ItemPointer->x();}

float Widget::GetItemY(Item* item)
{return item->ItemPointer->y();}

float Widget::GetItemR(Item* item)
{return (item->Color==nullptr)?-1:item->Color->color().red();}

float Widget::GetItemG(Item* item)
{return (item->Color==nullptr)?-1:item->Color->color().green();}

float Widget::GetItemB(Item* item)
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

void Widget::SetViewCenter(float x, float y,GraphicsView *gview)
{gview->SetCenter(x,y);}

void Widget::SetViewCenter(Item* item,GraphicsView *gview)
{gview->SetCenter(item->ItemPointer);}

float Widget::GetViewX(GraphicsView *gview)
{return gview->viewX;}

float Widget::GetViewY(GraphicsView *gview)
{return gview->viewY;}

GraphicsView* Widget::AddView(float x, float y, float width, float height)
{
   GraphicsView *view=new GraphicsView(this);
   view->setGeometry(x,y,width,height);
   view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用竖直滚动条
   view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平滚动条
   view->show();
   return view;
}

void Widget::SetViewSize(float x, float y, float width, float height, GraphicsView *gview)
{
    gview->setGeometry(x,y,width,height);
    gview->viewX=width/2;
    gview->viewY=height/2;
}

float Widget::GetScreenWidth()
{return QApplication::desktop()->width();}

float Widget::GetScreenHeigh()
{return QApplication::desktop()->height();}

GraphicsScene* Widget::AddScene(int width, int height)
{return new GraphicsScene(0,0,width,height);}

void Widget::SetScene(GraphicsView *view, GraphicsScene *scene,float viewX,float viewY)
{
    view->setScene(scene);
    if(viewX==-1)
    {viewX=view->width()/2;}
    if(viewY==-1)
    {viewY=view->height()/2;}
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

void Widget::ScaleView(float sx, float sy, GraphicsView *view)
{view->Scale(sx,sy);}

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

void Widget::DeleteFile(String path)
{QFile::remove(path);}

void Widget::ShearItem(Item* item,float x,float y)
{
   QTransform *tranform=new QTransform;
   tranform->shear(x,y);
   item->ItemPointer->setTransform(*tranform);
   item->ShearX=x;
   item->ShearY=y;
   delete tranform;
}

float Widget::GetItemShearX(Item* item)
{return item->ShearX;}

float Widget::GetItemShearY(Item* item)
{return item->ShearY;}

void Widget::AddKeyEvent(Qt::Key key,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar)
{
    for(auto i:AllEvent)
    {
        if(i.key==key)
        {
            i.PressFun=PressSlotfun;
            i.PressPar=PressPar;
            i.ReleaseFun=ReleaseSlotfun;
            i.ReleasePar=ReleasePar;
            return;
        }
    }
    InputEvent event{key,-1,-1,-1,-1,PressPar,PressSlotfun,ReleasePar,ReleaseSlotfun,};
    AllEvent<<event;
}

void Widget::DeleteKeyEvent(Qt::Key key)
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

void Widget::AddMouseEvent(float MouseX,float MouseY,float fMouseX,float fMouseY,String PressSlotfun,ParametersStru PressPar,String ReleaseSlotfun,ParametersStru ReleasePar)
{
    for(auto i:AllEvent)
    {
        if(i.MouseX==MouseX&&i.MouseY==MouseY&&i.fMouseX==fMouseX&&i.fMouseY==fMouseY)
        {
            i.PressFun=PressSlotfun;
            i.PressPar=PressPar;
            i.ReleaseFun=ReleaseSlotfun;
            i.ReleasePar=ReleasePar;
            return;
        }
    }
    InputEvent event;
    event.MouseX=MouseX;
    event.MouseY=MouseY;
    event.fMouseX=fMouseX;
    event.fMouseY=fMouseY;
    event.PressFun=PressSlotfun;
    event.PressPar=PressPar;
    event.ReleaseFun=ReleaseSlotfun;
    event.ReleasePar=ReleasePar;
    AllEvent<<event;
}

void Widget::DeleteMouseEvent(float MouseX, float MouseY,float fMouseX,float fMouseY)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent.at(i).MouseX==MouseX&&AllEvent.at(i).MouseY==MouseY&&AllEvent.at(i).fMouseX==fMouseX&&AllEvent.at(i).fMouseY==fMouseY)
        {
            AllEvent.removeAt(i);
            return;
        }
    }
}

void Widget::DeleteAllEvent()
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

QTimer* Widget::StartMultipleTimer(String slotfun,int time)
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

void Widget::DeleteTimer(QTimer* timer)
{delete timer;}
