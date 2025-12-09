# 浅论「组合大于继承」

## 继承的问题

继承：尝试使用唯物主义的范式描述一个客体。然而主体真的可以做到绝对客观吗？

- 多继承被扼杀，但客观现实中，难道不存在「即是，又是」的事物吗？多继承被禁止的原因，即避免「标识符矛盾」。机器不喜欢二义性，为了有效沟通，二义性必须被消除。语言如何消解二义性？通过添加定语。编程如何消解二义性？禁止多继承。这样一对比，后者的解决方案似乎有点粗暴。但对于继承体系而言，目前没有更好的解决方案。
- 继承是白盒复用。继承会无言地复制所有来自父类的复杂性，继承者被强加义务来了解所有内部实现。
  - 绝无可能！你能做的只是捕获当前版本快照下的细节。预判未来的变化是不可能的。函数签名是函数体的「降熵」，必然损失信息量。除非一个函数名的意义包含所有实现细节，但这不可能。
  - 随着继承树的增长，复杂性也呈线性增长。

> 该例出自 Effective Java

```JAVA
public class InstrumentedHashSet<E> extends HashSet<E> {
    private int addCount = 0;

    @Override
    public boolean add(E e) {
        addCount++;
        return super.add(e);
    }

    @Override
    public boolean addAll(Collection<? extends E> c) {
        addCount += c.size();
        return super.addAll(c);
    }

    public int getAddCount() {
        return addCount;
    }
}
```

```JAVA
InstrumentedHashSet<String> set = new InstrumentedHashSet<>();
set.addAll(List.of("A", "B", "C"));

System.out.println(set.getAddCount()); // 预期是 3 实际是 6
```

该例中：

- 父类实现细节的依赖
- 继承破坏了封装性
  - 子类的正确性依赖于父类的实现细节（如 addAll 调用 add），而父类的实现可能在后续版本中发生变化，导致子类行为异常。

作为使用者，关心的是「怎么用」，而不是「历史、意义、成因」。

> 动物分类学不通过 DNA 判定哺乳动物，而是依据行为特征和生理结构（呼吸空气、哺乳后代、体表被毛）。我们关注的是"API 和行为"，而非"实现细节"。成为哺乳动物的原因不是源自某种原型生物的迭代，而是因为具备哺乳动物的外在表现与行为特征。
