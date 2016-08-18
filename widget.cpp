//-----本文件用于窗口的初始化-----
#include "widget.h"
#include "ui_widget.h"
#include "configure.h"

LFEvent *lfevent;
QGraphicsScene *MainScene;
GraphicsView *MainView;
JSVM *MainJSVM;

#ifdef SelfAdaption
float adaptiveRatioX;
float adaptiveRatioY;
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    Initialization();//开始初始化
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//程序启动时调用的函数
void Widget::Initialization()
{
    lfevent=new LFEvent;//初始化全局变量
    //编码校正
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //注册类型
    RegisterJSType(ParametersStru,"ParametersStru");
    RegisterJSType(LFEvent*,"LFEvent*");
    RegisterJSType(Item*,"Item*");
    RegisterJSType(String,"String");
    RegisterJSType(VideoPlayer*,"VideoPlayer*");
    RegisterJSType(GraphicsView*,"GraphicsView*");
    RegisterJSType(CaluThread*,"CaluThread*");
    RegisterJSType(AnimationType,"AnimationType");
    RegisterJSType(Pixmap*,"Pixmap*");
    RegisterJSType(MusicPlayer*,"MusicPlayer*");
    RegisterJSType(GraphicsScene*,"GraphicsScene*");
    RegisterJSType(Qt::Key,"QtKey");
    RegisterJSType(Variant,"Variant");//这个我感觉有点别扭……
    RegisterJSType(JSVM*,"JSVM*");

    #ifdef SelfAdaption
    //计算自适应比
    int scWidth=GetScreenWidth();
    int scHeigh=GetScreenHeigh();
    adaptiveRatioX=float(scWidth)/float(WindowsWidth);
    adaptiveRatioY=float(scHeigh)/float(WindowsHeigh);
    setGeometry(0,0,scWidth,scHeigh);
    setFixedSize(GetScreenWidth(),GetScreenHeigh());
    #else
    //计算窗口出现位置
    int widX=(GetScreenWidth()-WindowsWidth)/2;
    int widY=(GetScreenHeigh()-WindowsHeigh)/2;
    setGeometry(widX,widY,WindowsWidth,WindowsHeigh);
    setFixedSize(WindowsWidth,WindowsHeigh);
    #endif
    setWindowTitle(title);
    MainScene=AddScene(MaximumWidth,MaximunHeigh);
    MainView=AddView(0,0,WindowsWidth,WindowsHeigh);
    SetScene();
}
