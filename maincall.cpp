//-----本文件是对于maincall.h中部分函数的实现部分-----
#include "maincall.h"

void maincall::StartGame()//入口函数
{
    /*QVector<QString>addr;
    addr<<"D:/梦影测试/陈的混混/2.jpg";
    addr<<"D:/梦影测试/陈的混混/1.jpg";
    addr<<"D:/梦影测试/陈的混混/3.jpg";
    addr<<"D:/梦影测试/陈的混混/2.jpg";
    AddPicAnimation(addr,0,0,700);*/

    Item *i=AddPixmapItem("D:/梦影测试/陈的混混/2.jpg",0,0);
    BlurRadiusItem(i,20);
    AnimationBlurRadiusItem(i,0,100);
}
