# 10. 数组

数组是编程语言最重要的数据结构之一。  

Java 语言中提供的数组是用来存储固定大小的同类型元素。  

## 10.1 声明数组变量

如同基础变量类型一样，数组需要先声明后使用。  

```Java
dataType[] arrayRefVar;//首选方式

dataType arrayRefVar[];//效果相同，但不推荐
```

```dataType``` 表示数组变量类型，```arrayRefVar``` 表示数组的标识符

后者是 C++ 中常见的声明方式，不过实际上，C++ 也支持且推荐前者。  

 ```Java
int[] numbers;
```

## 10.2 创建数组

Java 采用 new 操作符来创建数组。  

```Java
arrayRefVar = new dataType[arraySize];
```

其中 ```arraySize``` 为数组的长度。  

如上的语法做了两件事：  

* 使用 ```dataType[arraySize]``` 创建了一个数组。  
* 把新创建的数组的引用赋值给变量 ```arrayRefVar```。  

声明与创建可以用一条语句完成。  

```Java
dataType[] arrayRefVar = new dataType[arraySize];
```

也可以使用列表初始化的方式创建数组并赋值，数组长度将等同参数数量。  

```Java
dataType[] arrayRefVar = {value0, value1, ..., valuek};
```

## 10.3 访问数组

使用下标访问数组。下标从 0 开始计数。  
