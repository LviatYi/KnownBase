# 4. 抽象工厂模式

## 4.1 模式动机

首先引入两个概念：

* **产品等级结构** 即产品的继承结构，用于划分产品种类。  
  > 如 *电视机* 和 *各类品牌的电视机* 构成了产品等级关系。  
* **产品族** 指由同一个工厂生产的，位于不同产品等级结构的一组产品。  
  > 如 *某种品牌的电视机* 和 *同类品牌的电冰箱* 属于同一个产品族。  

当一个工厂所需生产的具体产品不是一个简单对象，而是多个位于不同产品等级结构中属于不同类型的具体产品时需要使用 **抽象工厂关系** 。  

抽象工厂模式是所有形式的工厂模式中最为抽象和最具一般性的一种形态。  

* 抽象工厂模式与工厂方法模式最大的区别在于，工厂方法模式针对的是一个产品等级结构，而抽象工厂模式则需要面对多个产品等级结构，一个工厂等级结构可以负责多个不同产品等级结构中的产品对象的创建。  
* 当一个工厂等级结构可以创建出分属于不同产品等级结构的一个产品族中的所有对象时，抽象工厂模式比工厂方法模式更为简单、有效率。  

## 4.2 模式定义

> **抽象工厂模式** (Abstract Factory Pattern) 提供一个创建一系列相关或相互依赖对象的接口，而无须指定它们具体的类。抽象工厂模式又称为 Kit 模式，属于 **对象** 创建型模式。  

## 4.3 模式结构

抽象工厂模式包含如下角色：  

* AbstractFactory 抽象工厂
* ConcreteFactory 具体工厂
* AbstractProduvt 抽象产品
* Product 具体产品

```PlantUML
@startuml Factory_ClassDiagram
hide empty members
abstract AbstractFactory{
    + CreateProductA():void
    + CreateProductB():void
}
class ConcreteFactory1{
    + CreateProductA():void
    + CreateProductB():void
}
class ConcreteFactory2{
    + CreateProductA():void
    + CreateProductB():void
}

AbstractFactory<|..ConcreteFactory1
AbstractFactory<|..ConcreteFactory2

abstract AbstractProductA{
    + Eat():void
}
abstract AbstractProductB{
    + Drink():void
}

class ProductA1{
    +Eat():void
}
class ProductA2{
    +Eat():void
}
class ProductB1{
    +Drink():void
}
class ProductB2{
    +Drink():void
}
AbstractProductA<|..ProductA1
AbstractProductA<|..ProductA2
AbstractProductB<|..ProductB1
AbstractProductB<|..ProductB2

ConcreteFactory1..>ProductA1
ConcreteFactory1..>ProductB1
ConcreteFactory2..>ProductA2
ConcreteFactory2..>ProductB2
@enduml
```

## 4.4 时序图

```PlantUML
@startuml Factory_SequenceDiagram
actor "iMain" as Main
participant ":ConcreteFactory1" as ConcreteFactory1
participant ":ConcreteFactory2" as ConcreteFactory2
participant ":ProductA1" as ProductA1
participant ":ProductB1" as ProductB1
participant ":ProductA2" as ProductA2
participant ":ProductB2" as ProductB2

Main -> ConcreteFactory1++: CreateProduceA( )
create ProductA1
ConcreteFactory1 --> ProductA1--:<<create>>
Main -> ConcreteFactory1++: CreateProduceB( )
create ProductB1
ConcreteFactory1 --> ProductB1--:<<create>>

Main -> ProductA1++:Eat( )
Main -> ProductB1++:Drink( )

Main -> ConcreteFactory2++: CreateProduceA( )
create ProductA2
ConcreteFactory2 --> ProductA2--:<<create>>
Main -> ConcreteFactory2++: CreateProduceB( )
create ProductB2
ConcreteFactory2 --> ProductB2--:<<create>>

Main -> ProductA2++:Eat( )
Main -> ProductB2++:Drink( )

@enduml
```

## 4.5 代码分析

```C++
#include <iostream>
#include "AbstractFactory.h"
#include "AbstractProductA.h"
#include "AbstractProductB.h"
#include "ConcreteFactory1.h"
#include "ConcreteFactory2.h"

using namespace std;

int main(int argc, char *argv[])
{
    AbstractFactory * fc = new ConcreteFactory1();
    AbstractProductA * pa1 = fc->CreateProductA();
    AbstractProductB * pb1 = fc->CreateProductB();
    pa1->Eat();
    pb1->Drink();
    
    AbstractFactory * fc2 = new ConcreteFactory2();
    AbstractProductA * pa2 = fc2->CreateProductA();
    AbstractProductB * pb2 = fc2->CreateProductB();
    pa2->Eat();
    pb2->Drink();
}
```

```C++
// ConcreteFactory1.cpp
#include "ConcreteFactory1.h"
#include "ProductA1.h"
#include "ProductB1.h"

AbstractProductA * ConcreteFactory1::createProductA(){
    return new ProductA1();
}


AbstractProductB * ConcreteFactory1::createProductB(){
    return new ProductB1();
}
```

```C++
//ProductA1.cpp
#include "ProductA1.h"
#include <iostream>

using namespace std;

void ProductA1::Eat(){
    cout << "use Product A1" << endl;
}
```

## 4.6 模式分析

## 4.7 实例

## 4.8 优点

* 抽象工厂模式隔离了具体类的生成，使得客户并不需要知道什么被创建。由于这种隔离，更换一个具体工厂就变得相对容易。所有的具体工厂都实现了抽象工厂中定义的那些公共接口，因此只需改变具体工厂的实例，就可以在某种程度上改变整个软件系统的行为。  
* 当一个产品族中的多个对象被设计成一起工作时，它能够保证客户端始终只使用同一个产品族中的对象。这对一些需要根据当前环境来决定其行为的软件系统来说，是一种非常实用的设计模式。  
* 增加新的具体工厂和产品族很方便，无须修改已有系统，符合「开闭原则」。  

## 4.9 缺点

* 开闭原则的倾斜性。增加新的工厂和产品族容易，增加新的产品等级结构却很麻烦。  
* 在添加新的产品对象时，难以扩展抽象工厂来生产新种类的产品，这是因为在抽象工厂角色中规定了所有可能被创建的产品集合，要支持新种类的产品就意味着要对该接口进行扩展，而这将涉及到对抽象工厂角色及其所有子类的修改，显然会带来较大的不便。

## 4.10 适用环境

在以下情况下可以使用抽象工厂模式：

* 一个系统不应当依赖于产品类实例如何被创建、组合和表达的细节，这对于所有类型的工厂模式都是重要的。  
* 系统中有多于一个的产品族，而每次只使用其中某一产品族。  
* 属于同一个产品族的产品将在一起使用，这一约束必须在系统的设计中体现出来。  
* 系统提供一个产品类的库，所有的产品以同样的接口出现，从而使客户端不依赖于具体实现。  

## 4.11 模式应用

UI 设计中，界面主题的更换可以使用抽象工厂模式进行设计。如同意修改页面中的按钮、文本框的属性。  

## 4.12 模式扩展

### 4.12.1 「开闭原则」的倾斜性

「开闭原则」要求系统对扩展开放，对修改封闭，通过扩展达到增强其功能的目的。对于涉及到多个产品族与多个产品等级结构的系统，其功能增强包括两方面：  

* **增加产品族**
  对于增加新的产品族，工厂方法模式很好的支持了「开闭原则」，对于新增加的产品族，只需要对应增加一个新的具体工厂即可，对已有代码无须做任何修改。  
* **增加新的产品等级结构**
  对于增加新的产品等级结构，需要修改所有的工厂角色，包括抽象工厂类，在所有的工厂类中都需要增加生产新产品的方法，不能很好地支持「开闭原则」。

抽象工厂模式的这种性质称为「开闭原则」的倾斜性，抽象工厂模式以一种倾斜的方式支持增加新的产品，它为新产品族的增加提供方便，但不能为新的产品等级结构的增加提供这样的方便。

### 4.12.2 工厂模式的退化

* 当抽象工厂模式中每一个具体工厂类只创建一个产品对象，也就是只存在一个产品等级结构时，抽象工厂模式退化成工厂方法模式。  
* 当工厂方法模式中抽象工厂与具体工厂合并，提供一个统一的工厂来创建产品对象，并将创建对象的工厂方法设计为静态方法时，工厂方法模式退化成简单工厂模式。  
