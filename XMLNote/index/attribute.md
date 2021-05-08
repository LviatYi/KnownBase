# 4. 属性

XML 元素具有属性，属性提供额外信息。  

属性通常提供不属于数据组成部分的信息。在下面的实例中，文件类型与数据无关，但是对需要处理这个元素的软件来说却很重要：  

```XML
<file type="gif">computer.gif</file>
```

但实际上，也许你也可以这样写

```XML
<file>
    <filename>computer.gif</filename>
    <type>gif</type>
</file>
```

一般地，如果信息看起来像数据，那么就使用元素来描述它。  
如果不能判断，请用元素。  
