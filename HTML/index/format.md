# 9. 格式化

## 文本格式化

使用标签将文本进行简单的格式化。  

[样例](../example/9-1.html)  

### 加粗

```HTML
<b>This text is bold</b>
```

### 加重

```HTML
<strong>This text is strong</strong>
```

### 大号

```HTML
<big>This text is big</big>
```

### 强调

```HTML
<em>This text is emphasized</em>
```

### 倾斜

```HTML
<i>This text is italic</i>
```

### 缩小

```HTML
<small>This text is small</small>
```

### 下标

```HTML
This text contains
<sub>subscript</sub>
```

### 上标

```HTML
This text contains
<sup>superscript</sup>
```

### 插入

```HTML
<ins>Insert this line</ins>
```

### 删除

```HTML
<del>Delete this line</del>
```

---

## 预格式文本

使用 ```<pre>``` 标签表示预格式文本。  

预格式文本类似编程语言中的 「Raw string」（原始字符串）。

在此标签内的文本将按照代码原型展示。  

* 除非 ```</pre>``` 不用担心冲突问题。  
* 多余空白符将会保留。

[样例](../example/9-2.html)  

```HTML
<body>
    <pre>
    这是
    预格式文本。
    它保留了      空格
    和换行。
    </pre>

    <pre>
    for i = 1 to 10
        print i
    next i
    </pre>
</body>
```

---

## 「计算机输出」标签

这些标签都采用了特殊的样式风格表现文本，不过更推荐使用 CSS style 。  

[样例](../example/9-3.html)  

### 源代码

```HTML
<code>Computer code</code>
```

### 键盘文本

```HTML
<kbd>Keyboard input</kbd>
```

### 打字机代码

```HTML
<tt>Teletype text</tt>
```

### 样本文本

```HTML
<samp>Sample text</samp>
```

### 变量

```HTML
<var>Computer variable</var>
```

---

## 地址

[样例](../example/9-4.html)  

```HTML
<address>
Written by <a href="mailto:webmaster@example.com">Donald Duck</a>.<br> 
Visit us at:<br>
Example.com<br>
Box 564, Disneyland<br>
USA
</address>
```

---

## 缩略词

当鼠标移到缩略词上时，可以显示完整提示。  

[样例](../example/9-5.html)  

```HTML
<abbr title="etcetera">etc.</abbr>
<br />
<acronym title="World Wide Web">WWW</acronym>
```

HTML5 中不支持 ```<acronym>``` 标签。请使用 ```<abbr>``` 标签代替。  

## 文字方向

使用此格式可以正序或倒序输出文本。  

[样例](../example/9-6.html)  

```HTML
<bdo dir="ltr">Here is some text</bdo>
<br/>
<bdo dir="rtl">Here is some text</bdo>
```

```"ltr"``` 属性为正序；  
```"rtl"``` 属性为倒序；  

## 长引用

长引用会增加文本左右边距，并在元素前后增加空行。  

[样例](../example/9-7.html)  

```HTML
<p>
    This is a paragraph. 
    This is a paragraph. 
    This is a paragraph. 
    This is a paragraph. 
    This is a paragraph. 
    This is a paragraph. 
    This is a paragraph. 
</p>
<blockquote>
    This is a long quotation. 
    This is a long quotation. 
    This is a long quotation. 
    This is a long quotation. 
    This is a long quotation.
</blockquote>
```
