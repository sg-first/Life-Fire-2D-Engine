//-----本文件是引擎行为层给用户提供的接口的实现-----
#include "widget.h"

int Widget::AddPixmapItem(QString PicPath,float X,float Y,QString signfun,QString down,ParametersStru *par,QGraphicsScene *scene)
{
   MyPixmap *temp=new MyPixmap(QPixmap(PicPath));
   temp->fun=signfun;
   temp->s=this;
   temp->par=par;

   if(down==NULL)
   {temp->down=QPixmap(PicPath);}
   else
   {temp->down=QPixmap(down);}
   temp->up=QPixmap(PicPath);
   scene->addItem(temp);
   temp->setPos(X,Y);
   ItemNumber<<ItemNowNumber;
   Item *item=new Item{temp,temp,NULL,NULL,0,0};
   AllItem<<item;
   int retur=ItemNowNumber;
   ItemNowNumber++;
   return retur;
}

int Widget::AddTextItem(QString Text,QString Font,int Size,int CR,int CG,int CB,float X,float Y,QGraphicsScene *scene)
{
   QGraphicsTextItem *text=new QGraphicsTextItem(Text);
   text->setFont(QFont(Font,Size));
   text->setDefaultTextColor(QColor(CR,CG,CB));
   scene->addItem(text);
   text->setPos(X,Y);
   ItemNumber<<ItemNowNumber;
   Item *item=new Item{text,NULL,NULL,NULL,0,0};
   AllItem<<item;
   int retur=ItemNowNumber;
   ItemNowNumber++;
   return retur;
}

int Widget::AddRectItem(float x,float y,float width,float height,QGraphicsScene *scene)
{
   QGraphicsRectItem *rect=new QGraphicsRectItem(x,y,width,height);
   scene->addItem(rect);
   ItemNumber<<ItemNowNumber;
   Item *item=new Item{rect,NULL,NULL,NULL,0,0};
   AllItem<<item;
   int retur=ItemNowNumber;
   ItemNowNumber++;
   return retur;
}

int Widget::AddEllipseItem(float x,float y,float width,float height,QGraphicsScene *scene)
{
   QGraphicsEllipseItem *Ellipse=new QGraphicsEllipseItem(x,y,width,height);
   scene->addItem(Ellipse);
   ItemNumber<<ItemNowNumber;
   Item *item=new Item{Ellipse,NULL,NULL,NULL,0,0};
   AllItem<<item;
   int retur=ItemNowNumber;
   ItemNowNumber++;
   return retur;
}

int Widget::AddLineItem(float x,float y,float fx,float fy,QGraphicsScene *scene)
{
   QGraphicsLineItem *line=new QGraphicsLineItem(x,y,fx,fy);
   scene->addItem(line);
   ItemNumber<<ItemNowNumber;
   Item *item=new Item{line,NULL,NULL,NULL,0,0};
   AllItem<<item;
   int retur=ItemNowNumber;
   ItemNowNumber++;
   return retur;
}

void Widget::RotationItem(int item, float set,bool LastIndex)
{findItem(item,LastIndex)->ItemPointer->setRotation(set);}

void Widget::ScaleItem(int item, float set,bool LastIndex)
{findItem(item,LastIndex)->ItemPointer->setScale(set);}

void Widget::BlurRadiusItem(int item, float set,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   if(gritem->Blur==NULL)
   {gritem->Blur=new QGraphicsBlurEffect(this);}
   gritem->Blur->setBlurRadius(set);
   gritem->ItemPointer->setGraphicsEffect(gritem->Blur);
}

void Widget::SetOpacityItem(int item, float set,bool LastIndex)
{findItem(item)->ItemPointer->setOpacity(set);}

void Widget::SetColorItem(int item,float R,float G,float B,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   if(gritem->Color==NULL)
   {gritem->Color=new QGraphicsColorizeEffect(this);}
   gritem->Color->setColor(QColor(R,G,B));
   gritem->ItemPointer->setGraphicsEffect(gritem->Color);
}

void Widget::ClearScene(QGraphicsScene *scene)
{
   for(int i=0;i<AllItem.length();i++)
   {
       if(AllItem[i]->Blur!=NULL)
       {delete AllItem[i]->Blur;}
       if(AllItem[i]->Color!=NULL)
       {delete AllItem[i]->Color;}
       //由于场景中的图元会在调用clear方法时候自动删除，所以不用在这里删了
   }
   scene->clear();
   AllItem.clear();
   ItemNumber.clear();
   ItemNowNumber=0;
}

void Widget::DeleteItem(int item,bool LastIndex)
{
   EndAllAnimation(item);
   int sub=qListFindSubscript(LastIndex,item);
   delete AllItem[sub]->ItemPointer;
   if(AllItem[sub]->Blur!=NULL)
   {delete AllItem[sub]->Blur;}
   if(AllItem[sub]->Color!=NULL)
   {delete AllItem[sub]->Color;}
   AllItem.removeAt(sub);
   ItemNumber.removeAt(sub);
}

void Widget::MoveItem(int item, float X, float Y,bool LastIndex)
{findItem(item,LastIndex)->ItemPointer->setPos(X,Y);}

QString Widget::GetPath(QString str)
{
   QString path;
   QDir dir;
   path=dir.currentPath();
   path+="/"+str;
   return path;
}

void Widget::SetVisibleItem(int item,bool Enabled,bool LastIndex)
{findItem(item,LastIndex)->ItemPointer->setVisible(Enabled);}

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
        if (&player)
        player->play();
   }
   return player;
}

void Widget::PauseMusic(QMediaPlayer *player)
{player->pause();}

void Widget::ContinueMusic(QMediaPlayer *player)
{player->play();}

void Widget::AnimationMoveItem(int item,float X,float Y,int time,QString signfun,ParametersStru *par,bool LastIndex)
{
   QGraphicsItem* gr=findItem(item,LastIndex)->ItemPointer;
   float dx=gr->x();
   float dy=gr->y();
   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(0,0,X-dx,Y-dy,time,it);
   s->gr=gr;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(3);
}

EasyThread* Widget::StartThread(QString signfun,ParametersStru *par,bool track)
{
   if(track)
   {
     EasyThread *thread=new EasyThread;
     thread->fun=signfun;
     thread->par=par;
     thread->start();
     return thread;
   }
   QByteArray ba = signfun.toLatin1();
   const char *function = ba.data();
   if(par==NULL)
   {QMetaObject::invokeMethod(thob,function,Qt::QueuedConnection);}
   else
   {QMetaObject::invokeMethod(thob,function,Qt::QueuedConnection,Q_ARG(ParametersStru,*par));}
   return NULL;
}

void Widget::StopThread(EasyThread *thread)
{thread->terminate();}

bool Widget::ItemColliding(int item1,int item2,bool LastIndex1,bool LastIndex2)
{return isColliding(findItem(item1,LastIndex1)->ItemPointer,findItem(item2,LastIndex2)->ItemPointer);}

VideoPlayer* Widget::PlayVideo(QString path,int Volume,int x,int y,int width,int heigh,bool cycle,QString signfun,ParametersStru *par,QGraphicsScene *scene)
{
   if(x==-1)
   {x=viewX-(WindowsWidth/2);}
   if(y==-1)
   {y=viewY-(WindowsHeigh/2);}
   //time为视频时长，单位为秒
   VideoPlayer* video=new VideoPlayer(path,Volume,x,y,width,heigh,cycle,signfun,par,scene);
   video->start();
   return video;
}

void Widget::PauseVideo(VideoPlayer *video)
{video->mediaPlayer->pause();}

void Widget::ContinueVideo(VideoPlayer *video)
{video->mediaPlayer->play();}

void Widget::StopVideo(VideoPlayer *video)
{video->mediaPlayer->stop();}

void Widget::AnimationRotationItem(int item, float set,int times,QString signfun,ParametersStru *par,bool LastIndex)
{
   QGraphicsItem* gr=findItem(item,LastIndex)->ItemPointer;
   float CurrentModulus=gr->rotation();

   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(CurrentModulus,set,times,it);
   s->gr=gr;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(1);
}

void Widget::AnimationScaleItem(int item, float set,int times,QString signfun,ParametersStru *par,bool LastIndex)
{
   QGraphicsItem* gr=findItem(item,LastIndex)->ItemPointer;
   float CurrentModulus=gr->scale();
   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(CurrentModulus,set,times,it);
   s->gr=gr;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(2);
}

void Widget::AnimationBlurRadiusItem(int item, float set, int times,QString signfun,ParametersStru *par,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   float CurrentModulus;//当前系数
   //QGraphicsBlurEffect *Effect=gritem->Blur;
   if(gritem->Blur==NULL)
   {
       CurrentModulus=0;
       gritem->Blur=new QGraphicsBlurEffect(this);
   }

   QGraphicsItem* gr=gritem->ItemPointer;
   QGraphicsBlurEffect *effect=new QGraphicsBlurEffect(this);
   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(CurrentModulus,set,times,it);
   s->gr=gr;
   s->Effect=effect;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(4);

   gritem->Blur->setBlurRadius(set);
   //gritem->Blur=Effect;
}

void Widget::AnimationSetOpacityItem(int item, float set, int times,QString signfun,ParametersStru *par,bool LastIndex)
{
   QGraphicsItem* gr=findItem(item,LastIndex)->ItemPointer;
   float CurrentModulus=gr->opacity();
   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(CurrentModulus,set,times,it);
   s->gr=gr;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(5);
}

void Widget::AnimationSetColorItem(int item, float R, float G, float B, int times,QString signfun,ParametersStru *par,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   //当前系数
   float CurrentModulus;
   float CurrentModulus2;
   float CurrentModulus3;
   //QGraphicsColorizeEffect *Effect=gritem->Color;
   if(gritem->Color==NULL)
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
   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(CurrentModulus,CurrentModulus2,CurrentModulus3,R,G,B,times,it);
   s->gr=gr;
   s->co=co;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(6);

   gritem->Color->setColor(QColor(R,G,B));
}

float Widget::GetItemX(int item,bool LastIndex)
{return findItem(item,LastIndex)->ItemPointer->x();}

float Widget::GetItemY(int item,bool LastIndex)
{return findItem(item,LastIndex)->ItemPointer->y();}

float Widget::GetItemR(int item,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   if(gritem->Color==NULL)
   {return -1;}
   return gritem->Color->color().red();
}

float Widget::GetItemG(int item,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   if(gritem->Color==NULL)
   {return -1;}
   return gritem->Color->color().green();
}

float Widget::GetItemB(int item,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   if(gritem->Color==NULL)
   {return -1;}
   return gritem->Color->color().blue();
}

float Widget::GetItemBlur(int item,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   if(gritem->Blur==NULL)
   {return 0;}
   return gritem->Blur->blurRadius();
}

float Widget::GetItemOpacity(int item,bool LastIndex)
{return findItem(item,LastIndex)->ItemPointer->opacity();}

float Widget::GetItemRotation(int item,bool LastIndex)
{return findItem(item,LastIndex)->ItemPointer->rotation();}

float Widget::GetItemScale(int item,bool LastIndex)
{return findItem(item,LastIndex)->ItemPointer->scale();}

int Widget::AddPicAnimation(QVector<QString> address,int x,int y,int time,QString signfun,ParametersStru *par,bool cycle,QGraphicsScene *scene)
{
   assert(!address.isEmpty());//断言，确认传入的图片容器不为空
   MyPixmap *temp=new MyPixmap(QPixmap(address[0]));//将第一张图片变为图元
   scene->addItem(temp);//将第一张图片显示在场景中
   temp->setPos(x,y);//设置其位置
   Item *item=new Item{temp,temp,NULL,NULL,0,0};
   AllItem<<item;
   ItemNumber<<ItemNowNumber;
   int retur=ItemNowNumber;//准备返回图元管理器序号
   ItemNowNumber++;//目前序号加1

   QMutableListIterator<QPair<int,SC *> > it(scPointer);//创建迭代器
   SC *sc=new SC(0,0,time,it);//创建SC实例
   sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
   sc->cycle=cycle;//定义是否循环连续播图

   if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
   {
       sc->signfun=signfun;
       sc->par=par;
   }

   for(QVector<QString>::iterator iter=address.begin();iter!=address.end();++iter)//遍历容器中的所有图片
   {sc->pixmap.push_back(QPixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
   QPair<int,SC *> p(retur,sc);//创建关联容器准备将当前实例导入SC管理器
   scPointer<<p;//置入SC管理器
   sc->start(7);
   sc->num=retur;
   return retur;
}

void Widget::EndAnimation(int item,AnimationType choose)
{
   QMutableListIterator<QPair<int,SC *> > p(scPointer);
   p.toFront();
   while(p.hasNext())
   {
       if(p.next().first==item && p.value().second->choose==choose)
       {
           p.value().second->over=2;
           p.remove();
           break;
       }
   }
}

void Widget::EndAllAnimation(int item)
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

void Widget::SetViewItemCenter(int item,GraphicsView *gview,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
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

int Widget::GetScreenWidth()
{return QApplication::desktop()->width();}

int Widget::GetScreenHeigh()
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
   FIRST1 T1 OVER1 FIRST2 Q1 OVER2 T1 FIRSTOVER3
   connect(T1,SIGNAL(timeout()),Q1,SLOT(quit()));
   T1 TFFIRST1 time TFOVER1 Q1 FFIRSTOVER2 FDelFITST T1 FDelOVER FDelFITST Q1 FDelOVER
}

void Widget::SetItemLayer(int item,int Layer,bool LastIndex)
{
   //Qt默认都是0，如果在不手动排序的情况下将一个item设为顶层则设为1，底层-1
   findItem(item,LastIndex)->ItemPointer->setZValue(Layer);
}

void Widget::SetItemOrder(int Belowitem, int Aboveitem,bool LastIndexBelow,bool LastIndexAbove)
{findItem(Belowitem,LastIndexBelow)->ItemPointer->stackBefore(findItem(Aboveitem,LastIndexAbove)->ItemPointer);}

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

void Widget::WriteTXT(QString path, QString text)
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

void Widget::ChangePixmapItem(QString path,int item,bool LastIndex)
{
   MyPixmap *pixmap=findItem(item,LastIndex)->PixmapItemPoniter;
   assert(pixmap!=NULL);
   pixmap->setPixmap(QPixmap(path));
}

void Widget::ChangePicAnimationItem(QVector<QString> address,int item,int time,QString signfun,ParametersStru *par,bool cycle,bool LastIndex)
{
   EndAnimation(item,Picture);
   assert(!address.isEmpty());//断言，确认传入的图片容器不为空
   MyPixmap *temp=findItem(item,LastIndex)->PixmapItemPoniter;//查找到图元序号对应的MyPixmap指针
   assert(temp!=NULL);
   temp->setPixmap(QPixmap(address[0]));//变更当前图片为图集的第一帧

   QMutableListIterator<QPair<int,SC *> > it(scPointer);//创建迭代器
   SC *sc=new SC(0,0,time,it);//创建SC实例
   sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
   sc->cycle=cycle;//定义是否循环连续播图

   if(!cycle)//若不循环（默认是循环，true），搬移一下播放完成要发出的信号
   {
       sc->signfun=signfun;
       sc->par=par;
   }

   for(QVector<QString>::iterator iter=address.begin();iter!=address.end();++iter)//遍历容器中的所有图片
   {sc->pixmap.push_back(QPixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
   QPair<int,SC *> p(item,sc);//创建关联容器准备将当前实例导入SC管理器
   scPointer<<p;//置入SC管理器
   sc->start(7);
   sc->num=item;
}

void Widget::DeleteFile(QString path)
{QFile::remove(path);}

void Widget::SetShearItem(int item,float x,float y,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   QTransform *tranform=new QTransform;
   tranform->shear(x,y);
   gritem->ItemPointer->setTransform(*tranform);
   gritem->ShearX=x;
   gritem->ShearY=y;
   delete tranform;
}

float Widget::GetItemShearX(int item, bool LastIndex)
{return findItem(item,LastIndex)->ShearX;}

float Widget::GetItemShearY(int item, bool LastIndex)
{return findItem(item,LastIndex)->ShearY;}

void Widget::AnimationShearItem(int item, float fx, float fy, int time, QString signfun,ParametersStru *par,bool LastIndex)
{
   Item *gritem=findItem(item,LastIndex);
   QMutableListIterator<QPair<int,SC *> > it(scPointer);
   SC *s=new SC(gritem->ShearX,gritem->ShearY,fx,fy,time,it);
   s->gr=gritem->ItemPointer;
   s->signfun=signfun;
   s->par=par;
   QPair<int,SC *> p(item,s);
   scPointer<<p;
   s->start(8);

   gritem->ShearX=fx;
   gritem->ShearY=fy;
}

void Widget::SetKeyEvent(Qt::Key key, QString signfun,ParametersStru *par)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==key)
        {
            AllEvent[i]->par=par;
            AllEvent[i]->signfun=signfun;
            return;
        }
    }
    InputEvent *event=new InputEvent{key,-1,-1,-1,-1,-1,par,signfun};
    AllEvent<<event;
}

void Widget::DeleteKeyEvent(Qt::Key key)
{
    for(int i=0;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->key==key)
        {
            AllEvent.removeAt(i);
            return;
        }
    }
}

void Widget::SetMouseEvent(float MouseX, float MouseY,float fMouseX,float fMouseY,QString signfun, ParametersStru *par)
{
    vector <int> alllayout;
    for(int i=0;i<AllEvent.length();i++)
    {
        if(MouseX>=AllEvent[i]->MouseX&&
           MouseY>=AllEvent[i]->MouseY&&
           fMouseX<=AllEvent[i]->fMouseX&&
           fMouseY<=AllEvent[i]->fMouseY)
        {
            if(MouseX==AllEvent[i]->MouseX&&
               MouseY==AllEvent[i]->MouseY&&
               fMouseX==AllEvent[i]->fMouseX&&
               fMouseY==AllEvent[i]->fMouseY)
            {
                AllEvent[i]->par=par;
                AllEvent[i]->signfun=signfun;
                return;
            }
            alllayout.push_back(AllEvent[i]->layout);
        }
    }
    InputEvent *event=new InputEvent;
    event->MouseX=MouseX;
    event->MouseY=MouseY;
    event->par=par;
    event->fMouseX=fMouseX;
    event->fMouseY=fMouseY;
    if(!alllayout.empty())
    {
        bool(*fun)(int,int)=[](int a,int b){return a>b;};
        sort(alllayout.begin(),alllayout.end(),fun);
        event->layout=alllayout.at(0)+1;
    }
    else
    {event->layout=0;}
    event->signfun=signfun;
    AllEvent<<event;
}

void Widget::DeleteKeyEvent(float MouseX, float MouseY)
{
    for(int i;i<AllEvent.length();i++)
    {
        if(AllEvent[i]->MouseX==MouseX&&AllEvent[i]->MouseY==MouseY)
        {AllEvent.removeAt(i);}
    }
}
