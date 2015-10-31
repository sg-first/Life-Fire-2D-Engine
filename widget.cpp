//-----本文件用于窗口的初始化-----
#include "widget.h"
#include "ui_widget.h"

LFEvent *lfevent;
QGraphicsScene *MainScene;//声明舞台
GraphicsView *MainView;//声明视图

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
    qRegisterMetaType<ParametersStru*>("ParametersStru*");
    qRegisterMetaType<LFEvent*>("LFEvent*");
    qRegisterMetaType<Item*>("Item*");
    qRegisterMetaType<String>("String");
    qRegisterMetaType<VideoPlayer*>("VideoPlayer*");
    qRegisterMetaType<GraphicsView*>("GraphicsView*");
    qRegisterMetaType<EasyThread*>("EasyThread*");
    qRegisterMetaType<AnimationType>("AnimationType");
    qRegisterMetaType<Pixmap*>("Pixmap*");
    qRegisterMetaType<MusicPlayer*>("MusicPlayer*");
    qRegisterMetaType<GraphicsScene*>("GraphicsScene*");
    qRegisterMetaType<Qt::Key>("QtKey");
    qRegisterMetaType<QScriptValue>("QScriptValue");
    //计算窗口出现位置
    int widX=(GetScreenWidth()-WindowsWidth)/2;
    int widY=(GetScreenHeigh()-WindowsHeigh)/2;
    //设置窗口参数
    setGeometry(widX,widY,WindowsWidth,WindowsHeigh);
    setFixedSize(WindowsWidth,WindowsHeigh);
    setWindowTitle(title);
    MainScene=AddScene(MaximumWidth,MaximunHeigh);//初始化舞台
    //定义视图并显示
    MainView=AddView(0,0,WindowsWidth,WindowsHeigh);
    SetScene();
}
