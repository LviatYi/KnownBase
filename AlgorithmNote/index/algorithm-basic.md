# 1. 算法基础

## 1.1 伪代码

`INSERTION-SORT(A)`

```vb {.line-numbers}
for j = 2 to A.length
    key = A[j]
    // Insert A[j] into the sorted sequence A[1..j-1]
    i = j - 1
    while i > 0 and A[i] > key
        A[i+1] = A[i]
        i = i - 1
    A[i+1] = key
```

伪代码遵循以下约定：

- 缩进表示块结构。
- `while` `for` `repeat-until` `if-else` 等结构与其他高级语言具有相同作用。但不存在局部变量的概念，即块内变量在结束后仍有效。
- `for` 循环扩充了 `by` 关键字以定义步长。
- `//` 表示注释。
- 允许多重赋值，如 `i=j=e` ，等价于 `j=e i=j` 。
- 除非另有定义，一般不使用全局变量。
- 允许数组与索引访问。`A[i]` 。
- 允许对象与属性访问。`A.length` 。
- 存在按值传递与指针传递。
- 具有短路运算符。

## 1.2 算法复杂度

好的算法具有：

1. **正确性**
2. **简明性** 算法应思路清晰、层次分明、容易理解、利于编码和调试。
3. **效率** 算法应有效使用存储空间，并具有高的时间效率。
4. **最优性** 算法的执行时间已达到求解该类问题所需时间的下界。

### 1.2.1 时间复杂度

一个算法的 **时间复杂度** (time complexity) 是指算法运行所需要的时间。

设有一个在抽象机上运行的算法 $A$ ， $a_i$ 是执行第 $i$ 个运算 $O_i$ 所需的时间， $I$ 是某次运行时的输入数据，  
$n$ 是数据规模 ，  
算法 $A$ 的运行时间 $T$ 是 $n$ 和 $I$ 的函数，记为 $T(n,I)$ 。

又设在该次运算中，抽象机共有 $m$ 个基本运算，  
第 $i$ 个基本运算 $O_i$ 的执行次数为 $\beta_i$ , $1 \leqslant i \leqslant m$ , $\beta_i$ 也是 $n$ 和 $I$ 的函数，记为 $\beta_i(n,I)$ 。那么，算法 $A$ 在输入为 $I$ 时的运行时间是：

$$T(n,I)=\sum_{i=1}^{m}{\alpha_i \beta_i(n,I)}$$

**最好情况** (best case)  
 $$B(n)=min\{T(n,I)|I\in{D_n}\}=T(n,I')$$  
**最坏情况** (worst case)  
 $$B(n)=max\{T(n,I)|I\in{D_n}\}=T(n,I^*)$$  
**平均情况** (average case) $$A(n)=\sum_{I\in{D_n}}P(I)T(n,I)$$

（ $I'$ 与 $I^*$ 分别为最好和最坏情况时的数据实例）

### 1.2.2 空间复杂度

程序运行所需的存储空间包括以下两部分。

- **固定空间需求** (fixed space requirement) 这部分空间主要包括程序代码、常量、简单变量、定长成分的结构等所占的空间。与所处理 **数据** 的大小与数量 **无关** 。
- **可变空间存储** (variable space requirement) 这部分空间大小与算法处理的数据规模有关，包括 **数据本身所占空间** 与处理其所需要的 **额外空间** ，例如运行递归算法所需的系统栈空间。

## 1.3 渐进表示法

### 1.3.1 函数符号表示

#### 1.3.1.1 大 $O$ 符号 渐进上界

**Def.** 设 $f$ 和 $g$ 是定义域为自然数集 $N$ 上的函数。若存在正数 $c$ 和 $n_0$ ，使得对一切 $n \geqslant n_0$ 有 $$ 0 \leqslant f(n) \leqslant c g(n)$$
成立，则称 $f(n)$ 的渐进上界是 $g(n)$ ，记作
  $$f(n)=O(g(n))$$

> 设 $f(n)=n^2+n$ ，则 $f(n)=O(n^2)$，取 $c=2$ , $n_0=1$ 即可  
> $f(n)=O(n^3)$，取 $c=1$ , $n_0=2$ 即可

- $f(n)=O(g(n))$，$f(n)$ 的阶不高于 $g(n)$ 的阶。
- 可能存在多个正数 $c$ ，只要指出一个即可。
- 对前面有限个 $n$ 值可以不满足不等式。( $n \geqslant n_0$ )
- 常函数可以写作 $O(1)$ 。

#### 1.3.1.2 大 $\Omega$ 符号 渐进下界

**Def.** 设 $f$ 和 $g$ 是定义域为自然数集 $N$ 上的函数。若存在正数 $c$ 和 $n_0$ ，使得对一切 $n \geqslant n_0$ 有 $$ 0 \leqslant c g(n) \leqslant f(n)$$
成立，则称 $f(n)$ 的渐进下界是 $g(n)$ ，记作
  $$f(n)=\Omega(g(n))$$

> 设 $f(n)=n^2+n$ ，则 $f(n)=\Omega(n^2)$，取 $c=1$ , $n_0=1$ 即可  
> $f(n)=\Omega(100n)$，取 $c=\frac{1}{100}$ , $n_0=2$ 即可

- $f(n)=\Omega(g(n))$，$f(n)$ 的阶不低于 $g(n)$ 的阶。
- 可能存在多个正数 $c$ ，只要指出一个即可。
- 对前面有限个 $n$ 值可以不满足不等式。( $n \geqslant n_0$ )

#### 1.3.1.3 小 $o$ 符号 非渐进紧确上界

**Def.** 设 $f$ 和 $g$ 是定义域为自然数集 $N$ 上的函数。若存在正数 $c$ 和 $n_0$ ，使得对一切 $n \geqslant n_0$ 有 $$ 0 \leqslant f(n) < c g(n)$$
成立，则记作
  $$f(n)=o(g(n))$$

> 设 $f(n)=n^2+n$ ，则  
> $f(n)=o(n^3)$，取 $c\geqslant 1$ 显然成立

- $f(n)=o(g(n))$，$f(n)$ 的阶低于 $g(n)$ 的阶。
- 对不同正数 $c$ ，$n_0$ 不一样。$c$ 越小 $n_0$ 越大。
- 对前面有限个 $n$ 值可以不满足不等式。( $n \geqslant n_0$ )

#### 1.3.1.4 小 $\omega$ 符号 非渐进紧确下界

**Def.** 设 $f$ 和 $g$ 是定义域为自然数集 $N$ 上的函数。若存在正数 $c$ 和 $n_0$ ，使得对一切 $n \geqslant n_0$ 有 $$ 0 \leqslant c g(n) < f(n)$$
成立，则记作
  $$f(n)=\omega(g(n))$$

> 设 $f(n)=n^2+n$ ，则  
> $f(n)=\omega(n)$

- $f(n)=\omega(g(n))$，$f(n)$ 的阶高于 $g(n)$ 的阶。
- 对不同正数 $c$ ，$n_0$ 不一样。$c$ 越大 $n_0$ 越大。
- 对前面有限个 $n$ 值可以不满足不等式。( $n \geqslant n_0$ )

#### 1.3.1.5 $\Theta$ 符号

**Def.** 若 $f(n)=O(g(n))$ 且 $f(n)=\Omega(g(n))$ ，则记作 $$f(n)=\Theta(g(n))$$

> 设 $f(n)=n^2+n,g(n)=100n^2$ 那么有 $f(n)=\Theta(g(n))$

- $f(n)$ 的阶与 $g(n)$ 的阶相等。
- 对前面有限个 $n$ 值可以不满足条件。

### 1.3.2 有关函数渐近界的定理

#### 1.3.2.1 定理 1

设 $f$ 和 $g$ 是定义域为自然数集合的函数。

1. 如果 $lim_{n \to \infty}{\frac{f(n)}{g(n)}}$ 存在，并且等于某个常数 $c>0$ ，那么 $f(n)=\Theta(g(n))$
2. 如果 $lim_{n \to \infty}{\frac{f(n)}{g(n)}}=0$ ，那么 $f(n)=o(g(n))$
3. 如果 $lim_{n \to \infty}{\frac{f(n)}{g(n)}}=+\infty$ ，那么 $f(n)=\omega(g(n))$

可证明：多项式函数的阶低于指数函数的阶  
$$n^d=o(r^n),r>1,d>0$$  
可证明：对数函数的阶低于幂函数的阶  
$$\ln{n}=o(n^d),d>0$$

#### 1.3.2.2 定理 2 传递性

设 $f,g$ 和 $h$ 是定义域为自然数集合的函数。

1. 如果 $f=O(g)$ 且 $g=O(h)$ ，那么 $f=O(h)$
2. 如果 $f=\Omega(g)$ 且 $g=\Omega(h)$ ，那么 $f=\Omega(h)$
3. 如果 $f=\Theta(g)$ 且 $g=\Theta(h)$ ，那么 $f=\Theta(h)$

函数的阶之间的关系具有传递性

> 按照阶从高到低排序以下函数：  
> $f(n)=\frac{(n^2+n)}{2},g(n)=10n$  
> $h(n)=1.5^n,t(n)=n^{\frac12}$
>
> $h(n)=\omega(f(n)),$  
> $f(n)=\omega(g(n)),$  
> $g(n)=\omega(t(n)),$
>
> 排序：$h(n),f(n),g(n),t(n)$

#### 1.3.2.3 定理 3

设函数 $f$ 和 $g$ 的定义域为自然数集，若对某个其他函数 $h$ ，有 $f=O(h)$ 和 $g=O(h)
$ ，那么  
$$f+g=O(h)$$

该性质可以推广到有限个函数。  
算法由有限步骤构成。若每一步的时间复杂度函数的上界都是 $h(n)$ 那么该算法的时间复杂度函数可以写作 $O(h(n))$ 。

### 1.3.3 标准记号与常用函数

指数级：  
$2^n,3^n,n!,\ldots$  
多项式级：  
$n,n^2,n\log{n},n^\frac12,\ldots$  
对数多项式级：  
$\log{n},\log^2{n},\log{\log{n}},\ldots$

#### 1.3.3.1 对数函数

符号：  
$\lg{n}=\log_2{n}$（不关注底数）  
$\lg^k{n}=(\lg{n})^k$（取幂）  
$\lg{\lg{n}}=\lg({\lg{n}})$（复合）

性质：  
$\log_2{n}=\Theta(\log_l{n})$  
$a^{\log_b{n}}=n^{\log_b{a}}$  
$\log_b{n}=o(n^{\alpha})\quad\alpha>0$

#### 1.3.3.2 指数函数与阶乘

**Stirling 公式** $n!=\sqrt{2\pi n}(\frac{n}{e})^{n}(1+\Theta(\frac1n))$

$n!=o(n^n)$  
$n!=\omega(2^n)$  
$\bf{\log{n!}=\Theta(n\log{n})}$

#### 1.3.3.3 取整函数

$\lfloor x \rfloor$ 表示小于等于 $x$ 的最大的整数  
$\lceil x \rceil$ 表示大于等于 $x$ 的最小的整数

> $\lfloor 2.6 \rfloor = 2$  
> $\lceil 2.6 \rceil =3$  
> $\lfloor 2 \rfloor = \lceil 2 \rceil =2$

应用  
二分搜索中：

- 输入数组长度 $n$
- 中位数的位置 $\lfloor \frac n2 \rfloor$
- 与中位数比较后子问题大小 $\lfloor \frac n2 \rfloor$

#### 1.3.3.4 斐波那契数列

使用如下递归式定义 **斐波那契数列**：

$$F_0=0$$ $$F_1=1$$ $$F_i=F_{i-1} + F_{i-2},i \geqslant 2$$

斐波那契数列与 **黄金分割率** $\varphi$ 及其共轭数 $\psi$ 有关，其为以下方程的两根：

$$x^2 = x+1$$

$$\varphi =\frac {1+\sqrt{5}} {2}$$ $$\psi =\frac {1-\sqrt{5}} {2}$$

$$F_i = \frac{\varphi^i - \psi ^i}{\sqrt{5}}$$

这蕴涵着

$$F_i = \lfloor \frac{\varphi^i}{\sqrt 5} + \frac 12 \rfloor$$

## 1.4 递推关系分析

### 1.4.1 数列求和公式

#### 1.4.1.1 等差、等比数列与调和级数

$$\sum^{n}_{k=1}{a_k}=\frac{n(a_1+a_n)}{2} $$

$$\sum^n_{k=0}aq^k=\frac{a(1-q^{n+1})}{1-q}\quad\sum^\infty_{k=0}aq^k=\frac{a}{1-q}(q<1>)$$

$$\sum^{n}_{k=1} {\frac 1k}=\ln{n}+O(1)$$

> 二分检索算法  
> 输入：数组 $T$ ，下标从 $l$ 到 $r$ ；数 $x$  
> 输出：$j$
>
> ```C {.line-numbers}
> l <- 1; r <- n
> while l <= r do
>   m <- ⌊(l+r/2)⌋
>   if T[m] = x then return m //x 中位元素
>   else if T[m] > x then r<- m-1
>     else l <- m+1
> return 0
> ```
>
> 假设 $n=2^k-1$ ，输入有 $2n+1$ 种
>
> - **$x$ 在 $T$ 中**  
>   $x=T[1]$ > $x=T[2]$ > $\cdots$ > $x=T[n-1]$ > $x=T[n]$
> - **$x$ 不在 $T$ 中**  
>   $x<T[1]$ > $T[1]<x<T[2]$ > $\cdots$ > $T[n-1]<x<T[n]$ > $T[n]<x$
>
> 比较 1 次 1 个比较 2 次 2 个  
> 比较 3 次 4 个比较 $k$ 次 $2^{k-1}$  
> 总次数：对每个输入乘以次数并求和  
> 则
>
> $$
> \begin{aligned}
>   A(n) &= \frac{1}{2n+1}[\sum^{k-1}_{t=1}{t2^{t-1}+k(2^{k-1}+n+1)}]\\
>   &= \frac{k2^k-2^k+1+k2^k}{2^{k+1}-1}\\
>   &\approx k-\frac12\\
>   &=\lfloor \log n \rfloor + \frac 12
> \end{aligned}
> $$

#### 1.4.1.2 估计和式上界的放大法

放大法：

1. $\sum^n_{k=1}a_k\leqslant na_{max}$
2. 假设存在常数 $r<1$ ，使得对一切 $k\geqslant 0$ 有 $\frac{a_{k+1}}{a_k}\leqslant r$ 成立  
   $$\sum^n_{k=0}a_k\leqslant\sum^\infty_{k=0}a_0r^k=a_0\sum^\infty_{k=0}r^k=\frac{a_0}{1-r}$$

### 1.4.2 递推方程

设序列 $a_0,a_1,\cdots,a_n,\cdots$ 简记为 ${a_n}$，一个把 $a_n$ 与某些个 $a_i (i < n)$ 联系起来的等式叫做关于序列 ${a_n}$ 的 **递推方程** 。

递推方程的求解指：  
给定关于序列 ${a_n}$ 的递推方程和若干初值，计算 $a_n$ 。

> 裴波那契数列  
> $1 ,1 ,2 ,3 ,5 ,8 ,13 ,21 ,34 ,55 ,\cdots$ 递推方程：$f_n=f_{n-1}+f_{n-2}$  
> 初值：$f_0=1,f_1=1$ 解： $$f_n=\frac{1}{\sqrt {5}}(\frac{1+\sqrt{5}}{2})^{n+1}-\frac{1}{\sqrt {5}}(\frac{1-\sqrt{5}}{2})^{n+1}$$

#### 1.4.2.1 迭代法

迭代方法的思想是 **扩展递推式** ，将递推式先转换成一个和式，然后计算该和式，得到渐进复杂度。它需要较多的数学运算。

**递归树** (recursion tree) 可以形象地看到递推式的迭代过程。

> $T(n)=2T(n/2)+n$ 的递归树
>
> ```Mermaid
> graph TB
>
> D1-1-->D2-1
> D1-1-->D2-2
> D2-1-->D3-1
> D2-1-->D3-2
> D2-2-->D3-3
> D2-2-->D3-4
>
> D1-1["T(n)|n"]
> D2-1["T(n/2)|n/2"]
> D2-2["T(n/2)|n/2"]
> D3-1["T(n/4)|n/4"]
> D3-2["T(n/4)|n/4"]
> D3-3["T(n/4)|n/4"]
> D3-4["T(n/4)|n/4"]
> ```

如解决 **汉诺塔问题** 。

#### 1.4.2.2 替换法

替换方法要求首先猜测递推式的解，然后用 **归纳法** 证明，

#### 1.4.2.3 主方法

需要主方法求解的特殊递推式 $T(n)=aT(n/b)+f(n)$

其中  
$a\geqslant 1 , b>1$ 是常数。  
$f(n)$ 是一个渐进正函数。  
$n/b$ 指 $\lfloor n/b \rfloor$ 或 $\lceil n/b \rceil$

主方法依赖于 **主定理** :

设如上的递推式 $T(n)=aT(n/b)+f(n)$

则 $T(n)$ 有如下渐进界。

(1) 若对某常数 $\epsilon>0$ ，有 $f(n) = O(n^{log_b {a-\epsilon}})$ ，则 $T(n)=\Theta(n log_b{a})$  
(2) 若 $f(n) = \Theta(n log_b{a})$，则 $T(n) = \Theta(n^{log_b{a}} logn)$  
(3) 若对某常数 $\epsilon > 0$ ，有$f(n)=\Omega(n^{log_b{a+\epsilon}})$，且对某个常数 $c<1$ 和所有足够大的 $n$ ，有 $af(n/b)\leqslant cf(n)$，则 $T(n)=\Theta(f(n))$ 。

若 $f(n)$ 不符合要求，则不可使用主定理求解递推式。

> 如下几个递推式可以使用主定理法求解: $T(n) = 16T(n/4) + n$  
> $T(n) = T(3n/7) + 1$  
> $T(n) = 3T(n/4) + nlogn$

## 1.5 分摊分析

若执行 $n$ 个运算的总时间为 $T(n)$ 则每个运算的 **平均代价** (average cost) 为 $T(n)/n$ 。  
**分摊分析** (amortized analysis) 是对一个长的运算序列所需的最坏情况时间求平均值。

分摊分析之关心最坏情况，所以分摊分析和平均情况分析的不同之处在于不需要假定运算的概率。

### 1.5.1 聚集方法

**聚集方法** (aggregate analysis) 中需要对所有 $n$ ，计算由 $n$ 个运算构成的运算序列在最坏情况下的总的执行时间 $T(n)$ ，则每个运算的平均代价为 $T(n)$ 。  
序列中允许包含不同类型的运算，但每个运算的分摊代价是相同的。

### 1.5.2 会计方法

对于给定的数据结构，会计方法 (accounting method) 对每个运算预先赋予不同的 **费值** (charge) 。其中，某些运算的费值可能超过它们的 **实际代价** (actual cost) ，而另一些运算的费值会低于实际代价。对每个运算所记的费值称为 **分摊代价** (amortized cost) 。其超出部分如同 **存款** (credit) 一样保存起来，用于补偿以后代价不足的运算。

与聚焦分析不同的是，会计方法的分摊代价可以不同。

> 对于一个栈，有 `push()` 、 `pop()` 、 `multipop(k)` 三种方法。
>
> |  运算名  | 实际代价 | 分摊代价 |   功能    |
> | :------: | :------: | :------: | :-------: |
> |   push   |    1     |    2     |   压入    |
> |   pop    |    1     |    0     |   弹出    |
> | multipop | min(k,m) |    0     | 弹出 k 个 |
>
> 其中 m 指当前栈含有元素的个数。

此例中，分摊代价的设计可以保证在执行一个运算序列的任何时刻，其代价余额不会是负值。因为对于每个可弹出的元素，都必然先被压入。在运算结束后，只有栈空或栈非空两种情况，即 `pop()` 、 `multipop(k)` 运算代价不会高于 `push()` 的运算代价。  
在此例中非常好地表现了 **存款** 的概念。

### 1.5.3 势能方法

给定一个初始数据结构，执行该数据结构上的一个运算将使该数据结构改变状态。 **势能方法** (potential method) 为数据结构的每个状态定义一个被称为 **势能** 的量。设数据结构的初始状态为 $D_0$ 对 $D_0$ 执行一个 $n$ 此运算的序列， $c_i$ 是第 $i$ 个运算的实际代价， $D_i$ 为在数据结构的状态 $D_{i-1}$ 时执行第 $i$ 个运算后得到的数据结构的新状态。势能函数 $\Phi$ 将数据结构的每个状态映射为一个实数 $\Phi(D_i)$ ，称为数据结构在该状态下的势能。第 $i$ 个运算的分摊代价 $\hat{c_i}$ 定义为：  
$$\hat{c_i}=c_i+\Phi(D_i)-\Phi(D_{i-1})$$

从上式可知，每个运算的分摊代价是其实际代价 $c_i$ 加上执行该运算所引起的数据结构势能的增量 $D_i$