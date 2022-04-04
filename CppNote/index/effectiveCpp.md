# Effective Cpp Note

## 1. 让自己习惯 C++

### 1.1 视 C++ 为一个语言联邦

- **C** C++ 的基础。
- **Object-Oriented C++** 面向对象。
- **Template C++** 模板编程，拓展了 C++ 的泛型能力。
- **STL** 标准模板库。

### 1.2 使用 `const` `enum` `inline` 而不是 `#define`

即使用编译行为代替预处理行为。

可获得更清晰的符号跟踪。

```Cpp
const double PI = 3.1415926;
const char* const name="LviatYi";

class Class{
    static const int MAX_CAPACITY = 30;// 静态常量声明
};

const int Class::MAX_CAPACITY; //常量定义
```

> 「声明」仅建立了一个标识符。而「定义」赋予标识符空间。
>
> - 常量若只有带赋初值的声明，使用时可能采用立即数替代。
> - 这种量若无声明，取地址行为可能是未定义的。某些编译器（GCC）将报错，某些编译器（MSVC）则会通过编译。

永远不要使用宏函数，即使带了控制优先级以避免注入的括号。

```cpp
#define CALL_F_WITH_MAX(a,b) f((a) > (b) ? (a) : (b))   // NEVER

templete<typename T>
inline void CallFWithMax(const T& a, const T& b){
    f((a) > (b) ? (a) : (b));
}
```

### 1.3 尽可能使用 `const`

`const` 指定「只读」语义约束，借助编译器保障这个约束不被其他编程者违反。

- **其他编程者** 包含经历过某些时空变换的自己。

```Cpp
const typename *p;  // 指向 const 的指针。指向一个只读量。
typename * const p; // const 指针。p 本身只读。

std::vector<int>::const_iterator citer   // 指向 const 的指针。
const std::vector<int>::iterator iter   // const 指针。
```

---

#### 返回 `const` 的函数

返回 `const` 类型的函数可避免对表达式赋值。

```c++
const Number operator*(const Number& lhs, const Number& rhs);
...

Number a,b,c;
...
if( a * b = c ){}   //ERROR
```

---

#### `const` 成员函数

`const` 作用于成员函数是一种只读保证。

- 程序员可以知道哪些函数不会改动成员内容。
- 编译器也可以了解到这一点，因此允许其处理 const 对象。

> 如果两个成员函数只是常量性 (constness) 的不同，可以被 **重载** 。

`const` 修饰对于成员函数有时可能过于专制。这是 **bitwise** 的。

- `bitwise constness` 保证对象内的任何一个 bit 都不会更改。
  - 但这种保证却可能带来预期外的效果：指针。指针指向的内容并不受对象管理。
- `logical constness` 放松管制，允许对象内某些特殊的成员被改动。

`logical constness` 也是受编译器支持的，即使用 `mutable` 。`mutable` 将释放 non-static 成员的 bitwise 约束。

```c++
class CTextBlock{
public:
    std::size_t length() const;
private:
    char* pText;
    mutable std::size_t textLength;
    mutable bool lengthIsValid;
};

std::size_t CTextBlock::length() const{
    if(!lengthIsValid){
        textLength = std::strlen(pText);    // 允许的
        lengthIsValid = true;               // 允许的
    }
    return textLength;
}
```

---

#### 使用 `const_cast` 避免重复

很多时候使用 `const` 对 `non-const` 的重载，可能都包含大量的重复代码。实际上，大部分情况的 `const` 重载，只是多了限定返回类型的 `const` 关键字而已。

这个使用可以使用 `const_cast` 将 `const` 强制转换为 `non-const` ，并复用代码。

```c++
class TextBlock{
public:
    const char& operator[](std::size_t index) const{
        ...
        return text[index];
    }
    char& operator[](std::size_t index){
        return const_cast<char&>(
            static_cast<const TextBlock&>(*this)[index]
        );
    }
};
```

> 首先 `static_cast<const TextBlock&>` 强制转型为 `const` 避免自身调用。  
> 其次 `const_cast<char&>` 强制取消 `const` 。

不要反向实现，即通过 `const` 版本调用 `non-const` 版本。

- `const` 函数保证其对象的逻辑状态 (logical state) 没有改变，而调用的 `non-const` 没有这种保证。

---

### 1.4 确定对象在被使用前已被初始化

永远初始化对象，包括在任何位置的内置类型。

> 无论你对规则的记忆有多好。

在对象中，应区分 **赋值** (assignments) 与 **初始化** (initializations)。

```c++
class Student{
    string name;
    SchClass schClass;
    int age;

public:
    Student(
        const string& _name
    );
};

Student::Student(
    const string& _name
){
    this.name = _name;          // 这是赋值而非初始化。
    this.schClass = SchClass(); // 这甚至不应称为「赋初值」
    this.age = 0;
}
```

实际上，成员变量的初始化发生在调用默认构造函数之前。当进入构造函数内，其内部字段已经初始化完成（且已经发生一次赋初值行为）。

使用效率更高的 **成员初值列表** (member initialization list) 完成初始化。

```c++
Student::Student(
    const string& _name；
):  name(_name),
    schClass(),
    age(0) {};
```

这将直接调用复制构造函数代替「初始化、赋初值、再赋值」的构造过程。

对象的成员初始化具有固定的顺序，与成员初值列表无关。

- base classes 。
- 依次声明的成员变量。

---

#### 「不同编译单元内定义之 non-local static 对象」的初始化次序

`static` 对象，即所有寿命以构造为开始，以程序结束为结束的对象。包含：

- global 对象
- 定义域 namespace 作用域内的对象。
- 在 classes 内、函数内、在 file 作用域内被声明为 static 的对象。

其中：

- 函数内 static 对象称为 **local static 对象** 。
- 其他为 **non-local static 对象** 。

**编译单元** (translation unit) 指产出单一目标文件 (single obj file) 的源码。基本上是单一源码文件加上其所含入的头文件 (#include files) 。

C++ 对定义于不同编译单元内的 non-local static 对象的初始化次序没有明确定义。

因此，需要将每个 non-local static 对象声明到专属的 reference-returning 函数内。

> 类似单例模式的实现。

```c++
FileSys& getFileSysInstance(){
    static FileSys fs;
    return fs;
}
```

如此可以保证使用时对象的初始化。

但这是线程不安全的。需要在程序的单线程启动阶段 (single-threaded startup portion) 手工调用所有 reference-returning 函数，以消除与初始化有关的「竞速形势 (race conditions)」。

## 2. 构造 / 析构 / 赋值运算

### 2.5 了解 C++ 默认提供的函数与何时调用这些函数

C++ 自动提供如下成员函数（直到被调用时）：

- **默认构造函数** 如果没有定义构造函数
- **默认析构函数** 如果没有定义
- **复制构造函数** 如果没有定义
- **移动构造函数** 如果没有定义
- **移动赋值构造函数** 如果没有定义
- **赋值运算符** 如果没有定义
- **地址运算符** 如果没有定义

除非 base class 自身声明有 `virtual` 析构函数，否则提供 non-virtual 析构函数。


