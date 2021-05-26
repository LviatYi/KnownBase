# 8. 适配器模式

## 8.1 模式动机

定义一个包装类，来包装不兼容接口的对象。  

通常情况下，客户端可以通过目标类的接口访问它所提供的服务。有时，现有的类可以满足客户类的功能需要，但是它所提供的接口不一定是客户类所期望的，这可能是因为现有类中方法名与目标类中定义的方法名不一致等原因所导致的。 

> 用户 A 想通过 add() 方法调用一个加法算法，然而实际上可供使用的函数名为 add_int() 。因此可以对其进行封装。  

## 8.2 模式定义

> **适配器模式** (Adapter Pattern) 又称为 **包装器** (Wrapper) **模式** ，它可以作为类结构性模式，也可以作为对象结构性模式。  
> 
> * 适配器模式将一个接口转换成客户希望的另一个接口。  
> * 适配器模式使接口不兼容的那些类可以一起工作。  

## 8.3 模式结构

适配器模式包含如下角色：  

* Target 目标抽象类
* Adapter 适配器类
  即包装类。  
* Adaptee 适配者类
  即被包装类，被适配的类。  
* Client 客户类

适配器模式拥有对象适配器和类适配器两种实现：  

* 对象适配器

```PlantUML
@startUML Adapter_ClassDiagram_Object
hide empty member
class Client
class Target{
    + Request():void
}
class Adapter{
    - adaptee: Adaptee*
    + Request():void
}
class Adaptee{
    + SpecificRequest():void
}

Client .right.> Target
Target<|--Adapter
Adapter--> Adaptee

note left of Adapter
adaptee -> SpecificRequest( );
end note

@endUML
```

* 类适配器

```PlantUML
@startUML Adapter_ClassDiagram_Class
hide empty member
class Client
class Target{
    + Request():void
}
class Adapter{
    + Request():void
}
class Adaptee{
    + SpecificRequest():void
}

Client .right.> Target
Target<|--Adapter
Adaptee <|-- Adapter

note left of Adapter
SpecificRequest( );
end note
@endUML
```

## 8.4 时序图

```PlantUML
@startUML Adapter_SequenceDiagram
participant ":Client" as Client
participant ":Adaptee" as Adaptee
participant ":Adapter" as Adapter
create Adaptee
Client --> Adaptee : <<create>>
create Adapter
Client --> Adapter : new Adapter(adaptee) <<create>>
Client -> Adapter ++: Request( )
Adapter -> Adaptee ++ : SpecificRequest( ) 
@endUML
```

## 8.5 代码分析

```C++
#include <iostream>
#include "Adapter.h"
#include "Adaptee.h"
#include "Target.h"

using namespace std;

int main(int argc, char *argv[])
{
    Adaptee* adaptee = new Adaptee();
    Target* tar = new Adapter(adaptee);
    tar->request();

    return 0;
}
```

```C++
// Adapter.h
#include "Target.h"
#include "Adaptee.h"

class Adapter : public Target
{

public:
    Adapter(Adaptee *adaptee);
    virtual ~Adapter();

    virtual void request();//重写

private:
    Adaptee* m_pAdaptee;
};
```

```C++
// Adapter.cpp
#include "Adapter.h"

Adapter::Adapter(Adaptee * adaptee){
    m_pAdaptee =  adaptee;
}

Adapter::~Adapter(){

}

void Adapter::request(){
    m_pAdaptee->specificRequest();
}
```

```C++
// Adaptee.h
class Adaptee
{
public:
    Adaptee();
    virtual ~Adaptee();

    void specificRequest();
};
```

## 8.6 模式分析

## 8.7 实例

## 8.8 优点

* 将目标类和适配者类解耦。
  通过引入一个适配器类来重用现有的适配者类。  
* 增加了类的透明性和复用性。  
  将具体类的实现封装在适配者类中，对于客户端类来说是透明的，而且提高了适配者的复用性。  
* 更高的灵活性和扩展性。  
  通过使用配置文件，可以很方便地更换适配器，也可以在不修改原有代码的基础上增加新的适配器类，完全符合「开闭原则」。  

类适配器模式还具有如下优点：  

* 由于适配器类是适配者类的子类，因此可以在适配器类中置换一些适配者的方法，使得适配器的灵活性更强。

对象适配器模式还具有如下优点：  

* 一个对象适配器可以把多个不同的适配者适配到同一个目标，也就是说，同一个适配器可以把适配者类和它的子类都适配到目标接口。

## 8.9 缺点

类适配器模式的缺点如下：  

* 对于 Java、C# 等不支持多重继承的语言，一次最多只能适配一个适配者类，而且目标抽象类只能为抽象类，不能为具体类，其使用有一定的局限性，不能将一个适配者类和它的子类都适配到目标接口。  

对象适配器模式的缺点如下：  

* 与类适配器模式相比，要想置换适配者类的方法就不容易。如果一定要置换掉适配者类的一个或多个方法，就只好先做一个适配者类的子类，将适配者类的方法置换掉，然后再把适配者类的子类当做真正的适配者进行适配，实现过程较为复杂。  

## 8.10 适用环境

在以下情况下可以使用适配器模式：

* 系统需要使用现有的类，而这些类的接口不符合系统的需要。
* 想要建立一个可以重复使用的类，用于与一些彼此之间没有太大关联的一些类，包括一些可能在将来引进的类一起工作。

## 8.11 模式应用

Java 中，与数据库库的交互的 JBDC 接口和各个数据库的 API 之间使用了适配器模式。  

## 8.12 模式扩展

### 8.12.1 默认适配器模式 (Default Adapter Pattern) 或缺省适配器模式

当不需要全部实现接口提供的方法时，可先设计一个抽象类实现接口，并为该接口中每个方法提供一个默认实现（空方法），那么该抽象类的子类可有选择地覆盖父类的某些方法来实现需求，它适用于一个接口不想使用其所有的方法的情况。因此也称为单接口适配器模式。  
