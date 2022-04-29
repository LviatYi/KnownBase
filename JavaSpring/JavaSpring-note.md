# Java Spring Note

## 目录

1. [IOC 控制反转](index/ioc.md)

## 基本介绍

### Spring 简介

Spring 是分层的 Java SE/EE 一站式轻量级开源框架，以 IoC（Inverse of Control，控制反转）和 AOP（Aspect Oriented Programming，面向切面编程）为内核。

Spring 由 Rod Johnson 创立，2004 年发布了 Spring 框架的第一版，其目的是用于简化企业级应用程序开发的难度和周期。

Spring 是目前主流的 Java Web 开发框架，是 Java 世界最为成功的框架。该框架是一个轻量级的开源框架，具有很高的凝聚力和吸引力。

### 优点

- Spring 是一个开源的免费的框架。
- Spring 是一个轻量级的、非入侵式的框架。
- 控制反转（IOC），面向切面编程（AOP）。
- 支持事务的处理，对框架整合的支持。

### 组成

![Spring 组成][pic-springstructure]

- **Spring core 核心容器**  
  核心容器提供 spring 框架的基本功能。 Spring 以 bean 的方式组织和管理 Java 应用中的各个组件及其关系。 Spring 使用 BeanFactory 来产生和管理 Bean，它是工厂模式的实现。 BeanFactory 使用控制反转 (IoC) 模式将应用的配置和依赖性规范与实际的应用程序代码分开。BeanFactory 使用依赖注入的方式提供给组件依赖。
- **Spring context 上下文**  
  Spring 上下文是一个配置文件，向 Spring 框架提供上下文信息。Spring 上下文包括企业服务，如 JNDI、EJB、电子邮件、国际化、校验和调度功能。
- **Spring AOP 面向切面编程**  
  通过配置管理特性，Spring AOP 模块直接将面向方面的编程功能集成到了 Spring 框架中。所以，可以很容易地使 Spring 框架管理的任何对象支持 AOP。Spring AOP 模块为基于 Spring 的应用程序中的对象提供了事务管理服务。通过使用 Spring AOP，不用依赖 EJB 组件，就可以将声明性事务管理集成到应用程序中。
- **Spring DAO 模块**  
  DAO 模式主要目的是将持久层相关问题与一般的的业务规则和工作流隔离开来。Spring 中的 DAO 提供一致的方式访问数据库，不管采用何种持久化技术，Spring 都提供一直的编程模型。Spring 还对不同的持久层技术提供一致的 DAO 方式的异常层次结构。
- **Spring ORM 模块**  
  Spring 与所有的主要的 ORM 映射框架都集成的很好，包括 hibernate、JDO 实现、TopLink 和 IBatis SQL Map 等。Spring 为所有的这些框架提供了模板之类的辅助类，达成了一致的编程风格。
- **Spring Web 模块**  
  Web 上下文模块建立在应用程序上下文模块之上，为基于 Web 的应用程序提供了上下文。Web 层使用 Web 层框架，可选的，可以是 Spring 自己的 MVC 框架，或者提供的 Web 框架，如 Struts、Webwork、tapestry 和 jsf。
- **Spring Web MVC 框架**  
  MVC 框架是一个全功能的构建 Web 应用程序的 MVC 实现。通过策略接口，MVC 框架变成为高度可配置的。Spring 的 MVC 框架提供清晰的角色划分：控制器、验证器、命令对象、表单对象和模型对象、分发器、处理器映射和视图解析器。Spring 支持多种视图技术。

### Spring 扩展

- Spring Boot
  - 一个快速开发的脚手架。
  - 基于 SpringBoot 可以快速开发单个微服务。
- Spring Cloud
  - SpringCloud 是基于 SpringBoot 实现的。

## 参考资料

### 参考视频

[【狂神说 Java】Spring5 最新完整教程 IDEA 版通俗易懂](https://www.bilibili.com/video/BV1WE411d7Dv?from=search&seid=14885296346718072648) —— @ 遇见狂神说 Bilibili

## 版本号

`v0.01`

[pic-springstructure]: .\pic\springStructure.svg
