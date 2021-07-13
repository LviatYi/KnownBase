# 11. 装饰模式

## 11.1 模式动机

> 一般有两种方式可以实现给一个类或对象增加行为：
>
> - **继承机制** 使用继承机制是给现有类添加功能的一种有效途径，通过继承一个现有类可以使得子类在拥有自身方法的同时还拥有父类的方法。但是这种方法是静态的，用户不能控制增加行为的方式和时机。
> - **关联机制** 即将一个类的对象嵌入另一个对象中，由另一个对象来决定是否调用嵌入对象的行为以便扩展自己的行为，我们称这个嵌入的对象为装饰器 (Decorator)
>
> 装饰模式以对客户透明的方式动态地给一个对象附加上更多的责任，换言之，客户端并不会觉得对象在装饰前和装饰后有什么不同。装饰模式可以在不需要创造更多子类的情况下，将对象的功能加以扩展。

## 11.2 模式定义

> **装饰模式** (Decorator Pattern) 又称为 **包装器模式** (Wrapper) 或 **油漆工模式** ，是一种对象结构型模式。
>  
> - 动态地给一个对象增加一些额外的职责 (Responsibility) ，就增加对象功能来说，装饰模式比生成子类实现更为灵活。  

## 11.3 模式结构

装饰模式包含如下角色：

- Conponent 抽象构件
  - 具体构件和抽象装饰类的 **共同父类** ，声明了在具体构件中实现的业务方法。
  - 使客户端可以使用一致的方式处理未被装饰的对象以及装饰后对象。
- ConcreteComponent 具体构件
  - 定义具体的构件对象。
  - 实现抽象构件声明的方法。
- Decorator 抽象装饰类
  - 为具体构件增加职责。
  - 维护一个抽象构件的引用，以访问装饰前对象。
- ConcreteDecorator 具体装饰类
  - 实现抽象装饰类的职责。
  - 扩充对象的行为。

```PlantUML
@startuml Decorator_ClassDiagram
hide empty members
abstract Component{
    + operation()
}

class ConcreteComponent{
    + operation()
}

class Decorator{
    - component : Component
    + operation()
}

class ConcreteDecoratorA{
    - addedState :
    + operation()
}


class ConcreteDecoratorB{
    + operation()
    + addedBehavior()
}


Component <|-down- ConcreteComponent
Component <|-down- Decorator
Component <-right-o "component" Decorator

Decorator <|-down- ConcreteDecoratorA
Decorator <|-down- ConcreteDecoratorB

note right of Decorator
operation( ){
    return component.operation( );
}
end note

note bottom of ConcreteDecoratorB
super.operation( );
addedBehavior( );
end note

@enduml
```

## 11.4 时序图

```PlantUML
@startuml Decorator_SequenceDiagram
participant ":Client" as Client
participant ":ConcreteComponent" as ConcreteComponent
participant ":ConcreteDecoratorA" as ConcreteDecoratorA
create ConcreteComponent
activate Client
Client-->ConcreteComponent:<<create>>
create ConcreteDecoratorA
Client-->ConcreteDecoratorA:ConcreteDecoratorA(component)\n<<create>>
Client->ConcreteDecoratorA ++:operation( )
ConcreteDecoratorA->ConcreteComponent ++:operation( )
ConcreteDecoratorA->ConcreteDecoratorA ++:addBehavior( )
@enduml
```

## 11.5 代码分析

```Java
class Decorator extends Component
{
    private Component component;  //维护一个对抽象构件对象的引用

    public Decorator(Component component)  //注入一个抽象构件类型的对象
    {
        this.component=component;
    }

    public void operation()
    {
            component.operation();  //调用原有业务方法
    }
}
```

```Java
class ConcreteDecorator extends Decorator
{
    public ConcreteDecorator(Component  component)
    {
        super(component);
    }

    public void operation()
    {
        super.operation();  //调用原有业务方法
        addedBehavior();  //调用新增业务方法
    }

    //新增业务方法
    public void addedBehavior()
    {
        ......
    }
}
```

## 11.6 模式分析

装饰模式使用关联关系替代继承关系，符合合成复用原则。

> 与继承关系相比，关联关系的主要优势在于不会破坏类的封装性，而且继承是一种耦合度较大的静态关系，无法在程序运行时动态扩展。在软件开发阶段，关联关系虽然不会比继承关系减少编码量，但是到了软件维护阶段，由于关联关系使系统具有较好的松耦合性，因此使得系统更加容易维护。当然，关联关系的缺点是比继承关系要创建更多的对象。

使用装饰模式来实现扩展比继承更加灵活，它以对客户透明的方式动态地给一个对象附加更多的责任。装饰模式可以在不需要创造更多子类的情况下，将对象的功能加以扩展。

## 11.7 实例

```PlantUML
@startuml Decorator_Example
hide empty members
abstract Component{
    + display() : void
}
class Window{
    + display() : void
}
class Textbox {
    + display() : void
}
class ListBox{
    + display() : void
}
class ComponentDecorator{
    - component : Component
    + ComponentDecorator(Component component)
    + display() : void
}
class ScrollBarDecorator{
    + ScrollBarDecorator(Component component)
    + display() : void
    + setScrollBar() : void
}
class BlackBorderDecorator{
    + BlackBorderDecorator(Component component)
    + display() : void
    + setBlackBorder() : void
}

Component <|-- Window
Component <|-- Textbox
Component <|-- ListBox
Component <|-- ComponentDecorator
Component <-right-o ComponentDecorator
ComponentDecorator <|-- ScrollBarDecorator
ComponentDecorator <|-- BlackBorderDecorator
@enduml
```

```Java
//抽象界面构件类：抽象构件类，为了突出与模式相关的核心代码，对原有控件代码进行了大量的简化
abstract class Component
{
    public abstract void display();
}

//窗体类：具体构件类
class Window extends Component
{
    public void display()
    {
        System.out.println("显示窗体！");
    }
}

//文本框类：具体构件类
class TextBox extends Component
{
    public void display()
    {
        System.out.println("显示文本框！");
    }
}

//列表框类：具体构件类
class ListBox extends Component
{
    public void display()
    {
        System.out.println("显示列表框！");
    }
}

//构件装饰类：抽象装饰类
class ComponentDecorator extends Component
{
    private Component component; 维持对抽象构件类型对象的引用

    public ComponentDecorator(Component  component)  //注入抽象构件类型的对象
    {
        this.component = component;
    }

    public void display()
    {
        component.display();
    }
}

//滚动条装饰类：具体装饰类
class ScrollBarDecorator extends ComponentDecorator
{
    public ScrollBarDecorator(Component  component)
    {
        super(component);
    }

    public void display()
    {
        this.setScrollBar();
        super.display();
    }

    public void setScrollBar()
    {
            System.out.println("为构件增加滚动条！");
    }
}

//黑色边框装饰类：具体装饰类
class BlackBorderDecorator extends ComponentDecorator
{
    public BlackBorderDecorator(Component  component)
    {
        super(component);
    }

    public void display()
    {
        this.setBlackBorder();
        super.display();
    }

    public void setBlackBorder()
    {
        System.out.println("为构件增加黑色边框！");
    }
}
```

客户端编写如下代码：  

```Java
class Client
{
    public  static void main(String args[])
    {
        Component component,componentSB;  //使用抽象构件定义
        component = new Window(); //定义具体构件
        componentSB = new  ScrollBarDecorator(component); //定义装饰后的构件
        componentSB.display();
    }
}
```

## 11.8 优点

- 对于扩展一个对象的功能，装饰模式比继承更加灵活，不会导致类的个数急剧增加。即符合合成复用原则。  
- 可以通过一种动态的方式来扩展一个对象的功能，通过配置文件可以在运行时选择不同的具体装饰类，从而实现不同的行为。  
- 可以通过不断注入至另一个装饰类的方式，对一个对象进行多次装饰（仅透明装饰方式），通过使用不同的具体装饰类以及这些装饰类的排列组合，可以创造出很多不同行为的组合，得到功能更为强大的对象。  
- 具体构件类与具体装饰类可以独立变化，用户可以根据需要增加新的具体构件类和具体装饰类，原有类库代码无须改变，符合「开闭原则」。  

## 11.9 缺点

- 使用装饰模式进行系统设计时将产生很多小对象，这些对象的区别在于它们之间相互连接的方式有所不同，而不是它们的类或者属性值有所不同，大量小对象的产生势必会占用更多的系统资源，在一定程序上影响程序的性能。  
- 装饰模式提供了一种比继承更加灵活机动的解决方案，但同时也意味着比继承更加易于出错，排错也很困难，对于多次装饰的对象，调试时寻找错误可能需要逐级排查，较为繁琐。  

## 11.10 适用环境

- 在不影响其他对象的情况下，以动态、透明的方式给单个对象添加职责。  
- 当不能采用继承的方式对系统进行扩展或者采用继承不利于系统扩展和维护时可以使用装饰模式。不能采用继承的情况主要有两类
  - 系统中存在大量独立的扩展，为支持每一种扩展或者扩展之间的组合将产生大量的子类，使得子类数目呈爆炸性增长。  
  - 类已定义为不能被继承（如 Java 语言中的 final 类）。  

## 11.11 模式应用

## 11.12 模式扩展

### 11.12.1 透明装饰模式

透明装饰模式期待使用抽象构件类型 (Component) 定义所有对象。这意味着需要外部调用的方法一律需要在抽象构件类型中声明。  

透明装饰模式是装饰模式的标准实现。  

### 11.12.2 半透明装饰模式

半透明装饰模式需要使用具体装饰类型以调用新增方法。  

半透明装饰模式对于具体构件可以使用抽象构件类型来定义，但具体装饰类型必须指定。因为抽象装饰类型不包含新增方法的声明。  

半透明装饰模式具有一定灵活性，但是不能实现对用一个对象的多此装饰。  
