//-----本文件是引擎行为层给用户提供的接口的实现-----
#include "widget.h"

QPixmap* Widget::NewQPixmap(QString PicPath)
{return new QPixmap(PicPath);}

float Widget::GetQPixmapWidth(QPixmap *pixmap)
{return pixmap->width();}

float Widget::GetQPixmapHeight(QPixmap *pixmap)
{return pixmap->height();}

Item* Widget::AddPixmapItem(QString PicPath,float X,float Y,QString slotfun,QString down,ParametersStru *par,QGraphicsScene *scene)
{
    QPixmap mainpix(PicPath);
    MyItem *item=new MyItem(mainpix);
    item->fun=slotfun;
    item->s=this;
    item->par=par;
    if(down==NULL)
    {item->down=mainpix;}
    else
    {item->down=QPixmap(down);}
    item->up=mainpix;

    scene->addItem(item);
    item->setPos(X,Y);
    Item *ritem=new Item(item);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddPixmapItem(QPixmap *pixmap,float X,float Y,QString slotfun,QPixmap *down,ParametersStru *par,QGraphicsScene *scene)
{
    MyItem *item=new MyItem(*pixmap);
    item->fun=slotfun;
    item->s=this;
    item->par=par;
    if(down==NULL)
    {item->down=*pixmap;}
    else
    {item->down=*down;}
    item->up=*pixmap;

    scene->addItem(item);
    item->setPos(X,Y);
    Item *ritem=new Item(pixmap);
    AllItem<<ritem;
    return ritem;
}

Item* Widget::AddTextItem(QString Text,QString Font,int Size,int CR,int CG,int CB,float X,float Y,QGraphicsScene *scene)
{
   QGraphicsTextItem *text=new QGraphicsTextItem(Text);
   text->setFont(QFont(Font,Size));
   text->setDefaultTextColor(QColor(CR,CG,CB));
   scene->addItem(text);
   text->setPos(X,Y);
   Item *item=new Item(nullptr,text);
   AllItem<<item;
   return item;
}

Item* Widget::AddRectItem(float x,float y,float width,float height,QGraphicsScene *scene)
{
   QGraphicsRectItem *rect=new QGraphicsRectItem(x,y,width,height);
   scene->addItem(rect);
   Item *item=new Item(nullptr,rect);
   AllItem<<item;
   return item;
}

Item* Widget::AddEllipseItem(float x,float y,float width,float height,QGraphicsScene *scene)
{
   QGraphicsEllipseItem *Ellipse=new QGraphicsEllipseItem(x,y,width,height);
   scene->addItem(Ellipse);
   Item *item=new Item(nullptr,Ellipse);
   AllItem<<item;
   return item;
}

Item* Widget::AddLineItem(float x,float y,float fx,float fy,QGraphicsScene *scene)
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
   Item *gritem=item;
   if(gritem->Blur==nullptr)
   {gritem->Blur=new QGraphicsBlurEffect(this);}
   gritem->Blur->setBlurRadius(set);
   gritem->ItemPointer->setGraphicsEffect(gritem->Blur);
}

void Widget::MoveItem(Item* item, float X, float Y)
{item->ItemPointer->setPos(X,Y);}

void Widget::SetOpacityItem(Item* item, float set)
{item->ItemPointer->setOpacity(set);}

void Widget::SetColorItem(Item* item,float R,float G,float B)
{
   Item *gritem=item;
   if(gritem->Color==nullptr)
   {gritem->Color=new QGraphicsColorizeEffect(this);}
   gritem->Color->setColor(QColor(R,G,B));
   gritem->ItemPointer->setGraphicsEffect(gritem->Color);
}

void Widget::ClearScene(QGraphicsScene *scene)
{
   for(int i=0;i<AllItem.length();i++)
   {
       if(AllItem[i]->Blur!=nullptr)
       {delete AllItem[i]->Blur;}
       if(AllItem[i]->Color!=nullptr)
       {delete AllItem[i]->Color;}
       //由于场景中的图元会在调用clear方法时候自动删除，所以不用在这里删了
   }
   scene->clear();
   AllItem.clear();
}

void Widget::DeleteItem(Item* item)
{
   EndAllAnimation(item);

   if(item->PixmapItemPoniter==nullptr)
   {delete item->ItemPointer;}
   else
   {delete item->PixmapItemPoniter;}

   if(item->Blur!=nullptr)
   {delete item->Blur;}
   if(item->Color!=nullptr)
   {delete item->Color;}

   AllItem.removeAt(AllItem.indexOf(item));
   delete item;
}

QString Widget::GetPath(QString str)
{
   QString path;
   QDir dir;
   path=dir.currentPath();
   path+="/"+str;
   return path;
}

void Widget::SetVisibleItem(Item* item,bool Enabled)
{item->ItemPointer->setVisible(Enabled);}

void Widget::SetBackground(QString PicturePath,QGraphicsScene *scene)
{scene->setBackgroundBrush(QPixmap(PicturePath));}

void Widget::SetBackground(int R,int G,int B)
{scene->setBackgroundBrush(QColor(R,G,B));}

QMediaPlayer* Widget::PlayMusic(QString name,int volume,bool cycle)
{
   QMediaPlayer *player=new QMediaPlayer;
   if(!cycle)
   {
       player->setMedia(QUrl::fromLocalFile(name));
       player->setVolume(volume);
       player->play();
   }
   else
   {
       // 创建一直播放的背景音乐
       QUrl backgroundMusicUrl = QUrl::fromLocalFile(name);
       if (QFile::exists(backgroundMusicUrl.toLocalFile()))
       {
          player=new QMediaPlayer;
          player->setVolume(volume);
          QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();
          QMediaContent media(backgroundMusicUrl);
          backgroundMusicList->addMedia(media);
          backgroundMusicList->setCurrentIndex(0);
          // 设置背景音乐循环播放
          backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
          player->setPlaylist(backgroundMusicList);
        }
        player->play();
   }
   return player;
}

void Widget::PauseMusic(QMediaPlayer *player)
{player->pause();}

void Widget::ContinueMusic(QMediaPlayer *player)
{player->play();}

EasyThread* Widget::StartThread(QString slotfun,ParametersStru *par,bool track)
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

VideoPlayer* Widget::PlayVideo(QString path,int Volume,int x,int y,int width,int heigh,bool cycle,QString signfun,QGraphicsScene *scene)
{
   if(x==-1)
   {x=viewX-(WindowsWidth/2);}
   if(y==-1)
   {y=viewY-(WindowsHeigh/2);}
   VideoPlayer* video=new VideoPlayer(path,Volume,x,y,width,heigh,cycle,signfun,scene);
   video->start();
   return video;
}

void Widget::PauseVideo(VideoPlayer *video)
{video->mediaPlayer->pause();}

void Widget::ContinueVideo(VideoPlayer *video)
{video->mediaPlayer->play();}

void Widget::StopVideo(VideoPlayer *video)
{video->mediaPlayer->stop();}

void Widget::AnimationRotationItem(Item* item, float set,int times,QString signfun)
{
   assert(item->scPointer[Rotation]==nullptr);
   QGraphicsItem* gr=item->ItemPointer;
   float CurrentModulus=gr->rotation();
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[Rotation]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->start(Rotation);
}

void Widget::AnimationScaleItem(Item* item, float set,int times,QString signfun)
{
   assert(item->scPointer[Scale]==nullptr);
   QGraphicsItem* gr=item->ItemPointer;
   float CurrentModulus=gr->scale();
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[Scale]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->start(Scale);
}

void Widget::AnimationMoveItem(Item* item,float X,float Y,int time,QString signfun)
{
   assert(item->scPointer[Move]==nullptr);
   QGraphicsItem* gr=item->ItemPointer;
   float dx=gr->x();
   float dy=gr->y();
   SC *s=new SC(0,0,X-dx,Y-dy,time);
   item->scPointer[Move]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->start(Move);
}

void Widget::AnimationBlurRadiusItem(Item* item, float set, int times,QString signfun)
{
   assert(item->scPointer[BlurRadius]==nullptr);
   Item *gritem=item;
   float CurrentModulus;//当前系数
   if(gritem->Blur==nullptr)
   {
       CurrentModulus=0;
       gritem->Blur=new QGraphicsBlurEffect(this);
   }
   else
   {CurrentModulus=gritem->Blur->blurRadius();}
   QGraphicsItem* gr=gritem->ItemPointer;
   QGraphicsBlurEffect *effect=new QGraphicsBlurEffect(this);
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[BlurRadius]=s;
   s->gr=gr;
   s->Effect=effect;
   s->signfun=signfun;
   s->start(BlurRadius);
}

void Widget::AnimationSetOpacityItem(Item* item, float set, int times,QString signfun)
{
   assert(item->scPointer[Opacity]==nullptr);
   QGraphicsItem* gr=item->ItemPointer;
   float CurrentModulus=gr->opacity();
   SC *s=new SC(CurrentModulus,set,times);
   item->scPointer[Opacity]=s;
   s->gr=gr;
   s->signfun=signfun;
   s->start(Opacity);
}

void Widget::AnimationSetColorItem(Item* item, float R, float G, float B, int times,QString signfun)
{
   assert(item->scPointer[Color]==nullptr);
   Item *gritem=item;
   //当前系数
   float CurrentModulus;
   float CurrentModulus2;
   float CurrentModulus3;
   if(gritem->Color==nullptr)
   {
       //如果之前没有进行过着色,从0,0,0开始着色
       CurrentModulus=0;
       CurrentModulus2=0;
       CurrentModulus3=0;
       gritem->Color=new QGraphicsColorizeEffect(this);
   }
   else
   {
        QColor color=gritem->Color->color();
        CurrentModulus=color.red();
        CurrentModulus2=color.green();
        CurrentModulus3=color.blue();
   }

   QGraphicsItem* gr=gritem->ItemPointer;
   QGraphicsColorizeEffect *co = new QGraphicsColorizeEffect(this);
   SC *s=new SC(CurrentModulus,CurrentModulus2,CurrentModulus3,R,G,B,times);
   item->scPointer[Color]=s;
   s->gr=gr;
   s->co=co;
   s->signfun=signfun;
   s->start(Color);

   gritem->Color->setColor(QColor(R,G,B));
}

Item* Widget::AddPicAnimation(QVector<QString> address,int x,int y,int time,QString signfun,bool cycle,QGraphicsScene *scene)
{
   assert(!address.isEmpty());//断言，确认传入的图片容器不为空
   MyItem *temp=new MyItem(address[0]);//将第一张图片变为图元
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

   for(QVector<QString>::iterator iter=address.begin();iter!=address.end();++iter)//遍历容器中的所有图片
   {sc->pixmap.push_back(QPixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
   sc->start(Picture);
   sc->num=item;
   return item;
}

Item* Widget::AddPicAnimation(QVector<QPixmap*> allpixmap, int x, int y, int time, QString signfun, bool cycle, QGraphicsScene *scene)
{
    assert(!allpixmap.isEmpty());
    MyItem *item=new MyItem(*allpixmap[0]);
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

    for(int i=0;i<allpixmap.size();i++)
    {sc->pixmap.push_back(*allpixmap[i]);}
    sc->start(Picture);
    sc->num=ritem;
    return ritem;
}

void Widget::ChangePicAnimationItem(QVector<QString>allpixmap,Item* item,int time,QString signfun,bool cycle)
{
    assert(item->scPointer[Picture]==nullptr);
    assert(!allpixmap.isEmpty());//断言，确认传入的图片容器不为空
    MyItem *temp=item->PixmapItemPoniter;//查找到图元序号对应的MyPixmap指针
    temp->setPixmap(QPixmap(allpixmap[0]));//变更当前图片为图集的第一帧
    SC *sc=new SC(0,0,time);//创建SC实例
    item->scPointer[Picture]=sc;
    sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
    sc->cycle=cycle;//定义是否循环连续播图

    if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
    {sc->signfun=signfun;}

    for(QVector<QString>::iterator iter=allpixmap.begin();iter!=allpixmap.end();++iter)//遍历容器中的所有图片
    {sc->pixmap.push_back(QPixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
    sc->num=item;
}

void Widget::ChangePicAnimationItem(QVector<QPixmap*> allpixmap, Item *item, int time, QString signfun, bool cycle)
{
    assert(item->scPointer[Picture]==nullptr);
    assert(!allpixmap.isEmpty());//断言，确认传入的图片容器不为空
    MyItem *temp=new MyItem(*allpixmap[0]);//创建MyItem指针
    temp->setPixmap(*allpixmap[0]);//变更当前图片为图集的第一帧
    SC *sc=new SC(0,0,time);//创建SC实例
    item->scPointer[Picture]=sc;
    sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
    sc->cycle=cycle;//定义是否循环连续播图

    if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
    {sc->signfun=signfun;}

    for(int i=0;i<allpixmap.size();i++)//遍历容器中的所有图片
    {sc->pixmap.push_back(*allpixmap[i]);}//将所有图片压入SC类中储存图片的成员中
    sc->start(Picture);
    sc->num=item;
}

void Widget::AnimationShearItem(Item* item, float fx, float fy, int time, QString signfun)
{
   assert(item->scPointer[Shear]==nullptr);
   Item *gritem=item;
   SC *s=new SC(gritem->ShearX,gritem->ShearY,fx,fy,time);
   item->scPointer[Shear]=s;
   s->gr=gritem->ItemPointer;
   s->signfun=signfun;
   s->start(Shear);

   gritem->ShearX=fx;
   gritem->ShearY=fy;
}

float Widget::GetItemX(Item* item)
{return item->ItemPointer->x();}

float Widget::GetItemY(Item* item)
{return item->ItemPointer->y();}

float Widget::GetItemR(Item* item)
{
   Item *gritem=item;
   if(gritem->Color==nullptr)
   {return -1;}
   return gritem->Color->color().red();
}

float Widget::GetItemG(Item* item)
{
   Item *gritem=item;
   if(gritem->Color==nullptr)
   {return -1;}
   return gritem->Color->color().green();
}

float Widget::GetItemB(Item* item)
{
   Item *gritem=item;
   if(gritem->Color==nullptr)
   {return -1;}
   return gritem->Color->color().blue();
}

float Widget::GetItemBlur(Item* item)
{
   Item *gritem=item;
   if(gritem->Blur==nullptr)
   {return 0;}
   return gritem->Blur->blurRadius();
}

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
{
   gview->centerOn(x,y);
   if(gview==MainView)
   {
       this->viewX=x;
       this->viewY=y;
   }
}

void Widget::SetViewItemCenter(Item* item,GraphicsView *gview)
{
   Item *gritem=item;
   gview->centerOn(gritem->ItemPointer);
   if(gview==MainView)
   {
       this->viewX=gritem->ItemPointer->x();
       this->viewY=gritem->ItemPointer->y();
   }
}

float Widget::GetMainViewX()
{return viewX;}

float Widget::GetMainViewY()
{return viewY;}

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
{gview->setGeometry(x,y,width,height);}

float Widget::GetScreenWidth()
{return QApplication::desktop()->width();}

float Widget::GetScreenHeigh()
{return QApplication::desktop()->height();}

QGraphicsScene* Widget::AddScene(int width, int height)
{
   QGraphicsScene *scene=new QGraphicsScene(0,0,width,height);
   return scene;
}

void Widget::SetScene(GraphicsView *view, QGraphicsScene *scene)
{view->setScene(scene);}

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

QString Widget::ReadTXT(QString path,int line)
{
   QFile file(path);
   file.open(QIODevice::ReadOnly);
   QTextStream text(&file);
   QString concert;
   if(line==-1)
   {concert=text.readAll();}
   else
   {concert=text.readLine(line);}
   file.close();
   return concert;
}

void Widget::WriteTXT(QString path, QString text)//这个函数等等再搞，问题超大
{
   QFile file(path);
   file.open(QFile::Text|QFile::Append);
   QTextStream out(&file);
   out<<text;
   file.close();
}

void Widget::WriteINI(QString path, QString section, QString var, QString value)
{
   QSettings configIniWrite(path,QSettings::IniFormat);
   configIniWrite.setValue("/"+section+"/"+var,value);
}

QString Widget::ReadINI(QString path, QString section, QString var)
{
   QSettings configIniRead(path,QSettings::IniFormat);
   QString result=configIniRead.value("/"+section+"/"+var).toString();
   return result;
}

QString Widget::AESEncrypt(QString str,QString key)
{
  AesHelper aes(key);
  return aes.aesEncrypt(str);
}

QString Widget::AESUncrypt(QString str,QString key)
{
  AesHelper aes(key);
  return aes.aesUncrypt(str);
}

void Widget::ChangePixmapItem(QString path,Item* item)
{item->PixmapItemPoniter->setPixmap(QPixmap(path));}

void Widget::ChangePixmapItem(QPixmap* pixmap,Item* item)
{item->PixmapItemPoniter->setPixmap(*pixmap);}

void Widget::DeleteFile(QString path)
{QFile::remove(path);}

void Widget::SetShearItem(Item* item,float x,float y)
{
   Item *gritem=item;
   QTransform *tranform=new QTransform;
   tranform->shear(x,y);
   gritem->ItemPointer->setTransform(*tranform);
   gritem->ShearX=x;
   gritem->ShearY=y;
   delete tranform;
}

float Widget::GetItemShearX(Item* item)
{return item->ShearX;}

float Widget::GetItemShearY(Item* item)
{return item->ShearY;}

void Widget::SetKeyEvent(Qt::Key key, QString slotfun,ParametersStru *par)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==key)
        {
            AllEvent[i]->par=par;
            AllEvent[i]->slotfun=slotfun;
            return;
        }
    }
    InputEvent *event=new InputEvent{key,-1,-1,-1,-1,par,slotfun};
    AllEvent<<event;
}

void Widget::DeleteKeyEvent(Qt::Key key)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==key)
        {
            delete AllEvent[i];
            AllEvent.removeAt(i);
            return;
        }
    }
}

void Widget::SetMouseEvent(float MouseX, float MouseY,float fMouseX,float fMouseY,QString slotfun, ParametersStru *par)
{
    InputEvent *event=new InputEvent;
    event->MouseX=MouseX;
    event->MouseY=MouseY;
    event->par=par;
    event->fMouseX=fMouseX;
    event->fMouseY=fMouseY;
    event->slotfun=slotfun;
    AllEvent<<event;
}

void Widget::DeleteMouseEvent(float MouseX, float MouseY,float fMouseX,float fMouseY)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->MouseX==MouseX&&
           AllEvent[i]->MouseY==MouseY&&
           AllEvent[i]->fMouseX==fMouseX&&
           AllEvent[i]->fMouseY==fMouseY)
        {
            delete AllEvent[i];
            AllEvent.removeAt(i);
        }
    }
}

void Widget::DeleteAllEvent()
{
    for(int i=0;i<AllEvent.length();i++)
    {delete AllEvent[i];}
    AllEvent.clear();
}

void Widget::WaitSign(QString signfun)
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
