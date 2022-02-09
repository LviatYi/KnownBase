# 2. 简单工厂模式

## 2.1 模式动机

定义一个创建对象的接口，让其子类自己决定实例化哪一个工厂类，工厂模式使其创建过程延迟到子类进行。

> 我们要生产一台汽车。A 需要一台 Red 车，B 需要一台 Green 车，C 要一台 Blue 车。可以构造一个汽车工厂类，输入相应的参数，就可以实例化需要的汽车类。

## 2.2 模式定义

> **简单工厂模式** (Simple Factory Pattern) 又称为 **静态工厂方法** (Static Factory Method) 模式，它属于类创建型模式。
>
> - 在简单工厂模式中，可以根据参数的不同返回不同类的实例。
> - 简单工厂模式专门定义一个类来负责创建其他类的实例，被创建的实例通常都具有共同的父类。

## 2.3 模式结构

简单工厂模式包含如下角色：

- Factory 工厂角色

  工厂角色负责实现创建所有实例的内部逻辑。

- Product 抽象产品角色

  抽象产品角色是被创建的所有对象的共同父类，负责描述所有实例所共有的公共接口。

- Concrete Product 具体产品角色

  具体产品角色是简单工厂模式的创建目标，所有创建的对象都充当这个角色的某个具体类的实例。

```PlantUML
@startuml SimpleFactory_ClassDiagram
hide empty members
class Factory{
    +CreateProduction(string): Product
}
class ConcreteProductA{
    +Use( ):void

}
class ConcreteProductB{
    +Use( ):void
}
abstract Product{
    +Use( ):void
}
Product<|..ConcreteProductA
Product<|..ConcreteProductB

ConcreteProductA<..Factory
ConcreteProductB<..Factory
note left of Factory
    switch(argEnum)
    {
        case A:
            return new ConcreteProductA( );
        case B:
            return new ConcreteProductB( );
        ...
    }
end note
@enduml
```

## 2.4 时序图

```PlantUML
@startuml SimpleFactory_ClassDiagram

actor Main
participant ":Factouy" as FactoryObj
participant ":ConcreteProductA" as ConcreteProductAObj

Main -> FactoryObj ++:CreateProduct(argEnum):Product
activate Main
create ConcreteProductAObj
FactoryObj->ConcreteProductAObj--:<<create>>
Main -> ConcreteProductAObj++:Use()

@enduml
```

## 2.5 示例代码

```C++
#include "Factory.h"
#include "ConcreteProductA.h"
#include "ConcreteProductB.h"
Product* Factory::createProduct(ardEnum proname)
{
    switch(proname)
    {
        case argEnum.A:
            return new ConcreteProductA();
        case argEnum.B:
            return new ConcreteProductB();
        default :
            return Null;
    }
}
```

## 2.6 模式分析

- 将对象的创建和对象本身业务处理分离可以降低系统的耦合度，使得两者修改起来都相对容易。
- 在调用工厂类的工厂方法时，由于工厂方法是静态方法，使用起来很方便，可通过类名直接调用，而且只需要传入一个简单的参数即可，在实际开发中，还可以在调用时将所传入的参数保存在 XML 等格式的配置文件中，修改参数时无须修改任何源代码。
- 简单工厂模式最大的问题在于工厂类的职责相对过重，增加新的产品需要修改工厂类的判断逻辑，这一点与开闭原则是相违背的。
- 简单工厂模式的要点在于：当你需要什么，只需要传入一个正确的参数，就可以获取你所需要的对象，而无须知道其创建细节。

## 2.7 实例

（略）

## 2.8 优点

- 工厂类封装了类的创建逻辑，客户端免除了创建产品对象的责任。因此简单工厂模式实现了对 **责任的分割** 。
- 客户端无需知道所创建的具体产品类的类名，只需要知道对应的参数即可。
- 通过引入 XML 等配置文件，可在不修改客户端代码的情况下更换需要的产品类。一定程度上提高了系统的 **灵活性**。

## 2.9 缺点

- 系统中多了一个工厂类，一定程度上增加了系统的复杂度和理解难度。
- 增加新的产品类，需要更新工厂类。如果产品类过多，可能会造成工厂类负担过重。
- 构建产品类严重依赖工厂类。
- 简单工厂模式由于使用了静态工厂方法，造成工厂角色无法形成基于继承的等级结构。

## 2.10 适用环境

在以下情况下可以使用简单工厂模式：

- 工厂类负责创建的对象比较少。  
  由于创建的对象较少，不会造成工厂方法中的业务逻辑太过复杂。
- 客户端只知道传入工厂类的参数，对于如何创建对象不关心。  
  客户端既不需要关心创建细节，甚至连类名都不需要记住，只需要知道类型所对应的参数。

## 2.11 模式应用

JDK 类库中广泛使用了简单工厂模式，如工具类 `java.text.DateFormat` ，它用于格式化一个本地日期或时间。

```Java
public final static DateFormat getDateInstance();
public final static DateFormat getDateInstance(int style);
public final static DateFormat getDateInstance(int style,Locale
locale);
```
