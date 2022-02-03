# 6. 单例模式

## 6.1 模式动机

对于系统中的某些类，只需要或最多允许有一个实例（对象）。单例模式让类自身负责保存它的唯一实例，以此保证没有第二个实例被创建。  

## 6.2 模式定义

> **单例模式** (Singleton Pattern) 又称为 **单件模式** 或 **单态模式** ，它属于对象创建型模式。  
>  
> * 单例模式确保某一个类只有一个实例，而且自行实例化并向整个系统提供这个实例，这个类称为单例类，它提供全局访问的方法。  
> * 单例模式的要点有三个：
>   * 某个类只能有一个实例。  
>   * 它必须自行创建这个实例。  
>   * 它必须自行向整个系统提供这个实例。  

## 6.3 模式结构

单例模式包含如下角色：  

* Singleton 单例

```PlantULM
@startuml Singleton_ClassDiagram
class Singleton{
    - instance: Singleton
    + getInstance():Singleton
    + SingletonOperation():void
    - Singleton():void
}

note left of Singleton
    if (instance == NULL)
    {
        instance = new Singleton();
    }
    return instance;
end note

Singleton o--> Singleton :instance
@enduml 
```

## 6.4 时序图

```PlantUML
@startuml Singleton_SequenceDiagram
actor iMain
participant ":Singleton" as Singleton
iMain -> Singleton ++: getInstance( )
Singleton -> Singleton ++ : <<create>>
Singleton --
Singleton --
iMain -> Singleton: SingletonOperation( )
@enduml
```

## 6.5 代码分析

```C++
#include <iostream>
#include "Singleton.h"

using namespace std;

int main(int argc, char *argv[])
{
    Singleton* sg = Singleton::getInstance();
    sg->SingletonOperation();

    return 0;
}
```

```C++
// Singleton.cpp
#include "Singleton.h"
#include <iostream>
using namespace std;

Singleton * Singleton::instance = NULL;
Singleton::Singleton(){
}

Singleton::~Singleton(){
    delete instance;
}

Singleton* Singleton::getInstance(){
    if (instance == NULL)
    {
        instance = new Singleton();
    }

    return instance;
}


void Singleton::SingletonOperation(){
    cout << "Singleton Operation" << endl;
}
```

## 6.6 模式分析

* 单例模式目的是保证一个类仅有一个实例，并提供全局访问点。  
* 单例类拥有一个 **私有构造函数** ，保证用户不能通过 `new` 关键字进行实例化操作。  
* 单例模式拥有一个 **静态私有成员变量** 与 **静态公有工厂方法** ，用于检验是否有已存在的实例，否则实例化自己并储存。  

## 6.7 实例

略

## 6.8 优点

* 提供了对唯一实例的受控访问。  
  因为单例类封装了它的唯一实例，所以它可以严格控制客户怎样以及何时访问它，并为设计及开发团队提供了共享的概念。  
* 节约系统资源。  
  由于在系统内存中只存在一个对象，对于一些需要频繁创建和销毁的对象，单例模式无疑可以提高系统的性能。  
* 允许可变数目的实例。  
  我们可以基于单例模式进行扩展，使用与单例控制相似的方法来获得指定个数的对象实例。  

## 6.9 缺点

* 由于单例模式中没有抽象层，因此单例类的扩展有很大的困难。  
* 单例类的职责过重，在一定程度上违背了「单一职责原则」。因为单例类既充当了工厂角色，提供了工厂方法，同时又充当了产品角色，包含一些业务方法，将产品的创建和产品的本身的功能融合到一起。  
* 滥用单例将带来一些负面问题，如为了节省资源将数据库连接池对象设计为单例类，可能会导致共享连接池对象的程序过多而出现连接池溢出；现在很多面向对象语言 (Java、C#) 的运行环境都提供了自动垃圾回收的技术，因此，如果实例化的对象长时间不被利用，系统会认为它是垃圾，会自动销毁并回收资源，下次利用时又将重新实例化，这将导致对象状态的丢失。  

## 6.10 适用环境

在以下情况下可以使用单例模式：

* 系统只需要一个实例对象，如系统要求提供一个唯一的序列号生成器，或者需要考虑资源消耗太大而只允许创建一个对象。  
* 客户调用类的单个实例只允许使用一个公共访问点，除了该公共访问点，不能通过其他途径访问该实例。  
* 在一个系统中要求一个类只有一个实例时才应当使用单例模式。反过来，如果一个类可以有几个实例共存，就需要对单例模式进行改进，使之成为多例模式。  

## 6.11 模式应用

一个具有自动编号主键的表可以有多个用户同时使用，但数据库中只能有一个地方分配下一个主键编号，否则会出现主键重复，因此该主键编号生成器必须具备唯一性，可以通过单例模式来实现。  

## 6.12 模式扩展
