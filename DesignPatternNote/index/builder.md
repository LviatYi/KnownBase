# 5. 建造者模式

## 5.1 模式动机

将一个类的成员组装成类的过程封装。  

> 我们要生产一台汽车。这辆汽车由车轮、方向盘、发动机等部件组成，其部件的组装过程有先后顺序。可以构造一个建造者类，将复杂的具体构造细节封装。  

## 5.2 模式定义

> **建造者模式** (Builder Pattern) 又可以称为 **生成器模式** ，它属于对象创建型模式。  
>  
> * 将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。  
> * 建造者模式是一步一步创建一个复杂的对象，它允许用户只通过指定复杂对象的类型和内容就可以构建它们，用户不需要知道内部的具体构建细节。  

## 5.3 模式结构

建造者模式包含如下角色：  

* Builder 抽象建造者
* ConcreteBuilder 具体建造者
* Director 指挥者
* Product 产品角色

```PlantUML
@startuml Builder_ClassDiagram
hide empty members
class Director {
    - pbuilder :Builder*
    + Constuct() :Product*
    + setBuilder(Builder*) :void
}
class Builder{
    + BuildPartA() :void
    + BuildPartB() :void
    + BuildPartC() :void
    + getResult() :void
}
class ConcreteBuilder{
    + BuildPartA() :void
    + BuildPartB() :void
    + BuildPartC() :void
}
class Product

Director o-right- Builder
Builder <|.. ConcreteBuilder
ConcreteBuilder ..> Product
note bottom of Director
pbuilder -> BuildPartA();
pbuilder -> BuildPartB();
pbuilder -> BuildPartC();
pbuilder -> getresult();
end note
@enduml 
```

## 5.4 时序图

```PlantUML
@startuml Builder_SequenceDiagram
actor iMain
participant ":Director" as Director
participant ":ConcreteBuilder" as ConcreteBuilder

create ConcreteBuilder
iMain-->ConcreteBuilder: <<create>>
iMain->Director++: setBuilder(Builder*)
Director--
iMain->Director++: Constuct( ):Product*
Director->ConcreteBuilder++:BuildPartA( )
ConcreteBuilder--
Director->ConcreteBuilder++:BuildPartB( )
ConcreteBuilder--
Director->ConcreteBuilder++:BuildPartC( )
ConcreteBuilder--
Director->ConcreteBuilder++:getResult( )
ConcreteBuilder--
@enduml 
```

## 5.5 代码分析

```C++
#include <iostream>
#include "ConcreteBuilder.h"
#include "Director.h"
#include "Builder.h"
#include "Product.h"

using namespace std;

int main(int argc, char *argv[])
{
    ConcreteBuilder * builder = new ConcreteBuilder();
    Director director;
    director.setBuilder(builder);
    Product* pd =  director.Constuct();
    pd->show();

    delete builder;
    delete pd;
    return 0;
}
```

```C++
// ConcreteBuilder.cpp
#include "ConcreteBuilder.h"

ConcreteBuilder::ConcreteBuilder(){
}
ConcreteBuilder::~ConcreteBuilder(){
}

void ConcreteBuilder::BuildPartA(){
    m_prod->setA("A Style"); //不同的建造者，可以实现不同产品的建造  
}

void ConcreteBuilder::BuildPartB(){
    m_prod->setB("B Style");
}

void ConcreteBuilder::BuildPartC(){
    m_prod->setC("C style");
}
```

```C++
//  Director.cpp
#include "Director.h"

Director::Director(){
}

Director::~Director(){
}

void Director::setBuilder(Builder* buider){
    m_pbuilder = buider;
}

Product* Director::Constuct(){
    m_pbuilder->BuildPartA();
    m_pbuilder->BuildPartB();
    m_pbuilder->BuildPartC();

    return m_pbuilder->getResult();
}
```

## 5.6 模式分析

抽象建造者类 (Builder) 中定义了产品的创建方法和返回方法；  

建造者模式的结构中引入了指挥者类 (Director) ，该类的作用主要有两个：  

* 隔离了客户与生产过程。  
* 负责控制产品的生成过程。  

Director 针对抽象建造者编程，客户端只需要知道具体建造者的类型，即可通过 Director 类调用建造者的相关方法，最后 Builder 返回一个完整的产品对象。  

在客户端代码中，无须关心产品对象的具体组装过程，只需确定具体建造者的类型即可，建造者模式将复杂对象的构建与对象的表现分离开来，这样使得同样的构建过程可以创建出不同的表现。  

## 5.7 实例

实例：KFC 套餐

这个实例描述了 KFC 如何创建套餐：  

* 套餐是一个复杂对象，它一般包含主食（如汉堡、鸡肉卷等）和饮料（如果汁、 可乐等）等组成部分。  
* 不同的套餐有不同的组成部分。  
* KFC的服务员可以根据顾客的要求，一步一步装配这些组成部分，构造一份完整的套餐，然后返回给顾客。  

```PlantUML
@startuml Builder_Example
hide empty members

class KFCWaiter{
    - mb: MealBuilder
    + Construct():void
    + setMealBuilder():void
}
class Meal{
    - drink: string
    - food: string
    + getDrink() :string
    + getFood() :string
    + setDring() :string
    + setFood() :string
}
class MealBuilder{
    - meal:Meal
    + BuildDrink():void
    + BuildFood():void
    + getMeal():Meal
}
class SubMealBuilderA{
    + BuildDrink():void
    + BuildFood():void
}
class SubMealBuilderB{
    + BuildDrink():void
    + BuildFood():void
}
KFCWaiter o-right- MealBuilder
MealBuilder <|--SubMealBuilderA
MealBuilder <|--SubMealBuilderB
Meal --* MealBuilder
@enduml
```

## 5.8 优点

* 在建造者模式中，客户端不必知道产品内部组成的细节。  
  将产品本身与产品的创建过程解耦，使得相同的创建过程可以创建不同的产品对象。  
* 每一个具体建造者都相对独立，而与其他的具体建造者无关。  
  因此可以很方便地替换具体建造者或增加新的具体建造者，用户使用不同的具体建造者即可得到不同的产品对象。  
* 可以更加精细地控制产品的创建过程。  
  将复杂产品的创建步骤分解在不同的方法中，使得创建过程更加清晰，也更方便使用程序来控制创建过程。  
* 增加新的具体建造者无须修改原有类库的代码，指挥者类针对抽象建造者类编程，系统扩展方便，符合「开闭原则」。  

## 5.9 缺点

* 建造者模式所创建的产品一般具有较多的共同点，其组成部分相似，如果产品之间的差异性很大，则不适合使用建造者模式，因此其使用范围受到一定的限制。  
* 如果产品的内部变化复杂，可能会导致需要定义很多具体建造者类来实现这种变化，导致系统变得很庞大。  

## 5.10 适用环境

在以下情况下可以使用建造者模式：

* 需要生成的产品对象有复杂的内部结构，这些产品对象通常包含多个成员属性。  
* 需要生成的产品对象的属性相互依赖，需要指定其生成顺序。  
* 对象的创建过程独立于创建该对象的类。在建造者模式中引入了指挥者类，将创建过程封装在指挥者类中，而不在建造者类中。  
* 隔离复杂对象的创建和使用，并使得相同的创建过程可以创建不同的产品。  

## 5.11 模式应用

游戏设计中，地图包括天空、地面、背景等组成部分，人物角色包括人体、服装、装备等组成部分，可以使用建造者模式对其进行设计，通过不同的具体建造者创建不同类型的地图或人物。  

## 5.12 模式扩展

### 5.12.1 建造者模式的简化

* **省略抽象建造者角色** (Builder)
  如果系统中只需要一个具体建造者的话，可以省略掉抽象建造者。  
* **省略指挥者角色** (Director)
  在具体建造者只有一个的情况下，如果抽象建造者已经被省略，指挥者角色也没有存在意义。可以让 Builder 角色扮演双重角色。  

### 5.12.2 建造者模式与抽象工厂模式的比较

* 与抽象工厂模式相比，**建造者模式** 返回一个组装完好的完整产品，而 **抽象工厂模式** 返回一系列相关的产品，这些产品位于不同的产品等级结构，构成了产品族。  
* 在 **抽象工厂模式** 中，客户端实例化工厂类，然后调用工厂方法获取所需产品对象，而在 **建造者模式** 中，客户端可以不直接调用建造者的相关方法，而是通过指挥者类来指导如何生成对象，包括对象的组装过程和建造步骤，它侧重于一步步构造一个复杂对象，返回一个完整的对象。  
* 如果将 **抽象工厂模式** 看成 **汽车配件生产工厂** ，生产一个产品族的产品，那么 **建造者模式** 就是一个 **汽车组装工厂** ，通过对部件的组装可以返回一辆完整的汽车。  
