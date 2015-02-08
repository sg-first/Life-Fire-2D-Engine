 //-----本文件是引擎行为层接口的实现-----
#include "widget.h"

int Widget::AddPixmapItem(QString PicPath,float X,float Y,QString fun,QString down,QGraphicsScene *scene)
{
    myPixmap *temp=new myPixmap(QPixmap(PicPath));
    temp->fun=fun;
    temp->s=this;

    if(down==NULL)
    {temp->down=QPixmap(PicPath);}
    else
    {temp->down=QPixmap(down);}
    temp->up=QPixmap(PicPath);
    scene->addItem(temp);
    QGraphicsItem *Item=temp;

    /*if(fun!=NULL)//设置鼠标悬浮时的指针样式
    {Item->setCursor(Qt::PointingHandCursor);}
    else
    {Item->setCursor(Qt::ArrowCursor);}*/

    Item->setPos(X,Y);
    AllItem<<Item;
    ItemNumber<<ItemNowNumber;
    Blur<<0;
    ColorR<<0;
    ColorG<<0;
    ColorB<<0;
    int retur=ItemNowNumber;
    ItemNowNumber++;
    return retur;
}

int Widget::AddTextItem(QString Text,QString Font,int Size,int CR,int CG,int CB,float X,float Y,QGraphicsScene *scene)
{
QGraphicsTextItem *text=new QGraphicsTextItem(Text);
text->setFont(QFont(Font,Size));
//text->setDefaultTextColor(QColor(qrand()%CR,qrand()%CG,qrand()%CB));//设置颜色
text->setDefaultTextColor(QColor(CR,CG,CB));
scene->addItem(text);
text->setPos(X,Y);
AllItem<<text;
ItemNumber<<ItemNowNumber;
Blur<<0;
ColorR<<0;
ColorG<<0;
ColorB<<0;
int retur=ItemNowNumber;
ItemNowNumber++;
return retur;
}

void Widget::RotationItem(int Number, float set,bool LastIndex)
{
int Subscript=QListFindItem(LastIndex,Number);
AllItem[Subscript]->setRotation(set);
AllItem[Subscript]->rotation();
}

void Widget::ScaleItem(int Number, float set,bool LastIndex)
{
int Subscript=QListFindItem(LastIndex,Number);
AllItem[Subscript]->setScale(set);
AllItem[Subscript]->scale();
}

void Widget::BlurRadiusItem(int Number, float set,bool LastIndex)
{
int Subscript=QListFindItem(LastIndex,Number);
QGraphicsBlurEffect *Effect=new QGraphicsBlurEffect(this);
Effect->setBlurRadius(set);
AllItem[Subscript]->setGraphicsEffect(Effect);
Blur[Subscript]=set;
}

void Widget::SetOpacityItem(int Number, float set,bool LastIndex)
{
int Subscript=QListFindItem(LastIndex,Number);
AllItem[Subscript]->setOpacity(set);
}

void Widget::SetColorItem(int Number,float R,float G,float B,bool LastIndex)
{
int Subscript=QListFindItem(LastIndex,Number);
QGraphicsColorizeEffect *Effect = new QGraphicsColorizeEffect(this);
Effect->setColor(QColor(R,G,B));
AllItem[Subscript]->setGraphicsEffect(Effect);
ColorR[Subscript]=R;
ColorG[Subscript]=G;
ColorB[Subscript]=B;
}

void Widget::ClearScene(QGraphicsScene *scene)
{
QMutableListIterator<QPair<int,SC *> > p(scPointer);
p.toFront();
while(p.hasNext())
{p.next().second->over=1;}

scene->clear();
AllItem.clear();
ItemNumber.clear();
Blur.clear();
ColorR.clear();
ColorG.clear();
ColorB.clear();
ItemNowNumber=0;
}

void Widget::DeleteItem(int Number,bool LastIndex)
{
endAnimation(Number);
int Subscript=QListFindItem(LastIndex,Number);
delete AllItem[Subscript];
AllItem.removeAt(Subscript);
ItemNumber.removeAt(Subscript);
Blur.removeAt(Subscript);
ColorR.removeAt(Subscript);
ColorG.removeAt(Subscript);
ColorB.removeAt(Subscript);
}

void Widget::MoveItem(int Number, float X, float Y,bool LastIndex)
{
int Subscript=QListFindItem(LastIndex,Number);
AllItem[Subscript]->setPos(X,Y);
}

QString Widget::GetPath(QString str)
{
QString path;
QDir dir;
path=dir.currentPath();
path+="/"+str;
return path;
}

void Widget::Sleep(int time)
{QThread::msleep(time);}

int Widget::QListFindItem(bool LastIndex,int Number)
{
    int Subscript;
    if (!LastIndex)
    {Subscript=ItemNumber.indexOf(Number);}
    else
    {Subscript=ItemNumber.lastIndexOf(Number);}
    return Subscript;
}

void Widget::SetVisibleItem(int Number,bool Enabled,bool LastIndex)
{
    int Subscript=QListFindItem(LastIndex,Number);
    AllItem[Subscript]->setVisible(Enabled);
}

void Widget::SetBackground(QString PicturePath,QGraphicsScene *scene)
{scene->setBackgroundBrush(QPixmap(PicturePath));}

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

void Widget::AnimationMoveItem(int Number,float X,float Y,int time,QString signfun,bool LastIndex)
{
    QGraphicsItem* gr=AllItem[QListFindItem(LastIndex,Number)];
    float dx=gr->x();
    float dy=gr->y();
    QMutableListIterator<QPair<int,SC *> > it(scPointer);
    SC *s=new SC(0,0,X-dx,Y-dy,time,it);
    s->gr=gr;
    s->signfun=signfun;
    QPair<int,SC *> p(Number,s);
    scPointer<<p;
    s->start(3);
}

void Widget::EasyThread(QString Fun)
{
    QByteArray ba = Fun.toLatin1();
    const char *function = ba.data();
    QMetaObject::invokeMethod(thob,function);
}

bool Widget::IsColliding(QGraphicsItem* Ritem1,QGraphicsItem* Ritem2)
{return bool(Ritem1->QGraphicsItem::collidesWithItem(Ritem2));}

bool Widget::ItemColliding(int item1,int item2)
{return IsColliding(AllItem[QListFindItem(false,item1)],AllItem[QListFindItem(false,item2)]);}

VideoPlayer* Widget::PlayVideo(QString path,int Volume,int time,int x,int y,int width,int heigh,bool cycle,QString signfun,QGraphicsScene *scene)
{
    if(x==-1)
    {x=viewX-(WindowsWidth/2);}
    if(y==-1)
    {y=viewY-(WindowsHeigh/2);}
    //time为视频时长，单位为秒
    VideoPlayer* video=new VideoPlayer(path,Volume,time,x,y,width,heigh,cycle,signfun,scene);
    video->start();
    return video;
}

void Widget::PauseVideo(VideoPlayer *video)
{video->mediaPlayer->pause();}

void Widget::ContinueVideo(VideoPlayer *video)
{video->mediaPlayer->play();}

void Widget::StopVideo(VideoPlayer *video)
{
    if(video->signfun!=NULL)
    {
     QByteArray ba = video->signfun.toLatin1();
     const char *function = ba.data();
     QMetaObject::invokeMethod(lfevent,function);
    }
    delete video;
}

void Widget::AnimationRotationItem(int Number, float set,int times,QString signfun,bool LastIndex)
{
    QGraphicsItem* gr=AllItem[QListFindItem(LastIndex,Number)];
    float CurrentModulus=gr->rotation();

    QMutableListIterator<QPair<int,SC *> > it(scPointer);
    SC *s=new SC(CurrentModulus,set,times,it);
    s->gr=gr;
    s->signfun=signfun;
    QPair<int,SC *> p(Number,s);
    scPointer<<p;
    s->start(1);
}

void Widget::AnimationScaleItem(int Number, float set,int times,QString signfun,bool LastIndex)
{
    QGraphicsItem* gr=AllItem[QListFindItem(LastIndex,Number)];
    float CurrentModulus=gr->scale();
    QMutableListIterator<QPair<int,SC *> > it(scPointer);
    SC *s=new SC(CurrentModulus,set,times,it);
    s->gr=gr;
    s->signfun=signfun;
    QPair<int,SC *> p(Number,s);
    scPointer<<p;
    s->start(2);
}

void Widget::AnimationBlurRadiusItem(int Number, float set, int times,QString signfun,bool LastIndex)
{
    int sub=QListFindItem(LastIndex,Number);
    float CurrentModulus=Blur[sub];
    QGraphicsItem* gr=AllItem[sub];
    QGraphicsBlurEffect *Effect=new QGraphicsBlurEffect(this);
    QMutableListIterator<QPair<int,SC *> > it(scPointer);
    SC *s=new SC(CurrentModulus,set,times,it);
    s->gr=gr;
    s->Effect=Effect;
    s->signfun=signfun;
    QPair<int,SC *> p(Number,s);
    scPointer<<p;
    s->start(4);
    Blur[sub]=set;
}

void Widget::AnimationSetOpacityItem(int Number, float set, int times,QString signfun,bool LastIndex)
{
    QGraphicsItem* gr=AllItem[QListFindItem(LastIndex,Number)];
    float CurrentModulus=gr->opacity();
    QMutableListIterator<QPair<int,SC *> > it(scPointer);
    SC *s=new SC(CurrentModulus,set,times,it);
    s->gr=gr;
    s->signfun=signfun;
    QPair<int,SC *> p(Number,s);
    scPointer<<p;
    s->start(5);
}

void Widget::AnimationSetColorItem(int Number, float R, float G, float B, int times,QString signfun,bool LastIndex)
{
    int sub=QListFindItem(LastIndex,Number);
    float CurrentModulus=ColorR[sub];
    float CurrentModulus2=ColorG[sub];
    float CurrentModulus3=ColorB[sub];
    QGraphicsItem* gr=AllItem[sub];
    QGraphicsColorizeEffect *co = new QGraphicsColorizeEffect(this);
    QMutableListIterator<QPair<int,SC *> > it(scPointer);
    SC *s=new SC(CurrentModulus,CurrentModulus2,CurrentModulus3,R,G,B,times,it);
    s->gr=gr;
    s->co=co;
    s->signfun=signfun;
    QPair<int,SC *> p(Number,s);
    scPointer<<p;
    s->start(6);
    ColorR[sub]=R;
    ColorG[sub]=G;
    ColorB[sub]=B;
}

float Widget::GetItemX(int Number,bool LastIndex)
{return AllItem[QListFindItem(LastIndex,Number)]->x();}

float Widget::GetItemY(int Number,bool LastIndex)
{return AllItem[QListFindItem(LastIndex,Number)]->y();}

float Widget::GetItemR(int Number,bool LastIndex)
{return ColorR[QListFindItem(LastIndex,Number)];}

float Widget::GetItemG(int Number,bool LastIndex)
{return ColorG[QListFindItem(LastIndex,Number)];}

float Widget::GetItemB(int Number,bool LastIndex)
{return ColorB[QListFindItem(LastIndex,Number)];}

float Widget::GetItemBlur(int Number,bool LastIndex)
{return Blur[QListFindItem(LastIndex,Number)];}

float Widget::GetItemOpacity(int Number,bool LastIndex)
{return AllItem[QListFindItem(LastIndex,Number)]->opacity();}

float Widget::GetItemRotation(int Number,bool LastIndex)
{return AllItem[QListFindItem(LastIndex,Number)]->rotation();}

float Widget::GetItemScale(int Number,bool LastIndex)
{return AllItem[QListFindItem(LastIndex,Number)]->scale();}

int Widget::AddPicAnimation(QVector<QString> address,int x,int y,int time,QString signfun,bool cycle,QGraphicsScene *scene)
{
    assert(!address.isEmpty());//断言，确认传入的图片容器不为空
    myPixmap *temp=new myPixmap(QPixmap(address[0]));//将第一张图片变为图元
    scene->addItem(temp);//将第一张图片显示在场景中
    QGraphicsItem *Item=temp;//将第一张图片转换为图元标准格式
    Item->setPos(x,y);//设置其位置
    AllItem<<Item;//置入图元管理器
    ItemNumber<<ItemNowNumber;
    Blur<<0;
    ColorR<<0;
    ColorG<<0;
    ColorB<<0;
    int retur=ItemNowNumber;//准备返回图元管理器序号
    ItemNowNumber++;//目前序号加1

    QMutableListIterator<QPair<int,SC *> > it(scPointer);//创建迭代器
    SC *sc=new SC(0,0,time,it);//创建SC实例
    sc->pi=temp;//将SC操作的图元成员写为第一张图片的图元
    sc->cycle=cycle;//定义是否循环连续播图

    if(!cycle)//若不循环（默认是循环，true）
    {sc->signfun=signfun;}//搬移一下播放完成要发出的信号

    for(QVector<QString>::iterator iter=address.begin();iter!=address.end();++iter)//遍历容器中的所有图片
    {sc->pixmap.push_back(QPixmap(*iter));}//将所有图片压入SC类中储存图片的成员中
    QPair<int,SC *> p(retur,sc);//创建关联容器准备将当前实例导入SC管理器
    scPointer<<p;//置入SC管理器
    sc->start(7);
    sc->num=retur;
    return retur;
}

void Widget::endAnimation(int Number,QString signfun)
{
    QMutableListIterator<QPair<int,SC *> > p(scPointer);
    p.toFront();
    while(p.hasNext())
    {
        if(p.next().first==Number)
        {
            p.value().second->over=1;
            break;
        }
    }
    if(signfun!=NULL)
    {
     QByteArray ba = signfun.toLatin1();
     const char *function = ba.data();
     QMetaObject::invokeMethod(lfevent,function);
    }
}

void Widget::SetViewCenter(float x, float y,graphicsview *gview)
{
    gview->centerOn(x,y);
    if(gview==MainView)
    {
        this->viewX=x;
        this->viewY=y;
    }
}

void Widget::SetViewItemCenter(int Number,graphicsview *gview,bool LastIndex)
{
    int sub=QListFindItem(LastIndex,Number);
    gview->centerOn(AllItem[sub]);
    if(gview==MainView)
    {
        this->viewX=AllItem[sub]->x();
        this->viewY=AllItem[sub]->y();
    }
}

float Widget::GetMainViewX()
{return viewX;}

float Widget::GetMainViewY()
{return viewY;}

graphicsview* Widget::AddView(float x, float y, float width, float height)
{
    graphicsview *view=new graphicsview(this);
    view->setGeometry(x,y,width,height);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用竖直滚动条
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平滚动条
    view->show();
    return view;
}

void Widget::SetViewSize(float x, float y, float width, float height, graphicsview *gview)
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

void Widget::SetScene(graphicsview *view, QGraphicsScene *scene)
{view->setScene(scene);}

void Widget::SafeSleep(int time)
{
    FIRST1 T1 OVER1 FIRST2 Q1 OVER2 T1 FIRSTOVER3
    connect(T1,SIGNAL(timeout()),Q1,SLOT(quit()));
    T1 TFFIRST1 time TFOVER1 Q1 FFIRSTOVER2 FDelFITST T1 FDelOVER FDelFITST Q1 FDelOVER
}

void Widget::SetItemLayer(int Number,int Layer,bool LastIndex)
{
    //Qt默认都是0，如果在不手动排序的情况下将一个item设为顶层则设为1，底层-1
    AllItem[QListFindItem(LastIndex,Number)]->setZValue(Layer);
}

void Widget::SetItemOrder(int BelowNumber, int AboveNumber,bool LastIndex)
{AllItem[QListFindItem(LastIndex,BelowNumber)]->stackBefore(AllItem[QListFindItem(LastIndex,AboveNumber)]);}

void Widget::ScaleView(float sx, float sy, graphicsview *view)
{view->Scale(sx,sy);}

void Widget::RotateView(float set, graphicsview *view)
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

QString Widget::WriteINI(QString path, QString section, QString var, QString value)
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
