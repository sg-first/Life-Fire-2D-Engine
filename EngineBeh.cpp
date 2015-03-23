//-----本文件是引擎行为层给引擎调用的函数的实现-----
#include "widget.h"

int Widget::qListFindSubscript(bool LastIndex,int item)
{
    int sub;
    if (!LastIndex)
    {sub=ItemNumber.indexOf(item);}
    else
    {sub=ItemNumber.lastIndexOf(item);}
    return sub;
}

Item* Widget::findItem(int item, bool LastIndex)
{return AllItem[qListFindSubscript(LastIndex,item)];}

bool Widget::isColliding(QGraphicsItem* Ritem1,QGraphicsItem* Ritem2)
{return bool(Ritem1->QGraphicsItem::collidesWithItem(Ritem2));}
