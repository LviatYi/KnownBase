# Markdown 图表 使用笔记

## 0. 前言

在 Markdown 中，可采用 Mermaid 或 flow 编辑和渲染不同图表  

Mermaid 功能强大，可以应对不同的应用场景  

而 flow 恰如其名，只能应付流程图，功能单一，且渲染不仅略丑，还有奇怪的 bug 。它之所以会出现在这里，仅仅因为作者一开始先百度到了 flow ，就学了 flow...  

## 1. Mermaid 图

Mermaid是一个功能强大的库，可以渲染流程图、状态图、时序图、甘特图等  

### 1.1 流程图

示例：关于如何避免二义性表达「去买菜，如果有水果，则买水果」  

> ```Mermaid
> flowchart TB
>     start(start) --> DoSth1==> JudgeFruit
>     JudgeFruit-->|"Yes"|BuyApple-->BuyOrange-->DoSth3
>     JudgeFruit--"No"----->DoSth3
>     DoSth3-.-Output[/"Cout How much"/]
>     -->End(end)
> 
>     DoSth1[Buy some vegetables]
>     JudgeFruit{There is some fruit}
>     BuyApple[Buy some apple]
>     BuyOrange[Buy some Orange]
>     DoSth3[Back home]
> ```

````Markdown
```Mermaid
flowchart TB

start(start) --> DoSth1==> JudgeFruit
JudgeFruit-->|"Yes"|BuyApple-->BuyOrange-->DoSth3
JudgeFruit--"No"----->DoSth3
DoSth3-.-Output[/"Cout How much"/]
-->End(end)

DoSth1[Buy some vegetables]
JudgeFruit{There is some fruit}
BuyApple[Buy some apple]
BuyOrange[Buy some Orange]
DoSth3[Back home]
```
````

一些基础知识：

* 出现在Markdown中的Mermaid代码段，必须在Mermaid代码块中定义，否则将不会被识别并渲染  
* Mermaid中，允许「先使用后声明」  
* 每个语句以```;```结尾，不过这是可选的  

对于流程图，一般由如下几种要素构成：  

* **结点**  
一般指事件本身  
* **方向**  
指整个图表的方向，而非单条路径的方向  
* **路径**  
指结点之间的联系，包含方向等各种属性  

#### 1.1.1 结点

流程图使用不同的形状描述不同含义的结点  
而Mermaid使用不同语法描述不同的形状  

| 语法 | 结点 | 含义 |
| :--: | :--: | :--: |
| ```id( )``` | 圆角矩形结点 | 开始框/结束框 |
| ```id[ ]``` | 矩形结点 | 操作框 |
| ```id{ }``` | 菱形结点 | 判断框 |
| ```id[/ /]``` | 平行四边形结点 | 数据框 |
| ```id[\ \]``` | 逆平行四边形结点 |  |
| ```id[[ ]]``` | 双边矩形结点 | 子例程框 |
| ```id[( )]``` | 圆柱结点 | 磁盘框 |
| ```id(( ))``` | 圆形结点 | 联系点 |
| ```id[/ \]``` | 梯形结点 |  |
| ```id[\ /]``` | 倒梯形结点 | 手动操作 |
| ```id> ]``` | 右向旗帜状结点 |  |
| ```id{{ }}``` | 六边形结点 | 准备框 |

注：不可以使用「end」作为结点id，你可以使用End或者END  

#### 1.1.2 方向

Mermaid有如下关键字描述方向  

| 关键字 | 含义 |
| :--: | :--: |
| TB | 从上到下 |
| BT | 从下到上 |
| RL | 从左到右 |
| LR | 从右到左 |

#### 1.1.3 路径

路径可包含文字、强调、父子关系等属性  

| 语法 | 属性 |
| :--: | :--: |
| ```---``` | 线 |
| ```-->``` | 带箭头线 |
| ```--text---```/```---|text|``` | 带文本线 |
| ```--text-->```/```-->|text|``` | 带文本带箭头线 |
| ```===``` | 粗线 |
| ```==>``` | 带箭头粗线 |
| ```==text===```/```===|text|``` | 带文本粗线 |
| ```-.-``` | 虚线 |
| ```-.->``` | 带箭头虚线 |
| ```-.text.-``` | 带文本虚线 |

* **关于线长** 添加多个 ``` - ``` 、``` = ``` 或 ``` . ``` 可以分别延长线、粗线或虚线
* **关于特殊文本**  

  * 如果文本中带有奇奇怪怪的字符，可以使用```" "```将其封装。
  * 也可用HTML转义字符或char表示特殊字符

> ```Mermaid
>  graph LR
>  A["引号的转义字符:&quot"] -->B["引号的十进制char:&#34"]
> ```

``` Markdown
 graph LR
 A["引号的转义字符:&quot"] -->B["引号的十进制char:&#34"]
```

* **其他** 可以使用 ```&``` 将同为起点或同为终点的结点组合以简化语法
没错，这就是一个语法糖

> ``` Mermaid
> graph LR
>  start1(start1)
>  start2(start2)
>  end1(end1)
>  end2(end2)
> 
>  start1 & start2 --> end1 & end2
> ```

```Markdown
graph LR
 start1(start1)
 start2(start2)
 end1(end1)
 end2(end2)

 start1 & start2 --> end1 & end2
```

### 1.1.4 子图

在流程图中可以包含若干子流程图  
子图需包含在```subgraph```块中，并以```end```结尾  

子图可带有id  

> ```Mermaid
> graph TB
>     a1-->c2
>     subgraph id1 [one]
>     a1-->a2
>     end
>     subgraph id2 [two]
>     b1-->b2
>     end
>     subgraph three
>     c1-->c2
>     end
> ```

```Markdown
graph TB
    a1-->c2
    
    subgraph id1 [one]
    a1-->a2
    end

    subgraph id2 [two]
    b1-->b2
    end

    subgraph three
    c1-->c2
    end
```

若将图表定义为```flowchart```，则可描述子图与子图或节点与子图的联系  

> ```Mermaid
> flowchart TB
>     c1-->a2
>     subgraph one
>     a1-->a2
>     end
>     subgraph two
>     b1-->b2
>     end
>     subgraph three
>     c1-->c2
>     end
>     one --> two
>     three --> two
>     two --> c2
> ```

```Markdown
flowchart TB
    c1-->a2

    subgraph one
    a1-->a2
    end

    subgraph two
    b1-->b2
    end

    subgraph three
    c1-->c2
    end

    one --> two
    three --> two
    two --> c2
```

## 2. flow图

你也可以使用 flow 编辑一张简单的流程图  

> 示例：一个简单的流程图
>
> ```flow
> s=>start: 开始框
> pl=>parallel: 多输出操作框1
> op1=>operation: 操作框1
> op2=>operation: 操作框2
> op3=>operation: 操作框3
> cond=>condition: 判断框(是或否?)
> sub1=>subroutine: 子流程
> io=>inputoutput: 输入输出框
> e=>end: 结束框
> 
> s(right)->pl
> pl(path1,bottom)->op1
> pl(path2,right)->op2
> op1->cond
> op2(right)->op3->e
> cond(no)->sub1(top)->op1
> cond(yes)->io->e
> ```

````Markdown

```flow
s=>start: 开始框
pl=>parallel: 多输出操作框1
op1=>operation: 操作框1
op2=>operation: 操作框2
op3=>operation: 操作框3
cond=>condition: 判断框(是或否?)
sub1=>subroutine: 子流程
io=>inputoutput: 输入输出框
e=>end: 结束框

s(right)->pl
pl(path1,bottom)->op1
pl(path2,right)->op2
op1->cond
op2(right)->op3->e
cond(no)->sub1(top)->op1
cond(yes)->io->e
```
````

注：出现在Markdown中的flow代码段，必须在flow代码块中定义，否则将不会被识别并渲染  

由上图我们可以清晰地看到  
标准流程图由节点（描述对象）与的箭头（描述流程）组成  

而描述流程图的flow代码则由节点定义与流程描述构成  

使用节点前需要在之前进行定义  
因此在flow中常常先定义节点，再连接节点，最后调整样式  

```Markdown
定义节点
连接节点
样式调整（可选）
```

### 定义节点

节点主要用如下几种类型名定义  

|   类型名       |   类型含义    |
|   :--:        |   :--:        |
|   start       |   开始框      |
|   end         |   结束框      |
|   operation   |   操作框      |
|   parallel    |   多输出操作框 |
|   condition   |   判断框      |
|   inputoutput |   输入输出框  |
|   subroutine  |   子流程框    |

flow采用```节点名=>类型名: 框内文本```的方式为节点定义与赋值  

注意，冒号与框内文本之间的必须用空格隔开  
而多余空格的存在则是语法错误  

```Markdown
s=>start
//定义一个开始框s
```

### 连接节点

箭头则简单粗暴，即```->```  

箭头可以添加一些含义或形式
这样能使图表更直观  

#### 箭头方向

箭头默认方向向下,也可以通过
加关键字的方法使之  
向右

```Markdown
(right)->
```

向左

```Markdown
(left)->
```

向上

```Markdown
(top)->
```

向下

```Markdown
(bottom)->
```

因此不加以说明的情况下，整个流程图将呈现自上而下的姿态。  

#### 条件流向

对于判断框，将有是 非两种输出  
是  

```Markdown
(true)->
```

非

```Markdown
(flase)->
```

也可以使用```yes\no```两种关键字  

#### 多输出

除了判断框，多输出操作框也可以拥有多个输出  
且可用```bottom``` ```top``` ```left``` ```right```指定其输出方向  
因此可以这样写  

```Markdown
(path1,left)->
(path2,bottom)->
```

将节点名与箭头结合，即可连接节点  

> ```flow
> s=>start: 从这里开始
> e=>end: 从这里结束
> 
> s(right)->e
> ```

至此，你已学会了flow的基础操作  
