# 21. 观察者模式

## 21.1 模式动机

观察者模式是及其重要和广泛的设计模式。

一个对象的状态或行为的变化将引起其他对象的状态或行为的变化（即联动），则可使用 **观察者模式** 。

观察者模式定义了对象之间 **一对多** 的依赖关系，让一个对象的改变能够影响其他对象。

## 21.2 模式定义

> **观察者模式** (Observer Pattern) 又称为 **发布 - 订阅模式** (Publish/Subscribe) 、**模型 - 视图模式** (Model/View) 、**源 - 监听器模式** (Source/Listener) 或 **从属者模式** (Dependents) ，它属于对象行为型模式。
>
> - 定义对象间的一对多依赖关系。
> - 每当一个对象状态发生改变时，其相关依赖对象皆得到通知并被自动更新。

## 21.3 模式结构

观察者模式包含如下角色：

- Subject 目标
  - 目标又称为主题，指被观察的对象。
  - 在目标中定义了一个观察者集合。
  - 一个观察目标可以接受任意数量的观察者来观察。
  - 定义了通知方法 `notify()` 。
  - 目标类可以是接口、抽象类或具体类。
  - 提供一系列方法来增加和删除观察者对象。
- ConcreteSubject 具体目标
  - 目标类的子类。
  - 通常包含经常变动的数据。当状态发生改变时，向它的各个观察者发出通知。
  - 实现了在目标类中定义的抽象业务逻辑方法（如果有）。
  - 若无须扩展目标类，则具体目标类可以省略。
- Observer 观察者
  - 将对观察目标的改变做出反应。
  - 一般定义为接口，该接口声明了更新数据的方法 `update()` 。
- ConcreteObserver 具体观察者
  - 维护一个指向具体目标对象的引用。
  - 存储具体观察者的有关状态，这些状态需要和具体目标的状态保持同步。
  - 实现了在抽象观察者中定义的 `update()` 方法。
  - 通常在实现时，可以调用具体目标类的 `attach()` 方法将自己添加到目标类的集合中或通过 `detach()` 方法将自己从目标类的集合中删除。

```PlantUML
@startuml Observer_ClassDiagram
hide empty members

class Subject{
    - obs:Observer
    + attach(Observer obs)
    + detach(Observer obs)
    + notify()
}

class Observer{
    + update()
}

class ConcreteSubject{
    - obs:Observer
    - subjectState:
    + getState()
    + setState()
}

class ConcreteObserver{
    - observerState:
    + update()
}

Subject --right-> Observer
Subject <|-down- ConcreteSubject
ConcreteSubject <-right- ConcreteObserver
Observer <|.. ConcreteObserver
@enduml
```

## 21.4 时序图

## 21.5 代码分析

```JAVA
abstract class Subject {
    //定义一个观察者集合用于存储所有观察者对象
    protected ArrayList observers<Observer> = new ArrayList();
 
    //注册方法，用于向观察者集合中增加一个观察者
    public void attach(Observer observer) {
        observers.add(observer);
    }
 
    //注销方法，用于在观察者集合中删除一个观察者
    public void detach(Observer observer) {
        observers.remove(observer);
    }
 
    //声明抽象通知方法
    public abstract void notify();
}
```

```JAVA
class ConcreteSubject extends Subject {
    //实现通知方法
    public void notify() {
        //遍历观察者集合，调用每一个观察者的响应方法
        for(Object obs:observers) {
            ((Observer)obs).update();
        }
    }
}
```

```JAVA
interface Observer {
    //声明响应方法
    public void update();
}
```

```JAVA
class ConcreteObserver implements Observer {
    //实现响应方法
    public void update() {
        //具体响应代码
    }
}
```

## 21.6 模式分析

观察者模式描述了如何建立对象与对象之间的依赖关系，以及如何构造满足这种需求的系统。

观察者模式包含观察目标和观察者两类对象，一个目标可以有任意数目的与之相依赖的观察者，一旦观察目标的状态发生改变，所有的观察者都将得到通知。

作为对这个通知的响应，每个观察者都将监视观察目标的状态以使其状态与目标状态同步，这种交互也称为 **发布 - 订阅** (Publish-Subscribe) 。

观察目标是通知的发布者，它发出通知时并不需要知道谁是它的观察者，可以有任意数目的观察者订阅它并接收通知。

## 21.7 实例

## 21.8 优点

- 观察者模式可以实现表示层和数据逻辑层的分离，定义了稳定的消息更新传递机制，并抽象了更新接口，使得可以有各种各样不同的表示层充当具体观察者角色。
- 观察者模式在观察目标和观察者之间建立一个抽象的耦合。观察目标只需要维持一个抽象观察者的集合，无须了解其具体观察者。由于观察目标和观察者没有紧密地耦合在一起，因此它们可以属于不同的抽象化层次。
- 观察者模式支持广播通信，观察目标会向所有已注册的观察者对象发送通知，简化了一对多系统设计的难度。
- 观察者模式满足「开闭原则」的要求，增加新的具体观察者无须修改原有系统代码，在具体观察者与观察目标之间不存在关联关系的情况下，增加新的观察目标也很方便。

## 21.9 缺点

- 如果一个观察目标对象有很多直接和间接观察者，将所有的观察者都通知到会花费很多时间。
- 如果在观察者和观察目标之间存在循环依赖，观察目标会触发它们之间进行循环调用，可能导致系统崩溃。
- 观察者模式没有相应的机制让观察者知道所观察的目标对象是怎么发生变化的，而仅仅只是知道观察目标发生了变化。

## 21.10 适用环境

## 21.11 模式应用

Java 原生工具包提供了对观察者模式的支持。

`java.util` 提供了 Observable 类以及 Observer 接口。

## 21.12 模式扩展

### 21.12.1 MVC 架构

MVC(Model-View-Controller) 架构应用了观察者模式，其包含三个角色： **模型** (Model)， **视图** (View) 和 **控制器** (Controller) 。

其中模型可对应于观察者模式中的观察目标，而视图对应于观察者，控制器可充当两者之间的中介者。
当模型层的数据发生改变时，视图层将自动改变其显示内容。
