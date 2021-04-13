# 11. 头部

HTML 的头部包含文档标题、作者信息、文档描述、字符集等信息。  

所有头部标签元素都由 ```<head>``` 元素包含。  

## 11.1 ```title``` 元素

```title``` 是 **必需** 的。  
```title``` 元素定义了文档的标题。  
标题用于：  

* 工具栏显示标题  
* 收藏夹显示标题
* 搜索引擎结果显示标题

## 11.2 ```base``` 元素

```title``` 元素描述了基本的链接目标，该标签作为所有链接标签的默认链接。默认链接即不需要定义 ```href``` 属性的链接。  

 ```HTML
 <base href="www.google.com" target="blank">
 ```

## 11.3 ```link``` 元素

```link``` 元素定义了文档与外部资源之间的关系。  
```link``` 元素通常用于链接到样式表。  

 ```HTML
 <link rel="stylesheet" type="text/css"  href="mystyle.css">
 ```

```link``` 元素还可以指定网页 Logo 。  

 ```HTML
 <link rel="shortcut icon" href="图片url">
 ```

## 11.4 ```style``` 元素

```style``` 元素定义了 HTML 文档的样式文件引用地址。  
在 ```style``` 元素中也可以直接添加样式来渲染 HTML 文档。  

 ```HTML
 <style type="text/css">
 body {background-color:yellow}
 p {color:blue}
 </style>
 ```

## 11.5 ```meta``` 元素

```meta``` 元素描述一些基本的元数据。  

与 XHTML 不同， HTML 中的 ```<meta>``` 标签没有结束标签。  

你可以：  

* 定义文档的字符编码。  

 ```HTML
 <meta charset="UTF-8">
 ```

* 为搜索引擎定义关键词。  

 ```HTML
 <meta name="keywords" content="HTML,Learning,Note">
 ```

* 为网页定义描述内容。  

 ```HTML
 <meta name="description" content="HTML 学习笔记">
 ```

* 定义网页作者。  

 ```HTML
 <meta name="author" content="LviatYi">
 ```

* 每 30 秒刷新当前页面。  

 ```HTML
 <meta http-equiv="refresh" content="30">
 ```

对于 ```name``` 和 ```http-equiv``` 属性，用于将 ```content``` 属性分别关联到 HTTP 头部和名称上，因此前者必然与后者搭配使用。  

## 11.6 ```script``` 元素

```script``` 元素用于加载脚本文件，如 JavaScript。  
