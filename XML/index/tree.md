# 1. 树结构

XML 文档使用简单的具有自我描述性的语法。  

一般地，XML 文档由以下部分构成：

- 声明
- 元素及其属性
- 注释
- 实体引用
  - XML 的保留字符。
- 处理指令
  - 允许应用程序进行处理的部分。

```XML {.line-numbers} class
<?xml version="1.0" encoding="UTF-8"?>
<note>
    <to>Tove</to>
    <from>Jani</from>
    <heading>Reminder</heading>
    <body>Don't forget me this weekend!</body>
</note>
<!-- Comments -->
```

第 1 行是 XML 声明，包含 XML 版本 (1.0) 和所使用的编码 (UTF-8) 。  

第 2 行描述文档的 **根元素** ：「本文档是一个便签 (Note) 」。  
当然，末尾需要一个结束标签。  

随后 4 行描述了根的 4 个**子元素** 。  

第 8 行为文档注释，一般会被解析器无视。

## 1.1 XML 文档构成一种树形结构

XML 文档由元素构成。

元素包含：

- 开始标签与结束标签
- 属性
- 文字内容

XML 必须包含 **根元素** 。该元素是所有元素的父元素。  
而所有的元素都可以拥有子元素。  
