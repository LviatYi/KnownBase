# 9. 桥接模式

## 9.1 模式动机

将继承关系转换为关联关系，以此降低类与类之间的耦合，此即桥接模式。  

> 用户 A 需要一个红色的三角形。  
> 可以提供两种解决方案：  
>  
> * 构建各种形状的类，每个类提供一套颜色版本，随后生成红色的三角形类。  
> * 构建一个形状类，在类中定义形状与颜色，随后生成三角形的、红色的形状类。  
>  
> 其中第二中解决方案即桥接模式。  

## 9.2 模式定义

> **桥接模式** (Bridge Pattern) 又称为 **柄体** (Handle and Body) **模式** 或 **接口** (Interface) **模式** ，它属于对象结构性模式。  
>  
> * 将抽象部分与它的实现部分分离，使它们都可以独立地变化。  

## 9.3 模式结构

桥接模式包含如下角色：  

* Abstraction 抽象类
* Refined Abstraction 扩充抽象类
* Implementor 实现类接口
* Concrete Implementor 具体抽象类

```PlantUML
@startUML Bridge_ClassDiagram
hide empty member
class Client
abstract Abstraction{
    - pImp: Implementor*
    + Operation():void
    + Abstraction(Implementor*):void
}
class RefinedAbstraction{
    + Operation():void
    + RefinedAbstraction(Implementor*)():void
}
class Implementor{
    + OperationImp():void
}
class ConcreteImplementorA{
    + OperationImp():void
}
class ConcreteImplementorB{
    + OperationImp():void
}

Client .right.> Abstraction
Abstraction o-right->Implementor
Abstraction <|-- RefinedAbstraction
Implementor <|.. ConcreteImplementorA
Implementor <|.. ConcreteImplementorB

note bottom of Abstraction
pImp -> OperationImp( );
end note
@endUML
```

## 9.4 时序图

```PlantUML
@startUML Bridge_SequenceDiagram
participant ":Client" as Client
participant ":ConcreteImplementorA" as ConcreteImplementorA
participant ":RefinedAbstraction" as RefinedAbstraction

create ConcreteImplementorA
Client --> ConcreteImplementorA:<<create>>
create RefinedAbstraction
Client --> RefinedAbstraction: RefinedAstraction(Implementor*)( )<<create>>

Client -> RefinedAbstraction++:Operation( )
RefinedAbstraction->ConcreteImplementorA++:OperationImp( )
@endUML
```

## 9.5 代码分析

```C++
#include <iostream>
#include "ConcreteImplementorA.h"
#include "ConcreteImplementorB.h"
#include "RefinedAbstraction.h"
#include "Abstraction.h"

using namespace std;

int main(int argc, char *argv[])
{

    Implementor* pImp = new ConcreteImplementorA();
    Abstraction* pa = new RefinedAbstraction(pImp);
    pa->operation();

    Abstraction* pb = new RefinedAbstraction(new ConcreteImplementorB());
    pb->operation();

    delete pa;
    delete pb;

    return 0;
}
```

```C++
// RefinedAbstraction.h
#include "Abstraction.h"

class RefinedAbstraction : public Abstraction
{

public:
    RefinedAbstraction();
    RefinedAbstraction(Implementor* imp);
    virtual ~RefinedAbstraction();

    virtual void operation();
};
```

```C++
// RefinedAbstraction.cpp

#include "RefinedAbstraction.h"
#include <iostream>
using namespace std;


RefinedAbstraction::RefinedAbstraction(){
}

RefinedAbstraction::RefinedAbstraction(Implementor* imp):Abstraction(imp){
}

RefinedAbstraction::~RefinedAbstraction(){
}

void RefinedAbstraction::operation(){
    cout << "do something else ,and then " << endl;
    m_pImp->operationImp();
} 
```

## 9.6 模式分析

## 9.7 实例

## 9.8 优点

## 9.9 缺点

## 9.10 适用环境

## 9.11 模式应用

## 9.12 模式扩展
