# Cell RefCell in Rust

![StackOverflow][badge-stackoverflow] ![CC BY-SA 4.0][badge-CCBYSA4]

**翻译** 自 [**StackOverflow**](https://stackoverflow.com/a/45674912/26125642) | [**CC BY-SA 4.0**][CCBYSA4]

---

Rust 有两个基本概念：

- **Ownership** 所有权
- **Mutability** 可变性

各种指针类型都与 **所有权** 有关 (Box Rc Arc)：它们允许 控制 单个对象 是否有 单个或多个 所有者。  
各种单元类型都与 **可变性** 有关 (Cell RefCell Mutex RwLock AtomicXXX)。

---

Rust 安全性的基本规则是：**非别名非可变性** (Aliasing NAND Mutability)。这意味着，一个对象只有在其内部不存在其他引用时，才能被安全地更改。

该规则通常由借用检查器 (borrow checker) 在编译时强制执行：

- 如果有 `&T` ，则不能同时对作用域中的同一个对象拥有一个 `&mut T`。
- 如果有 `&mut T` ，则不能在范围内同时拥有对同一对象的任何引用。

即「同时只能存在一个可变引用，或多个不可变引用」。

然而该限制在一些场景下极大地降低了灵活性，有时确实需要能够对同一对象进行多个引用并对其进行修改。此时是 Cell 的用武之地。

Cell 和 RefCell 的思想是以受控方式 允许存在别名并进行修改：

- Cell 防止创建指向其内部的引用，以避免 **悬垂引用** (dangling references)。
- RefCell 将 **非别名异或可变性** (Aliasing XOR Mutability) 的检查从 **编译时** 转移到 **运行时**。

该功能亦被称为 **内部可变性** (interior mutability)，即允许修改一个 从外部看起来不可变的 对象 `&T`。

当这种可变性扩展到多个线程时，您将使用 Mutex RwLock 或 AtomicXXX ；它们提供相同的功能：

- **AtomicXXX** (Cell) 不涉及内部，只是移入/移出。
- **RwLock** (RefCell) 可以通过守卫获取内部的引用。
- **Mutex** （简化的 RwLock）不区分只读保护和写保护。因此在概念上类似于仅具有 borrow_mut 方法的 RefCell 。

---

- **Box** (C++ unique_ptr)
- **Arc** (C++ shared_ptr)
- **Rc** （C++ shared_ptr 的非线程安全版本）

Cell 和 RefCell 类似于可变类型，但提供了防止别名问题的额外保证。可以将 Cell 视为 `std::atomic` ，将 RefCell 视为 `std::shared_mutex` 的非线程安全版本（尝试获取锁时将抛出异常而不是阻塞）。

```
+-----------+
| Ownership |
+--+--------+                              +================+
   |                         +-Static----->| T              |(1)
   |                         |             +================+
   |                         |
   |                         |             +================+
   |          +-----------+  | Local    Val| Cell<T>        |(1)
   +-Unique-->| Borrowing +--+-Dynamic---->|----------------|
   |          +-----------+  |          Ref| RefCell<T>     |(1)
   |                         |             +================+
   |                         |
   |                         |             +================+
   |                         | Threaded    | AtomicT        |(2)
   |                         +-Dynamic---->|----------------|
   |                                       | Mutex<T>       |(1)
   |                                       | RwLock<T>      |(1)
   |                                       +================+
   |
   |
   |                                       +================+
   |                         +-No--------->| Rc<T>          |
   |                         |             +================+
   | Locally  +-----------+  |
   +-Shared-->| Mutable?  +--+             +================+
   |          +-----------+  |          Val| Rc<Cell<T>>    |
   |                         +-Yes-------->|----------------|
   |                                    Ref| Rc<RefCell<T>> |
   |                                       +================+
   |
   |
   |                                       +================+
   |                         +-No--------->| Arc<T>         |
   |                         |             +================+
   | Shared   +-----------+  |
   +-Between->| Mutable?  +--+             +================+
     Threads  +-----------+  |             | Arc<AtomicT>   |(2)
                             +-Yes-------->|----------------|
                                           | Arc<Mutex<T>>  |
                                           | Arc<RwLock<T>> |
                                           +================+
```

- 在 (1) 情况下，`T` 可以替换为 `Box<T>`
- (2) 中，当 `T` 是 `bool` 或数字类型时使用 `AtomicT`

[badge-stackoverflow]: https://img.shields.io/badge/Stack_Overflow-FE7A16?style=for-the-badge&logo=stack-overflow&logoColor=white
[badge-CCBYSA4]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
[CCBYSA4]: https://creativecommons.org/licenses/by-sa/4.0/
