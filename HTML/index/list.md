# 15. 列表

HTML 支持有序、无序和定义列表。  

## 15.1 无序列表

HTML 使用 `<ul>` (unorder list) 标签创建无序列表。  
使用 `<li>` (list item) 标签定义列表项。  

> * Coffee
> * Milk

```HTML
<ul>
<li>Coffee</li>
<li>Milk</li>
</ul>
```

## 15.2 有序列表

HTML 使用 `<ol>` (order list) 标签创建有序列表。  
使用 `<li>` 标签定义列表项。  

> 1. Coffee
> 2. Milk

```HTML
<ol>
<li>Coffee</li>
<li>Milk</li>
</ol>
```

## 15.3 自定义列表

HTML 使用 `<dl>` (order list) 标签创建自定义列表。  
使用 `<dt>` (definition term) 标签定义列表项。  
使用 `<dd>` (definition description) 标签定义列表项内容。  

```HTML
<dl>
<dt>Coffee</dt>
<dd>- black hot drink</dd>
<dt>Milk</dt>
<dd>- white cold drink</dd>
</dl>
```
