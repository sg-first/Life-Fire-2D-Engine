//-----本文件为一些为了简化操作建立的宏-----
#pragma once

//空对象
#define NULL_String ""
#define NULL_ParametersStru _NULLParametersStru
#define NULL_JSParStru _NULLJSParStru
#define NULL_Pointer nullptr
//异步变同步
#define SynchronousStart(fun) {QTimer t;\
                    QEventLoop q;\
                    t.setSingleShot(true);\
                    QObject::connect(lfevent,SIGNAL( fun ()),&q,SLOT(quit()));
#define SynchronousFinish() t.start();q.exec();}
//类型容器相关
#define RegisterJSType(TypeName,JSName) qRegisterMetaType<TypeName>(JSName)
//#define RegisterVariantType(TypeName) Q_DECLARE_METATYPE(TypeName) 这个似乎不用了，注册JS类型也会注册这个
#define ToVariant(Variant,Var) Variant.setValue(Var)
#define FromVariant(Variant,Type) Variant.value<Type>()
//实例更名
#define asynchronous Qt::QueuedConnection
#define synchronization Qt::DirectConnection
