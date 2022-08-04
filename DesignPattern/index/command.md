# 16. 命令模式

## 16.1 模式动机

软件开发中，我们经常需要向某些对象发送请求（调用其中的某个或某些方法），但是对请求的接收者与被执行的操作并不了解。  
此时，我们期待消除请求发送者与请求接收者之间的耦合，以灵活地指定请求接收者以及被请求的操作。  
**命令模式** 为此类问题提供了一个较为完美的解决方案，其可以将请求发送者和接收者完全解耦，发送者与接收者之间没有直接引用关系，发送请求的对象只需要知道如何发送请求，而不必知道如何完成请求。  

## 16.2 模式定义

> **命令模式** (Command Pattern) 又称为 **动作模式** (Action) 或 **事务模式** (Transaction) ，它属于对象行为型模式。  
> 
> - 将一个请求封装为一个对象，从而让我们可用不同的请求对客户进行参数化。  
> - 将请求排队或者记录请求日志，以及支持可撤销的操作。
> 命令模式是一种对象行为型模式，其别名为动作(Action)模式或事务(Transaction)模式。  

## 16.3 模式结构

命令模式包含如下角色：

- Command（抽象命令类）
  - 抽象命令类一般是一个抽象类或接口。  
  - 其中声明了用于执行请求的 `execute()` 等方法。  
  - 通过这些方法可以调用请求接收者的相关操作。  
- ConcreteCommand（具体命令类）
  - 具体命令类是抽象命令类的子类。
  - 其实现了在抽象命令类中声明的方法，它对应具体的接收者对象，将接收者对象的动作绑定其中。  
  - 在实现 `execute()` 方法时，将调用接收者对象的相关操作 (Action) 。  
- Invoker（调用者）
  - 调用者即请求发送者，它通过命令对象来执行请求。  
  - 一个调用者并不需要在设计时确定其接收者，因此它只与抽象命令类之间存在关联关系。  
  - 在程序运行时可以将一个具体命令对象注入其中，再调用具体命令对象的 `execute()` 方法，从而实现间接调用请求接收者的相关操作。  
- Receiver（接收者）
  - 接收者执行与请求相关的操作，它具体实现对请求的业务处理。  

```PlantUML
@startuml Command_ClassDiagram
hide empty members

class Client{

}

class Command{
    + execute()
}

class Invoker{

}

class ConcreteCommand{
    - Receiver : receiver
    + execute()
}

class Receiver{
    + action()
}

Client ..right.> Invoker
Client ..> ConcreteCommand
Invoker o--right->Command
Command <|-- ConcreteCommand
Receiver <--left-ConcreteCommand:receiver

note bottom of ConcreteCommand
    execute( ){
        receiver.action( );
    }
end note
@enduml
```

## 16.4 时序图

## 16.5 代码分析

## 16.6 模式分析

命令模式的核心在于引入了 **命令类** 。  
通过命令类来降低发送者和接收者的耦合度，请求发送者只需指定一个命令对象，再通过命令对象来调用请求接收者的处理方法。  

命令模式允许请求的一方和接收的一方独立开来：  

- 请求的一方不必知道接收请求的一方的接口。
- 请求的一方不必知道请求如何被接收、操作是否被执行、何时被执行以及是怎么被执行的。

## 16.7 实例

```Java
class Invoker {
    private Command command;
    
    //构造注入
    public Invoker(Command command) {
    this.command = command;
    }
    
    //设值注入
    public void setCommand(Command command) {
    this.command = command;
    }
    
    //业务方法，用于调用命令类的execute()方法
    public void call() {
    command.execute();
    }
}
```

```Java
class ConcreteCommand extends Command {
    private Receiver receiver; 
 
    public void execute() {
        receiver.action(); 
    }
}
```

## 16.8 优点

- 降低系统的耦合度。由于请求者与接收者之间不存在直接引用，因此请求者与接收者之间实现完全解耦，相同的请求者可以对应不同的接收者，同样，相同的接收者也可以供不同的请求者使用，两者之间具有良好的独立性。
- 新的命令可以很容易地加入到系统中。由于增加新的具体命令类不会影响到其他类，因此增加新的具体命令类很容易，无须修改原有系统源代码，甚至客户类代码，满足「开闭原则」的要求。
- 可以比较容易地设计一个命令队列或宏命令（组合命令）。
- 为请求的撤销 (Undo) 和恢复 (Redo) 操作提供了一种设计和实现方案。

## 16.9 缺点

使用命令模式可能会导致某些系统有过多的具体命令类。
因为针对每一个对请求接收者的调用操作都需要设计一个具体命令类，因此在某些系统中可能需要提供大量的具体命令类，这将影响命令模式的使用。

## 16.10 适用环境

- 系统需要将请求调用者和请求接收者解耦，使得调用者和接收者不直接交互。请求调用者无须知道接收者的存在，也无须知道接收者是谁，接收者也无须关心何时被调用。
- 系统需要在不同的时间指定请求、将请求排队和执行请求。一个命令对象和请求的初始调用者可以有不同的生命期，换言之，最初的请求发出者可能已经不在了，而命令对象本身仍然是活动的，可以通过该命令对象去调用请求接收者，而无须关心请求调用者的存在性，可以通过请求日志文件等机制来具体实现。
- 系统需要支持命令的撤销 (Undo) 操作和恢复 (Redo) 操作。
- 系统需要将一组操作组合在一起形成宏命令。

## 16.11 模式应用

## 16.12 模式扩展

### 16.12.1 命令队列

使用队列替换 Invoke 中的单个 command 属性，可以实现批量 Command 的处理。

```Java
class CommandQueue {
    //定义一个ArrayList来存储命令队列
    private ArrayList<Command> commands = new ArrayList<Command>();
        
    public void addCommand(Command command) {
        commands.add(command);
    }
        
    public void removeCommand(Command command) {
        commands.remove(command);
    }
        
    //循环调用每一个命令对象的execute()方法
    public void execute() {
        for (Object command : commands) {
            ((Command)command).execute();
        }
    }
}
```

```Java
class Invoker {
    private CommandQueue commandQueue; //维持一个CommandQueue对象的引用
        
    //构造注入
    public Invoker(CommandQueue commandQueue) {
        this. commandQueue = commandQueue;
    }
        
    //设值注入
    public void setCommandQueue(CommandQueue commandQueue) {
        this.commandQueue = commandQueue;
    }
        
    //调用CommandQueue类的execute()方法
    public void call() {
        commandQueue.execute();
    }
}
```

如果请求接收者的接收次序没有严格的先后次序，我们还可以使用多线程技术来并发调用命令对象的 `execute()` 方法，从而提高程序的执行效率。

### 16.12.2 撤销命令

在 Command 中增加 `Undo()` 函数，实现相反操作。

需要保存每次 Command 的 Action 参数，实现方式多样，如 **日志** 或 **备忘录模式** 。

### 16.12.3 请求日志

维护 Command 的名称属性，并在命令执行时追加日志的读写。

### 16.12.4 宏命令

**宏命令** (Macro Command) 又称为 **组合命令** ，它是组合模式和命令模式联用的产物。

- 宏命令是一个具体命令类，它拥有一个集合属性，在该集合中包含了对其他命令对象的引用。  
- 通常宏命令不直接与请求接收者交互，而是通过它的成员来调用接收者的方法。当调用宏命令的 **execute()** 方法时，将递归调用它所包含的每个成员命令的 **execute()** 方法。  
- 一个宏命令的成员可以是简单命令，还可以继续是宏命令。执行一个宏命令将触发多个具体命令的执行，从而实现对命令的批处理。  

命令模式与透明组合模式的结合应用：  

```PlantUML
@startuml MacroCommand_ClassDiagram
hide empty members

class Invoker{

}

class Command{
    + addCommand(Command command)
    + removeCommand(Command command)
    + getCommand(int index)
    + execute()
}

class ConcreteCommandA{
    - Receiver : receiver
    + execute()
}

class ConcreteCommandB{
    - Receiver : receiver
    + execute()
}

class MacroCommand{
    - commands :List<Command>

    + addCommand(Command command)
    + removeCommand(Command command)
    + getCommand(int index)
    + execute()
}

Invoker o--right->Command
Command <|-- ConcreteCommandA
Command <|-- ConcreteCommandB
Command <|-- MacroCommand


note bottom of MacroCommand
    execute( ){
        for(Command command:commands){
            command.execute();
        }
    }
end note
@enduml
```
