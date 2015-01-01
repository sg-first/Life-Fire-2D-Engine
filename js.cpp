#include "maincall.h"

void maincall::CallJs(QString path)
{
    QScriptEngine myengine;
    QScriptValue function = myengine.newQObject(this);
    myengine.globalObject().setProperty("fun",function);
    QScriptValue lfvar = myengine.newQObject(lfevent);
    myengine.globalObject().setProperty("lfvar",lfvar);
    /*如果想要在js中使用QT中的变量，请事先修改globalvar.h中的lfevent类，
    从其中添加您的变量，并在调用本函数前将其赋值，即可在js中使用lfvar.XX的方式使用*/

    QFile scripfile(path);
    scripfile.open(QIODevice::ReadOnly);
    QTextStream text(&scripfile);
    QString concert=text.readAll();
    scripfile.close();

    myengine.evaluate(concert,path);
}

void maincall::CallJsFunction(QString path, QString functionss)
{
    QScriptEngine myengine;
    QScriptValue function = myengine.newQObject(this);
    myengine.globalObject().setProperty("fun",function);
    QScriptValue lfvar = myengine.newQObject(lfevent);
    myengine.globalObject().setProperty("lfvar",lfvar);
    /*如果想要在js中使用QT中的变量，请事先修改globalvar.h中的lfevent类，
    从其中添加您的变量，并在调用本函数前将其赋值，即可在js中使用lfvar.XX的方式使用*/

    QFile scripfile(path);
    scripfile.open(QIODevice::ReadOnly);
    QTextStream text(&scripfile);
    QString concert=text.readAll();
    scripfile.close();
    myengine.evaluate(concert,path);
    //QScriptValue add = myengine.globalObject().property(functionss); 关于返回值的有需要再处理
}
