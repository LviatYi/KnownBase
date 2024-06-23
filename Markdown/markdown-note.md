# Markdown 使用笔记

[toc]

## 0. 前言

Markdown 是语法简单却功能强大的轻量级标记语言。它允许人们使用易写的纯文本格式编写文档，然后转换为 XHTML 文档。因此其与 HTML 语言有着很好的兼容性。

与 HTML 不同的是，Markdown 语言重视的是文档结构而非形式美观。这意味着 Markdown 文档也许看起来相当「单调」，但这并不意味着 Markdown 不美观。

实际上 Markdown 之所以是技术文档的首要选择，正是因为 Markdown 的语法使其简洁易读，方便实用。同时，作为开发者也应在内容上遵守一定的规则，如此才能发挥 Markdown 的真正效用。

### 开发环境

- **VS Code**  
  一款及其轻量化+模块化的编辑器。
- **Markdown Preview Enhanced**  
  一款强大的 VS Code 的 Markdown 编辑与预览扩展集。

不同的 Markdown 处理器对相同语法可能有着不同的解释，对标准 Markdown 特性的支持也是稍有差异。如果你使用的是不同的 Markdown 处理器，且对照本文档出现了意外情况，请以使用中的处理器的开发文档为准。

### 版本号

`v1.31`

## 1. 标题

标题有两种实现方式：

- `###` Atx 风格 。
- `===` Setext 风格 。

### Atx 风格标题

用 `###` 表示标题  
用 `#` 的数量表示标题的次序

> # 一级标题
>
> ## 二级标题
>
> ### 三级标题
>
> #### 四级标题
>
> ##### 五级标题
>
> ###### 六级标题

```Markdown
# 一级标题
###### 六级标题
```

### Setext 风格标题

不推荐使用 Setext 风格标题。  
Setext 使用两行表示标题。  
上行为标题文本，下行为如下的标识符。

- 一级标题 `===`
- 二级标题 `---`

> # 一级标题
>
> ## 二级标题

```Markdown
这是一级标题
=============

这是二级标题
-------------
```

## 2. 段落

在 Markdown 中，段落用两个以上空格与换行符表示

也可以用一个空行来表示一个段落

> 段落一段落一段落一段落一段落一  
> 段落二段落二段落二段落二段落二

> 段落一段落一段落一段落一段落一
>
> 段落二段落二段落二段落二段落二

```Markdown
段落一段落一段落一段落一段落一
段落二段落二段落二段落二段落二

段落一段落一段落一段落一段落一

段落二段落二段落二段落二段落二

```

不同的 Markdown 处理器可能出现不同的效果，且个别渲染器足够「智能」，即使没有双空格也视为换行。但极不推荐这样做。  
在本文档中，统一使用两个空格加一个回车表示段落。

## 3. 引用块

Markdown 使用 email 样式的「 > 」字符作为引用块。

> Markdown is a text-to-HTML conversion tool for web writers.  
> Markdown allows you to write using an easy-to-read, easy-to-write plain text format, then convert it to structurally valid XHTML (or HTML).
>
> 在块中 每行末尾都需要强制换行。

块引用中支持嵌套。

> > 块中块
> >
> > > 块中块中块
> > >
> > > > 块中块中块中块

```Markdown
>> 块中块
>>> 块中块中块
>>>> 块中块中块中块
```

块引用中可以包含 Markdown 元素

> 块中的 Markdown 元素:  
> </br>
>
> ## 二级标题
>
> </br>
>  
> ``` C
> int main()
> {
>    cout>> "代码块" >>endl;
> }
> ```

````Markdown
> 块中的 Markdown 元素:
> ## 二级标题
>
> ``` C
> int main()
> {
>    cout>> "代码块" >>endl;
> }
> ```
````

## 4. 列表

### 无序列表

无序列表使用 `+` `-` `*` 。

> - Red
> - Green
>
> * Red
> * Green
>
> - Red
> - Green

```Markdown
+ Red
+ Green
* Red
* Green
- Red
- Green
```

### 有序列表

有序列表使用 `数字 + 句号` 。

> 1. 第一点
> 2. 第二点
> 3. 第三点

```Markdown
1. 第一点
2. 第二点
3. 第三点
```

允许从其他序号起始有序列表：

> 3. 第三点
> 4. 第四点
> 5. 第五点

```Markdown
3. 第三点
4. 第四点
5. 第五点
```

除首个列表序号，其余列表序号与代码中的标号无关。  
但极不推荐不连续的标号。

```Markdown
3. 第三点
6. 第四点
666. 第五点
```

> 3. 第三点
> 4. 第四点
> 5. 第五点

如果块注释被包含在列表项中，应该使用缩进表达这种逻辑关系。  
代码块同理。

> 1. 列表项 1
> 2. 列表项 2
>
>    > 列表项 2 包含的块
>
>    列表项 2 包含的块包含的代码段（好绕）
>
>    ```C
>    int main()
>    {
>        cout<<「 Hello world again 」<<endl;
>        return 0
>    }
>    ```
>
> 3. 列表项 3

````Markdown
1. 列表项 1
2. 列表项 2
   > 列表项 2 包含的块

   列表项 2 包含的块包含的代码段（好绕）
   ``` C
   int main()
   {
       cout<<「 Hello world again 」<<endl;
       return 0
   }
   ```
3. 列表项 3
````

### 缩进列表

缩进列表使用 `:` 。

> 表头  
> : 第一点  
> : 第二点

```Markdown
表头
: 第一点
: 第二点
```

### 复选框

在无序或有序列表符后添加 `[ ]` 或 `[x]` 来添加可以交互的复选框。

- [ ] 计划 1
- [ ] 计划 2
- [x] 计划 3

```Markdown
* [ ] 计划 1
* [ ] 计划 2
* [x] 计划 3
```

复选框不能放在引用块中。

## 5. 代码块

代码块会原样输出代码，不用担心与 Markdown 代码冲突。

（不推荐）允许直接使用四个空格或一个 `Tab` 表示不指定语言代码块。

>     int main()
>     {
>         cout << 「 Hello World! 」 <<endl;
>         return 0;
>     }

```Markdown
    int main()
    {
        cout << 「 Hello World! 」 <<endl;
        return 0;
    }
```

推荐使用「 ``` 」表示不指定或指定语言的代码块。  
如果指定了语言，在高级的渲染器中会为代码染色，使其具有更强的可读性。  
建议指定语言。

```C
int main()
{
    cout << 「 你已经看到我好几次啦 」 << endl;
    return 0;
}
```

````Markdown
``` C
int main()
{
    cout << 「 Hello World! 」 <<endl;
    return 0;
}
```
````

使用「 ` 」标记行内代码。

> C++ 使用 `cout<< "文本" <<endl;` 输出一行。

```Markdown
C++ 使用 `cout<< "文本" <<endl;`  输出一行。
```

如果需要标明行数，请添加 `{.line-numbers} class`

```C {.line-numbers}
int main()
{
    cout << 「 Hello World! 」 <<endl;
    return 0;
}
```

````Markdown
```C {.line-numbers}
int main()
{
    cout << 「 Hello World! 」 <<endl;
    return 0;
}
```
````

可以通过添加 `highlight` 属性指定行地使代码高亮

```C {.line-numbers,highlight=[2-3,5]}
    cout << line 1 << endl;
    cout << line 2 << endl;
    cout << line 3 << endl;
    cout << line 4 << endl;
    cout << line 5 << endl;
```

````Markdown
```C {highlight=[2-3,5]}
    cout << line 1 << endl;
    cout << line 2 << endl;
    cout << line 3 << endl;
    cout << line 4 << endl;
    cout << line 5 << endl;
```
````

实际上，「 ` 」的个数是无限制的。但收尾应保持一致。

你可以使用多个「 ` 」来避免一些冲突。

但行内代码块建议使用一个。

## 6. 字体修饰

Markdown 可以使用以下的标记字体

### 斜体

> _斜体文本_  
> _通常用于补充解释，或引用名人名言 / 作品名等场景_

```Markdown
*文本*
_文本_
```

### 粗体

> **粗体文本**  
> **粗体会降低阅读速度，从而起到强调文本的作用**

```Markdown
**文本**
__文本__
```

### 粗斜体

> **_粗斜体文本_**  
> **_粗斜体更偏向于装饰_**

```Markdown
***文本***
___文本___
```

为了让文档更具实用意义，请克制地使用粗体与斜体。

### 删除线

> ~~被删除文本~~

```Markdown
~~文本~~
```

### 高亮

> ==高亮文本==

```Markdown
==文本==
```

### 上标

> 文本^上标文本^

```Markdown
文本^上标文本^
```

### 下标

> 文本~下标文本~

```Markdown
文本~下标文本~
```

### 下划线

> <u>下划线文本</u>

```Markdown
<u>文本</u>
```

实际上下划线并不是原生 Markdown 语法，而是来自 HTML 的扩展。

### 脚注

脚注的格式为 `[\^x]` 其中 `x` 可以是数字、字母或汉字、单词或词组。  
脚注必须与其引用所对应。

> 本文作者：@LviatYi[^lviatyi] 是一个充满潜力的[^2]（未来）全栈游戏开发者[^3]

[^lviatyi]: 一个自命不凡且不自知的人
[^2]: 不自知
[^3]: 自命不凡

```Markdown
......[^AAA]......[^2]......[^3]......

[^AAA]: text1
[^2]: text2
[^3]: text3

```

脚注的说明部分在渲染时将被自动移动至文档末尾。  
你可以通过点击引用标号或下拉至文档末尾找到它们。  
为了便于管理，建议将代码中的脚注解释也移至文档末尾。

## 7. 链接

允许在 Markdown 中插入指向外部网页或其他文件的链接。

> 文本式 [Github](https://github.com "软件源代码托管服务平台")
>
> 地址式 <https://github.com>

```Markdown
[显示文本](链接 "提示文本")

其他文本<链接>
```

外部链接请标注 `https://` 等其他协议头。否则将视为相对路径。

还可以使用变量式链接，从而像声明变量一样使用，并在文档末尾初始化链接：

> [Github 平台][github]
>
> [github]: https://www.twitter.com "软件源代码托管服务平台"

```Markdown
[显示文本][变量名]

[变量名]:链接 "提示文本"
```

为了便于管理，建议使用变量式链接。

## 8. 图片

允许在 Markdown 中插入图片。

> ![Github Logo](https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fbpic.588ku.com%2Felement_origin_min_pic%2F00%2F85%2F53%2F1156e916d95db0c.jpg&refer=http%3A%2F%2Fbpic.588ku.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg?sec=1614142767&t=2bd7d77d1b8e0028a5a12587fc76d34c "Github 的 Logo")

```Markdown
![属性文本](图片地址 "提示文字")
```

图片同样允许变量式声明。

建议使用 HTML 对图片进行格式扩展。

## 9. 表格

Markdown 支持插入表格，但样式有限。

> | 表头   | 表头   |
> | ------ | ------ |
> | 单元格 | 单元格 |
> | 单元格 | 单元格 |

```Markdown
|  表头  |  表头  |
|  ----  | ------ |
| 单元格 | 单元格 |
| 单元格 | 单元格 |

或

  表头  |  表头
  ----  | -----
 单元格 | 单元格
 单元格 | 单元格
```

可以在隔断层加入 `:` ，以控制所在列的对齐。

> | 默 认 左 对 齐 | 左 对 齐 | 居 中 对 齐 | 右 对 齐 |
> | -------------- | :------- | :---------: | -------: |
> | 居左           | 居左     |    居中     |     居右 |
> | 居左           | 居左     |    居中     |     居右 |

```Markdown
|  默 认 左 对 齐  |  左 对 齐  |  居 中 对 齐 |  右 对 齐  |
|  -------------   | :--------- | :----------: | ---------: |
|       居左       |    居左    |     居中     |    居右    |
|       居左       |    居左    |     居中     |    居右    |
```

代码中的空白符和 `|` 只需要一个，但推荐使用代码格式化工具（比如 Prettier）进行调整，以提高可读性。

## 10. 公式

Markdown 支持插入 Latex 公式。

实际上，大多渲染器支持 TeX 或 LaTeX 的语法，但 Github 并不支持 Latex 公式。

LaTeX 语法很复杂，在此文档中展示将占用极大的版面。建议自行查阅 Latex 语法。

[Markdown Formula 公式使用笔记](./markdown-note-formula.md)

## 11. 图表

Markdown 允许使用 Mermaid 等扩展绘制流程图、顺序图、甘特图等图表。

建议自行查阅相关语法，也可以参阅如下链接：

[Markdown Diagrams 图表使用笔记](./markdown-note-diagrams.md)

## 12. 目录

使用 `[TOC]` 标记添加目录。

TOC 目录仅提供文章内（页内）链接，有一定局限性。

## ∞.更上一层楼

你可以使用 HTML 丰富 Markdown 功能，比如借助锚点添加页内超链接，从而形成目录。

但是建议你在掌握 Markdown 语法以及相关开发规范前，不要使用过多的 HTML 标签。
