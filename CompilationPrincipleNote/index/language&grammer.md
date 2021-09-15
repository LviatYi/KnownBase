# 2. 语言及其语法

## 2.1 语法定义

### 2.1.1 文法定义

任何语言程序都可看成是一定字符集（字母表）上的一字符串（有限序列）。

遵循某种规则可以形成和产生一个 **合式** 的程序，这样的规则称为一个语言的语法。  
**语法** 包括：

- 词法规则  
  单词符号的形成规则。
- 语法规则（产生规则）  
  语法单位的形成规则。

> 表达式 `0.5 * x + c`  
> 含有 **单词符号**：
>
> - 常数 `0.5`
> - 标识符 `x` `c`
> - 算符 `*` `+`
>
> 表达式 `0.5 * x + c` 称为语言的一个 **语法范畴** ，或 **语法单位**。  
> 语言的单词符号由 **词法规则** 确定。

#### 2.1.1.1 字母表

字母表 $\Sigma$ 是一个有穷 **符号** 集合。

符号：字母、数字、标点符号……

##### 字母表上的运算

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

#### 2.1.1.2 串

设 $\Sigma$ 是一个字母表， $\forall x\in \Sigma^{*}$，$x$ 称为 $\Sigma$ 上的一个 **串**。

串是字母表中符号的一个 **有穷序列**。

串 $s$ 的长度，通常记作 $|s|$，是指 $s$ 中符号的个数。  
空串是长度为 0 的串，用 $\varepsilon$ 表示。

##### 串上的运算

- 如果 $x$ 和 $y$ 是串，那么 $x$ 和 $y$ 的 **连接** (concatenation) 是把 $y$ 附加到 $x$ 后面而形成的串，记作 $xy$。
  - 空串是连接运算的 **单位元** (identity) ，即对于任何 $s$ 都有 $\varepsilon s =s \varepsilon =s$ 。
  - 设 $x,y,z$ 是三个字符串，若 $x=yz$ ，则称 $y$ 是 $x$ 的前缀，$z$ 是 $x$ 的后缀。
- 如果 $s$ 是串，那么 $s$ 的幂运算为：
  $$
  \begin{cases}
      s^{0}=\varepsilon               \\
      s^{n}=s^{n-1} s,n \geqslant 1   \\
  \end{cases}
  $$
  串 $s$ 的 $n$ 次幂：将 $n$ 个 $s$ 连接起来。

#### 2.1.1.3 语法定义

**上下文无关文法** （简称 **文法** ）是一种语法规则的描述方式。  
文法描述语言的语法结构。其定义的语法单位是完全独立于这个单位可能出现的环境。即 **上下文无关的**。

形式化定义：

$$
G=(V_{T},V_{N},P,S)
$$

- $V_{T}$ **终结符集合**  
  **终结符** (terminal symbol) 是文法所定义的语言的基本符号。也称为 **词法单元** (token)。

  如何理解 **终结**？

  - 不可再推导的最小单位。
  - 在语法分析树中为叶子节点。

- $V_{N}$ **非终结符集合**  
  **非终结符** (nonterminal) 是用来表示语法单位的符号，一个非终结符可理解为终结符的集合。也称为 **语法变量**。
- $P$ **产生式集合**  
  **产生式** (production) 描述了将终结符和非终结符组合成串的方法。  
  其一般形式为：
  $$
  \alpha \rightarrow \beta
  $$
  读作： $\alpha$ 定义为 $\beta$
  - $\alpha \in (V_{T} \cup V_{N})^{+}$ ，且 $\alpha$ 中至少包含 $V_{N}$ 中的一个元素：称为产生式的 **头部** (head) 或 **左部** (left side)。
  - $\beta \in (V_{T} \cup V_{N})^{*}$ : 称为产生式的 **体** (body) 或 **右部** (right side)。
- $S$ **开始符号**  
  $S \in V_{N}$ 。**开始符号** (start symbol) 表示的是该文法中最大的语法单位。

> $$
> \begin{align*}
>     G  =  ( &\{id,+,*,(,)\},\{E\},P,E)  \\
>     P  = \{ & E \rightarrow E+E,        \\
>             & E \rightarrow E*E,        \\
>             & E \rightarrow (E),        \\
>             & E \rightarrow id \}       \\
> \end{align*}
> $$

在不引起歧义的前提下，可以只写产生式：

> $$
> \begin{align*}
>     G: & E \rightarrow E+E  \\
>        & E \rightarrow E*E  \\
>        & E \rightarrow (E)  \\
>        & E \rightarrow id   \\
> \end{align*}
> $$

当左部相同，产生式可继续简写。如：

$$
\alpha \rightarrow \beta_{1},\alpha \rightarrow \beta_{2},\dots ,\alpha \rightarrow \beta_{n}
$$

可简记为：

$$
\alpha \rightarrow \beta_{1} | \beta_{2} | \dots | \beta_{n}
$$

读作 $\alpha$ 定义为 $\beta_{1}$ ，或 $\beta_{2}$ ， $\dots$ 或 $\beta_{n}$ 。  
$\beta_{1}$ ，$\beta_{2}$ ， $\dots$， $\beta_{n}$ 称为 $\alpha$ 的 **候选式** (candidate) 。

> $$
> \begin{align*}
>     G:   E \rightarrow   & E+E  \\
>                         |& E*E  \\
>                         |& (E)  \\
>                         |& id   \\
> \end{align*}
> $$

#### 2.1.1.4 符号约定

- 终结符
  - 字母表中排在前面的 **小写字母** `a` `b` `c`。
  - 运算符。
  - 标点符号。
  - 数字。
  - 粗体字符串。
- 非终结符
  - 字母表中排在前面的 **大写字母** `A` `B` `C`。
  - 字母 S 。 通常代表开始符号。
  - 小写、斜体名字 `expr` `stmt`。
  - 代表程序构造的大写字母 `E`（表达式） `T`（项） `F`（因子）。
- 文法符号（终结符或非终结符）
  - 字母表中排在后面的 **大写字母** `X` `Y` `Z`。
- 终结字符串或空串
  - 字母表中排在后面的 **小写字母** `u` `v`。
- 文法符号串或空串
  - 小写希腊字母 $\alpha$ $\beta$ $\gamma$

> $E \rightarrow i | EAE$  
> $A \rightarrow + | *$  
> 其中 $E$ $A$ 是非终结符，$E$ 是开始符号，$i$ $+$ $*$ 为终结符

#### 2.1.2 推导和归约

> 文法：
>
> 1. < 句子 > $\rightarrow$ < 名词短语 >< 动词短语 >
> 1. < 名词短语 > $\rightarrow$ < 形容词 >< 名词短语 >
> 1. < 名词短语 > $\rightarrow$ < 名词 >
> 1. < 动词短语 > $\rightarrow$ < 动词 >< 名词短语 >
> 1. < 形容词 > $\rightarrow$ little
> 1. < 名词 > $\rightarrow$ boy
> 1. < 名词 > $\rightarrow$ apple
> 1. < 动词 > $\rightarrow$ eat
>
> ![推导和归约](../pic/derive&reduct.png "推导和归约")

##### 推导

给定文法 $G=(V_{T},V_{N},P,S)$，如果 $\alpha \rightarrow \beta \in P$ ，那么可以将符号串 $\gamma\alpha\delta$ 中的 $\alpha$ **替换** 为 $\beta$ ，也就是说，将 $\gamma\alpha\delta$ 重写 (Rewrite) 为 $\gamma\beta\delta$ ，记作 $\gamma\alpha\delta \Rightarrow \gamma\beta\delta$ 。此时，称文法中的符号串 $\gamma\alpha\delta $ **直接推导** (directly derive) 出 $\gamma\beta\delta$ 。

> 即用产生式的右部 **替换** 产生式的左部。

如果 $\alpha_{0} \Rightarrow \alpha_{1},\alpha_{1} \Rightarrow \alpha_{2},\alpha_{2} \Rightarrow \alpha_{3},\dots,\alpha_{n-1} \Rightarrow \alpha_{n}$ ，则可以记作 $\alpha_{0} \Rightarrow \alpha_{1} \Rightarrow \alpha_{2} \Rightarrow \dots \alpha_{n-1} \Rightarrow \alpha_{n}$ ，称符号串 $\alpha_{0}$ **经过 $n$ 步推导出 $a_{n}$** 。可简记为 $\alpha_{0} \Rightarrow ^{n} a_{n}$ 。

- $\alpha \Rightarrow^{0} \alpha$
- $\Rightarrow^{+}$ 表示 「经过正数步推导」
- $\Rightarrow^{*}$ 表示 「经过若干步（允许为 0 ）推导」

##### 归约

归约是推导的逆过程。

在文法确定的前提下，根据推导和归约判断某词串是否是该语言的句子。  

- 句子的 **推导** 反映语言的 **生成** 。  
- 句子的 **归约** 反映语言的 **识别** 。  

#### 2.1.3 句型和句子

如果 $S \Rightarrow^{*} \alpha,\alpha \in (V_{T} \cup V_{N})^{*}$，则称 $\alpha$ 是 $G$ 的一个 **句型** (sentenial form) 。  

- 一个句型中既可以包含 **终结符** ，又可以包含 **非终结符** ，也可能是 **空串** 。  

如果 $S \Rightarrow^{*} w,w \in {V_{T}}^{*}$，则称 $w$ 是 $G$ 的一个 **句型** (sentence) 。  

- 句子是 **不包含非终结符** 的 **句型**。  

#### 2.1.4 语言的形式化定义

由文法 $G$ 的开始符号 $S$ 推导出的所有句子构成的集合称为 **文法 $G$ 生成的语言**，记为 $L(G)$。即

$$
L(G)=\{w|S\Rightarrow ^{*} w,w\in {V_{T}}^{*}\}
$$

文法解决了 **无穷** 语言的 **有穷表示** 问题。  
