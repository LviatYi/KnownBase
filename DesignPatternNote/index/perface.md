# 0. 序言

## 0.1 设计模式简介

### 0.1.1 简单介绍

设计模式即软件开发的总体指导思路或参照样板。  

设计模式如下所示：  

* 创建型模式
  * 简单工厂模式
  * 工厂方法模式
  * 抽象工厂模式
  * 建造者模式
  * 原型模式
  * 单例模式
* 结构型模式
  * 适配器模式
  * 桥接模式
  * 装饰模式
  * 组合模式
  * 外观模式
  * 享元模式
  * 代理模式
* 行为型模式
  * 命令模式
  * 中介者模式
  * 观察者模式
  * 状态模式
  * 策略模式

### 0.1.2 软件设计原则

* **单一职责原则** (Single Responsibility Principle)
  * 一个类只负责一个功能领域中的相应职责。  
  * 或者可以定义为：就一个类而言，应该只有一个引起它变化的原因。  
* **开闭原则** (Open Closed Principle)
  * 软件中的对象应该对于扩展是开放的，但是对于修改是封闭的。  
  * 即允许一个实体允许在不改变其源代码的前提下变更它的行为。  
* **里氏代换原则** (Liskov Substitution Principle)
  * 任何基类可以出现的地方，子类一定可以出现。  
  * 保证了基类的复用性。  
* **依赖倒置原则** (Dependence Inversion Principle)
  * 程序应依赖于抽象接口，而不依赖于具体实现。  
  * 即对抽象进行编程，不要对实现进行编程。  
* **接口隔离原则** (Interface Segregation Principle)
  * 客户端不应该依赖它不需要的接口。一个类对另一个类的依赖应该建立在最小的接口上。  
* **抽象类** (Abstract Class)
  * 抽象类往往用来表征对问题领域进行分析、设计中得出的抽象概念，是对一系列看上去不同，但是本质上相同的具体概念的抽象。  
  * 抽象类不能被实例化，它只能作为基类。  

### 0.1.3 创建型模式

**创建型模式** (Creational Pattern) 描述了「对象怎么来」。  
创建者模式对类的实例化过程进行了抽象，以将软件模块中对象的创建和对象的使用分离。  

### 0.1.4 结构型模式

**结构型模式** 描述了「对象和谁有关」。  

### 0.1.5 行为型模式

**行为型模式** 描述了「对象之间在做什么」。  

### 0.1.6 J2EE 模式

**J2EE 模式** 描述了「对象合起来要做什么」。  

## 0.2 Note简介

本份 Note 旨在记录学习进度，提供部分参考，而非学习教程。

类似「每条 Java 语句都需要以半角分号 ```;``` 结尾」这种重要知识点不会在Note中被提及，因此不适合新手作为教材学习。  

## 0.3 学习资料

### 0.3.1 参考资料  

[图说设计模式](https://design-patterns.readthedocs.io/zh_CN/latest/index.html)  —— @ colin Github  

[永不磨灭的设计模式](https://blog.csdn.net/ShuSheng0007/article/details/115980889)  —— @ ShuSheng007 CSDN  

[史上最全设计模式](https://blog.csdn.net/LoveLion/article/details/17517213?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162198894416780274118367%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162198894416780274118367&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-17517213.first_rank_v2_pc_rank_v29&utm_term=%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F)  —— @ LoveLion CSDN  

### 0.3.2 开发环境  

VS Code