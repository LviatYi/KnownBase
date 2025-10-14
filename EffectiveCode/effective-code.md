# Effective Code

## 让无效状态在类型中无法被表达

在面向对象的视角中，事物可以被抽象为一系列状态和其转换规则的集合。  

显然，在所有状态组合中，并非所有的组合都是有效的。比如，用户的年龄不可能是负数，使用非负整数即可在代码中规避这种无效状态的表达。

### 使用枚举表达状态，而非布尔拼贴

```Rust
// Not Effective
pub struct DisplayProps {
    pub x: u32,
    pub y: u32,
    pub monochrome: bool,
    // `fg_color` must be (0, 0, 0) if `monochrome` is true.
    pub fg_color: RgbColor,
}
```

```Rust
// Effective
pub enum Color {
    Monochrome,
    Foreground(RgbColor),
}

pub struct DisplayProps {
    pub x: u32,
    pub y: u32,
    pub color: Color,
}
```

### 使用 newtype 包装原始类型

newtype 最基础的作用是对一个简单类型提供了文本语义。

```Rust
struct Millimeter(f64);
struct UserId(Uuid); struct OrderId(Uuid);
```

此外，在 Rust 中，还能轻松地为 newtype 赋予行为或 trait。

```Rust
pub struct WeekDay(u8);

impl WeekDay {
    pub fn new(day: u8) -> Option<Self> {
        if day < 1 || day > 7 {
            None
        } else {
            Some(WeekDay(day))
        }
    }
}
```

### 使用类型系统表达串行顺序

用单向流动的返回值表达状态转换。

```Rust
struct ClientDraft { /* ... */ }
struct ClientConnected { /* ... */ }
struct ClientAuthed { /* ... */ }

impl ClientDraft {
    fn connect(self) -> ClientConnected { /* ... */ }
}
impl ClientConnected {
    fn auth(self, token: Token) -> ClientAuthed { /* ... */ }
}
impl ClientAuthed {
    fn get(&self, url: Url) -> Response { /* ... */ }
}
```

还可以将构建器类型化：

```Rust
pub struct UserBuilder<NameSet, EmailSet> {
    name: Option<String>,
    email: Option<String>,
    _name: PhantomData<NameSet>,
    _email: PhantomData<EmailSet>,
}

pub struct User;

pub enum Set {}
pub enum Unset {}

impl UserBuilder<Unset, Unset> {
    pub fn new() -> Self {
        Self {
            name: None,
            email: None,
            _name: Default::default(),
            _email: Default::default(),
        }
    }
    pub fn with_name(self, n: &str) -> UserBuilder<Set, Unset> {
        UserBuilder::<Set, Unset> {
            name: Some(n.to_string()),
            email: self.email,
            _name: Default::default(),
            _email: Default::default(),
        }
    }
}

impl UserBuilder<Set, Unset> {
    pub fn with_email(self, e: &str) -> UserBuilder<Set, Set> {
        UserBuilder::<Set, Set> {
            name: self.name,
            email: Some(e.to_string()),
            _name: Default::default(),
            _email: Default::default(),
        }
    }
}

impl UserBuilder<Set, Set> {
    pub fn build(self) -> User {
        User
    }
}
```
