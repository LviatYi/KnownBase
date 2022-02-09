# 18. 迭代器模式

## 18.1 模式动机

开发中常使用聚合对象存储一系列数据。

聚合对象拥有两个职责：

- 存储数据
- 遍历数据

从依赖性来看，前者是聚合对象的基本职责；而后者既是可变化的，又是可分离的。因此，可以将遍历数据的行为从聚合对象中分离出来，封装在一个被称之为「**迭代器**」的对象中，由迭代器来提供遍历聚合对象内部数据的行为，这将简化聚合对象的设计，更符合「单一职责原则」的要求。

## 18.2 模式定义

> **迭代器模式** (Iterator Pattern)，它属于对象行为型模式。
>
> - 提供一种方法来访问聚合对象，而不用暴露这个对象的内部表示。
> - 迭代器亦可称为 **游标** (Cursor) 。

## 18.3 模式结构

迭代器模式常结合工厂方法模式使用。

迭代器模式包含如下角色：

- Iterator 抽象迭代器
  - 一个定义了访问和遍历元素的接口。
  - 声明了用于遍历数据元素的方法。通常包括：
    - `first()` 获取第一个元素。
    - `next()` 访问下一个元素。
    - `hasNext()` 判断是否还有下一个元素。
    - `currentItem()` 获取当前元素。
- ConcreteIterator 具体迭代器
  - 实现了抽象迭代器接口。
  - 完成对聚合对象的遍历，同时在具体迭代器中通过游标来记录在聚合对象中所处的当前位置。
  - 具体实现中，游标通常是一个表示位置的非负整数。
- Aggregate 抽象聚合类
  - 用于存储和管理元素对象。
  - 充当抽象迭代器工厂角色。声明一个 **createIterator()** 方法用于创建一个迭代器对象。
- ConcreteAggregate 具体聚合类
  - 实现了在抽象聚合类中声明的 **createIterator()** 方法，该方法返回一个与该具体聚合类对应的具体迭代器 ConcreteIterator 实例。

```PlantUML
@startuml Interpreter_ClassDiagram
hide empty members

class Aggregate{
    + createIterator()
}

class Iterator{
    + first()
    + next()
    + hasNext()
    + currentItem()
}

class ConcreteAggregate{
    + createIterator()
}

class ConcreteIterator{
    + first()
    + next()
    + hasNext()
    + currentItem()
}
Aggregate <|..ConcreteAggregate
Iterator <|.. ConcreteIterator
ConcreteAggregate ..right.> ConcreteIterator
@enduml
```

## 18.4 时序图

## 18.5 代码分析

```JAVA
interface Iterator {
    public void first(); //将游标指向第一个元素
    public void next(); //将游标指向下一个元素
    public boolean hasNext(); //判断是否存在下一个元素
    public Object currentItem(); //获取游标指向的当前元素
}
```

```JAVA
class ConcreteIterator implements Iterator {
    private ConcreteAggregate objects; //维持一个对具体聚合对象的引用，以便于访问存储在聚合对象中的数据
    private int cursor; //定义一个游标，用于记录当前访问位置
    public ConcreteIterator(ConcreteAggregate objects) {
        this.objects=objects;
    }

    public void first() {}
    public void next() {}
    public boolean hasNext() {}
    public Object currentItem() {}
}
```

```JAVA
interface Aggregate {
    Iterator createIterator();
}
```

```JAVA
class ConcreteAggregate implements Aggregate {
    public Iterator createIterator() {
    return new ConcreteIterator(this);
    }
}
```

## 18.6 模式分析

迭代器模式是一种使用频率非常高的设计模式，通过引入迭代器可以将数据的遍历功能从聚合对象中分离出来，聚合对象只负责存储数据，而遍历数据由迭代器来完成。

由于很多编程语言的类库都已经实现了迭代器模式，因此在实际开发中，我们只需要直接使用 Java、C# 等语言已定义好的迭代器即可，迭代器已经成为我们操作聚合对象的基本工具之一。

## 18.7 实例

## 18.8 优点

- 它支持以不同的方式遍历一个聚合对象，在同一个聚合对象上可以定义多种遍历方式。在迭代器模式中只需要用一个不同的迭代器来替换原有迭代器即可改变遍历算法，我们也可以自己定义迭代器的子类以支持新的遍历方式。
- 迭代器简化了聚合类。由于引入了迭代器，在原有的聚合对象中不需要再自行提供数据遍历等方法，这样可以简化聚合类的设计。
- 在迭代器模式中，由于引入了抽象层，增加新的聚合类和迭代器类都很方便，无须修改原有代码，满足“开闭原则”的要求。

## 18.9 缺点

- 由于迭代器模式将存储数据和遍历数据的职责分离，增加新的聚合类需要对应增加新的迭代器类，类的个数成对增加，这在一定程度上增加了系统的复杂性。
- 抽象迭代器的设计难度较大，需要充分考虑到系统将来的扩展，例如JDK内置迭代器Iterator就无法实现逆向遍历，如果需要实现逆向遍历，只能通过其子类ListIterator等来实现，而ListIterator迭代器无法用于操作Set类型的聚合对象。在自定义迭代器时，创建一个考虑全面的抽象迭代器并不是件很容易的事情。

## 18.10 适用环境

- 访问一个聚合对象的内容而无须暴露它的内部表示。将聚合对象的访问与内部数据的存储分离，使得访问聚合对象时无须了解其内部实现细节。
- 需要为一个聚合对象提供多种遍历方式。
- 为遍历不同的聚合结构提供一个统一的接口，在该接口的实现类中为不同的聚合结构提供不同的遍历方式，而客户端可以一致性地操作该接口。

## 18.11 模式应用

## 18.12 模式扩展
