//-----本文件无需修改-----
#include "widget.h"
#include "maincall.h"
#include <QApplication>

QObject *thob;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    maincall *m=new maincall;
    thob=m;
    m->QWidget::show();
    m->StartGame();//启动游戏
    return a.exec();
}
