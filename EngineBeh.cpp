//-----本文件是引擎行为层给引擎调用的函数的实现-----
#include "widget.h"

bool Widget::isColliding(QGraphicsItem* Ritem1,QGraphicsItem* Ritem2)
{return bool(Ritem1->QGraphicsItem::collidesWithItem(Ritem2));}
