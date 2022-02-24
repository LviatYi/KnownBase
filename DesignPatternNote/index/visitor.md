# 25. 访问者模式

## 25.1 模式动机

需要在不修改现有系统的情况下扩展系统的功能，为这些不同类型的元素增加新的操作，则可使用 **访问者模式**。

## 25.2 模式定义

> **访问者模式** (Visitor Pattern)，它属于对象行为型模式。
>
> - 提供一个作用于某对象结构中的各元素的操作表示。
> - 允许在不改变各元素的类的前提下定义作用于这些元素的新操作。

## 25.3 模式结构

- Vistor 抽象访问者
  - 为对象结构中每一个具体元素声明一个访问操作。
  - 从访问操作的名称或参数类型可知需要访问的具体元素的类型。
- ConcreteVisitor 具体访问者
  - 具体访问者实现了每个由抽象访问者声明的操作。
  - 每一个操作用于访问对象结构中一种类型的元素。
- Element 抽象元素
  - 一般是抽象类或者接口。
  - 定义一个 `accept()` 方法，该方法通常以一个抽象访问者作为参数。
- ConcreteElement 具体元素
  - 具体元素实现了 `accept()` 方法。
  - 在 `accept()` 方法中调用访问者的访问方法以便完成对一个元素的操作。
- ObjectStructure 对象结构
  - 一个元素的集合，用于存放元素对象，并且提供了遍历其内部元素的方法。
  - 可以结合组合模式来实现，也可以是一个简单的集合对象，如一个 List 对象或一个 Set 对象。

```PlantUML
@startuml Visitor_ClassDiagram
hide empty members

class Client{

}

class ObjectStructure{

}

class Visitor{
    + visitConcreteElementA(ConcreteElementA eA)
    + visitConcreteElementB(ConcreteElementB eB)
}

class ConcreteVisitorA{
    + visitConcreteElementA(ConcreteElementA eA)
    + visitConcreteElementB(ConcreteElementB eB)
}

class ConcreteVisitorB{
    + visitConcreteElementA(ConcreteElementA eA)
    + visitConcreteElementB(ConcreteElementB eB)
}

class Element{
    + accept(Visitor visitor)
}

class ConcreteElementA{
    + accept(Visitor visitor)
    + operationA()
}

class ConcreteElementB{
    + accept(Visitor visitor)
    + operationB()
}

note bottom of ConcreteElementA
accept(Visitor visitor){
    visitor.visitConcreteElementA(this);
}
end note

Client --> Visitor
ObjectStructure --> Element
Client --> ObjectStructure
Visitor <|.. ConcreteVisitorA
Visitor <|.. ConcreteVisitorB
Element <|.. ConcreteElementA
Element <|.. ConcreteElementB
@enduml
```

## 25.4 时序图

## 25.5 代码分析

```JAVA
abstract class Visitor
{
    public abstract void visit(ConcreteElementA elementA);
    public abstract void visit(ConcreteElementB elementB);
    public void visit(ConcreteElementC elementC)
    {
        //元素ConcreteElementC操作代码
    }
}
```

```JAVA
class ConcreteVisitor extends Visitor
{
    public void visit(ConcreteElementA elementA)
    {
        //元素ConcreteElementA操作代码
    }
    public void visit(ConcreteElementB elementB)
    {
        //元素ConcreteElementB操作代码
    }
}
```

```JAVA
interface Element
{
    public void accept(Visitor visitor);
}
```

```JAVA
class ConcreteElementA implements Element
{
    public void accept(Visitor visitor)
    {
        visitor.visit(this);
    }
        
    public void operationA()
    {
        //业务方法
    }
}
```

```JAVA
class ObjectStructure
{
    private ArrayList<Element> list = new ArrayList<Element>(); //定义一个集合用于存储元素对象
 
    public void accept(Visitor visitor)
    {
        Iterator i=list.iterator();
        
        while(i.hasNext())
        {
            ((Element)i.next()).accept(visitor); //遍历访问集合中的每一个元素
        }
    }
 
    public void addElement(Element element)
    {
        list.add(element);
    }
 
    public void removeElement(Element element)
    {
        list.remove(element);
    }
}
```

## 25.6 模式分析

访问者模式中对象结构存储了不同类型的元素对象，以供不同访问者访问。访问者模式包括两个层次结构，一个是访问者层次结构，提供了抽象访问者和具体访问者，一个是元素层次结构，提供了抽象元素和具体元素。相同的访问者可以以不同的方式访问不同的元素，相同的元素可以接受不同访问者以不同访问方式访问。在访问者模式中，增加新的访问者无须修改原有系统，系统具有较好的可扩展性。

## 25.7 实例

## 25.8 优点

- 增加新的访问操作很方便。使用访问者模式，增加新的访问操作就意味着增加一个新的具体访问者类，实现简单，无须修改源代码，符合「开闭原则」。
- 将有关元素对象的访问行为集中到一个访问者对象中，而不是分散在一个个的元素类中。类的职责更加清晰，有利于对象结构中元素对象的复用，相同的对象结构可以供多个不同的访问者访问。
- 让用户能够在不修改现有元素类层次结构的情况下，定义作用于该层次结构的操作。

## 25.9 缺点

- 增加新的元素类很困难。在访问者模式中，每增加一个新的元素类都意味着要在抽象访问者角色中增加一个新的抽象操作，并在每一个具体访问者类中增加相应的具体操作，这违背了「开闭原则」的要求。
- 破坏封装。访问者模式要求访问者对象访问并调用每一个元素对象的操作，这意味着元素对象有时候必须暴露一些自己的内部操作和内部状态，否则无法供访问者访问。

## 25.10 适用环境

- 一个对象结构包含多个类型的对象，希望对这些对象实施一些依赖其具体类型的操作。在访问者中针对每一种具体的类型都提供了一个访问操作，不同类型的对象可以有不同的访问操作。
- 需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作“污染”这些对象的类，也不希望在增加新操作时修改这些类。访问者模式使得我们可以将相关的访问操作集中起来定义在访问者类中，对象结构可以被多个不同的访问者类所使用，将对象本身与对象的访问操作分离。
- 对象结构中对象对应的类很少改变，但经常需要在此对象结构上定义新的操作。

## 25.11 模式应用

## 25.12 模式扩展
