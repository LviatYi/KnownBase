# 5. 变量与常量

## 5.1 变量

Java 中，所有变量在使用前做声明。  

声明语法：  

```java
type identifier [ = value][, identifier [= value] ...];
```

type 为变量类型  
identifier 变量名
value 为赋予的值 [ 可选的 ]
可在同一行声明多个变量，并用 ```,``` 隔开，但是强烈不建议这样做。  

根据变量的作用域，变量分为：  

* **类变量** 独立与方法之外的变量，用 ```static``` 修饰。  
* **实例变量** 独立于方法之外的变量，不用```static``` 修饰。  
* **局部变量** 类的方法中的变量。  

```java
public class variable
{
    
    int number1=11111;//实例变量 需要实例化才可使用

    static long number2=22222;//类变量 不需要实例化即可使用

    public static void main(String[] args)
    {
        int number3=10;//局部变量 必须声明和手动初始化
        System.out.println(number3);//可在作用域内直接调用

        //System.out.println(number1);//不能使用 未被实例化
        System.out.println(number2);//可在类内直接调用

        variable var1=new variable();//实例化 variable
        System.out.println(var1.number1);//可以使用
    }
}
```

## 5.2 常量

常量必须手动初始化且不能二次更改。  
在 Java 中使用 final 关键字修饰常量，声明时在变量类型前加 final 即可。  

```java
final double PI = 3.1415926;
```

一般常作为类常量使用。  

```java
static final double PI = 3.1415926;
```

修饰符间不存在先后顺序。  
