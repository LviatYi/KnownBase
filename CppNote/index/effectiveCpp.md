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
class Drived: public Base{
public:
    Drived(const Drived& rhs);
    Drived& operator=(const Drived& rhs);
private:
    int num;
}

Drived::Drived(const Drived& rhs):num(rhs.num){};
Drived& Drived::operator=(const Drived& rhs){
    this->num = rhs.num;
};
```

如上 copying 函数只顾及了子类中的内容，而忽视了对基类内容的拷贝。

应改为：

```c++
class Drived: public Base{
public:
    Drived(const Drived& rhs);
    Drived& operator=(const Drived& rhs);
private:
    int num;
}

Drived::Drived(const Drived& rhs):Base(rhs),num(rhs.num){};
Drived& Drived::operator=(const Drived& rhs){
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

使用函数替换静态成员请参考条款 4 。

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

如条款 3 所述，以 `const` 修饰 `operator*` 的返回类型可避免如下错误：

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

值传递意味着原传入值不被改变，而 `const reference` 也提供这种保证。
而且还有如下两个好处：

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
