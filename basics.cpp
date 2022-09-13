//-----本文件是对于basics.h中定义的类的实现部分-----
#include "basics.h"
#include "globalVar.h"

//ParametersStru
bool ParametersStru::operator !=(const ParametersStru &par)
{
    if(intVar==par.intVar&&
            floatVar==par.floatVar&&
            StringVar==par.StringVar&&
            boolVar==par.boolVar&&
            VideoPlayerVar==par.VideoPlayerVar&&
            GraphicsViewVar==par.GraphicsViewVar&&
            CaluThreadVar==par.CaluThreadVar&&
            AnimationTypeVar==par.AnimationTypeVar&&
            PixmapVar==par.PixmapVar&&
            ItemVar==par.ItemVar&&
            MusicPlayerVar==par.MusicPlayerVar&&
            GraphicsSceneVar==par.GraphicsSceneVar&&
            KeyVar==par.KeyVar)
    {return false;}
    return true;
}

ParametersStru& ParametersStru::operator =(const ParametersStru &par)
{
    intVar=par.intVar;
    floatVar=par.floatVar;
    StringVar=par.StringVar;
    boolVar=par.boolVar;
    VideoPlayerVar=par.VideoPlayerVar;
    GraphicsViewVar=par.GraphicsViewVar;
    CaluThreadVar=par.CaluThreadVar;
    AnimationTypeVar=par.AnimationTypeVar;
    PixmapVar=par.PixmapVar;
    ItemVar=par.ItemVar;
    MusicPlayerVar=par.MusicPlayerVar;
    GraphicsSceneVar=par.GraphicsSceneVar;
    KeyVar=par.KeyVar;
    return *this;
}

ParametersStru::ParametersStru(const ParametersStru &par):QObject(0)
{
    intVar=par.intVar;
    floatVar=par.floatVar;
    StringVar=par.StringVar;
    boolVar=par.boolVar;
    VideoPlayerVar=par.VideoPlayerVar;
    GraphicsViewVar=par.GraphicsViewVar;
    CaluThreadVar=par.CaluThreadVar;
    AnimationTypeVar=par.AnimationTypeVar;
    PixmapVar=par.PixmapVar;
    ItemVar=par.ItemVar;
    MusicPlayerVar=par.MusicPlayerVar;
    GraphicsSceneVar=par.GraphicsSceneVar;
    KeyVar=par.KeyVar;
}

//ExpansionSlot
void ExpansionSlot::call(ParametersStru par)
{
    if(this->parslot!=nullptr)
    {
        this->parslot(par);
        return;
    }
    if(this->voidslot!=nullptr)
    {
        this->voidslot();
        return;
    }
    QJSValue ret=MainJSVM->globalObject().property(slotname);
    ret.call(QJSValueList());
}

//CaluThread
void CaluThread::run()
{
    if(this->fun!=NULL_String)
    {
        //不是在runfun里调用的，也就是说必然是非扩展事件，直接通过原生槽执行
        QByteArray ba = fun.toLatin1();
        const char *function = ba.data();
        if(par!=NULL_ParametersStru)
        {QMetaObject::invokeMethod(thob,function,synchronization,Q_ARG(ParametersStru,par));}
        else
        {QMetaObject::invokeMethod(thob,function,synchronization);}
        return;
    }
    else
    {
        //扩展事件
        if(!this->track) //检查是否是非追踪调用
        {QObject::connect(this,SIGNAL(finished()),this,SLOT(playFinished()));} //线程函数执行完毕立刻销毁
        this->exfun->call(par);
    }
    return;
}

void CaluThread::playFinished()
{delete this;}

//独立函数
ExpansionSlot* FindExpansionSlot(String slotfun)
{
    int expansion_slot_len = AllExpansionSlot.length();
    for (int i = 0; i < expansion_slot_len; ++i) {
        ExpansionSlot *slot = AllExpansionSlot.at(i);
        if(slot->getslotname()==slotfun) //确定找到
        {return slot;}
    }
    return nullptr;
}

void RunFun(String slotfun, ParametersStru par, ExecutionMode CT, bool expansion)
{
    if(expansion) //注意，不存在同名的槽，所以能找到就直接返回
    {
        //扩展调用
        ExpansionSlot *slot=FindExpansionSlot(slotfun);
        if(slot!=nullptr)
        {
            if(CT==asynchronous) //如果是异步
            {
                //注意，异步扩展槽不能使用引擎接口
                CaluThread *thread=new CaluThread(slot,par,false);
                thread->start();
            }
            else
            {slot->call(par);} //同步直接执行就好了
            return;
        }
    }
    //非扩展调用
    QByteArray ba = slotfun.toLatin1();
    const char *function = ba.data();
    if(par!=NULL_ParametersStru)
    {QMetaObject::invokeMethod(thob,function,CT,Q_ARG(ParametersStru,par));}
    else
    {QMetaObject::invokeMethod(thob,function,CT);}
}
