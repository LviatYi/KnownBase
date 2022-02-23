# 24. 模板方法模式

## 24.1 模式动机

某些过程存在一部分相似或固定的步骤，而另一部分则是可变的，则可使用 **模板方法模式** 进行设计。

## 24.2 模式定义

> **模板方法模式** (Template Method Pattern) ，它属于类行为型模式。
>
> - 定义一个操作中算法的框架，而将一些步骤延迟到子类中。
> - 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

## 24.3 模式结构

- AbstractClass 抽象类
  - 定义了一系列 **基本操作** (PrimitiveOperations) 。
  - 基本操作可以是具体的，也可以是抽象的，每一个基本操作对应算法的一个步骤。
  - 其子类可以重定义或实现这些步骤。
  - 实现了一个 **模板方法** (Template Method) ，用于定义一个算法的框架。
  - 模板方法不仅可以调用基本方法或其他对象中的方法。
- ConcreteClass 具体子类
  - 抽象类的子类。
  - 实现在父类中声明的抽象基本操作以完成子类特定算法的步骤。
  - 也可覆盖在父类中已经实现的具体基本操作。

```PlantUML
@startuml TemplateMethod_ClassDiagram
hide empty members

class AbstractClass{
    + TemplateMethod()
    + PrimitiveOperation1()
    + PrimitiveOperation2()
    + PrimitiveOperation3()
}

class ConcreteClass{
    + PrimitiveOperation1()
    + PrimitiveOperation2()
}

note bottom of AbstractClass
TemplateMethod(){
    ...
    + PrimitiveOperation1()
    ...
    + PrimitiveOperation2()
    ...
    + PrimitiveOperation3()
}
end note

AbstractClass <|-right- ConcreteClass
@enduml
```

## 24.4 时序图

## 24.5 代码分析

```Csharp
abstract class AbstractClass 
{
  // 模板方法
  public void TemplateMethod() 
  {
    Open();
    PrimitiveOperation1();
    PrimitiveOperation2();
    PrimitiveOperation3();
    Display();
    // 通过钩子方法来确定某步骤是否执行
    if(IsPrint()) 
    {
      Print();
    }
  }
  
  // 钩子方法 预置判断
  public bool IsPrint()
  {
    return true;
  }
 
  // 基本方法 抽象方法
  public abstract void PrimitiveOperation1();    

  // 基本方法 具体方法
  public void PrimitiveOperation2(){
    // 实现代码
  }
 
  // 基本方法 钩子方法
  public virtual void PrimitiveOperation3(){
    // 实现代码
  }
}
```

```Csharp
// 具体子类
class ConcreteClass : AbstractClass 
{
  public override void PrimitiveOperation1(){
    // 实现代码
  }
 
  public override void PrimitiveOperation3(){
    // 实现代码
  }
}
```

## 24.6 模式分析

一般地，模板方法模式将抽象与具体分别划分为 **模板方法** 与 **基本方法** 。

- 模板方法
  - 定义在抽象类中。
  - 由基本操作方法组合而成的总算法。
  - 是一个具体方法，给出了一个顶层逻辑框架，而逻辑的组成步骤在抽象类中可以是具体方法，也可以是抽象方法。
  - 因此不能存在于接口。
- 基本方法
  基本方法是实现算法各步骤的方法，是模板方法的组成部分。
  - 抽象方法
    - 由抽象类声明，由具体子类实现。
  - 具体方法
    - 由抽象类或具体类声明并实现。
  - 钩子方法
    - 由抽象类或具体类声明并实现。子类可加以扩展。
    - 可默认空实现。
    - 可用于预置过程或预置判断。

## 24.7 实例

## 24.8 优点

- 在父类中形式化地定义一个算法，而由它的子类来实现细节的处理，在子类实现详细的处理算法时并不会改变算法中步骤的执行次序。
- 模板方法模式是一种代码复用技术，它在类库设计中尤为重要，它提取了类库中的公共行为，将公共行为放在父类中，而通过其子类来实现不同的行为，它鼓励我们恰当使用继承来实现代码复用。
- 可实现一种反向控制结构，通过子类覆盖父类的钩子方法来决定某一特定步骤是否需要执行。
- 在模板方法模式中可以通过子类来覆盖父类的基本方法，不同的子类可以提供基本方法的不同实现，更换和增加新的子类很方便，符合单一职责原则和开闭原则。

## 24.9 缺点

- 需要为每一个基本方法的不同实现提供一个子类，如果父类中可变的基本方法太多，将会导致类的个数增加，系统更加庞大，设计也更加抽象，此时，可结合桥接模式来进行设计。

## 24.10 适用环境

- 对一些复杂的算法进行分割，将其算法中固定不变的部分设计为模板方法和父类具体方法，而一些可以改变的细节由其子类来实现。即：一次性实现一个算法的不变部分，并将可变的行为留给子类来实现。
- 各子类中公共的行为应被提取出来并集中到一个公共父类中以避免代码重复。
- 需要通过子类来决定父类算法中某个步骤是否执行，实现子类对父类的反向控制。

## 24.11 模式应用

## 24.12 模式扩展
