# 10. 组合模式

## 10.1 模式动机

> 组合模式为处理树形结构提供了一种较为完美的解决方案，它描述了如何将容器和叶子进行递归组合，使得用户在使用时无须对它们进行区分，可以一致地对待容器和叶子。  

## 10.2 模式定义

> **组合模式** (Composite Pattern) 又称为 **「整体 - 部分」** (Part - Whole) **模式** ，它属于对象结构型模式。  
>  
> * 组合模式组合多个对象形成树形结构，以表示具有「整体 - 部分」关系的层次结构。  
> * 组合模式对单个对象（即叶子对象）和组合对象（即容器对象）的使用具有一致性。  

## 10.3 模式结构

组合模式包含如下角色：  

* Component 抽象构件
  * 抽象构件可以是接口或抽象类，为叶子构件和容器构件对象声明接口，在该角色中可以包含所有子类共有行为的声明和实现。  
  * 在抽象构件中定义了访问及管理它的子构件的方法，如增加子构件、删除子构件、获取子构件等。  
* Leaf 叶子构件
  * 叶子构件表示叶子节点对象，叶子节点没有子节点，它实现了在抽象构件中定义的行为。  
  * 对于那些访问及管理子构件的方法，可以通过异常等方式进行处理。  
* Composite 容器构件
  * 容器构件表示容器节点对象，容器节点包含子节点，其子节点可以是叶子节点，也可以是容器节点。  
  * 容器提供一个集合，用于存储子节点，实现了在抽象构件中定义的行为，包括那些访问及管理子构件的方法，在其业务方法中可以递归调用其子节点的业务方法。  

```PlantUML
@startuml Composite_ClassDiagram
hide empty members
abstract Component{
    + Operation()
    + add(Component c)
    + remove(Component c)
    + getChild(int i)
}

class Leaf{
    + Operation()
}

class Composite{
    + Operation()
    + add(Component c)
    + remove(Component c)
    + getChild(int i)
}

Component <|-down- Leaf
Component <|-down- Composite
Component <-right-o "children" Composite

note bottom of Composite
for(Component child:children){
    child.Operation();
}
end note
@endumld
```

## 10.4 时序图

（略）  

## 10.5 代码分析

```Java
// Component
abstract class Component {
    public abstract void add(Component c); //增加成员
    public abstract void remove(Component c); //删除成员
    public abstract Component getChild(int i); //获取成员
    public abstract void Operation();  //业务方法
}
```

``` Java
// Leaf
class Leaf extends Component {
    public void add(Component c) { 
        //异常处理或错误提示 
    }    
        
    public void remove(Component c) { 
        //异常处理或错误提示 
    }
    
    public Component getChild(int i) { 
        //异常处理或错误提示
        return null; 
    }
    
    public void Operation() {
        //叶子构件具体业务方法的实现
    } 
}
```

``` Java

class Composite extends Component {
    private ArrayList<Component> list = new ArrayList<Component>();
    
    public void add(Component c) {
        list.add(c);
    }
    
    public void remove(Component c) {
        list.remove(c);
    }
    
    public Component getChild(int i) {
        return (Component)list.get(i);
    }
    
    public void Operation() {
        //容器构件具体业务方法的实现
        //递归调用成员构件的业务方法
        for(Object obj:list) {
            ((Component)obj).Operation();
        }
    }
```

## 10.6 模式分析

* 组合模式的关键是定义了一个抽象构件类，它既可以代表叶子，又可以代表容器，而客户端针对该抽象构件类进行编程，无须知道它到底表示的是叶子还是容器，可以对其进行统一处理。  
* 容器中既可以包含叶子，也可以包含容器。这种特性使之能够表示树形结构。  

## 10.7 实例

一款能对系统文件进行杀毒的杀软。  

```PlantUML
@startuml Composite_Example
hide empty members
abstract AbstractFile{
    + add(AbstractFile file):void
    + remove(AbstractFile file):void
    + getChild(int i):AbstractFile
    + killVirus( ):void
}

class ImageFile{
    - name : String
    + add(AbstractFile file):void
    + remove(AbstractFile file):void
    + getChild(int i):AbstractFile
    + killVirus( ):void
}
class VideoFile{
    - name : String
    + add(AbstractFile file):void
    + remove(AbstractFile file):void
    + getChild(int i):AbstractFile
    + killVirus( ):void
}
class TextFile{
    - name : String
    + add(AbstractFile file):void
    + remove(AbstractFile file):void
    + getChild(int i):AbstractFile
    + killVirus( ):void
}
class Folder{
    - name : String
    - fileList : ArrayList
    + Folder(String name)
    + add(AbstractFile file):void
    + remove(AbstractFile file):void
    + getChild(int i):AbstractFile
    + killVirus( ):void
}
AbstractFile <|-- ImageFile
AbstractFile <|-- VideoFile
AbstractFile <|-- TextFile
AbstractFile <|-- Folder
AbstractFile <--o Folder : fileList

note bottom of Folder
killVirus(){
    for(child:fileList){
        child.killVirus();
    }
}
end note
@endumld
```

## 10.8 优点

## 10.9 缺点

## 10.10 适用环境

## 10.11 模式应用

## 10.12 模式扩展

易见，每次增加新的构件，都不得不实现抽象构件的方法。这在某些叶子构件中是不需要的。  

为了简化代码，提供两个解决方案：  

* 抽象构件提供默认实现，叶子构件提供具体实现。  
  * 默认实现可提供提示「不支持」的输出。  
  * 也可定义文件对象时使用叶子而不是抽象层。  
* 抽象构件不再声明管理或访问成员构件的方法。  
  * 容器构件负责声明管理或访问成员构件的方法。  
  * 同时意味着必然需要一个容器类。否则不能管理叶子和容器。  
  * 这意味着容器类对于用户不是透明的。  

根据抽象构件类的定义形式，我们可将组合模式分为透明组合模式和安全组合模式。  

### 10.12.1 透明组合模式

透明组合模式是组合模式的标准形式。  

透明组合模式要求抽象构件声明所有用于管理对象的方法。  
这样能保证所有的构件类都有相同的接口。  

上文的解决方案一提供了不透明的实现方法，但是其管理方法仍包含在抽象构件中，因此仍属于透明组合模式。  

### 10.12.2 透明组合模式
