# 3. 元素

XML 文档由元素构成。  
元素由开始标签，至结束标签。  

元素可以包含：  

* 其他元素
* 文本
* 属性

## 3.1 命名规则

XML 元素遵守以下命名规则：

* 名称可以包含字母、数字以及其他字符。  
* 名称不能以数字或标签符号开始。  
* 名称不能以字母 xml 开始，包括其他大小写组合。  
* 名称不能包含空格。  

## 3.2 命名规范

注意，XML 为结构化数据而生，所以在命名时，不要花里胡哨。  

## 3.3 扩展

XML 元素是可扩展的，以携带更多信息。  

```XML
<note>
    <to>Tove</to>
    <from>Jani</from>
    <body>Don't forget me this weekend!</body>
</note>
```

如上实例，如果我们补充了一些其他信息：  

```XML
<note>
    <date>2008-01-10</date>
    <to>Tove</to>
    <from>Jani</from>
    <heading>Reminder</heading>
    <body>Don't forget me this weekend!</body>
</note>
```

程序读取时也不应崩溃。因为其仍然能够获得原有的信息。  
