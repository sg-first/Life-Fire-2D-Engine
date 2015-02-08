//-----本文件是对于maincall.h中部分函数的实现部分-----
#include "maincall.h"

void maincall::StartGame()//入口函数
{
//PlayVideo("D:/下载/测试视频.wmv",100,5);//不循环模式
    int a=AddPixmapItem("D:/梦影测试/demo/mylogo.png",0,0);
    BlurRadiusItem(a,10);
    BlurRadiusItem(a,50);
}
