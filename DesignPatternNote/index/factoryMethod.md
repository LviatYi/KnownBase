# 3. 工厂方法模式

## 3.1 模式动机

将工厂类抽象，为产品创建一个具体的工厂子类。  

> 不再将所有的产品都交付给同一个工厂创建，而是交给专门的工厂子类。  

## 3.2 模式定义

> **工厂方法模式** (Factory Method Pattern) 又称为 **工厂模式** ，也叫 **虚拟构造器** (Virtual Constructor) **模式** 或者 **多态工厂** (Polymorphic) **模式**，它属于类创建型模式。  
>  
> * 与简单工厂模式相比，工厂模式将工厂再次抽象。  
> * 由工厂父类负责定义创建产品对象的公共接口。  
> * 由工厂子类负责生成具体对象，确定究竟该实例化哪一个具体产品类。  

## 3.3 模式结构

工厂方法模式包含如下角色：  

* Product 抽象产品
* Concrete Product 具体产品
* Factory 抽象工厂
* Concrete Factory 具体工厂

```PlantUML
@startuml Factory_ClassDiagram
hide empty members
abstract Product{
    + use():void
}
abstract Factory{
    + FactoryMethod()：Product
}

class ConcreteProduct{
    + Use():void
}

class ConcreteFactory{
    + FactoryMethod(): Product
}

Product<|..ConcreteProduct
Factory<|..ConcreteFactory
ConcreteProduct<.right.ConcreteFactory
note bottom of ConcreteFactory
    return new ConcreteProduct( );
end note
@enduml
```

## 3.4 时序图

```PlantUML
@startuml Factory_SequenceDiagram
actor Main
participant ":ConcreteFactory" as ConcreteFactoryObj
participant ":ConcreteProduct" as ConcreteProductObj
Main -> ConcreteFactoryObj ++: FactoryMethod( ):Product
activate Main 
create ConcreteProductObj
ConcreteFactoryObj->ConcreteProductObj--: <<create>>
Main -> ConcreteProductObj++: Use( )
@enduml
```

## 3.5 代码分析

```C++
#include "Factory.h"
#include "ConcreteFunction.h"
#include "Product.h"
#include "iostream"
using namespace std;

int main(int argc,char* argv[])
{
    Factory* fc=new ConcreteFactory();
    Product* prod=fc->FactoryMethod();
    prod->Use();

    delete fc;
    delete prod;

    return 0;
}
```

## 3.6 模式分析

* 工厂方法模式是简单工厂模式的进一步抽象和推广。  
* 由于使用了面向对象的多态性，工厂方法模式保持了简单工厂模式的优点，同时克服了它的缺点。  
* 在工厂方法模式中，核心的工厂类不再负责所有产品的创建，而是将具体创建工作交给子类去做。这个核心类仅仅负责给出具体工厂必须实现的接口，而不负责哪一个产品类被实例化这种细节。  
* 因此工厂方法模式可以允许系统在不修改工厂角色的情况下引进新产品。  

## 3.7 实例

（略）

## 3.8 优点

* 工厂方法负责产品的创建，如此可以对用户隐藏产品类的实例化过程。这一点与简单工厂模式相同。  
* 工厂模式的关键是工厂方法具有多态性。所有具体工厂类都拥有统一的抽象父类。  
* 使用工厂方法模式的另一个优点是在系统中加入新产品时，无须修改抽象工厂和抽象产品提供的接口，无须修改客户端，也无须修改其他的具体工厂和具体产品，而只要添加一个具体工厂和具体产品就可以了。这样，系统的可扩展性也就变得非常好，完全符合「开闭原则」。  

## 3.9 缺点

* 比简单工厂模式更甚，添加新产品时不仅需新增具体产品类，还需要提供与之对应的具体工厂类。给系统带来了额外开销。  
* 由于考虑到系统的可扩展性，需要引入抽象层，在客户端代码中均使用抽象层进行定义，增加了系统的抽象性和理解难度，且在实现时可能需要用到DOM、反射等技术，增加了系统的实现难度。  

## 3.10 适用环境

在以下情况下可以使用工厂方法模式：

* 一个类不知道它所需要的对象的类。  
  在工厂方法模式中，客户端不需要知道具体产品类的类名，只需要知道所对应的工厂（具体工厂类）即可，具体的产品对象由具体工厂类创建。  
* 一个类通过其子类来指定创建哪个对象。  
  在工厂方法模式中，对于抽象工厂类只需要提供一个创建产品的接口，而由其子类来确定具体要创建的对象，利用面向对象的多态性和里氏代换原则，在程序运行时，子类对象将覆盖父类对象，从而使得系统更容易扩展。
* 将创建对象的任务委托给多个工厂子类中的某一个，客户端在使用时可以无须关心是哪一个工厂子类创建产品子类，需要时再动态指定，可将具体工厂类的类名存储在配置文件或数据库中。  

## 3.11 模式应用

JDBC中的工厂方法：

```Java
Connection conn=DriverManager.getConnection("jdbc:microsoft:sqlserver://loc
alhost:1433; DatabaseName=DB;user=sa;password=");
Statement statement=conn.createStatement();
ResultSet rs=statement.executeQuery("select * from UserInfo");
```

## 3.12 模式扩展

* 使用多个工厂方法  
  在抽象工厂角色中可以定义多个工厂方法，从而使具体工厂角色实现这些不同的工厂方法，这些方法可以包含不同的业务逻辑，以满足对不同的产品对象的需求。
* 产品对象的重复使用  
  工厂对象将已经创建过的产品保存到一个集合（如数组、 List 等）中，然后根据客户对产品的请求，对集合进行查询。如果有满足要求的产品对象，就直接将该产品返回客户端；如果集合中没有这样的产品对象，那么就创建一个新的满足要求的产品对象，然后将这个对象在增加到集合中，再返回给客户端。  
* 多态性的丧失和模式的退化  
  如果工厂仅仅返回一个具体产品对象，便违背了工厂方法的用意，发生退化，此时就不再是工厂方法模式了。一般来说，工厂对象应当有一个抽象的父类型，如果工厂等级结构中只有一个具体工厂类的话，抽象工厂就可以省略，也将发生了退化。当只有一个具体工厂，在具体工厂中可以创建所有的产品对象，并且工厂方法设计为静态方法时，工厂方法模式就退化成简单工厂模式。  
