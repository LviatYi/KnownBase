# 22. 状态模式

## 22.1 模式动机

某些对象存在多种状态，不同状态能够决定对象的不同行为，且其状态能在某些条件下相互转换。可使用 **状态模式** 进行设计。

状态模式用于解决系统中复杂对象的 **状态转换** 以及 **不同状态下行为** 的封装问题。

状态模式将一个对象的状态从该对象中分离出来，封装到专门的状态类中，使得对象状态可以灵活变化，对于客户端而言，无须关心对象状态的转换以及对象所处的当前状态，无论对于何种状态的对象，客户端都可以一致处理。

## 22.2 模式定义

> **状态模式** (State Pattern) ，它属于对象行为型模式。
>
> - 允许一个对象在其内部状态改变时改变行为。
> - 对象看起来似乎修改了自身的类。

## 22.3 模式结构

- Context 环境类
  - 又称为上下文类，是拥有多种状态的对象。
  - 由于其状态存在多样性且在不同状态下对象的行为有所不同，因此将状态独立出去形成单独的状态类。
  - 在环境类中维护一个状态类的实例以定义当前状态。
- State 抽象状态类
  - 定义一个接口以封装与环境类的一个特定状态相关的行为。
  - 声明了各种不同状态对应的方法，在其子类中实现这些方法。
  - 由于不同状态下对象的行为可能不同，因此在不同子类中方法的实现可能存在不同。
  - 相同的方法可以写在抽象状态类中。
- ConcreteState 具体状态类
  - 抽象状态类的子类。
  - 每个子类实现一个与环境类某状态相关的行为。
  - 每个具体状态类对应环境的一个具体状态，不同的具体状态类允许有不同行为。

```PlantUML
@startuml Observer_ClassDiagram
hide empty members

class Context{
    - state : State
    + request()
    + setState(State state)
}

class State{
    + handle()
}

class ConcreteStateA{
    + handle()
}

class ConcreteStateB{
    + handle()
}

Context o--> State
State <|-- ConcreteStateA
State <|-- ConcreteStateB
@enduml
```

## 22.4 时序图

## 22.5 代码分析

```JAVA
abstract class State {
    //声明抽象业务方法，不同的具体状态类可以不同的实现
    public abstract void handle();
}
```

```JAVA
class ConcreteState extends State {
    public void handle() {
        //方法具体实现代码
    }
}
```

```JAVA
class Context {
    private State state; //维持一个对抽象状态对象的引用
    private int value; //其他属性值，该属性值的变化可能会导致对象状态发生变化

    //设置状态对象
    public void setState(State state) {
        this.state = state;
    }

    public void request() {
        //其他代码
        state.handle(); //调用状态对象的业务方法
        //其他代码
    }
}
```

## 22.6 模式分析

- 环境类是真正拥有状态的对象。
- 将环境类中与状态有关的部分封装到专门的状态类中。
- 实际使用时，环境类与抽象状态类可能存在单向关联关系之外更为复杂的关系（依赖或关联关系）。

## 22.7 实例

## 22.8 优点

## 22.9 缺点

## 22.10 适用环境

## 22.11 模式应用

## 22.12 模式扩展
