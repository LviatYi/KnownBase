# 13. 享元模式

## 13.1 模式动机

在某些场景中，对象的数量十分庞大，这将耗费大量的系统资源。当其中含有大量重复或相似对象时，可以利用享元模式进行优化。

享元模式通过共享技术实现相同或相似对象的重用。

## 13.2 模式定义

> **享元模式** (Flyweight Pattern) 又称为轻量级模式，它属于对象结构性模式。
>
> - 运用共享技术有效地支持大量细粒度对象的复用。
> - 系统只使用少量的对象，而这些对象都很相似，状态变化很小，可以实现对象的多次复用。
> - 享元模式要求能够共享的对象必须是细粒度对象。

## 13.3 模式结构

享元模式常结合工厂模式使用。

享元模式包含如下角色：

- Flyweight 抽象享元类
  - 通常是一个接口或抽象类。
  - 声明了具体享元类公共的方法。
    - 可提供享元对象的内部数据（内部状态）。
    - 也可设置外部数据（外部状态）。
- ConcreteFlyweight 具体享元类
  - 实现了抽象享元类，其实例称为享元对象。
  - 为内部状态提供了存储空间。
  - 通常可以结合单例模式来设计具体享元类，为每一个具体享元类提供唯一的享元对象。
- UnsharedConcreteFlyweight 非共享具体享元类
  - 并不是所有的抽象享元类的子类都需要被共享，不能被共享的子类可设计为非共享具体享元类。
  - 当需要时，可以直接通过实例化创建。
- FlyweightFactory 享元工厂类
  - 用于创建并管理享元对象。
  - 针对抽象享元类编程，将各种类型的具体享元对象存储在一个享元池中。
    - 享元池一般设计为一个存储「键值对」的集合（也可以是其他类型的集合），可以结合工厂模式进行设计。
    - 当用户请求一个具体享元对象时，享元工厂提供一个存储在享元池中已创建的实例或者创建一个新的实例（如果不存在的话），返回新创建的实例并将其存储在享元池中。

```PlantUML
@startuml Flyweight_ClassDiagram
hide empty members

class FlyweightFactory{
    - flyweights : HashMap <String , Flyweight*>
    + getFlyweight (String key) : Flyweight
}
abstract Flyweight{
    + operation(extrinsicState)
}
class ConcreteFlyweight{
    - IntrinsicState :
    + operation(extrinsicState)
}
class UnsharedConcreteFlyweight{
    - allState:
    + operation(extrinsicState)
}

FlyweightFactory o-right-> Flyweight : flyweights
Flyweight <|.. ConcreteFlyweight
Flyweight <|.. UnsharedConcreteFlyweight

note bottom of FlyweightFactory{
    getFlyweight( ) 返回单例
}
@enduml
```

## 13.4 时序图

```PlantUML
@startUML Flyweight_SequenceDiagram
participant iMain
participant ":FlyweightFactory" as FlyweightFactory
participant ":ConcreteFlyweight" as ConcreteFlyweight

activate iMain
iMain --> FlyweightFactory : <<create>>
iMain --> FlyweightFactory ++: getFlyweight("one")
FlyweightFactory --> ConcreteFlyweight : <<create>>
return :Flyweight obj()

iMain --> ConcreteFlyweight : operation(extrinsicState)

...

iMain --> FlyweightFactory ++: getFlyweight("one")
return :Flyweight obj()

iMain --> ConcreteFlyweight : operation(extrinsicState)

@endUML
```

## 13.5 代码分析

```C++
#include "ConcreteFlyweight.h"
#include "FlyweightFactory.h"
#include "Flyweight.h"
using namespace std;

int main(int argc, char *argv[])
{
  FlyweightFactory factory;
  Flyweight * fw = factory.getFlyweight("one");
  fw->operation();

  Flyweight * fw2 = factory.getFlyweight("two");
  fw2->operation();
  //aready exist in pool
  Flyweight * fw3 = factory.getFlyweight("one");
  fw3->operation();
  return 0;
}
```

```C++
Flyweight* FlyweightFactory::getFlyweight(string str){
  map<string,Flyweight*>::iterator itr = m_mpFlyweight.find(str);

  if(itr == m_mpFlyweight.end())
  {
    Flyweight * fw = new ConcreteFlyweight(str);
    m_mpFlyweight.insert(make_pair(str,fw));
    return fw;
  }
  else
  {
    cout << "aready in the pool,use the exist one:" << endl;
    return itr->second;
  }
}
```

```C++
ConcreteFlyweight::ConcreteFlyweight(string str){
  intrinsicState = str;
}

ConcreteFlyweight::operate(ExtrinsicState state){
  cout<<"this obj has a extrinsic state"<<state.getString()<<endl;
}
```

## 13.6 模式分析

享元模式的核心在于享元工厂类。

享元工厂类提供了一个用于存储享元对象的享元池。

- 用户需要对象时，首先从享元池中获取。
- 如果享元池中不存在，则创建一个新的享元对象返回给用户，并在享元池中保存该新增对象。

藉由享元工厂，不同的变量可以引用到相同的对象，因此能够节省资源。  
同时正因如此，开发者需要正确区分 **内部状态** (Internal State) 和 **外部状态** (External State) 。

- 内部状态是存储在享元对象内部并且不会随环境改变而改变的状态，因此内部状态可以共享。
- 外部状态是随环境改变而改变的、不可以共享的状态。

享元对象的外部状态必须由客户端保存，并在享元对象被创建之后，在需要使用的时候再传入到享元对象内部。  
一个外部状态与另一个外部状态之间是 **相互独立** 的。

## 13.7 实例

## 13.8 优点

- 享元模式的优点在于它可以极大减少内存中对象的数量，使得相同对象或相似对象在内存中只保存一份。
- 享元模式的外部状态相对独立，而且不会影响其内部状态，从而使得享元对象可以在不同的环境中被共享。

## 13.9 缺点

- 享元模式使得系统更加复杂，需要分离出内部状态和外部状态，这使得程序的逻辑复杂化。
- 为了使对象可以共享，享元模式需要将享元对象的状态外部化，而读取外部状态使得运行时间变长。

## 13.10 适用环境

- 一个系统有大量相同或者相似的对象，由于这类对象的大量使用，造成内存的大量耗费。
- 对象的大部分状态都可以外部化，可以将这些外部状态传入对象中。
- 使用享元模式需要维护一个存储享元对象的享元池，而这需要耗费资源，因此，应当在多次重复使用享元对象时才值得使用享元模式。

## 13.11 模式应用

享元模式在编辑器软件中大量使用，如在一个文档中多次出现相同的图片，则只需要创建一个图片对象，通过在应用程序中设置该图片出现的位置，可以实现该图片在不同地方多次重复显示。

## 13.12 模式扩展

### 13.12.1 单纯享元模式

在单纯享元模式中，所有的具体享元类都是可以共享的，不存在非共享具体享元类。

### 13.12.2 复合享元模式

将一些单纯享元使用组合模式加以组合，可以形成复合享元对象，这样的复合享元对象本身不能共享，但是它们可以分解成单纯享元对象，而后者则可以共享。
