# 19. 中介者模式

## 19.1 模式动机

当某些类或对象之间的相互调用关系错综复杂，则可以提供一个中间类来协调复杂的调用或通知关系。即 **中介者** 模式。

## 19.2 模式定义

> **中介者模式** (Mediator Pattern) 又称为 **调停者模式** ，它属于对象行为型模式。
>
> - 用一个中介对象（中介者）封装一系列的对象交互。
> - 中介者使各对象不需要显式地相互引用，从而使其耦合松散，且允许独立地改变它们之间的交互。

## 19.3 模式结构

- Mediator 抽象中介者
  - 定义一个接口，该接口用于与各同事对象之间进行通信。
- ConcreteMediator 具体中介者
  - 抽象中介者的子类。
  - 通过协调各个同事对象来实现协作行为。
  - 维持了对各个同事对象的引用。
- Colleague 抽象同事类
  - 定义各个同事类公有的方法，并声明了一些抽象方法来供子类实现。
  - 维持了一个对抽象中介者类的引用，其子类可以通过该引用来与中介者通信。
- ConcreteColleague 具体同事类
  - 抽象同事类的子类。
  - 实现了在抽象同事类中声明的抽象方法。
  - 每一个同事对象在需要和其他同事对象通信时，先与中介者通信，通过中介者来间接完成与其他同事类的通信。

```PlantUML
@startuml Mediator_ClassDiagram
hide empty members

class Mediator{

}

class ConcreteMediator{

}

class Colleague{
    mediator:Mediator
}

class ConcreteColleagueA{

}

class ConcreteColleagueB{

}

Mediator <|--ConcreteMediator
Mediator <--Colleague
Colleague <|-- ConcreteColleagueA
Colleague <|-- ConcreteColleagueB
ConcreteMediator-->ConcreteColleagueA
ConcreteMediator-->ConcreteColleagueB
@enduml
```

## 19.4 时序图

## 19.5 代码分析

```JAVA
abstract class Mediator {
    protected ArrayList<Colleague> colleagues; //用于存储同事对象

    //注册方法，用于增加同事对象
    public void register(Colleague colleague) {
        colleagues.add(colleague);
    }

    //声明抽象的业务方法
    public abstract void operation();
}
```

```JAVA
class ConcreteMediator extends Mediator {
    //实现业务方法，封装同事之间的调用
    public void operation() {
        ((Colleague)(colleagues.get(0))).method1(); //通过中介者调用同事类的方法
    }
}
```

```JAVA
abstract class Colleague {
    protected Mediator mediator; //维持一个抽象中介者的引用

    public Colleague(Mediator mediator) {
        this.mediator=mediator;
    }

    public abstract void method1(); //声明自身方法，处理自己的行为

    //定义依赖方法，与中介者进行通信
    public void method2() {
        mediator.operation();
    }
}
```

```JAVA
class ConcreteColleague extends Colleague {
    public ConcreteColleague(Mediator mediator) {
        super(mediator);
    }

    //实现自身方法
    public void method1() {
        ......
    }
}
```

## 19.6 模式分析

中介者模式的核心在于 **中介者类** 的引入。中介者类将 **网状耦合关系** 重构为 **星状耦合关系** 。  

在中介者模式中，中介者类承担了两方面的职责：

- 中转作用（结构性）
  - 通过中介者提供的中转作用，各个同事对象就不再需要显式引用其他同事。
  - 当需要和其他同事进行通信时，可通过中介者来实现间接调用。
  - 该中转作用属于中介者在结构上的支持。
- 协调作用（行为性）
  - 中介者可以更进一步的对同事之间的关系进行封装，同事可以一致的和中介者进行交互，而不需要指明中介者需要具体怎么做。
  - 中介者根据封装在自身内部的协调逻辑，对同事的请求进行进一步处理，将同事成员之间的关系行为进行分离和封装。
  - 该协调作用属于中介者在行为上的支持。

## 19.7 实例

## 19.8 优点

- 中介者模式 **简化了对象之间的交互** ，它用中介者和同事的一对多交互代替了原来同事之间的多对多交互，一对多关系更容易理解、维护和扩展，将原本难以理解的网状结构转换成相对简单的星型结构。
- 中介者模式可将 **各同事对象解耦** 。中介者有利于各同事之间的松耦合，我们可以独立的改变和复用每一个同事和中介者，增加新的中介者和新的同事类都比较方便，更好地符合「开闭原则」。

## 19.9 缺点

- 在具体中介者类中包含了大量同事之间的交互细节，可能会导致具体中介者类非常复杂，使得系统难以维护。

## 19.10 适用环境

- 系统中对象之间存在复杂的引用关系，系统结构混乱且难以理解。
- 一个对象由于引用了其他很多对象并且直接和这些对象通信，导致难以复用该对象。
- 想通过一个中间类来封装多个类中的行为，而又不想生成太多的子类。可以通过引入中介者类来实现，在中介者中定义对象交互的公共行为，如果需要改变行为则可以增加新的具体中介者类。

## 19.11 模式应用

## 19.12 模式扩展
