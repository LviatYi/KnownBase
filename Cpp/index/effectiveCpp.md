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
    this->name = _name;          // 这是赋值而非初始化。
    this->schClass = SchClass(); // 这甚至不应称为「赋初值」
    this->age = 0;
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

除非基类自身声明有 `virtual` 析构函数，否则提供 non-virtual 析构函数。

---

#### 若类内含有 reference 或 const 成员，需手动支持赋值操作

C++ 不允许修改 reference 的指向目标，因为修改目标的数据占用了这个语法。

```c++
Name name1 = Name("Jun");
Name name2 = Name("Zhi");
Name& nameR = name1;

nameR = name2;  // 这将修改 name1 内容，而非使 nameR 指向 name2
```

---

#### 若基类声明赋值运算为 `private` ，则子类不会自动提供赋值运算

自动生成的赋值运算需要依赖基类赋值运算。

### 2.6 若不想使用编译器自动生成函数，应明确拒绝

将明确不需要自动生成的函数声明为 `private` 。

且不要实现之。

前者将在编译期拒绝外部调用，后者将在链接期拒绝内部及友元调用。

构建一个 Uncopyable 类并继承之，可以将拒绝内部及友元调用的警告提前至编译期。

```c++
class Uncopyable{
protected:
    Uncopyable(){};
    ~Uncopyable(){};
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class Sth: private Uncopyable{
    ...
};
```

### 2.7 为多态基类声明 virtual 析构函数

如果一个类作为基类，且带有至少一个虚函数，则一定要为之声明 virtual 析构函数。

否则藉由基类指针释放子类对象时，将造成「局部销毁」而内存泄露。

当一个类带有虚函数时，将生成一个 **vptr** (virtual table pointer)。其指向一个由函数指针构成的数组，称为 **vtbl** (virtual table) 。

- 实际被调用的函数取决于该对象的 vptr 所指的 vtbl ，编译器将在其中寻找适当的函数指针。
- 若类含虚函数，其对象的体积将会增加。

因此不要为非多态基类（即不包含虚函数的基类）声明 virtual 析构函数。

> 如 2.6 中的 Uncopyable 类。  
> 这种类不会作为基类指针使用，因此其不具备多态性。

由于 C++ 缺乏禁止派生的机制，因此一般约定：

- 不允许继承不带 virtual 析构函数的类。

#### 抽象类与析构函数

作为抽象类，应有：

- 带有 **纯虚析构函数** 。
- 为纯虚析构函数提供的一个定义。

纯虚函数是可以拥有定义的，且纯虚析构函数将被子类析构函数调用，如无定义则将发生链接错误。

### 2.8 不要向析构函数外抛出异常

一般有两种方案解决析构函数抛出异常：

- 记录并调用 `abort()` 终止。
- 仅记录。

```c++
DBConn::~DBConn(){
    try{ db.close(); }
    catch(...){
        // 记录
        std::abort();
    }
}
```

```c++
DBConn::~DBConn(){
    try{ db.close(); }
    catch(...){
        // 记录
    }
}
```

但是这两种方式都无法对「导致 close 抛出异常」的情况做出反应。

因此有如下解决方案，以向客户提供处理错误的机会：

```c++
class DBConn{
public:
    void close(){
        if( !closed ){
            db.close();
            closed = true;
        }
    }
    ~DBConn(){
        if( !closed ){
            try{ db.close();}
            catch{
                // 记录
                ...
                // 吞下异常或继续
            }
        }
    }
private:
    DBConnection db;
    bool closed;
};
```

### 2.9 绝不在构造和析构过程中调用 virtual 函数

调用子类的构造函数与析构函数时，会调用父类的构造函数与析构函数。具体有如下顺序：

- 先调用父类构造函数，再调用子类构造函数。
- 先调用子类析构函数，再调用父类析构函数。

明显，在父类的构造函数与析构函数中，首先子类是不可见的，其次子类的成员也并为初始化，因此调用子类的虚函数是不可行且不安全的。

因此，不应在构造和析构 **过程** 中调用虚函数。这个过程包括构造和析构函数本身及其调用的其他函数。

### 2.10 令 `operator=` 返回一个 reference to `*this`

对于内置类型，可以使用连锁赋值：

```c++
int x,y,z;
x = y = z = 15;
```

由于赋值运算符具有 R-L 结合性，因此从右开始运行，即：

```c++
int x,y,z;
x = (y = (z = 15));
```

对于重载了赋值运算符的自定义类型，也应使其保持这种特性。因此赋值运算符必须返回一个 reference 指向运算符的左侧实参。

此条同样适用于 `+=` `-=` 等其他赋值相关运算符。

### 2.11 在赋值运算符中处理「自我赋值」

自我赋值可能是潜在的、难以避免的。

```c++
a[i] = a[j]
```

但自我赋值可能会造成严重的问题，如内存泄露，其常发于指针对象。

```c++
Widget& Widget::operator=(const Widget& rhs){
    delete this->pb;
    this->pb = new WidgetContent(*rhs.pb);   // 若为自我赋值则出现问题。
    return *this;
}
```

传统做法采用 **证同测试** (identity test) 检验是否自我赋值。

方法一（证同测试）：

```c++
Widget& Widget::operator=(const Widget& rhs){
    if( this == &rhs) return *this;

    delete this->pb;
    this->pb = new WidgetContent(*rhs.pb);
    return *this;
}
```

传统方法虽然解决了「自我赋值安全性」，但仍不具备「异常安全性」。

- 可能处于其他原因，指针指向的内容仍为空（内存未成功分配等）。

如果解决「异常安全性」，则「自我赋值安全性」也将被避免。

方法二：

```c++
Widget& Widget::operator=(const Widget& rhs){
    WidgetContent* pOrig = this->pb;
    this->pb = new WidgetContent(*rhs.pb);
    delete pOrig;
    return *this;
}
```

方法三（copy and swap 技术）：

```c++
class Widget{
    void swap(Widget& rhs);
}

Widget& Widget::operator=(const Widget& rhs){
    Widget temp(rhs);
    swap(temp);
    return *this;
}
```

可缩写为：

```c++
class Widget{
    void swap(Widget& rhs);
};

Widget& Widget::operator=(Widget rhs){
    swap(rhs);
    return *this;
}
```

不清晰但编译器可能会生成更高效的代码。

### 2.12 赋值对象时不要忘记每个成分

拷贝构造函数与赋值函数统称 copying 函数。

有如下代码：

```c++
class Derived: public Base{
public:
    Derived(const Derived& rhs);
    Derived& operator=(const Derived& rhs);
private:
    int num;
}

Derived::Derived(const Derived& rhs):num(rhs.num){};
Derived& Derived::operator=(const Derived& rhs){
    this->num = rhs.num;
};
```

如上 copying 函数只顾及了子类中的内容，而忽视了对基类内容的拷贝。

应改为：

```c++
class Derived: public Base{
public:
    Derived(const Derived& rhs);
    Derived& operator=(const Derived& rhs);
private:
    int num;
}

Derived::Derived(const Derived& rhs):Base(rhs),num(rhs.num){};
Derived& Derived::operator=(const Derived& rhs){
    Base::operator=(rhs);
    this->num = rhs.num;
};
```

注意两个不同的 copying 函数在实现上的语法区别。

通过两者之间相互调用以避免代码重复是不合理的。

可以通过抽取公共操作，定义新的成员函数 (init) 消除代码重复。

### 3.13 以对象管理资源

对象在作用域结束时将被自动析构。将资源放入对象，可实现自动管理。

使用类指针对象（智能指针）封装指针，可以实现对象指针的自动管理。

```c++
void f(){
    std::shared_ptr<Student> pStu(createStuInstance());
}
```

**RAII 原则** (Resource Acquisition Is Initialization)：

- 获得资源后立即放入管理对象
- 管理对象运用析构函数确保资源被释放。

#### 不要将动态内存分配得到的数组作为智能指针的初始化形参

智能指针底层使用 `delete` 而非 `delete[]` 释放资源。因此以下行为将引发不可见的预期外错误。

```c++
std::shared_ptr<std::string> strs(new std::string[10]);
```

### 3.14 警惕资源管理类中的 copying 行为

智能指针只可以满足 heap-based 资源的自动管理。若智能指针无法满足需求，则可以建立自己的资源管理类。

对于互斥器对象有如下锁相关函数：

```c++
void lock(Mutex* pm);
void unlock(Mutex* pm);
```

为确保资源被正确的释放，则需要使用类似指针管理的机制在资源析构后自动调用解锁。

```c++
class Lock {
public:
    explicit Lock(Mutex* pm): mutexPtr(pm){
        lock(mutexPtr);
    }
    ~Lock() { unlock(mutexPtr); }
private:
    Mutex* mutexPtr;
};
```

客户将使用如下方式调用：

```c++
Mutex m;
...
{
    Lock ml(&m);
    ...
}
```

对于其复制行为，一般如下解决方案：

- 禁止复制
  - 许多情况下复制 RAII 对象是不合理的。
- 使用「引用计数法」(reference-count)

  - 可以在 RAII 对象中内含一个 shared_ptr 即可完成。
  - shared_ptr 允许自定义删除器 (deleter) 。

    - 删除器用于替代 shared_ptr 的默认删除行为，是一个函数或函数对象。

    ```c++
    class Lock {
    public:
        explicit Lock(Mutex* pm): mutexPtr(pm,unlock){
            lock(mutexPtr.get());
        }
        // 依赖编译器生成析构函数。将自动调用 non-static 成员变量的析构函数。
    private:
        std::shared_ptr<Mutex> mutexPtr;
    };
    ```

- 复制底部资源
  - 即深拷贝。将资源本身也生成副本并赋予复制对象。
- 转移所有权
  - 有时需求需要确保永远只有一个 RAII 对象指向一个未加工资源。
  - 则可交换底层指针所指对象。

若无自定义的 copying 函数，编译器则将自动生成。这可能出乎预期。

### 3.15 在资源管理类中提供对原始资源的访问

使用资源管理类封装资源后，需要为其提供暴露资源的 API 以提供资源访问。

可以提供显式转换或隐式转换。

显式转换：

- 提供 `.get()` 方法，返回资源指针。
- 重载指针取值操作符 `->` `*` 。

如上方案 C++ smart pointer 都有提供。

隐式转换：

```c++
class Font{
public:
    operator FontHandle() const{    // RAII
        return f;
    }
private:
    FontHandle* f;                  // Resource
};
```

隐式转换将提供便利，但同时将增加风险。

```c++
Font f1(getFont());
...
FontHandle f2 = f1;     // 可能是非预期的错误。
```

是否提供隐式转换函数需要进行更多考量。

### 3.16 成对使用 new 和 delete 时要采取相同形式

`new []` 需要与 `delete[]` 搭配，这是很基础的语法规则。

需要特别留意 `typedef` 定义的别名是否为数组形式。

一般约定不要使用 `typedefs` 即类似：

```c++
typedef std::string AddressLines[4];
```

### 3.17 以独立语句将 newed 对象置入智能指针

设有如下函数：

```c++
int priority();     // 一个普通的函数。用于计算程序优先权。
void processWidget(std::shared_ptr<Widget> pw,int priority);
```

有如下调用：

```c++
processWidget(std::shared_ptr<Widget>(new Widget),priority());
```

C++ 对参数计算顺序是未标准化的。只能保证 `Widget` 初始化优先于 `shared_ptr<Widget>` 的初始化。

若有如下顺序：

```c++
new Widget;
priority();
shared_ptr<Widget>();
```

若 `priority()` 发生异常，将造成资源泄露。

因此有如下原则：

不能分离 **资源创建** 与 **资源封装** 。

```c++
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw,priority());
```

## 4. 设计与声明

> 强迫用户记住规则不是好的设计。  
> 记得照顾其他程序员的感受，为他们带去更多便利。  
> 不要目光短浅，做个好人。

### 4.18 让接口容易被正确使用，不易被误用

#### 通过外覆类型避免不明确的参数

有如下接口：

```c++
class Date{
public:
    Date(int month, int day, int year);
}
```

对于用户而言， `(int, int, int)` 参数列表可能很不直观。

可以定义外覆类型 (wrapper types) 。

```c++
struct Day{
    explicit Day(int d):val(d){};
    int val;
};
```

使用 `Day` 替换 `int` 以预防不明确的参数传递。

扩展至类以定义更多约束规则。

```c++
class Month{
public:
    static Month Jan(){
        return Month(1);
    }
    ...
    static Month Dec(){
        return Month(12);
    }

private:
    explicit Month(int m):val(m){};
}
```

使用函数替换静态成员请参考 **条款 4** 。

> 使用 enum 不具备类型安全性，例如 enum 可被作为 int 使用。

代价是膨胀的代码。

---

#### 尽量使 type 行为与内置 type 一致

一般人清楚如下行为是不可行的：

```c++
int a, b;
a * b = 10;
```

除非有更好理由，不要允许类似封装 types 有类似行为。

如 **条款 3** 所述，以 `const` 修饰 `operator*` 的返回类型可避免如下错误：

```c++
if (a * b = c) ...
```

---

#### 让行为具有一致性

在代码里同时使用英文词汇、汉语拼音以及各自的缩写作为命名是灾难性的。

同样的，接口也是如此。

一个反例，在 Java 中：

- 对于数组，有 `length` 属性。
- 对于 `String` 有 `length` 方法。
- 对于 `List` 有 `size` 方法。

言行如一的人是可靠的，不会给周围人带去更多不必要的麻烦。

---

#### 返回智能指针而不是普通指针

强迫客户将返回值存储于一个资源管理类中，可以避免很多资源泄露。

使用 `shared_ptr` 并定义删除器，可以强定义析构行为。

同时，使用 `shared_ptr` 与删除器可以避免 **cross-DLL problem** 。

- 这指一个动态分配内存的指针在不同的 DLL 文件中做了 `new` 与 `delete` 行为。
- 不同 DLL 文件可能编译自不同环境，因而 `new/delete` 的行为一致性是不保证的。

而 `shared_ptr` 将追踪删除器记录，确保 `new` 与 `delete` 来自同一个 DLL 文件。

### 4.19 设计 class 犹如设计 type

一个好的 type 具有如下目标：

- 自然的语法
- 直观的语义
- 一或多个高效实现品

设计 class 时要谨慎考虑如下问题：

- 新 type 的对象应该如何被创建和销毁。
  - 这将决定以下函数的设计：
    - 构造函数
    - 析构函数
    - 内存分配函数
    - 释放函数
- 对象的初始化和对象的赋值该有怎样的差别。
  - 这将决定以下函数的行为与差异：
    - 构造函数
    - 赋值操作符
- 新 type 的对象如果被 **值传递** 意味着什么。
  - 这将决定 拷贝构造函数。
- 新 type 的 **合法值** 是什么。
  - 这将决定 成员变量的约束条件（定义域）。
  - 这往往在 构造函数、赋值操作符与 setter 函数 中进行错误检查。
- 新 type 需要配合某个继承图系 (inheritance graph) 吗。
  - 如果继承，则留意函数是否是 virtual 的。
  - 如果允许被继承，则留意函数（特别是析构函数）是否需要声明为 virtual 。
- 新 type 需要什么转换。
  - 是否允许与其他 type 进行转换。
  - 是否允许隐式转换。
- 新 type 需要什么合理的操作符与函数。
  - 决定哪些函数是需要的。
  - 且哪些函数是 member 的。
- 应该驳回什么样的标准函数。
  - 决定哪些函数是 private 的。
- 新 type 的哪些成员可被哪些角色取用。
  - 决定成员变量的可见性。
  - 决定哪个 class 和 function 是友元的。
- 新 type 的「未声明接口」 (undeclared interface) 是什么。
  - 它对效率、异常安全性以及资源运用（多任务锁定和动态内存）提供什么保证。
- 新 type 有多么一般化。
  - 究竟需要新 type 还是新的 class template。
- 真的需要这个新 type 吗。
  - 也许一个或多个 non-member 函数或 templates 即可达到目标。

### 4.20 优先使用 pass-by-reference-to-const 而非 pass-by-value

缺省情况下，C++ 以值传递将对象传递至（或来自）函数，除非另外指定。

传入值即实参的副本，由对象的 copy 构造函数生成。这可能造成昂贵的时空成本。

值传递意味着原传入值不被改变，而 `const reference` 也提供这种保证。而且还有如下两个好处：

- `const` 是更明确的声明。
- 引用传递具有更优的性能。
- 引用传递不会发生 **对象切割** (slicing) 。

对象切割指：将子类对象作为参数值传递给父类形参，将调用父类构造函数。这意味着子类对象将退化为父类对象。

一般地，编译器使用指针实现引用。

对于如下类型值传递可能拥有更优越的性能：

- 内置类型
- 迭代器
- 函数对象

但自定义类型最好避免值传递。

### 4.21 函数必须返回对象时，不要返回引用

- 存放结果的对象一般不会由参数提供给函数。
- 存放结果的对象若由函数定义，则其为一个 local 成员。它将在作用域外销毁。
- 若在函数内使用动态内存分配，这对客户形成了极大的内存泄露风险。

因此通过复制返回新对象是唯一可行解。

```c++
inline const Number operator*(const Number& lhs,const Number& rhs){
    return Number(lhs.val * rhs.val);
}
```

实际上，编译器可能施行优化，以改善目标码运行效率。这种操作可能会将返回值的构造和析构过程安全地消除。

作为成员函数，可以返回对象自身引用，即 `*this` ，以实现链式运算。

### 4.22 将成员变量声明为 private

将成员变量声明为 private 将使对象拥有以下优点：

- **一致性** 只允许客户通过成员函数访问对象。
  - 此条维护了 **条款 18** 的一致性观点。即用户不需要纠结访问 class 成员是否该使用 `()` ，因为所有可访问的接口都是函数。
- **细微划分访问控制** 定义 `getter/setter` （访问器）控制对成员变量的读写行为。
  - 使变量可以在读写性上有更多可能。
  - 可藉由访问器添加约束性条件。
- **封装性** 其后维护代码时，某些成员变量可能变化为 **计算属性** ，即通过函数得出的量，这种变化对于客户端不会带来更多负担。

封装性与「当其内容改变时可能造成的代码破坏量」成 **反比** 。

一致性与细微划分访问控制对于 `protect` 来说同样适用。

而 `protect` 相比于 `public` 并不会带来更好的封装性。

修改一个 `public` 成员，对用户代码是毁灭性的。  
修改一个 `protect` 成员，对 derived class 是毁灭性的。

同样是改动大量代码， `protect` 并不比 `public` 拥有更多封装性。

对于可见性，只有两种：

- 提供封装 `private`
- 不提供封装

### 4.23 优先采用 `non-member` 且 `non-friend` 而非 `member` 或 `friend` 函数

#### 更好的封装性

面向对象守则要求，数据尽可能地被封装。

优先采用 `non-member` 且 `non-friend` 函数具有如下优点：

- 其具有更好的封装性。
- 其具有更优的包裹弹性 (packaging flexibility)。

封装意味着不可见。越多属性被封装，则越少第三者能看到它。而越少的第三者看到它，意味着开发者拥有更大的弹性修改它，因为改变造成的影响因封装而降至最低。

并非所有类都为了封装性而存在，因此「成为 class 的 `non-member`」并不意味着它「不可以是另一个 class 的 `member`」。

对于 Java ，C# 而言，一切皆为对象。可以令 `non-member` 函数成为某个工具类的 `public static` `member` 函数。而对于 C++ 而言，可以仅使之成为 `non-member non-friend` 函数，并使之位于合适的 `namespace` 内。

#### 更好的切割性

将 `non-member non-friend` 函数置于指定的 `namespace` 且声明于不同的头文件中，则可以带来更好的切割性。

用户可以不引入不使用的函数，也可以在包含相同 `namespace` 的头文件声明新的函数以扩展功能。

### 4.24 若所有参数皆需类型转换，请为此采用 `non-member` 函数

设存在一个有理数 (Rational) 类型：

```c++
class Rational{
public:
    Rational(   int numerator = 0,      // 允许 int-to-Rational 隐式转换。
                int denominator = 1);
    int numerator() const;              // 分子
    int denominator() const;            // 分母
}
```

其含有对乘号 `*` 的重载。若将其定义为 `member` 函数：

```c++
class Rational{
    ...
public:
    const Rational operator*(const Rational& rhs) const;
}
```

对于有理数而言，将其与一个 `int` `long` `float` `double` 相乘非常合理。

而上种实现难以满足这种需求。至少不能满足一半。

```c++
result = Rational(10) * 5;  //allowed
result = 5 * Rational(10);  //not allowed
```

只有当参数被列于参数列中 (parameter list) ，才允许发生隐式类型转换。

因此有如下解决方案，使之成为 `non-member` 函数：

```c++
const Rational operator*(const Rational& lhs, const Rational& rhs);
```

> 为了引出友元函数，「C++ Primer Plus」使用为此函数赋予友元属性，解决上述难题。

然而优秀的哲学观要求尽量避免友元函数。如果使用 public 接口足以解决问题，则应使之成为 `non-member non-friend` 函数。

### 4.25 考虑写出一个不抛异常的 `swap` 函数

所谓 `swap` 函数，指将两对象的值彼此赋予对方。

标准库提供了类似如下的 `swap` 算法：

```c++
template<typename T>
void swap(T& a,T& b){
    T temp(a);
    a = b;
    b = temp;
}
```

这涉及了一次 `copy` 构造与两次赋值运算，这可能带来性能问题。

设有如下 pimpl (pointer to implementation) 类：

```c++
class WidgetImpl {
private:
    int a, b, c;
    vector<double>v;
};

class Widget {
private:
    WidgetImpl* widget_impl_;
};
```

显然，对于其 swap 行为仅需要 swap 指针内容即可。但我们一般定义其 copying 函数为深拷贝。参考 **条款 14** 。这意味着会有多余的复制行为。

于是有如下解决方案：

```c++
class WidgetImpl {
private:
    int a, b, c;
    vector<double>v;
};

class Widget {
public:
    void swap(Widget& other) {
        std::swap(this->widget_impl_, other.widget_impl_);
    }
private:
    WidgetImpl* widget_impl_;
};

void swap<Widget>(Widget& lhs, Widget& rhs) {
    lhs.swap(rhs);
}
```

但如果 Widget 为模板类，则依习惯可能有如下错误代码：

```c++
// ERROR CODE
template<typename T>
class WidgetImpl {
public:
private:
    int a, b, c;
    vector<T>v;
};

template<typename T>
class Widget {
public:
    void swap(Widget& other) {
        std::swap(this->widget_impl_, other.widget_impl_);
    }
private:
    WidgetImpl<T>* widget_impl_;
};

// 对 std::swap 的特化
template<typename T>
void swap<Widget<T>>(Widget<T>& lhs, Widget<T>& rhs) {
    // ERROR: Function template partial specialization is not allowed
    // ERROR: 不允许模板函数的偏特化
    lhs.swap(rhs);
}
```

也许重载函数是个解决方法。

```c++
// 对 std::swap 的重载
template<typename T>
void swap(Widget<T>& lhs, Widget<T>& rhs) {
    // 注意函数重载与函数特化的区别
    lhs.swap(rhs);
}
```

但 `namespace std` 并不允许开发者添加新的 `templates` `classes` 或 `functions` （重载即意味着添加新的 `templates` ），只能全特化 `std` 内的 `templates`。因此应该将 `swap` 置入 `Widget` 所在的命名空间内，其既不是 `std::swap` 的重载，也不是 `std::swap` 的特化。

```c++
namespace WidgetStuff{
    template<typename T>
    class Widget{...}

    template<typename T>
    void swap(Widget<T>& lhs, Widget<T>& rhs){lhs.swap(rhs);}
}
```

如果仅仅这样做而没有对 `std::swap` 进行特化，则意味加入限定名的 `std::swap()` 调用无法调用优化后的版本。但加入了限定名的调用非常常见。其可能出现在：

- 未知程序员无意识的限定。
- 标准库的模板实现。

因此对于 `swap` ，总结有如下方法论：

- 如果缺省的 `swap` 有足够的效率，则不要自行实现 `swap` 函数。
- 提供一个 `public swap` 成员函数，其针对性地优化了 `swap` 过程，且绝不应该抛出异常。
- 在 `class` 或 `template` 所在的命名空间内提供一个 `non-member swap` ，并令其调用 `swap` 成员函数。
- 如果是一个 `class` 而非 `class template` ，则特化 `std::swap` 。

作为使用者，在调用 `swap()` 函数前应 `using std::swap`

对于为何不应该抛出异常：

- `swap` 应为其 `class` （或 `class template` ）提供异常安全性 (exception-safety) 保障。
- 一般地，高效率的 `swap` 基于内置类型操作，本身便不会抛出异常。

## 5. 实现

### 5.26 尽可能延后变量定义式的出现时间

应留意声明变量所带来的构造与析构成本。

- 如果用不到，就不要提前声明。
- 如果可以，直接在构造时赋值。

```c++
// Worse
string encryptPassword(const string& password){
    string encrypted;
    if(password.length() < MinimumPasswordLength){
        throw ...
    }
    ...
    return encrypted;
}
```

```c++
// Better
string encryptPassword(const string& password){
    if(password.length() < MinimumPasswordLength){
        throw ...
    }
    string encrypted = encrypt(password);
    ...
    return encrypted;
}
```

对于声明放置在循环内还是循环外，有如下时空花费参考：

```c++
Student stu1;
for(int i = 0 ;i < n ;i++){
    stu1 = k;
    Student stu2(k);
}
```

- **循环外** $1$ 个构造函数 + $1$ 个析构函数 + $n$ 个赋值操作
- **循环内** $n$ 个构造函数 + $n$ 个析构函数

另仍要考虑到循环外方案的副作用，即使变量的作用域扩大，是否可能损害程序的可理解性与易维护性。

因此除非 **同时满足** 以下两条件：

- 赋值成本比一组「构造 + 析构」成本更低。
- 所构建的模块对效率要求高 (performance-sensitive) 。

应采用循环外，否则采用循环内。

### 5.27 尽量少做转型动作

请保证「类型错误」绝不可能发生！

C++ 提供四种新式转型 (C++-style casts)。

- const_cast<T>( expression )
  - cast away the constness
  - 消除对象的常量性。
- dynamic_cast<T>( expression )
  - safe downcasting
  - 安全向下转型。
  - 决定某对象是否归属其继承体系中的某个类型。
  - 耗费大量运行成本。
- static_cast<T>( expression )
  - implicit conversions
  - 强迫隐式转换。
  - 可为对象赋予常量性（`non-const` >> `const`）。
  - 允许向上转型。
    - 包括转型至空指针。
  - 允许向下转型。
    - 包括将空指针转型。
  - 允许基本类型间转型。
- reinterpret_cast<T>( expression )
  - 允许任何转型。
  - 低级转型，**及其危险** 。
  - 实际结果取决于编译器，**不可移植** 。

使用新式转型有如下好处：

- 在代码中是人机易读的（包括人工辨识与 grep 等工具）。
- 细化转型动作的作用，使编译器更易于诊断出错误的应用。

#### 对象布局永远当成非预期的

由于多重继承（菱形继承）的存在，一个对象可能拥有一个以上的地址指向它。

```c++
class Base1{}
class Base2{}
class Derived:public Base1,public Base2{}
...
Derived* instance = new Derived{};                          //0x013D80D0
Base1* instance_base_1 = static_cast<Base1*>(&instance);    //0x013D80D0
Base2* instance_base_2 = static_cast<Base2*>(&instance);    //0x013D80D8
```

这意味着指针在包含继承关系的转型中，会有一个偏移量（offset）在运行期被施加于原指针之上，以确定新的指针位置。不仅是多继承，即便是单继承也有可能发生偏移行为。

对象的布局方式与地址计算方式随编译器的不同而不同。不要自信于了解对象的布局方式。

#### 转型是值返回

如下代码可能造成预期外行为：

```c++
class Window{
public:
    virtual void onResize(){...}
    ...
};

class SpecialWindow:public Window{
public:
    virtual void onResize(){
        static_cast<Window>(*this).onResize();  // 期待先调用父类 onResize()
        ...
    }
};
```

由于转型是值返回，因此预期中所调用的父类的 `onResize()` 实际上来自一个父类的副本。这可能是预期外的。

明确使用如下方式调用父类函数。

```c++
class SpecialWindow:public Window{
public:
    virtual void onResize(){
        Window::onResize();  // 调用自身父类 onResize()
        ...
    }
};
```

#### 即便是有合理理由，也尽量避免 `dynamic_cast`

`dynamic_cast` 的效率很低，与其实现版本中包含的「`class` 名称的字符串比较」有关。

一般 `dynamic_cast` 有如下使用场景：

期待调用一个认定为 `derived class` 的 `derived` 函数，但只能取得一个指向 `base` 的指针或引用。

```c++
// Original code
class Derived: public Base{
public:
    void ind_fun(){}
}
...
vector<shared_ptr<Base>> bases;
...
for(auto iter = bases.begin();
iter != bases.end();
++iter){
    if(Derived* pd = dynamic_cast<Derived*>(iter->get())){
        pd->ind_fun();
    }
}
```

有两个一般性方法可以解决问题：

- 使用容器并在其中存储直接指向 `derived class` 对象的指针（通常是智能指针），以消除「通过 `base class` 接口处理对象」的需要。

```c++
// Optimized code1
class Derived: public Base{
public:
    void ind_fun(){}
}
...
vector<shared_ptr<Derived>> deriveds;
...
for(auto iter = deriveds.begin();
iter != deriveds.end();
++iter){
    (*iter)->ind_fun();
}
```

> LviatYi 2022.04 注：这是否有点太理想化。如果存在继承，则必然要考虑其他派生类。这样丧失了面向抽象编程的特性。

- 将必要的接口在父类中提供。类似设计模式中的 **透明组合模式** 。
  - 在 `base class` 中提供派生类需要调用的函数。
  - 在 `base class` 中提供缺省实现。

```c++
// Optimized code2
class Base{
    virtual void ind_fun(){};   // 缺省实现，什么也不做
}

class Derived: public Base{
public:
    void ind_fun(){}
}
...
vector<shared_ptr<Base>> bases;
...
for(auto iter = bases.begin();
iter != bases.end();
++iter){
    (*iter)->ind_fun();
}
```

以上两种方法旨在尽力提供 `dynamic_cast` 的替代方案，并不适用于所有情况。

绝对应该避免的是 **连串 (cascading) `dynamic_cast`** ：

```c++
for(auto iter = bases.begin();
iter != bases.end();
++iter){
    if(Derived1* pd = dynamic_cast<Derived1*>(iter->get())){...}else if(Derived2* pd = dynamic_cast<Derived2*>(iter->get())){...}
    else if(Derived3* pd = dynamic_cast<Derived3*>(iter->get())){...}
    ...
}
```

这不仅有极低的效率，还会有极高的维护成本。

#### 隔离转型动作

完全摆脱转型动作不切实际。

应尽可能隔离转型动作，将其隐藏在某个函数内。应尽可能允许用户在不使用转型动作的情况下完成工作。

### 5.28 避免返回 `handles` 指向对象内部成分

设计一个矩形：

```c++
class Point{
public:
    Point(int x,int y);
    ...
    void setX(int x);
    void setY(int y);
};

struct RectData{
    Point ulhc; // upper left-hand corner 左上角
    Point lrhc; // lower right-hand corner 右下角
};

class Rectangle{
private:
    shared_ptr<RectData> pData;
public:
    Point& upperLeft()const{return pData->ulhc;}    // 注意点
    Point& lowerRight()const{return pData->lrhc;}   // 考虑到效率，返回引用
};
```

这种设计可以通过编译，但却是错误的设计。

其中 `upperLeft()` 与 `lowerRight()` 分别作为获取左上角与右上角坐标的 `getter` ，其本身应该作为 `const` 函数。然而以上设计却允许用户修改器内容，且可以通过编译。

因此要注意：

- 成员变量的封装性最多只等于「返回其 `reference`」的函数的访问级别（水桶的短板）。
  - 例中的 `ulhc` 和 `lrhc` 声明为 private ，实际却为 public 。因为其被两个 `getter` 传出了 `reference` 。
- 如果 `const` 成员函数传出一个 `reference` ，后者所指数据与对象自身有关联，而它又被存储于对象之外，那么这个函数的调用者可以修改那笔数据 （ bitwise constness ，见 **条款 3** ）。

以上情况可推广至 **handle** （其包括引用、指针和迭代器，用以取得某个对象）。返回 handle 便有降低对象封装性的风险。

通常来说，对象「内部」指其成员变量，但实际上，不被公开使用的成员函数，同样是对象内部的一部分。这意味着返回一个私有的成员函数指针同样需要慎重对待。

一般地，可以通过返回 `const handle` 解决上述问题。

```c++
class Rectangle{
...
    const Point& upperLeft()const{return pData->ulhc;}
    const Point& lowerRight()const{return pData->lrhc;}
};
```

但即便如此，仍可能导致 `dangling handles` （空悬的 handle ），即 handle 所指东西不复存在。

```c++
class GUIObj{...};  // GUI 对象，内含一个 Rectangle 作为边界
const Rectangle boundingBox(const GUIObj& obj) // 值返回 GUI 对象中的 Rectangle 边界
```

而后客户如此使用这个函数：

```c++
GUIObj* guiObj;
...
const Point* pUpperLeft = &(boundingBox(*pgo).upperLeft());
```

错误之处在于，当函数执行完毕， **boundingBox()** 返回的对象将被销毁，这将造成 `pUpperLeft` 所指的对象连带着被销毁。

这个责任由客户承担还是由开发者承担，很难定义。为了方便他人，应尽量避免返回一个 handle 代表对象内部成分。

### 5.29 为了「异常安全」而努力是值得的

异常安全性观点要求满足以下两条件：

- 不泄露任何资源
  - 例如调用一个带有互斥器的成员函数，若在调用时出现异常，可能不会调用 `unlock()` ，从而造成死锁。
- 不允许数据败坏
  - 例如 `new` 而造成的空指针异常。

**条款 13** 与 **条款 14** 保证了第一条被正确处理。

异常安全函数 (Expection-safe functions) 提供以下三个保证之一：

- **基本承诺**
  - 如果异常被抛出，程序内的任何事物保持在有效状态。
  - 没有任何对象或数据结构会因此而败坏，所有对象处于一种内部前后一致的状态。
- **强烈保证**
  - 如果异常被抛出，程序状态不改变。
  - 调用函数失败，则应返回调用前状态。
- **不抛掷 (nothrow) 保证**
  - 承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能。
  - 作用于内置类型（`int` , `pointer` 等）的操作应提供 nothrow 保证。
  - 抛出一个空异常 **不属于** nothrow ，因为其无法从声明中被辨识是安全的。

具有异常安全性的代码 (Exception-safe code) 必须提供上述三种保证之一。

应该尽可能提供更高等级的保证。

```c++
class Window{
private:
    shared_ptr<Image> bgImage;
    Mutex mutex;
    int changeCount;
    Image* bgImage;
};

void Window::changeBackground(std::istream& imgSrc){
    Lock ml(&mutex);// 使用 Lock 类，在其解析时自动解锁。
    bgImage.reset(new Image(imgSrc));// 使用智能指针，仅在成功 reset 后发生原资源的 delete。
    ++changeCount;// 仅在成功操作后记录变换。
}
```

除此之外 copy and swap 策略可以提供强烈保证。  
其原理为：封装即将修改的数据并提供一个副本，在修改时先修改副本，后采取 swap 操作。

```c++
struct PMImpl{
    shared_ptr<Image> bgImage;
    int changeCount;
};

class Window{
private:
    shared_ptr<PMImpl> pImpl;
};

void Window::changeBackground(std::istream& imgSrc){
    using std::swap;
    Lock ml(&mutex);
    shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));
    pNew->bgImage.reset(new Image(imgSrc));
    ++pNew->changeCount;

    swap(pImpl,pNew);
}
```

但不意味着运用了 copy and swap 就是完全安全的。

- 对于整个函数，异常安全性具有水桶效应。
  - 如果函数调用了另外的函数，若所调用的函数的异常安全性低于强烈保证，则原函数本身就不再是强烈保证的。
- 对于整个函数，异常安全性具有连带影响。
  - 如果另外先调用的 `f1()` 正常而后调用的 `f2()` 异常，则 `f1()` 修改的部分将影响强烈保证。

其次， copy and swap 中的 copy 部分明显影响了效率。

若成本难以割舍，则提供基本保证。除非所操作的屎山代码本身就没有提供异常安全性。
