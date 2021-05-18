# 11. 活动图

活动图描述系统随时间变化的行为。  
活动图本质上是一种流程图。  

```plantUML
@startuml Activity
start
: Hello world;
: This is a simple Activity Diagram;
stop
@enduml
```

## 11.1 元素

### 11.1.1 活动状态与动作状态

**活动状态** 用于表达状态机中的非原子的运行。  
**动作状态** 则是指原子的，不可中断的操作，并在动作完成后将转向另一个状态。  

活动状态有如下特点：  

* 活动状态可以分解成其他子活动或者动作状态。
* 活动状态的内部活动可以用另一个活动图来表示。
* 和动作状态不同，活动状态可以有入口动作和出口动作，也可以有内部转移。
* 动作状态是活动状态的一个特例，如果某个活动状态只包括一个动作，那么它就是一个动作状态。

动作状态有如下特点：  

* 动作状态是原子的，它是构造活动图的最小单位。
* 动作状态是不可中断的。
* 动作状态是瞬时的行为。
* 动作状态可以有入转换，入转换既可以是动作流，也可以是对象流。动作状态至少有一条出转换，这条转换以内部的完成为起点，与外部事件无关。
* 动作状态与状态图中的状态不同，它不能有入口动作和出口动作，更不能有内部转移。
* 在一张活动图中，动作状态允许多处出现。

UML 中活动状态和动作状态的图标相同，但是活动状态可以在图标中给出入口动作和出口动作等信息。  

### 11.1.2 动作流

动作之间的转换即动作流。在 UML 中使用带箭头的直线表示。  

### 11.1.3 开始节点与终止节点

即流程图中的开始节点与终止节点。  

图标与状态图中的开始节点与终止节点相同。  

### 11.1.4 对象

活动图中允许出现对象流。  

对象流是动作状态或者活动状态与对象之间的依赖关系。描述动作使用对象或动作对对象的影响。

用活动图描述某个对象时，可以把涉及到的对象放置在活动图中并用一个依赖将其连接到进行创建、修改和撤销的动作状态或者活动状态上，对象的这种使用方法就构成了对象流。  

## 11.2 分支

### 11.2.1 条件分支

类似与 `if...else` 语句的选择分支。  

```PlantUML
@startuml Activity
start
if(isTrue) then(True)
:Activity1;
else(False)
:Activity2;
endif

stop
@enduml
```

可以设置更多的 `else if` 以获得更多分支。  

多 `if else` 即 `switch` 语句。  

```PlantUML
@startuml Activity
start
switch(test?)
case(condition A)
: Activity1;
case(condition B)
: Activity2;
case(condition C)
: Activity3;
case(condition D)
: Activity4;
endswitch
stop
@enduml
```

### 11.2.2 循环分支

类似 `do...while` 语句的循环分支

```PlantUML
@startuml Activity
start 
repeat
: "Loop Activity 1";
repeat while(isTrue)
stop
@enduml
```

类似 `while` 语句的循环分支  

```PlantUML
@startuml Activity
start
while(isTrue)
    :Activity;
endwhile
stop
@enduml
```

### 11.2.3 并行分支

并行分支意味着程序将并发运行这些分支。  

```PlantUML
@startuml Activity
start
fork
:Activity1;
fork again
:Activity2;
end fork
stop
@enduml
```

### 11.2.4 连接器

连接器是类似接口的节点。  

```PlantUML
start
:Activity1;
(A)
detach
(A)
:Activity2;
stop
```

### 11.2.5 泳道

泳道将活动图中的活动分组，并把每一条泳道指定了负责的对象。  

仅允许动作流和对象流穿越泳道，活动严格隶属与一个泳道。  

```PlantUML
|#Gray|Swimlane1|
start
:Activity1;
|#DarkGray|Swimlane2|
:Activity2;
|Swimlane1|
:Activity3;
stop
```
