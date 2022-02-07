# 17. 解释器模式

## 17.1 模式动机

使用者期待使用一种新的语言达成特定的操作，则可预先定义文法规则来对语句进行规范与解释，从而实现功能。此即解释器模式。

解释器模式描述了如何为简单的语言定义一个文法，如何在该语言中表示一个句子，以及如何解释这些句子。

## 17.2 模式定义

> **解释器模式** (Interpreter Pattern)，它属于类行为型模式。
>
> - 定义一个语言的文法，并且建立一个解释器来解释该语言中的句子。

## 17.3 模式结构

- AbstractExpression 抽象表达式
  - 在抽象表达式中声明了抽象的解释操作。
  - 所有终结符表达式和非终结符表达式的公共父类。
- TerminalExpression 终结符表达式
  - 抽象表达式的子类。
  - 实现了与文法中的终结符相关联的解释操作，在句子中的每一个终结符都是该类的一个实例。
- NonterminalExpression 非终结符表达式
  - 抽象表达式的子类。
  - 实现了文法中非终结符的解释操作。
  - 由于在非终结符表达式中可以包含终结符表达式，也可以继续包含非终结符表达式，因此其解释操作一般通过递归的方式来完成。
- Context 上下文类
  - 用于存储解释器之外的一些全局信息。
  - 通常它临时存储了需要解释的语句。

```PlantUML
@startuml Interpreter_ClassDiagram
hide empty members

class Client{

}

class Context{

}

class AbstractExpression{
    + interpret(Context ctx)
}

class TerminalExpression{
    + interpret(Context ctx)
}

class NonterminalExpression{
    + interpret(Context ctx)
}

Client ..> Context
Client ..>AbstractExpression
Context <.. AbstractExpression
AbstractExpression <|-- TerminalExpression
AbstractExpression <|-- NonterminalExpression
AbstractExpression <--o NonterminalExpression
@enduml
```

## 17.4 时序图

## 17.5 代码分析

```JAVA
abstract class AbstractExpression {
    public abstract void interpret(Context ctx);
}
```

```JAVA
class TerminalExpression extends  AbstractExpression {
    public void interpret(Context ctx) {
        //终结符表达式的解释操作
    }
}
```

```JAVA
class NonterminalExpression extends  AbstractExpression {
    private AbstractExpression left;
    private AbstractExpression right;

    public NonterminalExpression(AbstractExpression left,AbstractExpression right) {
        this.left=left;
        this.right=right;
    }

    public void interpret(Context ctx) {
        //递归调用每一个组成部分的interpret()方法
        //在递归调用时指定组成部分的连接方式，即非终结符的功能
    }
}
```

```JAVA
class Context {
    private HashMap map = new HashMap();

    public void assign(String key, String value) {
        //往环境类中设值
    }

    public String lookup(String key) {
        //获取存储在环境类中的值
    }
}
```

## 17.6 模式分析

## 17.7 实例

## 17.8 优点

- 易于改变和扩展文法。由于在解释器模式中使用类来表示语言的文法规则，因此可以通过继承等机制来改变或扩展文法。
- 每一条文法规则都可以表示为一个类，因此可以方便地实现一个简单的语言。
- 实现文法较为容易。在抽象语法树中每一个表达式节点类的实现方式都是相似的，这些类的代码编写都不会特别复杂，还可以通过一些工具自动生成节点类代码。
- 增加新的解释表达式较为方便。如果用户需要增加新的解释表达式只需要对应增加一个新的终结符表达式或非终结符表达式类，原有表达式类代码无须修改，符合「开闭原则」。

## 17.9 缺点

- 对于复杂文法难以维护。在解释器模式中，每一条规则至少需要定义一个类，因此如果一个语言包含太多文法规则，类的个数将会急剧增加，导致系统难以管理和维护，此时可以考虑使用语法分析程序等方式来取代解释器模式。
- 执行效率较低。由于在解释器模式中使用了大量的循环和递归调用，因此在解释较为复杂的句子时其速度很慢，而且代码的调试过程也比较麻烦。

## 17.10 适用环境

- 可以将一个需要解释执行的语言中的句子表示为一个抽象语法树。
- 一些重复出现的问题可以用一种简单的语言来进行表达。
- 一个语言的文法较为简单。
- 执行效率不是关键问题。

## 17.11 模式应用

## 17.12 模式扩展

借助编译原理相关知识可以增强解释器功能。
