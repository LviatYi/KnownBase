# 14. 代理模式

## 14.1 模式动机

当无法直接访问某个对象或访问某个对象存在困难时，可以通过一个代理对象来间接访问。  
为了保证客户端使用的透明性，所访问的真实对象与代理对象需要实现相同的接口。

根据代理模式的使用目的不同，代理模式又可以分为多种类型，例如保护代理、远程代理、虚拟代理、缓冲代理等，它们应用于不同的场合，满足用户的不同需求。

## 14.2 模式定义

**代理模式** (Proxy Pattern) ，它属于对象结构型模式

- 给某一个对象提供一个代理或占位符，并由代理对象来控制对原对象的访问。
- 引入了一个新的代理对象，代理对象在客户端对象和目标对象之间起到中介的作用，它去掉客户不能看到的内容和服务或者增添客户需要的额外的新服务。

## 14.3 模式结构

代理模式包含如下角色：

- Subject 抽象主题角色
  - 声明了真实主题和代理主题的共同接口，因此允许在任何使用真实主题的地方使用代理主题。  
  - 客户端通常需要针对抽象主题角色进行编程。  
- Proxy 代理主题角色
  - 包含了对真实主题的引用，从而可以在任何时候操作真实主题对象。  
  - 提供一个与真实主题角色相同的接口，以便在任何时候都可以替代真实主题。
  - 可以控制对真实主题的使用，负责在需要的时候创建和删除真实主题对象，并对真实主题对象的使用加以约束。
- RealSubject 真实主题角色
  - 定义了代理角色所代表的真实对象，在真实主题角色中实现了真实的业务操作。  
  - 客户端可以通过代理主题角色间接调用真实主题角色中定义的操作。

```PlantUml
@startuml Proxy_ClassDiagram
hide empty members

class Client{

}
abstract Subject{
    + request()
}
class Proxy{
    - realSubject : RealSubject
    + preRequest()
    + request()
    + postRequest()
}
class RealSubject{
    + request():
}

Client ..right.>Subject
Subject <|-- Proxy
Subject <|-- RealSubject
Proxy --> RealSubject : realSubject
@enduml
```

## 14.4 时序图

```PlantUml
@startUML Proxy_SequenceDiagram
participant ":Client" as Client
participant ":Proxy" as Proxy
participant ":RealSubject" as RealSubject

Client --> Proxy ++: <<create>>
Proxy --> RealSubject ** :<<create>>
Proxy --

Client --> Proxy ++: request()
Proxy -->Proxy++:preRequest()
Proxy --

Proxy-->RealSubject++:request()
RealSubject--
Proxy-->Proxy++:afterRequest()
Proxy--
@endUML
```

## 14.5 代码分析

``` Csharp
abstract class Subject
{
    public abstract void Request();
}
```

``` Csharp
class RealSubject : Subject
{
    public override void Request()
    {
        //业务方法具体实现代码
    }
}
```

``` Csharp
class Proxy : Subject
{
    private RealSubject realSubject = new RealSubject(); //维持一个对真实主题对象的引用
 
    public void PreRequest() 
    {
        ...
    }
 
    public override void Request() 
    {
        PreRequest();
        realSubject.Request(); //调用真实主题对象的方法
        PostRequest();
    }
 
    public void PostRequest() 
    {
        ...
    }
}
```

## 14.6 模式分析

## 14.7 实例

## 14.8 优点

- 代理模式能够协调调用者和被调用者，在一定程度上降低了系统的耦合度。
- 远程代理使得客户端可以访问在远程机器上的对象，远程机器可能具有更好的计算性能与处理速度，可以快速响应并处理客户端请求。
- 虚拟代理通过使用一个小对象来代表一个大对象，可以减少系统资源的消耗，对系统进行优化并提高运行速度。
- 保护代理可以控制对真实对象的使用权限。

## 14.9 缺点

- 由于在客户端和真实主题之间增加了代理对象，因此有些类型的代理模式可能会造成请求的处理速度变慢。
- 实现代理模式需要额外的工作，有些代理模式的实现非常复杂。

## 14.10 适用环境

## 14.11 模式应用

## 14.12 模式扩展

实际开发中常用的代理模式形式上并不固定。常根据目的与实现方式分为不同种类。常用的几种如下：  

- 远程代理 (Remote Proxy)
  - 为一个位于不同的地址空间的对象提供一个本地的代理对象，这个不同的地址空间可以是在同一台主机中，也可是在另一台主机中，远程代理又称为大使 (Ambassador)。
- 虚拟代理 (Virtual Proxy)
  - 如果需要创建一个资源消耗较大的对象，先创建一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建。
- 保护代理 (Protect Proxy)
  - 控制对一个对象的访问，可以给不同的用户提供不同级别的使用权限。
- 缓冲代理 (Cache Proxy)
  - 为某一个目标操作的结果提供临时的存储空间，以便多个客户端可以共享这些结果。
- 智能引用代理 (Smart Reference Proxy)
  - 当一个对象被引用时，提供一些额外的操作，例如将对象被调用的次数记录下来等。
