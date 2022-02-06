# 15. 责任链模式

## 15.1 模式动机

当存在需要多个对象按序处理的请求，则可以使用职责链模式。

在职责链模式里，很多对象由每一个对象对其继任的引用而连接起来形成一条链。请求在这个链上传递，直到链上的某一个对象决定处理此请求。

发出这个请求的客户端并不知道链上的哪一个对象最终处理这个请求，这使得系统可以在不影响客户端的情况下动态地重新组织链和分配责任。

## 15.2 模式定义

> **职责链模式** (Chain of Responsibility Pattern)，它属于对象行为型模式。
>
> - 避免请求发送者与接收者耦合在一起，让多个对象都有可能接收请求，
> - 将这些对象连接成一条链，并且沿着这条链传递请求，直到有对象处理它为止。

## 15.3 模式结构

责任链模式包含如下角色：

- Handler 抽象处理者
  - 定义了一个处理请求的接口，一般设计为抽象类。
  - 由于不同的具体处理者处理请求的方式不同，因此在其中定义了抽象请求处理方法。
  - 每一个处理者的继任还是一个处理者，因此在抽象处理者中定义了一个抽象处理者类型的对象，作为其对继任的引用。通过该引用，处理者可以连成一条链。
- ConcreteHandler 具体处理者
  - 抽象处理者的子类，可以处理用户请求。
  - 实现了抽象处理者中定义的抽象请求处理方法。
  - 在处理请求之前需要进行判断，看是否有相应的处理权限，如果可以处理请求就处理它，否则将请求转发给后继者。
  - 在具体处理者中可以访问链中下一个对象，以便请求的转发。

```PlantUml
@startuml ChainOfResponsibility_ClassDiagram
hide empty members

class Client{

}

class Handler{
    - successor:Handler
    + handleRequest()
}

class ConcreteHandlerA{
    + handleRequest()
}

class ConcreteHandlerB{
    + handleRequest()
}

Client ..right.> Handler
Handler o--up-> Handler:successor

Handler <|-- ConcreteHandlerA
Handler <|-- ConcreteHandlerB
@enduml
```

## 15.4 时序图

## 15.5 代码分析

```Java
abstract class Handler {
  //维持对下家的引用
  protected Handler successor;

  public void setSuccessor(Handler successor) {
    this.successor=successor;
  }
  public abstract void handleRequest(String request);
}
```

```Java
class ConcreteHandler extends Handler {
  public void handleRequest(String request) {
    if (Condition) {
      //处理请求
    }
    else {
      this.successor.handleRequest(request);//转发请求
    }
  }
}
```

## 15.6 模式分析

职责链模式并不创建职责链，职责链的创建工作必须由系统的其他部分来完成，一般是在使用该职责链的客户端中创建职责链。  
职责链模式降低了请求的发送端和接收端之间的耦合，使多个对象都有机会处理这个请求。

## 15.7 实例

```Java
//采购单：请求类
class PurchaseRequest {
  private double amount;  //采购金额
  private int number;  //采购单编号
  private String purpose;  //采购目的

  public PurchaseRequest(double amount, int number, String purpose) {
    this.amount = amount;
    this.number = number;
    this.purpose = purpose;
  }

  public void setAmount(double amount) {
    this.amount = amount;
  }

  public double getAmount() {
    return this.amount;
  }

  public void setNumber(int number) {
    this.number = number;
  }

  public int getNumber() {
    return this.number;
  }

  public void setPurpose(String purpose) {
    this.purpose = purpose;
  }

  public String getPurpose() {
    return this.purpose;
  }
}

//审批者类：抽象处理者
abstract class Approver {
  protected Approver successor; //定义后继对象
  protected String name; //审批者姓名

  public Approver(String name) {
    this.name = name;
  }

  //设置后继者
  public void setSuccessor(Approver successor) {
    this.successor = successor;
  }

    //抽象请求处理方法
    public abstract void processRequest(PurchaseRequest request);
}

//主任类：具体处理者
class Director extends Approver {
  public Director(String name) {
    super(name);
  }

    //具体请求处理方法
  public void processRequest(PurchaseRequest request) {
    if (request.getAmount() < 50000) {
      System.out.println("主任" + this.name + "审批采购单：" + request.getNumber() + "，金额：" + request.getAmount() + "元，采购目的：" + request.getPurpose() + "。");  //处理请求
    }
    else {
      this.successor.processRequest(request);  //转发请求
    }
  }
}

//副董事长类：具体处理者
class VicePresident extends Approver {
  public VicePresident(String name) {
    super(name);
  }

    //具体请求处理方法
  public void processRequest(PurchaseRequest request) {
    if (request.getAmount() < 100000) {
      System.out.println("副董事长" + this.name + "审批采购单：" + request.getNumber() + "，金额：" + request.getAmount() + "元，采购目的：" + request.getPurpose() + "。");  //处理请求
    }
    else {
      this.successor.processRequest(request);  //转发请求
    }
  }
}

//董事长类：具体处理者
class President extends Approver {
  public President(String name) {
    super(name);
  }

    //具体请求处理方法
  public void processRequest(PurchaseRequest request) {
    if (request.getAmount() < 500000) {
      System.out.println("董事长" + this.name + "审批采购单：" + request.getNumber() + "，金额：" + request.getAmount() + "元，采购目的：" + request.getPurpose() + "。");  //处理请求
    }
    else {
      this.successor.processRequest(request);  //转发请求
    }
  }
}

//董事会类：具体处理者
class Congress extends Approver {
  public Congress(String name) {
    super(name);
  }

    //具体请求处理方法
  public void processRequest(PurchaseRequest request) {
    System.out.println("召开董事会审批采购单：" + request.getNumber() + "，金额：" + request.getAmount() + "元，采购目的：" + request.getPurpose() + "。");     //处理请求
  }
}
```

```Java

class Client {
  public static void main(String[] args) {
    Approver wjzhang,gyang,jguo,meeting;
    wjzhang = new Director("张无忌");
    gyang = new VicePresident("杨过");
    jguo = new President("郭靖");
    meeting = new Congress("董事会");

    //创建职责链
    wjzhang.setSuccessor(gyang);
    gyang.setSuccessor(jguo);
    jguo.setSuccessor(meeting);

    //创建采购单
    PurchaseRequest pr1 = new PurchaseRequest(45000,10001,"购买倚天剑");
    wjzhang.processRequest(pr1);

    PurchaseRequest pr2 = new PurchaseRequest(60000,10002,"购买《葵花宝典》");
    wjzhang.processRequest(pr2);

    PurchaseRequest pr3 = new PurchaseRequest(160000,10003,"购买《金刚经》");
    wjzhang.processRequest(pr3);

    PurchaseRequest pr4 = new PurchaseRequest(800000,10004,"购买桃花岛");
    wjzhang.processRequest(pr4);
  }
}
```

## 15.8 优点

- 职责链模式使得一个对象无须知道是其他哪一个对象处理其请求，对象仅需知道该请求会被处理即可，接收者和发送者都没有对方的明确信息，且链中的对象不需要知道链的结构，由客户端负责链的创建，降低了系统的耦合度。
- 请求处理对象仅需维持一个指向其后继者的引用，而不需要维持它对所有的候选处理者的引用，可简化对象的相互连接。
- 在给对象分派职责时，职责链可以给我们更多的灵活性，可以通过在运行时对该链进行动态的增加或修改来增加或改变处理一个请求的职责。
- 在系统中增加一个新的具体请求处理者时无须修改原有系统的代码，只需要在客户端重新建链即可，从这一点来看是符合“开闭原则”的。

## 15.9 缺点

- 由于一个请求没有明确的接收者，那么就不能保证它一定会被处理，该请求可能一直到链的末端都得不到处理；一个请求也可能因职责链没有被正确配置而得不到处理。
- 对于比较长的职责链，请求的处理可能涉及到多个处理对象，系统性能将受到一定影响，而且在进行代码调试时不太方便。
- 如果建链不当，可能会造成循环调用，将导致系统陷入死循环。

## 15.10 适用环境

- 有多个对象可以处理同一个请求，具体哪个对象处理该请求待运行时刻再确定，客户端只需将请求提交到链上，而无须关心请求的处理对象是谁以及它是如何处理的。
- 在不明确指定接收者的情况下，向多个对象中的一个提交一个请求。
- 可动态指定一组对象处理请求，客户端可以动态创建职责链来处理请求，还可以改变链中处理者之间的先后次序。

## 15.11 模式应用

## 15.12 模式扩展

### 15.12.1 纯职责链模式

在纯职责链模式中，要求一个具体处理者对象只能在两个行为中选择一个：

- 将责任全部承担。
- 将责任推给下家。

不允许出现某一个具体处理者对象在承担了一部分或全部责任后又将责任向下传递的情况。

而且在纯的职责链模式中，要求一个请求必须被某一个处理者对象所接收，不能出现某个请求未被任何一个处理者对象处理的情况。

实例中体现了纯职责链模式。

### 15.12.2 非纯职责链模式

在一个非纯职责链模式中，允许

- 某个请求被一个具体处理者部分处理后再向下传递。
- 一个具体处理者处理完某请求后其后继处理者可以继续处理该请求，而且一个请求可以最终不被任何处理者对象所接收。
