# 2. 语言及其语法

## 2.1 语法

任何语言程序都可看成是一定字符集（字母表）上的一字符串（有限序列）。

遵循某种规则可以形成和产生一个 **合式** 的程序，这样的规则称为一个语言的语法。  
语法分为：

- 词法规则
- 语法规则（产生规则）

表达式 `0.5 * x + c`  
含有 **单词符号**：

- 常数 `0.5`
- 标识符 `x` `c`
- 算符 `*` `+`

表达式 `0.5 * x + c` 称为语言的一个 **语法范畴** ，或 **语法单位**。  
语言的单词符号由 **词法规则** 确定。

### 2.1.1 字母表

字母表 $\Sigma$ 是一个有穷 **符号** 集合。

符号：字母、数字、标点符号……

#### 字母表上的运算

- 字母表 $\Sigma_{1}$ 和 $\Sigma_{2}$ 的 **乘积** (product)  
  $$
  \Sigma_{1}\Sigma_{2}=\{ab|a\in\Sigma_{1},b\in\Sigma_{2}\}
  $$
- 字母表 $\Sigma$ 的 **$n$ 次幂** (power)
  $$
  \begin{cases}
      \Sigma^{0}=\{\varepsilon\} \\
      \Sigma^{n}=\Sigma^{n-1}\Sigma,n \geqslant 1 \\
  \end{cases}
  $$
  $\varepsilon$ 其中表空串。
- 字母表 $\Sigma$ 的 **正闭包** (positive closure)
  $$
  \Sigma^{+}=\Sigma \cup \Sigma^{2} \cup \Sigma^{3} \cup \dots
  $$
  > $$
  > \{a,b,c\}^{+}=\{a,b,c,aa,bb,cc,ab,ac,bc,aaa,aab,aac,\dots\}
  > $$
  字母表的正闭包即长度为正数的符号串构成的集合。  
- 字母表 $\Sigma$ 的 **克林闭包** (kleene closure)
  $$
  \Sigma^{*}=\Sigma^{0} \cup \Sigma^{+} = \Sigma^{0} \cup \Sigma\cup \Sigma^{2} \cup \Sigma^{3} \cup \dots
  $$
  > $$
  > \{a,b,c\}^{+}=\{\varepsilon,a,b,c,aa,bb,cc,ab,ac,bc,aaa,aab,aac,\dots\}
  > $$
  字母表的克林闭包即任意长度的符号串构成的集合。  

### 2.1.2 串

设 $\Sigma$ 是一个字母表， $\forall x\in \Sigma^{*}$，$x$ 称为 $\Sigma$ 上的一个 **串**。  

串是字母表中符号的一个 **有穷序列**。  

串 $s$ 的长度，通常记作 $|s|$，是指 $s$ 中符号的个数。  
空串是长度为 0 的串，用 $\varepsilon$ 表示。  

#### 串上的运算

- 如果 $x$ 和 $y$ 是串，那么 $x$ 和 $y$ 的 **连接**  (concatenation) 是把 $y$ 附加到 $x$ 后面而形成的串，记作 $xy$。  
  - 空串是连接运算的 **单位元** (identity) ，即对于任何 $s$ 都有 $\varepsilon s =s \varepsilon =s$ 。  
  - 设 $x,y,z$ 是三个字符串，若 $x=yz$ ，则称 $y$ 是 $x$ 的前缀，$z$ 是 $x$ 的后缀。  
- 如果 $s$ 是串，那么 $s$ 的幂运算为：  
  $$
  \begin{cases}
      s^{0}=\varepsilon \\
      s^{n}=s^{n-1} s,n \geqslant 1   \\
  \end{cases}
  $$
  串 $s$ 的 $n$ 次幂：将 $n$ 个 $s$ 连接起来。  
