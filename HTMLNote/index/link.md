# 10. 链接

HTML 使用超链接将不同的文档相连。  

HTML 使用标签 ```<a>``` 来设置超链接。  

```HTML
<a href="url"> 链接文本 </a>
```

```href``` 属性用于描述链接的目标。  

[样例](../example/10-1.html)

 ```HTML
<a href="https://twitter.com/">川普的办公室</a>
```

## 10.2 常用属性

### 10.2.1 ```target``` 属性

使用 ```target``` 属性，可以定义被链接的文档在何处显示。  

 ```HTML
<a href="https://twitter.com/" target="_blank">川普的办公室</a>
 ```

这将会在新窗口打开链接指向的网页。  

### 10.2.1 ```id``` 属性

```id``` 属性用于在 HTML 文档中创建书签标记。  

书签对于用户来说是 **隐藏** 的。  

 ```HTML
<a  id=[id名]>显示文本</a>
 ```

可以使用链接将网页定位到书签。  

 ```HTML
 <a href="#[id名]">显示文本</a>
 ```

也可以链接到其他网页的书签。  

 ```HTML
 <a href="url#[id名]">显示文本</a>
 ```

若要访问的是文件夹，请在标注 ```/```。而若访问的是文件，则不要标注 ```/``` 。  
> HTML 请求时并不知道要找的是文件还是文件夹，若没有斜杠而找文件夹时， HTML 会失败请求一次，并再次添加斜杠以请求文件夹。  

如 ```href="https://www.runoob.com/html/```

## 10.2.3 ```mailto``` 属性

点击即可发邮件。  

 ```HTML
<a href=mailto:LviatYi@qq.con>send I love U</a>
```

还有如下参数：  

属性参数 | 功能
:------: | :-------:
 to |  收信人
 subject |  主题
 cc |  抄送
 bcc |  暗送
 body |  内容
