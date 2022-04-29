# 14. 表格

HTML 使用 `<table>` 标签定义表格。  

[样例](..\example\14-1.html)

```HTML
<table border="1">
    <tr>
        <th>Header 1</th>
        <th>Header 2</th>
    </tr>
    <tr>
        <td>row 1, cell 1</td>
        <td>row 1, cell 2</td>
    </tr>
    <tr>
        <td>row 2, cell 1</td>
        <td>row 2, cell 2</td>
    </tr>
</table>
```

使用 `<tr>` 标签指定行。  
在行内使用 `<td>` 标签指定列（行内的单元格）。  

## 14.1 边框

表格使用 `border` 属性控制边框。  

值为 1 时显示边框，否则不显示。  

默认不显示。  

## 14.2 表头

表格使用 `<th>` 标签替代 `<td>` 标签来定义表头。  
