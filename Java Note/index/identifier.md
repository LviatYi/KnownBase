# 2. 标识符

类名、变量名以及方法名被称为标识符  

## 2.1 关键字

关键字即保留字，指高级语言中已经被定义过的字，不可将其作为标识符使用。  

Java 中的关键字  

|  |  |  |  |  |
-------- | ------ | ------- | ----- | ----
abstract | assert | boolean | break | byte
case | catch | char | class | const
continue | default do | double | else
enum | extends | final | finally | float
for | goto | if | implements | import
instanceof | int | interface | long | native
new | package | private | protected | public
return | strictfp | short | static | super
switch | synchronized | this | throw | throws
transient | try | void | volatile | while

## 2.2 命名规范

（1）不能使用关键字作为标识符。  
（2）所有标识符都必须以字母 ```A-Z``` 或 ```a-z``` 、美元符 ```$``` 或下划线 ```_``` 开始。  
（3）标识符首字母后可由字母```A-Z``` 或 ```a-z```、美元符 ```$``` 、下划线 ```_``` 、数字 ```0-9``` 甚至汉字等其他语言字符组合而成。  
（4）Java 字符是大小写敏感的。  
（5）不推荐使用汉字等非英语字符，因为这样既不实用也不美观。  

合法标识符举例

```java
age  
number12  
_value  
$salary  
时间（不推荐）  
```

非法标识符举例

```java
123abc  
*abcde1234**
```

## 2.3 命名约定

一般在开发过程中，为了保证代码风格的一致性与易读性，开发者们会采用特定的代码风格区分不同类型的标识符。  

（1）所有的变量、方法、类名需要 **见名知意** 。  

```java
错误：
void function423()
{
    ...
} 

正确：
void getTime()
{
    ...
}
```

（2）**变量** 采用小驼峰命名法。即除第一个单词外，所有构成标识符的单词首字母均大写。  

```java
示例：timeNow lastName
```

（3）**常量** 采用全大写与下划线命名法。即所有字母大写，所有构成标识符的单词间用下划线连接。  

```java
示例：MAX_VALUE MIN_INT_VALUE
```

（4）**类名** 采用帕斯卡命名法。即所有构成标识符的单词首字母均大写。  

```java
示例：Student GoodMan
```

（5）**方法名** 采用小驼峰命名法。即除第一个单词外，所有构成标识符的单词首字母均大写。  

```java
示例：getTime runFunction
```
