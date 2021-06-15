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

识别类中存在的两种维度，将其设计为两个独立的继承等级结构。通常将普通业务方法和与之关系最密切的维度设计为 **抽象类** ，而将另一个维度设计为 **实现类** 。  

## 9.2 模式定义

> **桥接模式** (Bridge Pattern) 又称为 **柄体** (Handle and Body) **模式** 或 **接口** (Interface) **模式** ，它属于对象结构性模式。  
>  
> * 将抽象部分与它的实现部分分离，使它们都可以独立地变化。  

## 9.3 模式结构

桥接模式包含如下角色：  

* Abstraction 抽象类
  用于定义抽象类的 **接口** 。  
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
class RefinedAbstractionA{
    + Operation():void
    + RefinedAbstractionA(Implementor*)():void
}
class RefinedAbstractionB{
    + Operation():void
    + RefinedAbstractionB(Implementor*)():void
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
Abstraction <|-- RefinedAbstractionA
Abstraction <|-- RefinedAbstractionB
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
participant ":RefinedAbstractionA" as RefinedAbstractionA

create ConcreteImplementorA
Client --> ConcreteImplementorA:<<create>>
create RefinedAbstractionA
Client --> RefinedAbstractionA: RefinedAstraction(Implementor*)( )<<create>>

Client -> RefinedAbstractionA++:Operation( )
RefinedAbstractionA->ConcreteImplementorA++:OperationImp( )
@endUML
```

## 9.5 代码分析

```C++
#include <iostream>
#include "ConcreteImplementorA.h"
#include "ConcreteImplementorB.h"
#include "RefinedAbstractionA.h"
#include "Abstraction.h"

using namespace std;

int main(int argc, char *argv[])
{

    Implementor* pImp = new ConcreteImplementorA();
    Abstraction* pa = new RefinedAbstractionA(pImp);
    pa->operation();

    Abstraction* pb = new RefinedAbstractionA(new ConcreteImplementorB());
    pb->operation();

    delete pa;
    delete pb;

    return 0;
}
```

```C++
// RefinedAbstractionA.h
#include "Abstraction.h"

class RefinedAbstractionA : public Abstraction
{

public:
    RefinedAbstractionA();
    RefinedAbstractionA(Implementor* imp);
    virtual ~RefinedAbstractionA();

    virtual void operation();
};
```

```C++
// RefinedAbstractionA.cpp

#include "RefinedAbstractionA.h"
#include <iostream>
using namespace std;


RefinedAbstractionA::RefinedAbstractionA(){
}

RefinedAbstractionA::RefinedAbstractionA(Implementor* imp):Abstraction(imp){
}

RefinedAbstractionA::~RefinedAbstractionA(){
}

void RefinedAbstractionA::operation(){
    cout << "do something else ,and then " << endl;
    m_pImp->operationImp();
} 
```

## 9.6 模式分析

桥接模式的重点在于理解如何将抽象化与实现化脱耦，使其可以独立变化。  

* **抽象化**
  * 抽象化就是忽略一些信息，把不同的实体当作同样的实体对待。  
  * 在面向对象中，将对象的共同性质抽取出来形成类的过程即为抽象化的过程。  
* **实现化**
  * 针对抽象化给出的具体实现，就是实现化。  
  * 抽象化与实现化是一对互逆的概念，实现化产生的对象比抽象化更具体，是对抽象化事物的进一步具体化的产物。  
* **脱耦**
  * 脱耦就是将抽象化和实现化之间的耦合解脱开，或者说是将它们之间的强关联改换成弱关联，将两个角色之间的继承关系改为关联关系。  
  * 桥接模式中的所谓脱耦，就是指在一个软件系统的抽象化和实现化之间使用关联关系（组合或者聚合关系）而不是继承关系，从而使两者可以相对独立地变化，这就是桥接模式的用意。  

## 9.7 实例

```PlantUML
@startuml Bridge_Example
hide empty members
abstract Pen{
    # color : Color
    + setColor(Color color)
    + Draw()
}

class BigPen{
    + Draw()
}
class MiddlePen{
    + Draw()
}
class SmallPen{
    + Draw()
}

abstract Color{
    + PutColor()
}

class Red{
    + PutColor()
}
class Green{
    + PutColor()
}
class Blue{
    + PutColor()
}

Pen <|-- BigPen
Pen <|-- MiddlePen
Pen <|-- SmallPen

Pen o-right-> Color : BRIDGE
Color <|.. Red
Color <|.. Green
Color <|.. Blue
@enduml
```

基于不同平台的视频播放器（兼容不同格式），可使用桥接模式来设计。  

## 9.8 优点

桥接模式的优点如下：  

* 分离抽象接口及其实现部分。  
* 桥接模式有时类似于多继承方案，但是多继承方案违背了类的单一职责原则（即一个类只有一个变化的原因），复用性比较差，而且多继承结构中类的个数非常庞大，桥接模式是比多继承方案更好的解决方法。  
* 桥接模式提高了系统的可扩充性，在两个变化维度中任意扩展一个维度，都不需要修改原有系统。  
* 实现细节对客户透明，可以对用户隐藏实现细节。  

## 9.9 缺点

桥接模式的缺点如下：  

* 桥接模式的引入会增加系统的理解与设计难度，由于聚合关联关系建立在抽象层，要求开发者针对抽象进行设计与编程。  
* 桥接模式要求正确识别出系统中两个独立变化的维度，因此其使用范围具有一定的局限性。  

## 9.10 适用环境

在以下情况下可以使用桥接模式：  

* 如果一个系统需要在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承联系，通过桥接模式可以使它们在抽象层建立一个关联关系。  
* 抽象化角色和实现化角色可以以继承的方式独立扩展而互不影响，在程序运行时可以动态将一个抽象化子类的对象和一个实现化子类的对象进行组合，即系统需要对抽象化角色和实现化角色进行动态耦合。  
* 一个类存在两个独立变化的维度，且这两个维度都需要进行扩展。  
* 虽然在系统中使用继承是没有问题的，但是由于抽象化角色和具体化角色需要独立变化，设计要求需要独立管理这两者。  
* 对于那些不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统，桥接模式尤为适用。  

## 9.11 模式应用

> 一个 Java 桌面软件总是带有所在操作系统的视感 (LookAndFeel) ，如果一个 Java 软件是在 Unix 系统上开发的，那么开发人员看到的是 Motif 用户界面的视感；在 Windows 上面使用这个系统的用户看到的是 Windows 用户界面的视感；而一个在 Macintosh 上面使用的用户看到的则是 Macintosh 用户界面的视感， Java 语言是通过所谓的 Peer 架构做到这一点的。 Java 为 AWT 中的每一个 GUI 构件都提供了一个 Peer 构件，在 AWT 中的 Peer 架构就使用了桥接模式。  

## 9.12 模式扩展

常常将适配器模式与桥接模式联用。  
