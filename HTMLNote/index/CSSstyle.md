# 12. CSS 样式

CSS (Cascading Style Sheets) 用于渲染 HTML 元素标签的样式。  

CSS 可以通过以下方式添加到 HTML 中：  

* **内联样式** 在 HTML 元素中使用 ```style``` 属性。  
* **内部样式表** 在 HTML 文档头部 ```<head>``` 区域使用 ```style``` 元素来包含 CSS 。  
* **外部样式表** **（常用）** 使用外部 CSS 文件。  

## 12.1 内联样式

一般，当特殊的样式需要应用到个别元素时，就可以使用内联样式。  

方法即在相关标签中使用 ```style``` 属性，其能够包含任何 CSS 属性，

 ```HTML
 <p style="color:blue;margin-left:20px;">如何更改段落的颜色和左外边距？</p>
 ```

## 12.2 内部样式表

当单个文件需要特别样式时，可以使用内部样式表。  

```HTML
<style type="text/css">
body {background-color:yellow;}
p {color:blue;}
</style>
```

## 12.3 外部样式表

当样式需要被应用到很多页面时，可以使用外部样式表。  

 ```HTML
 <link rel="stylesheet" type="text/css" href="mystyle.css">
 ```

一般，修改父级元素样式，子级元素也会改变。但有些元素却不这样。如 ```<a>``` ，此时应使用内联样式。  
