//-----本文件是对于NewType.h中定义的新类型的成员函数的实现部分-----
#include "widget.h"

//MyItem
void MyItem::SetButton(Pixmap up, Pixmap down, String Music,int volume)
{
    this->isbutton=true;
    this->up=up;
    this->down=down;
    this->Music=Music;
    this->volume=volume;
}

void MyItem::SetEvent(String PressFun,ParametersStru PressPar,String ReleaseFun,ParametersStru ReleasePar)
{
    this->PressFun=PressFun;
    this->PressPar=PressPar;
    this->ReleaseFun=ReleaseFun;
    this->ReleasePar=ReleasePar;
}

bool MyItem::IsRegion()
{
    int x=this->x();
    int width=this->pixmap().width();
    int y=this->y();
    int height=this->pixmap().height();

    int xmin,ymin,xmax,ymax;
    xmin=x;
    xmax=x+width;

    if(x<0)
    {xmin=0;}
    if(x+width>WindowsWidth)
    {xmax=WindowsWidth;}

    ymin=y;
    ymax=y+height;

    if(y<0)
    {ymin=0;}
    if(y+height>WindowsHeigh)
    {ymax=WindowsHeigh;}


    if(xmax<s->mapFromGlobal(QCursor::pos()).x() || xmin>s->mapFromGlobal(QCursor::pos()).x())
    {return false;}
    if(ymax<s->mapFromGlobal(QCursor::pos()).y() || ymin>s->mapFromGlobal(QCursor::pos()).y())
    {return false;}
    return true;
}

void Widget::PassMousePressEvent(QPointF point)
{
    QMouseEvent e(QEvent::Type::MouseButtonPress,point,Qt::MouseButton::LeftButton,nullptr,nullptr);
    this->mousePressEvent(&e);
}

void Widget::PassMouseReleaseEvent(QPointF point)
{
    QMouseEvent e(QEvent::Type::MouseButtonRelease,point,Qt::MouseButton::LeftButton,nullptr,nullptr);
    this->mouseReleaseEvent(&e);
}

void Widget::PassMouseReleaseEvent(QMouseEvent *e)
{this->mouseReleaseEvent(e);}

void Widget::PassMouseMoveEvent(QMouseEvent *e)
{this->mouseMoveEvent(e);}

/*void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{s->PassMouseReleaseEvent(e);}*/

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{s->PassMouseMoveEvent(e);}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(isbutton)//如果是按钮就放音乐并且切换图元
    {
        MusicPlayer *player=new MusicPlayer;
        player->singleplay(Music,volume);
        this->setPixmap(down);
    }

    if(PressFun!=NULL_String)//如果有事件，就执行
    {RunFun(PressFun,PressPar);}

    s->PassMousePressEvent(e->pos());
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(isbutton)//是按钮切回原图元
    {this->setPixmap(up);}

    if(ReleaseFun!=NULL_String&&IsRegion())
    {RunFun(ReleaseFun,ReleasePar);}

    s->PassMouseReleaseEvent(e->pos());
}

//VideoPlayer
VideoPlayer::VideoPlayer(QString Path, int Volume, int x, int y, int width, int heigh, bool cycle, QString signfun, QGraphicsScene *scene)
    : QWidget(0)
{
    mediaPlayer=new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVolume(Volume);
    videoItem=new QGraphicsVideoItem;
    videoItem->setSize(QSizeF(width,heigh));
    scene->addItem(videoItem);
    mediaPlayer->setVideoOutput(videoItem);
    videoItem->setPos(x,y);//设置视频位置，默认为窗口左上角
    this->cycle=cycle;
    this->Path=Path;
    this->signfun=signfun;
}

void VideoPlayer::start()
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(Path));
    mediaPlayer->play();
    QObject::connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playover(QMediaPlayer::State)));
}

void VideoPlayer::playover(QMediaPlayer::State state)
{
    if(state!=QMediaPlayer::StoppedState)
    {return;}
    if(!cycle)
    {
        if(signfun!=NULL_String)
        {RunFun(signfun);}
        delete this;
    }
    else
    {mediaPlayer->play();}
}

VideoPlayer::~VideoPlayer()
{
    delete mediaPlayer;
    delete videoItem;
}

//MusicPlayer
void MusicPlayer::singleplay(String name, int volume)
{
    this->setMedia(QUrl::fromLocalFile(name));
    this->setVolume(volume);
    this->play();
    QObject::connect(this,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playover(QMediaPlayer::State)));
}

void MusicPlayer::multipleplay(String name,int volume)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(name);
    if (QFile::exists(backgroundMusicUrl.toLocalFile()))
    {
       this->setVolume(volume);
       cyclelist = new QMediaPlaylist();
       QMediaContent media(backgroundMusicUrl);
       cyclelist->addMedia(media);
       cyclelist->setCurrentIndex(0);
       // 设置背景音乐循环播放
       cyclelist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
       this->setPlaylist(cyclelist);
     }
     this->play();
}

void MusicPlayer::playover(QMediaPlayer::State state)
{
    if(state!=QMediaPlayer::StoppedState)
    {return;}
    delete this;
}

MusicPlayer::~MusicPlayer()
{delete cyclelist;}

//GraphicsView
void GraphicsView::Scale(int sX, int sY)
{scale(sX,sY);}

void GraphicsView::Rotate(float set)
{rotate(set);}

void GraphicsView::SetCenter(int x, int y)
{
    this->centerOn(x,y);
    this->viewX=x;
    this->viewY=y;
}

void GraphicsView::SetCenter(QGraphicsItem *item)
{
    this->centerOn(item);
    this->viewX=item->x();
    this->viewY=item->y();
}

//EasyThread
void EasyThread::run()
{
    RunFun(this->fun,this->par,Qt::DirectConnection);//同步执行
}

//Item
Item::Item(MyItem* pixmapitem,QGraphicsItem *graphicsitem)
{
    this->PixmapItemPoniter=pixmapitem;
    if(graphicsitem!=nullptr)
        this->ItemPointer=graphicsitem;
    else
        this->ItemPointer=pixmapitem;
    for(unsigned int a=0;a<sizeof(this->scPointer)/sizeof(this->scPointer[0]);++a)
        this->scPointer[a]=nullptr;
}

Item::~Item()
{
    if(PixmapItemPoniter==nullptr)
    {delete ItemPointer;}
    else
    {delete PixmapItemPoniter;}
    delete Blur;
    delete Color;
}

//ParametersStru
bool ParametersStru::operator !=(const ParametersStru &par)
{
    if(intVar==par.intVar&&
            floatVar==par.floatVar&&
            StringVar==par.StringVar&&
            boolVar==par.boolVar&&
            VideoPlayerVar==par.VideoPlayerVar&&
            GraphicsViewVar==par.GraphicsViewVar&&
            EasyThreadVar==par.EasyThreadVar&&
            AnimationTypeVar==par.AnimationTypeVar&&
            PixmapVar==par.PixmapVar&&
            ItemVar==par.ItemVar&&
            MusicPlayerVar==par.MusicPlayerVar&&
            GraphicsSceneVar==par.GraphicsSceneVar&&
            VariantVar==par.VariantVar&&
            QtKeyVar==par.QtKeyVar)
    {return false;}
    return true;
}

ParametersStru& ParametersStru::operator =(const ParametersStru &par)
{
    intVar=par.intVar;
    floatVar=par.floatVar;
    StringVar=par.StringVar;
    boolVar=par.boolVar;
    VideoPlayerVar=par.VideoPlayerVar;
    GraphicsViewVar=par.GraphicsViewVar;
    EasyThreadVar=par.EasyThreadVar;
    AnimationTypeVar=par.AnimationTypeVar;
    PixmapVar=par.PixmapVar;
    ItemVar=par.ItemVar;
    MusicPlayerVar=par.MusicPlayerVar;
    GraphicsSceneVar=par.GraphicsSceneVar;
    VariantVar=par.VariantVar;
    QtKeyVar=par.QtKeyVar;
    return *this;
}

ParametersStru::ParametersStru(const ParametersStru &par):QObject(0)
{
    intVar=par.intVar;
    floatVar=par.floatVar;
    StringVar=par.StringVar;
    boolVar=par.boolVar;
    VideoPlayerVar=par.VideoPlayerVar;
    GraphicsViewVar=par.GraphicsViewVar;
    EasyThreadVar=par.EasyThreadVar;
    AnimationTypeVar=par.AnimationTypeVar;
    PixmapVar=par.PixmapVar;
    ItemVar=par.ItemVar;
    MusicPlayerVar=par.MusicPlayerVar;
    GraphicsSceneVar=par.GraphicsSceneVar;
    VariantVar=par.VariantVar;
    QtKeyVar=par.QtKeyVar;
}

Item::Item(QPixmap *pixmap)
{Item(new MyItem(*pixmap));}

//JSParStru
void JSParStru::add(QObject *pointer,QString name)
{
    pointerVec<<pointer;
    nameVec<<name;
}

bool JSParStru::operator !=(const JSParStru &par)
{
    if(pointerVec==par.pointerVec&&nameVec==par.nameVec)
    {return false;}
    return true;
}

//独立函数
void RunFun(QString signfun,ParametersStru par,Qt::ConnectionType CT)
{
    //默认异步执行
    QByteArray ba = signfun.toLatin1();
    const char *function = ba.data();
    if(par!=NULL_ParametersStru)
    {QMetaObject::invokeMethod(thob,function,CT,Q_ARG(ParametersStru,par));}
    else
    {QMetaObject::invokeMethod(thob,function,CT);}
}
