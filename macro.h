//-----一些宏-----
#pragma once

#define NULL_String ""
#define NULL_ParametersStru _NULLParametersStru
#define NULL_JSParStru _NULLJSParStru
#define NULL_Pointer nullptr

#define SynchronousStart(fun) {QTimer t;\
                    QEventLoop q;\
                    t.setSingleShot(true);\
                    QOjbect::connect(lfevent,SIGNAL( fun ()),&q,SLOT(quit()));
#define SynchronousFinish() t.start();q.exec();}
#define RegisterJSType(TypeName,JSName) qRegisterMetaType<TypeName>(JSName)

//类型容器相关
//#define RegisterVariantType(TypeName) Q_DECLARE_METATYPE(TypeName) 这个似乎不用了，注册JS类型也会注册这个
#define ToVariant(Variant,Var) Variant.setValue(Var)
#define FromVariant(Variant,Type) Variant.value<Type>()
