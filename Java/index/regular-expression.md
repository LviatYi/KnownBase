# 12. 正则表达式

正则表达式定义了字符串的模式。  

正则表达式可以用来搜索、编辑或处理文本。  

正则表达式并不仅限于某一种语言，但是在每种语言中有细微的差别。  

java.util.regex 包主要包括以下三个类：  

* **Pattern 类** pattern 对象是一个正则表达式的编译表示。Pattern 类没有公共构造方法。要创建一个 Pattern 对象，你必须首先调用其公共静态编译方法，它返回一个 Pattern 对象。该方法接受一个正则表达式作为它的第一个参数。  
* **Matcher 类** Matcher 对象是对输入字符串进行解释和匹配操作的引擎。与 Pattern 类一样，Matcher 也没有公共构造方法。你需要调用 Pattern 对象的 matcher 方法来获得一个 Matcher 对象。  
* **PatternSyntaxException 类** PatternSyntaxException 是一个非强制异常类，它表示一个正则表达式模式中的语法错误。  

> 以下实例中使用了正则表达式 ```.*runoob.*``` 用于查找字符串中是否包了 runoob 子串：  
>  
> ```Java
> import java.util.regex.*;
>  
> class RegexExample1{
>    public static void main(String[] args){
>       String content = "I am noob " +
>         "from runoob.com.";
>  
>       String pattern = ".*runoob.*";
>  
>       boolean isMatch = Pattern.matches(pattern, content);
>       System.out.println("字符串中是否包含了 'runoob' 子字符串? " + isMatch);
>    }
> }
> ```
>  
> 输出：  
> 字符串中是否包含了 'runoob' 子字符串? true  
