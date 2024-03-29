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
    static const int MAX_CAPACITY = 30;// 静态常量声明，某些编译器中这不是定义。
};

const int Class::MAX_CAPACITY; //常量定义，一般出现在实现文件
```

在某些编译器中，class 的 static const 整型（integral type，例如 ints，chars，bools）需要特殊处理，其包含赋值的声明式不一定代表定义。

> 「声明」仅建立了一个标识符。而「定义」赋予标识符空间。
>
> - 在某些编译器中，常量若只有带赋初值的声明，使用时可能采用立即数替代。
> - 这种量若无定义，取地址行为可能是未定义的。某些编译器（GCC）将报错，某些编译器（MSVC）则会通过编译。
> - 若不取地址，其行为是安全的。

当编译器不支持 static 成员的类内赋值，可以将初值置于定义式。但当在 class 编译期需要一个 class 常量值：

```c++
class Class{
    static const int MAX_CAPACITY; // static 成员类内赋值不允许

    int array[MAX_CAPACITY]; // 使用该常量
};
const int Class::MAX_CAPACITY = 30; // 晚了！执行时 array 初始化已完成
```

此时可用 enum hack 技术补偿之：

```c++
class Class{
    enum { MAX_CAPACITY = 30 };

    int array[MAX_CAPACITY];
};
```

- enum hack 的某些行为更像 #define 而非 const，这有时是合乎需求的：
  - 取 enum 的地址是不合法的。
- enum hack 技术被广泛应用于各种代码，其为模板元编程的基础技术。

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

言行如一的人是可靠的，不至于给周围人带去很多不必要的麻烦。

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
    class Widget{...};

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
class Base1{};
class Base2{};
class Derived:public Base1,public Base2{};
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
};

class Derived: public Base{
public:
    void ind_fun(){}
};
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

### 5.30 透彻了解 inlining

编译器将 `inline` 函数调用直接替换为函数本体。

如果函数本体很小，编译器可能产出更小的目标码，反之则会产出更大的目标码，这意味着更大的内存占用从而导致额外的换页行为与更低的 cache 命中率。

#### `inline` 允许显式或隐式申请

`inline` 修饰符只是一个申请而非强制命令。这项申请既可以隐式地提出，也可以显式地提出。

隐式提出：

- 将函数定义于 `class` 定义式内。

这通常包含定义于 `class` 内的成员函数与友元函数。

显式提出：

- 使用 `inline` 修饰符。

#### `inline` 常置于头文件内

`inline` 函数与 `templates` 一样，通常定义于头文件内。但 `function template` 并不一定是 `inline` 的。

大多数构建环境 (build env) 在编译过程中进行 inlining 。做这种替换必须在发现函数调用前知道「被调用的 `inline` 函数」是什么样的。因此 `inline` 函数通常置于头文件内。

而 `templates` 通常被置于头文件的原因是其一旦被使用，编译器为了在编译器将其具现化，需要知道它是什么样的。

而 `templates` 与 `inline` 无关。

#### 编译器可能拒绝 `inline`

由于可能的代码膨胀，大部分编译器拒绝将过于复杂的函数（带有循环或递归的） inlining。

同时，被调用的 `virtual` 函数也不能被 inlining。因为 `virtual` 函数在运行期才被确定。

#### 虽然函数是 `inline` 的，但仍可能生成函数本体

如，当取一个 `inline` 函数的指针时，编译器通常会为此函数生成 `outlined` 函数本体。与此同时，编译器不会对通过函数指针调用的函数进行 inlining。

即便程序员没有使用函数指针，也可能会发生失败的 inlining。

编译器可能生成构造函数和析构函数的 outline 副本，以便在 array 内部元素的构造或析构过程中调用。

除此之外，即便是对构造或析构函数定义了类内空实现，其也难被 inlined。因为空的构造函数并不意味着什么也不做，类内私有成员正按某种顺序进行自身构造函数调用，而且在构造时将进行异常处理，以免构造到一半时出错造成内存泄漏。

这就意味着更复杂的代码将在编译时生成，这样的代码并不适合被 inlined。

```c++
Derived::Derived(){
    Base::Base();
    try{
        member1.Member();
    }catch(...){
        Base::~Base();
        throw;
    }
    try{
        member2.Member();
    }catch(...){
        member1.~Member();
        Base::~Base();
        throw;
    }
}
```

因此构造函数与析构函数不应该是 inlined 。

#### `inline` 函数可能是难以维护的

若修改 `inline` 函数，这意味着所有调用函数的地方都需要重新编译。而修改 `non-inline` 函数只需要重新链接。动态链接的程序库甚至不需要改动。

#### `inline` 函数难以调试

无法对一个不存在的函数打断点。

一般的构建环境仅仅有如下作为：

- 禁止在 debug 中 inlining。

综上，将一个函数 inlining 需要谨慎考虑。一般仅将小型、频繁调用的函数进行 inlining。

### 5.31 将文件间的编译依存关系降至最低

C++ 对于接口与实现分离没有语法上较好的支持。

#### 前置声明与引用头文件

在使用符号前，必须有对应的声明。有两种方式添加声明：

- 前置声明
- 引用头文件

前者由使用者自行添加，其要求对此符号的声明完全了解：

> class 还是 template？

后者一般由符号的定义者提供。

头文件引用的处理发生在编译器前，因此头文件若发生改动，将引起一连串的重新编译。

C++ 不允许类外声明，其中一个理由为：

- 编译器必须在编译期知晓对象的大小，以便进行正确的内存分配。

而不需要处理内存分配的符号使用（声明、指针、引用），则建议使用前置声明来避免重新编译。

因此可以将接口与实现分离：

```c++
#include<string>
#include<memory>
class PersonImpl;
class Date;
class Address;

class Person{
public:
    Person(
        const std::string& name,
        const Date& birthday,
        const Address& address);
    std::string name() const;
    std::string birthday() const;
    std::string address() const;
private:
    std::shared_ptr<PersonImpl> pImpl;
};
```

其中 main class `Person` 只内涵一个指针成员指向其实现类，这种设计即 pimpl idiom 。  
其使得 `Person` 的客户与 `Date`、`Address`、`Person` 的实现细目分离。

这种处理的关键在于以「声明的依存性」替换「定义的依存性」，这就是编译依存性最小化的本质：现实中让头文件尽可能自我满足，否则让它与其他文件内的声明式（而非定义式）相依存。

- 如果使用 `obj references` 或 `obj pointers` 可以完成任务，就不要使用 `obj` 本身。
  - 如果只使用前者，就只需要一个类型声明式。
- 尽量以 `class` 声明式替换 `class` 定义式。
  - 在声明中使用某个 `class` 时，并不需要其 `class` 的定义。即便是值传递的。
- 为声明式和定义式提供不同的头文件。
  - 实际上，前置声明也形成头文件并由符号设计者提供。
  - 一般命名上采用 `fwd` 后缀，如 `iosfwd`。

#### 使用 interface

除此之外，另一种制作 `handle class` 的方法是使用 `abstract base class` ，即 **抽象基类**，亦即 `Interface class`。

通常，C++ Interface 不包含成员变量、构造函数（这在 C++ 中是有弹性的，而 Java 中严格禁止），而仅有一个 virtual 析构函数与一系列纯虚函数。

由于其特性，Interface 禁止被实例化，因此其只能通过引用或指针使用。一般地，存在一个工厂函数负责实例化 interface 的具体实现类。这种函数通常在 interface 中被声明为 `static`。

```c++
class Person{
public:
    virtual ~Person();
    virtual std::string name() const = 0;
    virtual std::string birthday() const = 0;
    virtual std::string address() const = 0;

    static std::shared_ptr<Person> createInstance(
        const std::string&name,
        const Date&birthday,
        const std::string&address);
};
```

实践中的工厂函数会根据不同的条件创建不同类型的 interface 实现类。包括但不限于：

- 额外的参数值。
- 读自文件或数据库的数据。
- 环境变量。

采用如上的方式虽会带来降低编译依存性的好处，但也有一定的代价，如 `virtual` 带来的更多间接跳跃与虚函数表成本。

## 6. 继承与面向对象设计

### 6.32 确定你的 public 继承塑膜出 is-a 关系

**公开继承** (public inheritance) 意味着 is-a 关系。

强调了 **里氏代换原则** 。

> **里氏代换原则** (Liskov Substitution Principle)
>
> - 任何基类可以出现的地方，都可以用子类替换之。

确定 is-a 关系时不可囿于常识性判断，而应该经过站在软件设计适用性的角度上严谨论证。

> - 鸟会飞
> - 企鹅是鸟
> - 企鹅会飞？

### 6.33 避免遮掩继承而来的名称

作用域使得相同名称间可能存在遮掩现象。即名称查找将优先搜索更近且更小范围的名称。

对于对象来说，遮掩意味着覆盖。

- 除了虚函数之外，子类中的函数将覆盖基类中的同名函数。

有如下代码：

```c++
class Base{
public:
    virtual void func1() = 0;
    virtual void func1(int);
};

class Derived: public Base{
public:
    virtual void func1();
};
...
Derived d;
d.func1(1); // Error
```

这意味着 Derived 的 `func1()` 覆盖了 Base 的 `func1(int)` ，即便是不同类型的虚函数。

> 设计者为了防止程序员在程序库或应用框架内建立新的 derived class 时附带地从疏远的 base classes 继承重载函数。

但通常程序员对这一特性相当排斥 ，因按照常理子类应继承基类所有成员。可以使用 using 声明式强制继承所有同名重载函数。

```c++
class Base{
public:
    virtual void func1() = 0;
    virtual void func1(int);
};

class Derived: public Base{
public:
    using Base::func1;
    virtual void func1();
};
```

对于私有继承，通常仅需使基类中的个别函数被暴露。一般采用转交函数 (forwarding function) 。

```c++
class Base{
public:
    virtual void func1() = 0;
    virtual void func1(int);
};

class Derived: private Base{
public:
    virtual void func1(){
        Base::func1();
    };
};
```

### 6.34 区分接口继承和实现继承

公有继承可更加细化为以下两种：

- **函数接口继承** (function interfaces)
- **函数实现继承** (function implementations)

设有如下代码：

```c++
class Shape{
public:
    virtual void draw() const = 0;
    virtual void error(const string& msg);
    int objectID() const;
    ...
};
class Rectangle: public Shape {...};
class Ellipse: public Shape {...};
```

抽象类 Shape 包含如下成员函数：

- 纯虚函数 `draw()` 。
  - 所有继承 Shape 的子类必须重新声明虚函数。这意味着对其提供定义。
  - 纯虚函数允许被定义，但必须通过限定名以调用。
  - 声明一个纯虚函数的目的是为了让子类 **只继承函数接口** 。
- 虚函数 `error()` 。
  - 基类提供了缺省实现。
  - 子类可以选择覆写 (override) 之。
  - 声明一个虚函数的目的是为了让子类 **继承函数接口和缺省实现** 。
- 函数 `objectID()` 。
  - 继承时具有不变性 (invariant) 而非特异性 (specialization) 。
  - 声明一个非虚函数的目的是为了让子类 **继承函数的接口及一份强制性实现** 。

同时提供函数接口与缺省实现可能为后期维护或扩展形成隐患。

- 面向对象设计要求不同类的共同性质应被提升至公共的基类。
- 而后期扩展的新子类也许会发生「变异」，因而缺省实现可能完全不适用，但并不被编译器提醒。

可以采用如下两种方式将接口与实现分离：

```c++
// 允许默认行为与接口有不同保护级别
class Base {
public:
    virtual void vfunc()=0;
protected:
    void defaultFunc();
};

Base::defaultFunc(){
    ...
};

class Derived: public Base{
public:
    virtual void vfunc(){
        defaultFunc();
    };
};
```

```c++
// 避免过多名称形成重复，造成命名空间污染
class Base {
public:
    virtual void vfunc()=0;
};

Base::vfunc(){
    ...
};

class Derived: public Base{
public:
    virtual void vfunc(){
        Base::vfunc();
    };
};
```

### 6.35 考虑 virtual 函数以外的其他选择

#### 藉由非虚接口实现模板方法模式

> **模板方法模式** (Template Method Pattern) ，它属于类行为型模式。
>
> - 定义一个操作中算法的框架，而将一些步骤延迟到子类中。
> - 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

C++ 通过 NVI (non-virtual interface) 技术实现模板方法模式。

```c++
class Base {
public:
    // 模板方法是基本方法的外覆器 (wrapper)
    void method(){
        // 子类不得重新定义

        templateMethod();
    }

private:
    virtual void templateMethod(){
        // 子类可重新定义
        ...
    }
};
```

模板方法模式有如下优点：

- 保证在基本方法执行前后的准备与清理工作。如记录日志、控制互斥器、验证约束等。

虽然看起来子类本身可能不会调用重新定义的虚函数，但实际上「函数何时被调用」与「函数如何实现机能」两者并无影响。

#### 藉由函数指针实现策略模式

> **策略模式** (Strategy Pattern) 又称为 **政策模式** (Policy) ，它属于对象行为型模式。
>
> - 将算法封装至算法类。
> - 允许算法类相互替换。
> - 其使算法独立于使用它的客户而变化。

策略模式提供了行为的弹性，其可在运行期改变计算函数。

```c++
class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter{
public:
    // 定义函数指针
    typedef int (*HealthCalcFunc)(const GameCharacter&);
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc):healthFunc(hcf) {}
    int healthValue() const{
        return healthFunc(*this);
    }

private:
    HealthCalcFunc healthFunc;
};
```

如此便可延后特化行为至构造时确定，但这种方式存在一些问题：

- 只能依赖类的公有接口得到信息。

一般通过弱化 class 的封装性，以使非成员函数访问类的非公开接口：

- 使非成员函数成为 **友元函数** 。
- 为其实现的某一部分提供公有访问函数。

#### 藉由 `std::function` 实现策略模式

`std::function` 是通用多态函数包装器，其可持有任何可调用物 (callable entity) ，即函数指针、函数对象或成员函数指针。

```c++
class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter{
public:
    // 定义 std::function，其可以保存任何与此签名兼容的可调用物。
    //  兼容包括：
    //  - 参数可隐式转换为 const
    //  - 返回类型可隐式转换为 int
    typedef function<int(const GameCharacter&)> HealthCalcFunc;
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc):healthFunc(hcf) {}
    int healthValue() const{
        return healthFunc(*this);
    }

private:
    HealthCalcFunc healthFunc;
};
```

```c++
// 普通函数
int defaultHealthCalc(const GameCharacter& gc) {
return 100;
};

// 仿函数
class HealthCalculator {
public:
    int operator()(const GameCharacter&) const {
        return 80;
    }
};

// 成员函数
class HasFunction {
public:
    int healthCalc(const GameCharacter& gc) {
        return 60;
    }
};

...
HasFunction has_func;

// 普通函数（已通过默认参数传入）
GameCharacter gc1;
// 仿函数
GameCharacter gc2((HealthCalculator()));
// 成员函数（需通过 bind() 进行包装）
GameCharacter gc3(bind(&HasFunction::healthCalc, has_func, placeholders::_1));
```

#### 传统策略模式

传统策略模式将策略本身视为类型。

```PlantUML
@startuml Strategy_ClassDiagram
hide empty members

class Context{
    - strategy : Strategy
    + algorithm()
}

class Strategy{
    + algorithm()
}

class ConcreteStrategyA{
    + algorithm()
}

class ConcreteStrategyB{
    + algorithm()
}

Context o-right->Strategy
Strategy <|-- ConcreteStrategyA
Strategy <|-- ConcreteStrategyB
@enduml
```

```c++
class GameCharacter;
class HealthCalcFunc{
public:
    virtual int calc(const GameCharacter& gc) const{
        ...
    }
};

HealthCalcFunc defaultHealthCalc;
class GameCharacter{
public:
    explicit GameCharacter(HealthCalcFunc* phcf = & defaultHealthCalc):pHealthCalc(phcf){}

    int healthValue() const{
        return pHealthCalc->calc(*this);
    }

private:
    HealthCalcFunc* pHealthCalc;
}
```

### 6.36 绝不重新定义继承而来的非虚函数

发生在非虚函数的覆写相当危险。

非虚函数是静态绑定的 (statically bound) 的，这意味着并不能通过 pointer-to-B 的指针调用 D 的同名函数。

```c++
class B {
public:
    void func() {
        std::cout << "Base" << endl;
    }
};

class D : public B {
public:
    void func() {
        std::cout << "Derived" << endl;
    }
};

int main() {
    D d;
    B* pb = &d;
    D* pd = &d;

    pb->func();
    pd->func();
}

-------- Out --------
Base
Derived
```

而虚函数则是动态绑定的 (dynamically bound) ，因此无论指针类型，都可以调用到实际指向的 D 的同名函数。

**条款 32** 规定了公有继承必须是 is-a 关系。 **条款 34** 规定了非虚函数应为该类的不变性而非特异性负责。

因此：

- 适用于基类对象的每一件事，也适用于子类对象。因为每一个子类对象都是一个基类对象。
- 基类的所有子类必然会继承基类非虚函数的接口与实现。

**条款 7** 是此条款在析构函数上的反映。

语法的自由提供了权利，但程序员应为代码合理性履行义务。

### 6.37 绝不重新定义继承而来的缺省参数值

虚函数是动态绑定的 (dynamically bound) 的，但缺省参数值却是静态绑定的 (statically bound) 。

**静态绑定** 也称为前期绑定 (early binding) 。

- 是在程序中被声明时所采用的类型。

**动态绑定** 也称为后期绑定 (late binding) 。

- 是目前所指对象的类型。

其行为与 **条款 36** 中反映类似。未被正确使用的静态绑定特性将在指针或引用表现异常。

当确有需要写出如下代码：

```c++
class Shape{
public:
    virtual void draw(int size=10) const = 0;
}

class Rectangle:public Shape{
public:
    virtual void draw(int size=10) const;
}
```

这种设计虽然合规，但是具有代码重复与相依性 (with dependencies) 的弱点。相依性指若基类缺省参数值改变，则子类也有必要更改，极大提高了出错的可能性。

这时我们需要进行替代设计。如 **条款 35** 中的 NVI 技术。

```c++
class Shape{
public:
    virtual void draw(int size=10) const {
        doDraw(10);
    };
private:
    virtual void doDraw(int size) const = 0;
}

class Rectangle:public Shape{
private:
    virtual void doDraw(int size) const;
}
```

### 6.38 通过复合塑膜出 has-a 或 is-implemented-in-terms-of 关系

**复合** (composition) 是类型之间的一种关系。一般呈现为某种类型的对象内含其他类型的对象。

```c++
class Address{};
class PhoneNumber{};
class Person{
private:
    Address address;
    PhoneNumber phoneNumber;
}
```

```plantUML
@startuml
hide empty members

Person *-down- PhoneNumber
Person *-down- Address
@enduml
```

复合意味着 has-a （有一个） 或 is-implemented-in-terms-of （根据某物实现出）关系。

> 程序中的某些对象相当于自然中的实际存在，如人、车、树，这些对象属于应用域 (application domain) ；  
> 另一些对象则是促成实现的人工制品，如缓冲区、互斥器、查找树等，这些对象属于实现域 (implementation domain) 。

当复合发生于应用域内的对象之间，表现出 has-a 关系。  
当它发生于实现域内则表现 is-implemented-in-terms-of 关系。

假设要设计某种内存友好型 Set （STL 中的 Set 通常以平衡二叉树实现，是面向速度的设计），大致目标要求以链表作为存储形式，因此决定复用 STL `list<T>`。

因此有如下设计：

```c++
template <typename T>
class Set: public std::list<T>{...};
```

这是一种错误设计。理由是：如果 Set is-a list ，且 list 可以内含重复元素，那么 Set 也应可以包含重复元素。但这与现实不符。

因此应进行如下设计：

```c++
template <typename T>
class Set{
public:
    bool member(const T& item) const;
    void insert(const T& item);
    void remove(const T& item);
    std::size_t size() const;
private:
    std::list<T> rep;
};
```

此即反映了 is-implemented-in-terms-of 关系。

### 6.39 明智而审慎地使用 private 继承

private 继承具有如下特性：

- 编译器不会自动将子类对象转换为基类对象。
- private 继承而来的所有成员将在子类中转化为 private。

private 继承意味着 implemented-in-terms-of （根据某物实现出）。

private 旨在采纳基类已经完备的某些特性，而非其他任何观念上的关系。亦理解为只继承 **实现部分**，而略去 **接口部分**。

当 is-implemented-in-terms-of 关系需要被描述时，已有两种选项供程序员选择：

- 复合关系
- private 继承

除非必要情况，尽可能避免 private 继承：

- 当 protected 成员或 virtual 函数需要特殊处理时。
- EBO (empty base optimization) 空白基类最优化。

```c++
class Timer{
public:
    explicit Timer(int tickFrequency);
    virtual void onTick() const;
};

// private 继承
class Widget: private Timer{
private:
    virtual void onTick() const;
};

// 复合关系
class Widget{
private:
    // 内部类 嵌套式 private 对象，仍是复合关系。
    class WidgetTimer: public Timer{
        public: virtual void onTick() const;
    };
    WidgetTimer timer;
};
```

如上的 public 继承加复合与 private 继承相比稍显复杂，但其具有如下优点：

- 其实现了密封功能（Java 的 final 和 C# 的 sealed）。  
  即阻止了子类重新定义 virtual 函数。
- 降低了编译依存性。  
  如果 Widget 继承 Timer ，则 Timer 的定义必须可见，因此必须引入相关头文件。  
  而使用指针指向 WidgetTimer 则只需一个声明式。详见 **条款 31**。

EBO (empty base optimization) 空白基类最优化需要 private 继承。

当一个类不带任何数据，即：

- 不包含任何 non-static 成员变量。
- 不包含任何 virtual 函数（包含虚函数的类将带有虚函数表）。

这种类被实例化后理论上不占用任何空间，但 C++ 标准要求凡是独立对象都必须有非 0 大小。而被继承的基类则例外（其非独立）。

```c++
class Empty{};

// sizeof(HoldsAnInt) > sizeof(int)
class HoldsAnInt{
private:
    int x;
    Empty e;
}

// sizeof(HoldsAnInt) == sizeof(int)
class HoldsAnInt: public Empty{
private:
    int x;
}
```

面对空间及其紧张的需求时应考虑 EBO，且应注意 EBO 仅在单一继承下可行。

### 6.40 明智而审慎地使用多重继承

多重继承 (multiple inheritance) 指一个子类继承多个父类。

C++ 提供了对多重继承的语法支持。

子类可能从多个基类继承相同名称，这可能导致更多的歧义机会。

```c++
class BorrowableItem{
public:
    void checkOut();
};

class ElectronicGadget{
private:
    bool checkOut() const;
};

class MP3Player:
    public BorrowableItem,
    public ElectronicGadget{};

MP3Player mp;
mp.checkOut();  // 歧义！调用哪个 checkOut()
mp.BorrowableItem::checkOut(); // 实际写法
```

虽然上例中只有一个 `checkOut()` 是可用的，但 C++ 首先寻找最佳匹配函数，其次才检验可用性。上例中有多个相同匹配程度的函数，因此无法找到最佳匹配，可用性尚未进入考察范围。

多重继承还可能发生严重的菱形继承，即继承而来的多个基类可能分别都继承自一个共同的基类（祖先基类）。C++ 面对菱形继承将默认复制祖先基类的成员，除非使用 virtual 继承。

```plantUML
@startuml
hide empty member
File <|-down- InputFile
File <|-down- OutputFile
InputFile <|-down- IOFile
OutputFile <|-down- IOFile
@enduml
```

```c++
class File{};
class InputFile:virtual public File {};
class OutputFile:virtual public File{};
class IOFile:
    public InputFile,
    public OutputFile{};
```

从行为上来看，所有 public 继承都应该是 virtual 的，因为要避免继承而来的成员变量重复。但也正因为要提供保证，C++ 将为 virtual 继承付出空间与时间上的代价和其他副作用：

- virtual base 的初始化责任是由继承体系中的最底层 (most derived) class 负责。
  - 如果派生自 virtual bases 的 class 需要初始化，必须认知其 virtual bases。
  - 当心的 derived class 加入继承体系中，它必须承担其 virtual bases 的初始化责任，无论直接或间接。

因此应尽可能少使用 virtual bases，其次使用时应尽可能避免在其中放置数据。

对于多重继承，参考 Java 对于 Interface 与继承的设计，即：

- 单一继承类型。
- 允许多继承 Interface 。

Java 中的 Interface 就类似 C++ 中不包含数据，仅包含函数声明的类型。

因此多重继承的最正当的用途即：

- public 继承某个 Interface class。
- private 继承某个协助实现的 class。

## 7. 模板与泛型编程

### 7.41 了解隐式接口和编译期多态

```c++
class Widget{
public:
    Widget();
    virtual ~Widget() {}
    virtual std::size_t size() const;
    virtual void normalize();
    void swap(Widget& other);
    ...
};

void doProcessing(Widget& w){
    if(w.size() > 10 && w != someNastyWidget){
        Widget temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

对于函数 `doProcessing()` 中的 `w` ：

- `w` 的类型明确声明为 Widget ，因此其必支持 Widget 接口。Widget 接口细节在源码中明确可见，即其为一个 **显式接口** (explicit interface) 。
- Widget 的某些成员函数是 virtual ，因此 `w` 对那些函数的调用将表现出运行期多态 (runtime polymorphism) ，即将在运行期根据 `w` 的动态类型决定究竟调用哪个函数。

对于 Template 与泛型编程，显式接口和运行期多态仍然存在，但重要性降低。与之相对，隐式接口与编译器多态占据主流。

设将 `doProcessing` 转变为函数模板。

```c++
template<typename T>
void doProcessing(T& w){
    if(w.size() > 10 && w != someNastyWidget){
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

对于模板函数 `doProcessing()` 中的 `w` ：

- `w` 必须支持哪种接口，取决于 template 中 w 的行为决定。
  - 至少包含： `size()` `normalize()` `swap()` 拷贝构造函数 不等比较符。
  - 此即隐式接口。
- 凡涉及 `w` 的任何函数调用，如操作符 `>` 和 `!=` ，都可能造成模板具现化 (instantiated) ，使这些调用得以成功。这些具现行为发生在编译期，「以不同的 template 参数具现化模板函数」会导致调用不同的函数，这就是所谓的编译期多态 (compile-time polymorphism) 。

运行期多态与编译期多态之间的差异，类似于「哪一个重载函数该被调用（发生在编译期）」与「哪一个 virtual 函数该被绑定（发生在运行期）」之间的差异。

**显式接口** 一般由函数的签名（函数名称、参数类型、返回类型）构成。

```c++
class Widget{
public:
    Widget();
    virtual ~Widget();
    virtual std::size_t size() const;
    virtual void normalize();
    void swap(Widget& other);
};
```

对于 Widget 来说，其显式接口包括：

- 构造函数
- 析构函数
- `size()`
- `normalize()`
- `swap()`
- 及其参数类型、返回类型、常量性
- copying 函数（自动生成）

另外还可以包括：

- typedefs
- public 成员变量（违反了 **条款 22**）

而 `隐式接口` 则完全不同，其由 **有效表达式** (valid expressions) 组成。

对于 `template doProcessing()` 来说，`T` 必须满足：

- 支持 `size()` (自身接口或继承而来的接口)，且返回值兼容 `>`。
  - 兼容指，其返回值可以隐式转换为支持 `>` 的对象。
- 兼容 `!=`。
- 抑或其他某些条件。
  - 也许隐式转换而来的某个类型支持重载的 `&&`，从而使表达式成立。

这些条件来自有效表达式：`if(w.size() > 10 && w != someNastyWidget)` 。条件的检查与显式接口同样地在编译期完成检查。

因此隐式接口应面向有效表达式。

### 7.42 了解 `typename` 的双重意义

对于 C++ 来说，`template` 声明式中的 `class` 和 `typename` 意义完全相同。

除非用于验证 **嵌套从属类型名称**。

template 内出现的名称若依赖于某个 template 参数，则称其为 **从属名称** (dependent names)。相反，不依赖任何 template 参数的名称称为 **非从属名称** (non-dependent names)。若从属名称在 class 内呈嵌套状，则称其为 **嵌套从属名称** (nested dependent name)。若嵌套从属名称指涉某类型，则称为 **嵌套从属类型名称** (nested dependent type name)。

```c++
template <typename C>
void print2nd(const C& container2){
    if (container2.size() >= 2){
        C::const_iterator iter(container.begin());  // Error
        ++iter;
        int value = *iter;
        std::cout << value;
    }
}
```

其中 `iter` 即从属名称，`C::const_iterator` 是一个嵌套从属名称。 `value` 为非从属名称。

嵌套从属名称可能导致 **解析** (parsing) 困难。

例如：

```c++
C::const_iterator* x;
```

`C` 在不指定类型的情况下，`C::const_iterator` 具有二义性。

- 可能是一个静态数据成员。
- 可能是一个内部类型。
- etc.

C++ 面对嵌套从属类型，默认解析为非类型，除非指定为 `typename`。

```c++
typename C::const_iterator iter;
```

「`typename` 必须作为嵌套从属名称的前缀词」的例外：

- `typename` 不可以出现在 base classes list 内的嵌套从属名称类型之前。
- `typename` 不可在成员初值列表 (member initialization list) 中作为 base class 修饰符。

```c++
template<typename T>
class Derived: public Base<T>::Nested{ // base class list 中不允许 typename
public:
    explicit Derived(int x):Base<T>::Nested(x){ // 成员初值列表不允许 typename
        typename Base<T>::Nested temp;
    }
};
```

设有如下代码，将一个迭代器指涉的对象做 local 副本：

```c++
template<typename IterT>
void workWithIterator(IterT iter){
    typename std::iterator_traits<IterT>::value_type temp(*iter);
}
```

其中 `std::iterator_traits<IterT>::value_type` 相当于「类型为 `IterT` 的对下你给所指对象的类型」。如若 `IterT` 为 `vector<int>::iterator`，则 `temp` 的类型为 `string`。

由于过长的名称，一般会考虑使用 `typedef` 简化代码：

```c++
template<typename IterT>
void workWithIterator(IterT iter){
    typedef typename std::iterator_traits<IterT>::value_type;
    value_type temp(*iter);
}
```

如上代码作为 `typename` 的标准应用。

### 7.43 学习处理模板化基类内的名称

设有如下代码，用于向目标公司发送特定信息：

```c++
class CompanyA{
public:
    void sendCleartext(const string& msg);
    void sendEncrypted(const string& msg);
};
class CompanyB{
public:
    void sendCleartext(const string& msg);
    void sendEncrypted(const string& msg);
};

class MsgInfo{...};

template<typename Company>
class MsgSender{
public:
    void sendClear(const MsgInfo& info){
        string msg;
        Company c;
        c.sendCleartext(msg);
    }

    void sendSecret(const MsgInfo& info){...}
};
```

现功能需要扩展，将添加日志记录功能，于是有：

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company>{
public:
    void sendClearMsg(const MsgInfo& info){
        log(...);
        sendClear(info); // Error
        log(...);
    }
};
```

`sendClearMsg()` 函数（命名原因见 **条款 33**、**条款 36**，避免遮掩继承而来的名称，避免覆盖一个 non-virtual 函数）将发生编译错误。

原因显而易见，`LoggingMsgSender` 并不确定 `Company` 是什么，从而就无法知道继承哪个 `MsgSender<Company>` （也许有一个特化版的 `MsgSender`）：

```c++
class CompanyZ{
// 一个新的 Company ，未定义 sendCleartext()
public:
    void sendEncrypted(const string& msg);
}

template<>
class MsgSender<CompanyZ>{
// CompanyZ 的全特化版本
public:
    void sendSecret(const MsgInfo& info){
        ...
    }
};
```

模板全特化 (total template specialization) 相对于偏特化是全面性的，一旦类型参数被定义，就没有其他 template 参数可供变化。

如此，编译器就有理由拒绝调用模板基类的函数，因为完全有可能存在一个特化版本的模板基类未提供同名接口。

有三种办法取消 C++ 的这种默认行为：

- 在调用基类的函数前添加 `this->`。

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company>{
public:
    void sendClearMsg(const MsgInfo& info){
        log(...);
        this->sendClear(info);
        log(...);
    }
};
```

- 使用 using 声明式。

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company>{
public:
    using MsgSender<Company>::sendCLear;
    void sendClearMsg(const MsgInfo& info){
        log(...);
        sendClear(info);
        log(...);
    }
};
```

- 指明函数位于基类中。  
  此解法往往不令人满意。当被调用的函数是虚函数时，这种明确资格修饰 (explicit qualification) 将关闭 virtual 绑定行为。

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company>{
public:
    void sendClearMsg(const MsgInfo& info){
        log(...);
        MsgSender<Company>::sendClear(info);
        log(...);
    }
};
```

从名称可视点 (visibility point) 角度出发，上述解法的思路都相同：向编译器提供「模板基类的任何特化版本都支持其一般版本所提供的接口」的保证。但这种保证责任由程序员承担，是不可靠的。当调用了某个未遵守保证的特化版本类的函数，将无法通过编译。

面对「指涉的模板基类成员」的无效引用，编译器的诊断可能发生在早期（解析模板子类的定义式时），也可能发生在晚期（当模板类被特定的模板参数具现化时）。秉持宁愿早诊断的原则，C++ 将假设对基类内容一无所知。

### 7.44 将与参数无关的代码抽离 templates

templates 在自适应代码复用方面为程序员提供了相当大的便利。通过 templates ，由编译器自行决定具现化的时机。但过于冗长的 template 可能反而导致代码膨胀 (code bloat)：其二进制码带着过多重复的代码、数据，即便源码看似简洁。

常用 **共性与变性分析** (commonality and variability analysis) 解决上述问题。

在编写函数或类时，常对不同的函数或类进行分析其异同。相似的实现码将被抽离出其他函数或基类中。编写 templates 时与之类似，但 templates 中发生的重复比较隐晦。

```c++
template<typename T,size_t n>
// 由于某些需求，需要 size_t 作为 template 非类型参数表示方阵的大小。
class SquareMatrix{
public:
    void invert();
}
```

C++ 将为 `SquareMatrix<int,5>` 与 `SquareMatrix<int,10>` 具现化两种 `invert()`。因此将相同部分抽离：

```c++
template<typename T>
class SquareMatrixBase{
protected:
    void invert(size_t matrixSize);
};

template<typename T,size_t n>
class SquareMatrix:private SquareMatrixBase<T>{
private:
    using SquareMatrixBase<T>::invert;
public:
    void invert(){
        this->invert(n);
    }
}；
```

如此改造使得对于给定元素对象类型，所有矩阵将共享同一个 `SquareMatrixBase::invert()`。

为了能保障功能的正常运作，需要把必要的数据放入 base 类中。

```c++
template<typename T>
class SquareMatrixBase{
protected:
    SquareMatrixBase(size_t n,T* pMem):size(n),pData(pMem){}
    void setDataPtr(T* ptr){ pData = ptr; }

    void invert(size_t matrixSize);
private:
    std::size_t size;
    T* pData;
};

template<typename T,size_t n>
class SquareMatrix:private SquareMatrixBase<T>{
private:
    using SquareMatrixBase<T>::invert;
    T data[n*n];
public:
    SquareMatrix():SquareMatrixBase<T>(n,data){}

    void invert(){
        this->invert(n);
    }
};
```

实际上，比较包含矩阵尺寸的 invert 版本与共享版本两者在速度或空间上的区别并非一目了然的。

在「尺寸专属版」中，尺寸是一个编译期常量，编译期会针对这一特点进行最优化，如使其称为直接操作数。

然而另一角度看，共享版本无疑能减少可执行文件大小，从而降低程序的 working set，并强化指令高速缓存区的引用集中化 (locality of reference)。

> 所谓 working set 指对一个在虚拟内存环境下执行的进程而言，其所使用的那一组内存页 (pages)。

因此到底何种方式能够有效提高效率，只能两者都尝试并在测试中进行比较。

上述都是非类型模板参数带来的膨胀，而类型参数也会导致膨胀。如 `vector<int>` 与 `vector<long>`。某些连接器将合并完全相同的函数实现码，而有些不会。

特别是对于指针类型来说，由于不同类型的指针的二进制表述相同，因此应令其调用来自公共基类中操作 `void*` 类型指针的函数。

### 7.45 运用成员函数模板接受所有兼容类型不会改变语言的基本规则。

智能指针作为一种「行为像指针」的对象，具有诸多好处，但其与旧式指针略有不及的一点在于：不支持隐式转换。

```c++
class Top{...};
class Middle: public Top{...};
class Bottom: public Middle{...};

Top* pt1 = new Middle; // Middle* 转换为 Top*
Top* pt2 = new Bottom; // Bottom* 转换为 Top*
const Top* pct2 = pt1; // Top* 转换为 const Top*
```

```c++
template<typename T>
class SmartPtr{
public:
    explicit SmartPtr(T* realPtr);
    ...
};

SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle); // Error
SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom); // Error
SmartPtr<const Top> pct2 = pt1; // Error
```

`SmartPtr<Top>` 与 `SmartPtr<Middle>` 之间没有任何关系，因此自然而然是不支持隐式转换的。

#### Templates 和泛型编程 (Generic Programming)

通过新增构造函数来提供对转型的支持的工作量是难以预估的。因为 template 可以被无限地具现化。

因此我们可以编写一个构造模板，这样的模板即 **成员模板函数** (member function templates)，常简称为 **成员模板** (member templates)。

```c++
template<typename T>
class SmartPtr{
public:
    template<typename U>
    SmartPtr(const SmartPtr<U>& other); // 泛化的拷贝构造函数。未被声明 explicit，因为允许隐式转换。
};
```

实际实现中要注意进行转换的约束。一般仅允许子类向基类的隐式转换。

```c++
template<typename T>
class SmartPtr{
public:
    template<typename U>
    SmartPtr(const SmartPtr<U>& other):heldPtr(other.get()){
        ...
    }
    T* get() const { return heldPtr; }
    ...
private:
    T* heldPtr;
};
```

如上代码中使用成员初始化列表，以 类型为 `U*` 的初值初始化类型为 `T*` 的成员变量。这个行为默认只有当「存在某个隐式转换将 `U*` 转为 `T*` 指针」时才能通过编译，符合设计目标。

成员模板不限于构造函数的应用，还常用于赋值操作。`shared_ptr` 支持所有「来自兼容的内置指针、`shared_ptrs`、`auto_ptrs`、`weak_ptrs`」的构造行为以及赋值操作。

```c++
template<class T>
class shared_ptr{
public:
    template<class Y>
    explicit shared_ptr(Y* p);
    template<class Y>
    shared_ptr(shared_ptr<Y> const& r);
    template<class Y>
    explicit shared_ptr(weak_ptr<Y> const& r);
    template<class Y>
    explicit shared_ptr(auto_ptr<Y>& r);

    template<class Y>
    shared_ptr& operator=(shared_ptr<Y> const& r);
    template<class Y>
    shared_ptr& operator=(auto_ptr<Y>& r);
};
```

- 除了泛化构造函数，以上所有构造函数都是 `explicit`。
- 与 `auto_ptr` 相关的函数并未声明为 `const` ，因为复制一个 `auto_ptr` 时，已经对其有改动了。

成员函数模板不会改变语言的基本规则。**条款 5** 指出，编译器默认生成 4 个成员函数，包括 2 个拷贝构造函数和赋值构造函数。在类内声明泛化拷贝构造函数不会阻止编译器生成默认的拷贝构造函数。赋值操作同上。

### 7.46 需要类型转换时请为模板定义非成员函数

**条款 24** 指出只有非成员函数才可对所有实参进行隐式类型转换，并以 `Rational` 为例。现有模板化 `Rational`：

```c++
template<typename T>
class Rational{
public:
    Rational(const T& numerator = 0,const T& denominator = 1);
    const T numerator() const;
    const T denominator() const;
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs){
    ...
}
```

当以平常逻辑使用时将发生错误：

```c++
Rational<int> oneHalf(1,2);
Rational<int> result = oneHalf * 2; // Error
```

编译器在 template 实参推导过程中不会将隐式类型转换函数纳入考虑，仅知道存在一个名为 `operator*` 且接受两个 `Rational<T>` 参数的函数，编译器不会主动将 `int (2)` 转换为 `Rational`。

令 `Rational<T> class` 声明适当的 `operator*` 为友元函数可以解决问题。

- template 实参推导仅施行于模板函数上，Class templates 不依赖这个过程。

每当 `class Rational<T>` 具现化时，`T` 的类型即可确定。

```c++
template<typename T>
class Rational{
public:
    friend const Rational operator*(const Rational& lhs,const Rational& rhs);
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs){
    ...
}
```

在 class template 内，template 名称可被用来作为「template 及其参数」的简略表达方式，效果等同如下代码：

```c++
template<typename T>
class Rational{
public:
    friend const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs);
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs){
    ...
}
```

如此一来，对 `operator*` 的混合式调用便可通过编译了。

- 当 `oneHalf` 被声明为 `Rational<int>` 时，`class Rational<int>` 便被具现化出来。
- 作为过程的一部分，接受两个 `Rational<int>` 参数的友元函数 `operator*` 也被自动声明出来，而这个函数是非模板函数，从而可以隐式转换。

虽通过编译，但上述代码将发生链接错误。

如上所述，编译器 `operator*` 跟随 `Rational` 具现化的 **同时** 自动声明出来，因此定义式应紧跟声明式，否则编译器具现化 `Rational` 时无法找到定义式，即便就在类外部的下方数行之内。

```c++
template<typename T>
class Rational{
public:
    friend const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs){
        ...
    }
};
```

如此方式与 friend 的传统用途「访问 class 的非公有接口」毫无联系。而友元函数的作用域为类外。

- 为了允许类型转换发生在所有实参之上，需要使之称为非成员函数；
- 为了使函数自动具现化，需要将其声明在 class 内；
- 为了在类内声明非成员函数的唯一办法：使之成为友元函数。

**条款 30** 指出，定义于类内的函数都隐式转换为了 inline ，即使是友元函数。但 inline 函数有负面效果。

可以令 `operator*` 不做任何事情，仅调用一个定义与 class 外的辅助函数：

```c++
template<typename T>
class Rational;
template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs,const Rational<T>& rhs);

template<typename T>
class Rational{
public:
    friend const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs){
        return doMultiply(lhs,rhs);
    };
};

template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs,const Rational<T>& rhs){
    ...
}
```

模板类不是类，而是用于生成类的模板。template 定义式应该跟随声明式放在头文件中。

- `operator*` 支持混合式操作，其允许隐式转换在参数列表中发生。
- 作为 template，`doMultiply` 不允许混合式操作，但 `operator*` 传给它的参数已经转换完成。

### 7.47 请使用 traits classes 表现类型信息

STL 主要由「用于表现容器、迭代器和算法」的 templates 组成，其次覆盖了若干工具性 templates 。

STL 共有 5 种迭代器分类：

- **input 迭代器** 仅向前移动，一次 1 步，只读且仅 1 次。  
  模仿指向输入文件的读指针 (read pointer)。
- **Output 迭代器** 仅向前移动，一次 1 步，只写且仅 1 次。  
  模仿指向输出文件的写指针 (write pointer)。

以上只适合 **一次性操作算法** (one-pass algorithms)。

- **forward 迭代器** 仅向前移动，一次 1 步，可读可写。
- **bidirectional 迭代器** 可前后移动，一次 1 步，可读可写。  
  `set` `multiset` `map` `multimap`
- **random 迭代器** 可前后移动，可跳跃距离，可读可写。  
  `vector` `deque` `string`

以上可用于 **多次性操作算法** (multi-pass algorithms)。

C++ 标准库分别提供了专属的卷标结构 (tag struct) 加以确认：

```c++
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};
```

STL 中存在一个工具性 template advance，用于将某个迭代器移动某个给定距离：

```c++
template<typename IterT,typename DistT>
void advance(IterT& iter,DistT d);
```

希望以如下方式实现 advance，以实现迭代器优势：

```c++
template<typename IterT,typename DistT>
void advance(IterT& iter,DistT d){
    if (iter is a random access iterator) {
        iter += d;
    } else {
        if ( d >= 0 ){
            while( d-- ) ++iter;
        } else {
            while( d++ ) --iter;
        }
    }
}
```

需要知晓 IterT 的类型信息，因此需要借助 **Traits**。

Traits 并不是 C++ 关键字或预定义的构件。Traits 是一种技术，是一个 C++ 程序员共同遵守的协议。

Traits 要求其必须能够施行于内置类型（如指针），因此不能通过将信息存储于类型中的方式实现，信息必须位于类型自身之外。

实现 Traits 的标准技术是将其放入一个 template 及其一或多个特化版本中。如 STL 中的 `iterator_traits`：

```c++
template<typename IterT>
struct iterator_traits;
```

一般 traits 被实现为 structs，但称之为 traits classes。

`iterator_traits` 的运作方式是：针对每一个类型 `IterT` ，在 `struct iterator_traits<IterT>` 内声明一个名为 `iterator_category` 的 typedef，后者用以确认 `IterT` 的迭代器分类。

`iterator_traits` 以两个部分实现上述要求。首先其要求每一个「用户自定义迭代器类型」必须嵌套一个 typedef，名为 `iterator_category`，用以确认适当的卷标结构。

以 deque 与 list 为例：

```c++
template<...>
class deque{
public:
    class iterator{
    public:
        typedef random_access_iterator_tag iterator_category;
    }
}

template<...>
class list{
public:
    class iterator{
    public:
        typedef bidirectional_iterator_tag iterator_category;
    }
}
```

而 `iterator_traits` 则能够将信息根据类型提取出来：

```c++
// 适应用户自定义类型
template<typename IterT>
struct iterator_traits{
    typedef typename IterT::iterator_category iterator_category;
}

// 偏特化版本 适应内置指针
template<typename IterT>
struct iterator_traits<IterT*>{
    typedef random_access_iterator_tag iterator_category;
}
```

以上即体现了设计并实现 trait class 的标准流程：

- 确认需要取得的类型相关信息。  
  例如对迭代器而言，希望取得分类 (category) 信息。
- 为信息选择名称。  
  例如 `iterator_category` 。
- 提供一个 template 和一组特化版本，内含支持的类型相关信息。  
  例如 `iterator_traits` 。

在先前的 advance 中，可以进行如下应用：

```c++
template <typename IterT,typename DistT>
void advance(IterT& iter,DistT d){
    if( typeid(typename std::iterator_traits<IterT>::iterator_category)
    == typeid(std::random_access_iterator_tag) ){
        ...
    }
}
```

如上代码存在一些问题：

- 编译问题，参考 **条款 48**。
- `IterT` 在编译期确定，即 if 语句中的条件在编译期即可有结果，却必须等到运行期。这不仅浪费时间，还可能造成可执行文件膨胀。

因此可以使用 **重载** 解决上述问题。

```c++
template <typename IterT,typename DistT>
void doAdvance(IterT& iter,DistT d,std::random_access_iterator_tag){
    iter += d;
}

template <typename IterT,typename DistT>
void doAdvance(IterT& iter,DistT d,std::bidirectional_iterator_tag){
    if ( d >= 0 ){
        while( d-- ) ++iter;
    } else {
        while( d++ ) --iter;
    }
}

template <typename IterT,typename DistT>
void doAdvance(IterT& iter,DistT d,std::input_iterator_tag){
    // 由于继承关系的存在，forward_iterator 也被此函数处理。
    if ( d < 0 ){
        throw std::out_of_range("Negative distance");
    }
    while( d-- ) ++iter;

}

template <typename IterT,typename DistT>
void advance(IterT& iter,DistT d){
    doAdvance(
        iter,
        d,
        typename std::iterator_traits<IterT>::iterator_category()
    );
}
```

总结如何使用 traits class：

- 建立一组重载函数或函数模板，彼此之间的差异只在于各自的 traits 参数，令每个函数实现码与其接受之 traits 信息相匹配。
- 建立一个控制函数或函数模板，调用上述重载函数并传递 traits class 的信息。

### 7.48 认识 template 元编程

模板元编程 (TMP,template metaprogramming) 是以 C++ 写成，执行于 C++ 编译器内的程序。TMP 的输出为从 templates 具现出的 C++ 源码。

TMP 是被发现而非发明出来的，当 templates 加入 C++ 时 TMP 即被引进，其主要有两大优势：

- TMP 使编程变得简单，提高了复用性，让不可能变为可能。
- TMP 执行于编译期，可以将部分工作从运行期提前，提高了运行效率与排错效率。

考虑 STL advance 的 `typeid` 实现方案：

```c++
template <typename IterT,typename DistT>
void advance(IterT& iter,DistT d){
    if( typeid(typename std::iterator_traits<IterT>::iterator_category)
    == typeid(std::random_access_iterator_tag) ){
        ...
    }
}
```

**条款 47** 指出，基于 `typeid` 的实现方案的效率比 traits 低，因为：

- 类型测试发生于运行期而非编译期。
- 「运行期类型测试」代码会被链接于可执行文件中。

此例展示了为何 TMP 的效率更高。

当传入一个非 `random_access_iterator` 时，如上代码将会出错。即便由于判断语句的存在，确保了运行时不会对 `random_access_iterator` 进行未定义操作，但编译器仍将报错。而 TMP 将针对不同类型形成不同代码，因此可以轻松实现。

此例展示了 TMP 如何将问题的解决简单化。

TMP 已被证明其图灵完备性 (Turing-complete) ，即它已经足够强大以处理任何计算，它可以声明变量、执行循环、编写及调用函数，但 TMP 实现相对于正常 C++ 语句实现迥然不同。针对 TMP 设计的程序库提供更高层级的语法。

以循环为例。TMP 并没有真正的循环构件，其循环效果藉由递归实现，这种递归与函数递归调用无关，而涉及「递归模板具现化」(recursive template instantiation)。

如下代码示例提供了阶乘运算：

```c++
template<unsigned n>
struct Factorial{
    enum {
        value = n * Factorial<n-1>::value;
    }
};
template<>
struct Factorial<0>{
    enum { value = 1 };
};
```

循环发生在 template 具现体 `Factorial<n>` 内部指涉另一个 `Factorial<n-1>` 时。当至特殊情况 `n = 0` 时递归结束。

每个 Factorial template 具现体都是一个 struct。每个 struct 都使用 enum hack 声明一个名为 `value` 的 TMP 变量，其用于保存当前计算值。对于 enum hack 技术详情，见 **条款 2**。

```c++
int main(){
    std::cout << Factorial<5>::value; // output: 120
}
```

实际应用中，常为达成以下目标使用 TMP ：

- **确保度量单位正确**
  - 在科学和工程应用程序中，确保量度单位（例如质量、距离、时间……等等）正确结合是绝对必要的。举个例子，将一个质量变量赋值给一个速度变量是错误的，但是将一个距离变量除以一个时间变量并将结果赋值给一个速度变量则成立。如果使用 TMP，就可以确保（在编译期）程序中所有量度单位的组合都正确，不论其计算多么复杂。这也就是为什么 TMP 可被用来进行早期错误侦测。这种 TMP 用途的一个有趣情况是，就连因次为分数的指数 (fractional dimensional exponents) 也可支持，但分数必须先在编译期被化简，例如 $time^{\frac12}$ 与 $time^{\frac48}$ 单位相同。
- **优化矩阵运算**
  - 使用 expression templates 可以消除临时对象并合并循环（如矩阵连乘）。
- **生成客户定制的设计模式实现品**
  - 设计模式如 Strategy，Observer，Visitor 等等都可以多种方式实现出来。运用所谓 policy-based design 之 TMP-based 技术，有可能产生一些 templates 用来表述独立的设计选项（所谓「policies」），然后可以任意结合它们，导致模式实现品带着客户定制的行为。这项技术已被用来让若干 templates 实现出智能指针的行为政策 (behavioral policies)，用以在编译期间生成数以百计不同的智能指针类型。这项技术已经超越编程工艺领域如设计模式和智能指针，更广义地成为 generative programming（殖生式编程）的一个基础。

## 8. 定制 new 和 delete

### 8.49 了解 new-handler 的行为

operator new 分配内存失败后将抛出异常。旧编译器将返回空指针。当抛出异常前，其先会调用一个客户指定的错误处理函数，即一个所谓的 new-handler。客户通过调用 `set_new_handler` （声明于 <new> 标准库） 设定这个函数。

```c++
namespace std {
    typedef void (*new_handler)();
    new_handler set_new_handler(new_handler p) noexcept;
}
```

`new_handler` 是一个函数指针，这个函数没有参数且返回 void。  
`set_new_handler` 需要一个 `new_handler`（新函数）并返回一个 `new_handler` (更改前的函数)。该函数不抛出异常。

允许这样使用 `set_new_handler`：

```c++
void outOfMem(){
    std::cerr << "Unable to satisfy request for memory\n";
    std::abort();
}

int main(){
    std::set_new_handler(outOfMem);
    int* pBigDataArray = new int[1e10L];
}
```

当 operator new 无法满足内存申请时，将不断调用 `new_handler` 函数，直到有足够内存（详见 **条款 51**）。

一个设计良好的 `new_handler` 函数必须做到一下几点：

- **让更多内存可被使用**  
  努力使下一次内存分配动作可能成功。
- **安装另一个 `new_handler`**  
  自动替换至有分配能力的 `new_handler`。
- **卸载 `new_handler`**  
  若找不到任何有分配能力的 `new_handler`，则考虑将 nullptr 传入 `set_new_handler`。
- **抛出 `bad_alloc`（或派生自 `bad_alloc`）的异常**  
  这个异常不会被 operator new 捕捉，将传播至申请内存处。
- **不返回**  
  通常调用 `abort()` 或 `exit()`。

以上选择将为实现 `new_handler` 提供弹性。

如若需要根据分配物所属的 class 来确定 `new_handler`，只需令每个 class 提供自己的 `set_new_handler` 与 operator new 。前者用于允许客户设定 `new_handler`，后者用于确保分配 class 对象内存的过程中使用 `new_handler`。

现有 Widget 类，将为其设定内存分配失败的行为。

```c++
class Widget{
public:
    static std::new_handler set_new_handler(std::new_handler p) noexcept;
    static void* operator new(std::size_t size_t) throw(std::bad_alloc);
private:
    static std::new_handler currentHandler;
};

std::new_handler Widget::currentHandler = nullptr;

std::new_handler Widget::set_new_handler(std::new_handler p) noexcept{
    std:: new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}
```

最后，Widget 的 operator new 负责完成一下事情：

- 调用标准 `set_new_handler`，告知 Widget 的错误处理函数。  
  这会将 Widget 的 `new_handler` 安装为 global `new_handler`。
- 调用 global operator new，执行实际的内存分配。如果分配失败，global operator new 会调用 Widget 的`new_handler`，因为那个函数刚刚被安装为 global`new_handler`。如果 global operator new 最终无法分配足够内存，会抛出一个 bad_alloc 异常。在此情况下 Widget 的 operator new 必须恢复原本的 global `new_handler`，然后再传播该异常。  
  为确保原本的 `new_handler` 总是能够被重新安装回去，Widget 将 global `new_handler` 视为资源并遵守 **条款 13** 的忠告，运用资源管理对象 (resource-managing objects) 防止资源泄漏。
- 如果 global operator new 能够分配足够一个 Widget 对象所用的内存，Widget 的 operator new 会返问一个指针，指向分配所得。Widget 析构函数会管理 global `new_handler`，它会自动将 operator new 被调用前的那个 global `new_handler`恢复回来。

如下代码使用 RAII 技术保存旧 new_handler 并重置。

```c++
class NewHandlerHolder{
public:
    explicit NewHandlerHolder(std::new_handler nh):handler(nh){} // 取得原 new_handler
    ~NewHandlerHolder() {
        // 释放时重置
        std::set_new_handler(handler);
    }
private:
    std::new_handler handler;
    NewHandlerHolder(const NewHandlerHolder&); // 组织 copying
    NewHandlerHolder& operator=(const NewHandlerHolder&);
}

void* Widget::operator new(std::size_t size) throw(std::bad_alloc){
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}
```

客户应如此使用：

```c++
void outOfMem();

Widget::set_new_handler(outOfMem); // 设定 outOfMem 作为 new_handler 函数
Widget* pw1 = new Widget;
std::string* ps = new std::string;
Widget::set_new_handler(nullptr); // 设定 nullptr 作为 new_handler 函数
Widget* pw2 = new Widget;
```

一般地，使用 mixin 风格的基类以允许子类继承单一能力——在此处即「设定 class 专属 new_handler 的能力」。将这个基类转换为 template ，以使每个子类获得实体互异的 class data 复件：

```c++
template<typename T>
class NewHandlerSupport{
public:
    static std::new_handler set_new_handler(std::new_handler p) noexcept;
    static void* operator new(std::size_t size_t) throw(std::bad_alloc);
private:
    static std::new_handler currentHandler;
};

template<typename T>
std::new_handler
NewHandlerSupport::set_new_handler(std::new_handler p) noexcept {
    std:: new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc){
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}

template<typename T>
std::new_handler NewHandlerHolder<T>::currentHandler = nullptr;
```

有了这个模板类，可以为 Widget 轻松添加 `set_new_handler`：

```c++
class Widget:public NewHandlerSupport<Widget>{
    ...
};
```

在 `NewHandlerSupport<T>` 中，代码内并未使用到参数 `T`。实际上 `T` 并不需要被直接使用，其作为达成实体互异的条件即可，参数 `T` 只是用来区分不同的子类，Template 机制将为每个 `T` 生成一份 currentHandler。

Widget 继承自一个模板化的基类，而后者却又以 Widget 作为类型参数。这是一种有用的技术，称为 **怪异的循环模板模式** (CRTP,curiously recurring template pattern)。

### 8.50 了解 new 和 delete 的合理替换时机

一般有如下常见理由，需要替换编译器提供的 operator new 或 operator delete：

- 用来检测运用上的错误。

如果 delete 失败，无疑会导致内存泄露 (memory leaks)。如果多次 delete 则会导致不确定行为。自行设计 new 与 delete 可以避免这些异常。

- 优化效率

new 与 delete 需要处理的情况非常复杂，包括大块内存、小块内存、大小混合型内存。其必须接纳各种分配形态，范围从程序存活期间的少量区块动态分配，到大数量短命对象的持续分配和归还。还必须考虑内存碎片问题，避免运行一段时间后无整块大内存可用。

对不同的对象进行合理定制 new 与 delete 相较于缺省而言效率更高。

- 收集使用上的统计数据

为了定制出最合理的 new 与 delete，必须对程序进行分析，主要需要了解：分配区块大小分布、寿命分布、倾向于 FIFO （先进先出）或 LIFO （后进先出）还是完全随机的分配与回收、分收形态是否随时间改变、最大分配量等等。

如下代码为检测溢出的一种方法：

```c++
// 溢出检测标记 将插入至内存首尾 当内存首尾发生改变时意味着溢出。
static const int signature = 0xDEADBEEF;
typedef unsigned char Byte;

void* operator new(std::size_t size) throw(std::bad_alloc){
    using namespace std;
    size_t realSize = size + 2 * sizeof(int);

    void* pMem = malloc(realSize);
    if (!pMem) throw bad_alloc();

    // 在首尾插入溢出检测标记
    *(static_cast<int*>(pMem)) = signature;
    *(reinterpret_cast<int*>(static_cast<Byte*>(pMem)+realSize-sizeof(int))) = signature;

    return static_cast<Byte*>(pMem) + sizeof(int);
}
```

如上代码中的 operator new 略去了反复调用 new-handling 函数（详见 **条款 51**），现在首先讨论内存对其问题。

许多计算机体系结构要求特定类型必须放在特定内存地址上，例如一般要求内存地址必须是 4 倍数，而 double 必须是 8 倍数。

`malloc()` 分配内存时将遵守这个规则，但上例代码中返回了一个偏移一个 int 大小的指针，这种未对齐的指针可能造成崩溃或低效率运行。

实际上已有相当多 IDE 提供的调试状态的内存管理函数、商业或开源的内存管理器提供给程序员，无需再自行设计内存管理。

一般有如下理由促使替换缺省的 new 与 delete：

- 为了检测运用上的错误（如前所述）。
- 为了收集动态分配内存的使用统计信息（如前所述）。
- 为了提高分配与回收速度。  
  泛用型分配器一般会比定制型分配器慢。
- 为了降低缺省内存管理器带来的额外空间开销。  
  泛用型分配器一般会比定制型分配器占用更多内存。
- 为了弥补缺省分配器中的非最佳对齐。  
  某些 x86 架构可能允许非对齐，但这会降低效率。
- 为了将相关对象成簇集中。  
  如果知晓某个数据结构往往被一起使用，则可以专门为此结构创建另一个 heap，以降低内存缺页频率。  
  new 和 delete 的 placement 版本可能可以实现这种集簇行为。
- 为了获得非传统的行为。  
  有时候你会希望 operator new 和 delete 做编译器附带版没做的某些事情。例如分配和归还共享内存 (shared memory) 内的区块，但唯一能够管理该内存的只有 C API 函数，那么写下一个定制版 new 和 delete (很可能是 placement 版本，见 **条款 52**），就可以用 C++ 习惯调用 C API。你也可以写一个自定的 operator delete，在其中将所有归还内存内容覆盖为 0，藉此增加应用程序的数据安全性。

### 8.51 编写 new 和 delete 时需固守常规

**条款 50** 指明了什么时候可以定制 operator new 与 delete。

此条款将解释定制 operator new 与 delete 时应遵守什么规则。

对于 operator new 来说，主要需遵守如下条件：

- 实现一致性 operator new 必须返回正确值。
- 内存不足时必须调用 `new_handler()`。
- 必须有对付零内存需求的准备。C++ 要求即便 0 byte，operator new 仍需要返回一个合法的指针。这种设定主要为了简化语言的其他部分。
- 避免不慎遮掩正常形式的 new（详见 **条款 52** ）。

operator new 返回：

- 成功分配则返回指向内存的指针。
- 失败则不断调用 `new_handler()`，尝试释放内存并重新分配。
- 否则抛出 bad_alloc 异常。

```c++
// 示例为成员版本
void* Base::operator new(std::size_t size) throw(std::bad_alloc){
    using namespace std;
    if (size != sizeof(Base)){
        // 防止基类的 operator new 被子类继承
        // C++ 要求对象必须具有非零大小，因此 sizeof 不可能为 0
        return ::operator new(size);
    }

    if (size == 0){
        // 处理 0 byte 申请，将其视为 1 byte
        size = 1;
    }
    while (true){
        // 表明其是一个无穷循环
        尝试分配 size bytes;

        if ( 分配成功 ){
            return 指针;
        }

        分配失败
        // 由于没有所谓 get_new_handler ，因此需要如此操作
        // 多线程需要锁
        new_handler globalHandler = set_new_handler(0);
        set_new_handler(globalHandler);

        if (globalHandler) {
            (*globalHandler)();
        } else {
            throw std::bad_alloc();
        }
        
    }
}
```

如果要定制 class 的数组分配行为，则需实现 operator new[] ，读作 array new。在这之中只需分配一块未加工内存即可，因为无法对 array 之内尚未存在的对象做任何事，也不知晓对象实际大小（被子类调用，而子类可能更大，在基类数组中是可以存放子类的）。

对于 operator delete 来说，主要需遵守如下条件：

- 保证删除空指针永远安全。

```c++
// 示例为成员版本
void Base::operator delete(void* rawMemroy) throw(){
    if (rawMemroy == 0) return;

    if (size != sizeof(Base)){
        ::operator delete(rawMemroy);
        return;
    }

    回收 rawMemroy 所指内存
}
```

### 8.52 写了 placement new 也要写 placement delete

```c++
Widget* pw = new Widget;
```

如上语句共有两个函数被调用：

- operator new
- Widget 默认构造函数

假设第一个函数调用成功而第二个函数调用异常，C++ 运行期系统有义务归还第一个函数分配的内存。

如果没有定制的 operator new 与 delete，C++ 将尝试调用默认行为。但当使用了定制的 operator new 时，C++ 将调用一个与 new 额外参数列表相同的 delete，找不到时不调用 delete，这意味着可能引起内存泄漏。

```c++
class Widget{
public:
    static void* operator new(std::size_t,std::ostream& logStream) throw(std::bad_alloc);
    static void operator delete(void* pMemory,std::size_t size) noexcept;
}
```

如果 operator new 接受的参数除了必需的 `size_t` 之外还有其他，那么它便是个 placement new。

> 实际上，placement new 最初的版本用于在一个指定位置进行构造对象：
>
> ```c++
> void operator new(std::size_t,void* pMemory) noexcept;
> ```
>
> 后通过扩展，一般性的「placement new」意味着带有任意额外参数的 new。

如上的 Widget 类的构造函数抛出异常后，可能引起内存泄漏，因为它需要一个：

```c++
void operator delete(void*,std::ostream&) noexcept;
```

添加以上实现，则不会再内存泄露。

这个与 placement new 对应的 placement delete 不会被用户调用，它仅在伴随 placement new 调用而触发的构造函数出现异常时被调用：

```c++
Widget* pw = new(std::cerr) Widget;
delete pw; // 调用了一个正常形式的 delete
```

这意味正常形式的 delete 同样要负责避免 placement new 可能造成的内存泄漏。

缺省情况下 C++ 将在全局作用域提供以下形式的 operator new：

```c++
void* operator new(std::size_t) throw(std::bad_alloc);
void* operator new(std::size_t,void*) noexcept;
// nothrow 版本，失败时仅返回空指针，不抛异常
void* operator new(std::size_t,const std::nothrow_t&) noexcept;
```

基类中的 placement new 将覆盖全局 new。
子类中的 placement new 将覆盖基类 new 与全局 new。

```c++
class Base{
public:
    static void* operator new(std::size_t,std::ostream& logStream)
    throw(std::bad_alloc);
}

Base* pb = new (std::cerr) Base; // Right
Base* pb = new Base; // Error

class Derived{
public:
    static void* operator new(std::size_t) throw(std::bad_alloc);
    Derived* pd = new Derived;
    Derived* pd = new (std::clog) Derived; // Error
}
```

为了防止这种情况（如非必要），需要设计一个 base class ，内含所哟正常形式的 new 和 delete。
而希望扩展的类型应利用继承机制与 using 声明式取得标准形式。

```c++
class StandardNewDeleteForms{
public:
    static void* operator new(std::size_t) throw(std::bad_alloc){
        return ::operator new(size);
    }
    static void* operator delete(void* pMemory) noexcept{
        return ::operator delete(pMemory);
    }
    static void* operator new(std::size_t,void* ptr) throw(std::bad_alloc){
        return ::operator new(size,ptr);
    }
    static void* operator delete(void* pMemory,void* ptr) noexcept{
        return ::operator delete(pMemory,ptr);
    }
    static void* operator new(std::size_t,const std::nothrow_t&) throw(std::bad_alloc){
        return ::operator new(size,nt);
    }
    static void* operator delete(void* pMemory,const std::nothrow_t&) noexcept{
        return ::operator delete(pMemory);
    }
}

class Widget: public StandardNewDeleteForms{
public:
    using StandardNewDeleteForms::operator new;
    using StandardNewDeleteForms::operator delete;
    
    static void* operator new(std::size_t,std::ostream& logStream) throw(std::bad_alloc);
    static void operator delete(void* pMemory,std::size_t size) noexcept;
}
```
