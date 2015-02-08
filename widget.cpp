//-----本文件用于窗口的初始化-----
#include "widget.h"
#include "ui_widget.h"

LFEvent *lfevent;
QGraphicsScene *scene;//声明舞台
graphicsview *MainView;//声明视图

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
    //初始化
    ItemNowNumber=0;
    lfevent=new LFEvent;
    //初始化窗口
    scene=new QGraphicsScene(0,0,10000,10000);
    int width=QApplication::desktop()->width();//获取分辨率宽
    int height=QApplication::desktop()->height();//获取分辨率高
    width=(width-WindowsWidth)/2;height=(height-WindowsHeigh)/2;//计算窗口应该出现的位置
    setGeometry(width,height,WindowsWidth,WindowsHeigh);//设置窗口初始位置和大小
    setFixedSize(WindowsWidth,WindowsHeigh);//设置窗口最大大小
    setWindowTitle(title);//设置窗口标题
    MainView=new graphicsview(this);//定义视图
    SetViewCenter(WindowsWidth/2,WindowsHeigh/2);
    MainView->setGeometry(0,0,WindowsWidth,WindowsHeigh);//定义视图大小
    MainView->setScene(scene);//视图定义到舞台
    MainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用竖直滚动条
    MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//禁用水平滚动条
    MainView->show();//视图显示
    SetViewCenter(WindowsWidth/2,WindowsHeigh/2);
    //编码校正
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
}
