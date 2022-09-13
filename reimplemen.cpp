//-----本文件是对于NewType.h中定义的类的实现部分-----
#include "widget.h"

QList<ExpansionSlot*> AllExpansionSlot;

//MyItem
void PixmapItem::SetButton(Pixmap up, Pixmap down, String Music,int volume)
{
    this->isbutton=true;
    this->up=up;
    this->down=down;
    this->Music=Music;
    this->volume=volume;
}

void PixmapItem::SetEvent(String PressFun,ParametersStru PressPar,String ReleaseFun,ParametersStru ReleasePar)
{
    this->PressFun=PressFun;
    this->PressPar=PressPar;
    this->ReleaseFun=ReleaseFun;
    this->ReleasePar=ReleasePar;
}

bool PixmapItem::IsRegion()
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

/*void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{s->PassMouseReleaseEvent(e);}*/

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{s->PassMouseMoveEvent(e);}

void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(isbutton)//如果是按钮就放音乐并且切换图元
    {
        MusicPlayer *player=new MusicPlayer;
        player->singleplay(Music,volume);
        this->setPixmap(down);
    }

    if(PressFun!=NULL_String)//如果有事件，就执行
        RunFun(PressFun,PressPar);

    //传递本次点击到区域鼠标事件检测区
    Pos nowpos=e->pos().toPoint();
    nowpos=Pos(this->x()+nowpos.x(),this->y()+nowpos.y());
    s->PassMousePressEvent(nowpos);
}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(isbutton)//是按钮切回原图元
        this->setPixmap(up);

    if(ReleaseFun!=NULL_String&&IsRegion())
        RunFun(ReleaseFun,ReleasePar);

    //传递本次释放到区域鼠标事件检测区
    Pos nowpos=e->pos().toPoint();
    nowpos=Pos(this->x()+nowpos.x(),this->y()+nowpos.y());
    s->PassMouseReleaseEvent(nowpos);
}

//VideoPlayer
VideoPlayer::VideoPlayer(String Path, int Volume, int x, int y, int width, int heigh, bool cycle, String signfun,ParametersStru par,GraphicsScene *scene)
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
    this->par=par;
}

void VideoPlayer::start()
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(Path));
    mediaPlayer->play();
    QObject::connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playFinished(QMediaPlayer::State))); //绑定槽，播放后自动销毁
}

void VideoPlayer::playFinished(QMediaPlayer::State state)
{
    Q_UNUSED(state);
    /*if(state!=QMediaPlayer::StoppedState)
    {return;}*/
    if(!cycle)
    {
        if(signfun!=NULL_String)
            RunFun(signfun,par);
        delete this;
    }
    else
    {mediaPlayer->play();}
}

VideoPlayer::~VideoPlayer()
{
    this->mediaPlayer->stop();
    delete mediaPlayer;
    delete videoItem;
}

//MusicPlayer
void MusicPlayer::singleplay(String name, int volume)
{
    this->setMedia(QUrl::fromLocalFile(name));
    this->setVolume(volume);
    this->play();
    QObject::connect(this,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playFinished(QMediaPlayer::State)));
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

void MusicPlayer::playFinished(QMediaPlayer::State state)
{
    Q_UNUSED(state);
    if(this->slotfun!=NULL_String)
        RunFun(slotfun,par);
    delete this; //播放结束后会自动释放资源
}

MusicPlayer::~MusicPlayer()
{
    this->stop();
    delete cyclelist;
}

//GraphicsView
GraphicsView::GraphicsView(QWidget *parent, Widget *s, int x, int y, int width, int height):QGraphicsView(parent),s(s)
{
    this->setGeometry(x,y,width,height);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //禁用竖直滚动条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //禁用水平滚动条
}

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

//Item
Item::Item(PixmapItem* pixmapitem,QGraphicsItem *graphicsitem)
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
