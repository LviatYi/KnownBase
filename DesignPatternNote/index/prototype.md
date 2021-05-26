# 7. 原型模式

## 7.1 模式动机

快速生成一个实例，随后在此基础上对其做修补。  

## 7.2 模式定义

> **原型模式** (Prototype Pattern) ，它属于对象创建型模式。  

## 7.3 模式结构

原型模式包含如下角色：  

* Prototype 原型
  一个接口，包含了一个克隆自己的方法。  
* Concrete Prototype 具体原型
  实现了 Prototype 接口。这个对象拥有复制自己的能力。  

```PlantUML
@startUML Prototype_ClassDiagram
hide empty member
interface Prototype{
    + Copy():Prototype
}
class ConcretePrototype{
    + field:type
    + Copy():Prototype
}

Prototype<|..ConcretePrototype

@endUML
```

## 7.4 时序图

（略）

## 7.5 代码分析

```C++
// Prototype.h

class Prototype
{
    virtual Prototype Copy() = 0;
}
```

```C++
// ConcretePrototype.cpp
#include"Prototype.h"
#include"ConcretePrototype.h"

class ConcretePrototype
{
private:
    List<string>* part;//类的主要内容 规模较大，创建很慢
public:
    Prototype Copy()
    {
        this.part = new List<string>();
    }
    Prototype Copy(List<string>* part)
    {
        this.part = part;
    }
}
```

## 7.6 模式分析

提供了新的对象生成方法：快速克隆。  

## 7.7 实例

## 7.8 优点

* 可以极大地提升对象创建的速度。  

## 7.9 缺点

* 相对增加了系统的复杂度。  

## 7.10 适用环境

在以下情况下可以使用原型模式：

* 对象构建代价过高，且需要多次构建。  
  例如某个对象的构建需要数据库的参与，构建需要花费大量时间。  
* 构建的多个对象需要处于某种原始状态。  
  随后随着程序运行慢慢增长。  

## 7.11 模式应用

## 7.12 模式扩展
