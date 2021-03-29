# 8. 样式

style 属性用于改变 HTML **元素** 的样式。  

[示例 8-1](../example/8-1.html)

```HTML
<body style="background-color:PowderBlue;">

<h1>Look! Styles and colors</h1>

<p style="font-family:verdana;color:red">
This text is in Verdana and red</p>

<p style="font-family:times;color:green">
This text is in Times and green</p>

<p style="font-size:30px">This text is 30 pixels high</p>

</body>
```

style 属性提供了一种改变所有 HTML 元素样式的通用方法。  
通过 HTML 样式，能够通过使用 style 属性直接将样式添加到 HTML 元素，或者间接地在独立的样式表中（CSS 文件）进行定义。  

---

## 应使用 HTML 样式属性表现样式

HTML 语言本旨在描述文档的结构性而非表达网页制作者的审美。后来随着网络发展，更加丰富的表现形式成为了大势所趋，因此 HTML 语言增加了某些标签或属性来满足这一需求。然而这种行为却破坏了 HTML 语言的系统性。
因此引入了 HTML 样式后，一些曾经表现样式的标签或属性应避免使用。  

---

## 样例

### 文本对齐

text-align 属性规定了元素中文本的水平对齐方式。  
[样例](../example/8-2.html)

```HTML
<body>
    <h1 style="text-align:center">This is a heading</h1>
    <p>The heading above is aligned to the center of this page.</p>
</body>
```

style 属性淘汰了旧的 ```"align"``` 属性。  

### 字体，颜色和尺寸

font-family 属性定义元素中文本的字体系列；  
color 属性定义元素中文本的颜色；  
font-size 属性定义元素中文本的字体尺寸。  
[样例](../example/8-3.html)

```HTML
<body>
    <h1 style="font-family:verdana">A heading</h1>
    <p style="font-family:arial;color:red;font-size:20px;">A paragraph.</p>
</body>
```

style 属性淘汰了旧的 ```<font>``` 标签。  

### 背景颜色

background-color 属性为元素定义了背景颜色。  
[样例](../example/8-4.html)

```HTML
<body style="background-color:rgb(0, 117, 0)">
        <h2 style="background-color:greenyellow">This is a heading</h2>
        <p style="background-color:rgb(127, 192, 30)">This is a paragraph.</p>
    </body>
</body>
```

style 属性淘汰了旧的 ```"bgcolor"``` 属性。

---

## 请保持对美的敬畏
