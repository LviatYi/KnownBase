# C# 编码约定

## 文档用语

本文档描述约定时将采用 RFC2119 协议规范。将采用如下词汇描述规范条目的重要程度：

| 词汇                   | 含义                                       |
| ---------------------- | ------------------------------------------ |
| 必须 MUST              | 规范的绝对要求                             |
| 禁止 MUST NOT          | 规范的绝对禁止                             |
| 推荐 RECOMMENDED       | 可能存在正当理由以忽略条目，但必须权衡利害 |
| 不推荐 NOT RECOMMENDED | 可能存在正当理由以忽略条目，但必须权衡利害 |
| 可以 MAY               | 某些场合下可以选用条目                     |

本文档描述命名规范时将采用以下词汇描述命名风格：

| 词汇        | 含义                                   |
| ----------- | -------------------------------------- |
| Pascal case | 即大驼峰法，首字母大写且单词首字母大写 |
| Camel case  | 即小驼峰法，首字母小写且单词首字母大写 |

本文档描述命名规范时将采用以下词汇描述缩进形式：

| 词汇   | 含义                 |
| ------ | -------------------- |
| 四空格 | 一单位缩进为四个空格 |
| tab    | 一单位缩进为一个 tab |

本文档描述命名规范时将采用以下词汇描述括号形式：

| 词汇   | 含义           |
| ------ | -------------- |
| Allman | 前括号另起新行 |
| K&R    | 前括号置于行尾 |

```csharp
// Allman
while (x == y){
    something();
    somethingelse();
}

// K&R
while (x == y){
    something();
    somethingelse();
}
```

[RFC2119][rfc2119]

## 任何现存的项目内指定的编码约定 **_必须_** 优先于此文档执行

## 命名约定

### 用词规范

- 如非必要，任何名称 **_必须_** 使用 Ascii 码内包含的字符描述。
- 如有必要，包含的非 Ascii 码必须使用 Unicode 转义序列替换。
- 任何名称 **_禁止_** 不规则且无意义。

---

### Pascal case

#### `class`, `record`, or `struct` 的命名 **_必须_** 使用 Pascal case

```Csharp
public class Student{
}
```

#### `interface` 的命名 **_必须_** 使用 Pascal case，且添加 `I` 前缀

```Csharp
public interface IWalkable{
}
```

#### `public` 成员（字段、事件）的命名 **_必须_** 使用 Pascal case

```Csharp
public class Student{
    public String Name;
}
```

- `record` 成员的所有参数命名都 **_必须_** 使用 Pascal case，因为它们是公共属性。

#### 所有方法与属性的命名 **_必须_** 使用 Pascal case

```Csharp
public class Student{
    public void Speak();
}
```

#### 所有常量变量或字段的命名 **_必须_** 使用 Pascal case

---

### Camel case

#### `private` 或 `internal` 字段的命名 **_必须_** 使用 Camel 法，并添加 `_` 前缀

```Csharp
public class Student{
    private String _userPassword;
}
```

#### 方法参数 **_必须_** 使用 Camel case

```csharp
public T SomeMethod<T>(int someNumber, bool isValid){
}
```

---

## 编码风格

### 缩进

#### **_推荐_** 使用四空格表示缩进

#### 默认 **_推荐_** 使用 K&R 法处理括号

#### **_禁止_** 单语句使用单行形式

应使用：

```Csharp
if (false)
    return null;
```

---

## 编程素质

### 语言行为

#### 所有字段 **_必须_** 声明于类型声明最上方

#### **_推荐_** 尽可能地使用 `readonly`

#### **_必须_** 使 `static` 在前而 `readonly` 在后

```csharp
public static readonly String Name = "LviatYi";
```

#### **_推荐_** 尽可能避免 `this.`

如非必要，不要使用 `this.`

#### **_必须_** 指定可见性

即使有默认值，也要指出 `public` `private` `protected` 或 `internal`

#### 可见性 **_必须_** 是第一个修饰符

```csharp
public static readonly String Name = "LviatYi";
```

#### **_不推荐_** 超过两行空行

#### **_不推荐_** 出现多余空格

#### **_推荐_** 仅在等式右侧显式可见时使用 `var`

通常是由于 new 或显式转换。

#### **_推荐_** 使用 `$String` 而非 `String+varible`

```csharp
// 推荐
String str = $"Hello world,{name}";
// 不推荐
String str = "Hello world," + name;
```

#### **_推荐_** 使用简洁的 `new()` 实例化对象

```csharp
// 推荐
Student stu = new();
// 不推荐
Student stu = new Student();
```

## 参考文档

[Microsoft | C# Code Convention][csharpcodeconvention]  
[Github Dotnet Styleguide][dotnetstyleguide]

[rfc2119]: https://www.rfc-editor.org/rfc/rfc2119.txt
[csharpcodeconvention]: https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/coding-style/coding-conventions
[dotnetstyleguide]: https://github.com/dotnet/runtime/blob/main/docs/coding-guidelines/coding-style.md
