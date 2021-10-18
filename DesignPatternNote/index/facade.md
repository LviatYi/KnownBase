# 12. 外观模式

## 12.1 模式动机

> 外观模式通过引入一个外观角色来简化客户端与子系统之间的交互，为复杂的子系统调用提供一个统一的入口，降低子系统与客户端的耦合度，且客户端调用非常方便。  

## 12.2 模式定义

> **外观模式** (Facade Pattern) 又称为门面模式，它是一种对象结构型模式。  
> 
> - 外部与一个子系统的通信必须通过一个统一的外观对象进行，为子系统中的一组接口提供一个一致的界面。  
> - 外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。

## 12.3 模式结构

外观模式包含如下两个角色：  

- Facade 外观角色
  - 在客户端可以调用它的方法，在外观角色中可以知道相关的（一个或者多个）子系统的功能和责任。  
  - 在正常情况下，它将所有从客户端发来的请求委派到相应的子系统去，传递给相应的子系统对象处理。
- SubSystem 子系统角色
  - 在软件系统中可以有一个或者多个子系统角色，每一个子系统可以不是一个单独的类，而是一个类的集合，它实现子系统的功能。  
  - 每一个子系统都可以被客户端直接调用，或者被外观角色调用，它处理由外观类传过来的请求。  
  - 子系统并不知道外观的存在，对于子系统而言，外观角色仅仅是另外一个客户端而已。

```PlantUML
@startuml Facade_ClassDiagram
hide empty members

class Client
class Facade
class SubSystemA
class SubSystemB
class SubSystemC

Client ..> Facade
Facade --> SubSystemA
Facade --> SubSystemB
Facade --> SubSystemC
@enduml
```

## 12.4 时序图

```PlantUML
@startuml Facade_SequenceDiagram
participant ":Client" as Client
participant ":Facade" as Facade
participant ":SystemA" as SystemA
participant ":SystemB" as SystemB

Client -> Facade ++:<<create>>
create SystemA
Facade-->SystemA:<<create>>
create SystemB
Facade-->SystemB:<<create>>
deactivate Facade
Client -> Facade ++: wrapOpration( )
Facade -> SystemA ++:operationA( )
Facade -> SystemB ++:operationB( )
@enduml
```

## 12.5 代码分析

```Java
class subSystem1{
  File read(){

  }
}
```

```Java
class subSystem2{
  File operate(){

  }
}
```

```Java
class subSystem3{
  File save(){

  }
}
```

```Java
class facadeSystem{
  private subSystem1;
  private subSystem2;
  private subSystem3;

  public facadeSystem(){

  }

  File function(){
    subSystem1.read();
    subSystem1.operate();
    subSystem1.save();
  }
}
```

## 12.6 模式分析

外观模式对所有子系统加了一层抽象，这样可以便于客户端的调用。  

外观模式是一种简单且常用的设计模式。  

外观模式是一种使用频率非常高的设计模式，它通过引入一个外观角色来简化客户端与子系统之间的交互，为复杂的子系统调用提供一个统一的入口，使子系统与客户端的耦合度降低，且客户端调用非常方便。  

外观模式并不给系统增加任何新功能，它仅仅是简化调用接口。在几乎所有的软件中都能够找到外观模式的应用，如绝大多数 B/S 系统都有一个首页或者导航页面，大部分 C/S 系统都提供了菜单或者工具栏，在这里，首页和导航页面就是 B/S 系统的外观角色，而菜单和工具栏就是 C/S 系统的外观角色，通过它们用户可以快速访问子系统，降低了系统的复杂程度。所有涉及到与多个业务对象交互的场景都可以考虑使用外观模式进行重构。  

## 12.7 实例

## 12.8 优点

- 它对客户端屏蔽了子系统组件，减少了客户端所需处理的对象数目，并使得子系统使用起来更加容易。通过引入外观模式，客户端代码将变得很简单，与之关联的对象也很少。  
- 它实现了子系统与客户端之间的松耦合关系，这使得子系统的变化不会影响到调用它的客户端，只需要调整外观类即可。  
- 一个子系统的修改对其他子系统没有任何影响，而且子系统内部变化也不会影响到外观对象。  

## 12.9 缺点

- 不能很好地限制客户端直接使用子系统类，如果对客户端访问子系统类做太多的限制则减少了可变性和灵活性。  
- 如果设计不当，增加新的子系统可能需要修改外观类的源代码，违背了开闭原则。  

## 12.10 适用环境

- 当要为访问一系列复杂的子系统提供一个简单入口时可以使用外观模式。  
- 客户端程序与多个子系统之间存在很大的依赖性。引入外观类可以将子系统与客户端解耦，从而提高子系统的独立性和可移植性。  
- 在层次化结构中，可以使用外观模式定义系统中每一层的入口，层与层之间不直接产生联系，而通过外观类建立联系，降低层之间的耦合度。  

## 12.11 模式应用

## 12.12 模式扩展

如果需要增加、删除或更换与外观类交互的子系统类，必须修改外观类或客户端的源代码，这将违背开闭原则，因此可以通过引入 **抽象外观类** 来对系统进行改进，在一定程度上可以解决该问题。  

抽象外观类即对外观类再添加一层抽象。  
