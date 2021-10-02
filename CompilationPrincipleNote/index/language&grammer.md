# 2. 语言及其语法

## 2.1 文法

### 2.1.1 基本概念

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

#### 2.1.1.2 <a id="String">串</a>

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

### 2.1.2 文法定义

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
  - 在语法分析树中为叶子结点。

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

### 2.1.3 符号约定

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
> 其中 $E$ $A$ 是非终结符，$E$ 是开始符号，$i$ $+$ $*$ 为终结符。

## 2.2 语言

### 2.2.1 推导和归约

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

#### 2.2.1.1 推导

给定文法 $G=(V_{T},V_{N},P,S)$，如果 $\alpha \rightarrow \beta \in P$ ，那么可以将符号串 $\gamma\alpha\delta$ 中的 $\alpha$ **替换** 为 $\beta$ ，也就是说，将 $\gamma\alpha\delta$ 重写 (Rewrite) 为 $\gamma\beta\delta$ ，记作 $\gamma\alpha\delta \Rightarrow \gamma\beta\delta$ 。此时，称文法中的符号串 $\gamma\alpha\delta $ **直接推导** (directly derive) 出 $\gamma\beta\delta$ 。

> 即用产生式的右部 **替换** 产生式的左部。

如果 $\alpha_{0} \Rightarrow \alpha_{1},\alpha_{1} \Rightarrow \alpha_{2},\alpha_{2} \Rightarrow \alpha_{3},\dots,\alpha_{n-1} \Rightarrow \alpha_{n}$ ，则可以记作 $\alpha_{0} \Rightarrow \alpha_{1} \Rightarrow \alpha_{2} \Rightarrow \dots \alpha_{n-1} \Rightarrow \alpha_{n}$ ，称符号串 $\alpha_{0}$ **经过 $n$ 步推导出 $a_{n}$** 。可简记为 $\alpha_{0} \Rightarrow ^{n} a_{n}$ 。

- $\alpha \Rightarrow^{0} \alpha$
- $\Rightarrow^{+}$ 表示 「经过正数步推导」
- $\Rightarrow^{*}$ 表示 「经过若干步（允许为 0 ）推导」

#### 2.2.1.2 归约

归约是推导的逆过程。

在文法确定的前提下，根据推导和归约判断某词串是否是该语言的句子。

- 句子的 **推导** 反映语言的 **生成** 。
- 句子的 **归约** 反映语言的 **识别** 。

### 2.2.2 句型和句子

如果 $S \Rightarrow^{*} \alpha,\alpha \in (V_{T} \cup V_{N})^{*}$，则称 $\alpha$ 是 $G$ 的一个 **句型** (sentenial form) 。

- 一个句型中既可以包含 **终结符** ，又可以包含 **非终结符** ，也可能是 **空串** 。

如果 $S \Rightarrow^{*} w,w \in {V_{T}}^{*}$，则称 $w$ 是 $G$ 的一个 **句型** (sentence) 

- 句子是 **不包含非终结符** 的 **句型**。

### 2.2.3 语言的形式化定义

由文法 $G$ 的开始符号 $S$ 推导出的所有句子构成的集合称为 **文法 $G$ 生成的语言**，记为 $L(G)$。即

$$
L(G)=\{w|S\Rightarrow ^{*} w,w\in {V_{T}}^{*}\}
$$

文法解决了 **无穷** 语言的 **有穷表示** 问题。

### 2.2.4 <a id="LanguageOperate">语言上的运算</a>

- L 和 M 的 **并**

  $$
  L \cup M = \{s|s \in L 或者 s \in M \}
  $$

- L 和 M 的 **连接**

  $$
  LM = \{st|s \in L 且 t \in M \}
  $$

- L 的 **幂**

  $$
  \begin{cases}
      L^{0}=\{\varepsilon\}           \\
      L^{n}=L^{n-1} L,n \geqslant 1   \\
  \end{cases}
  $$

- L 的 **克林闭包**

  $$
  L^{*}=\cup_{i=0}^{\infty}L^{i}
  $$

- L 的 **正闭包**

  $$
  L^{+}=\cup_{i=1}^{\infty}L^{i}
  $$

> 令 $L=\{A,B,\dots,Z,a,b,\dots,z\},D=\{0,1,\dots,9\}$ ，则 $L(L\cup D)^{*}$ 可表示 **标识符**。

## 2.3 文法分类

根据对文法产生式的不同要求，Chomsky 将文法分为四种类型：

- 0 型文法
- 1 型文法
- 2 型文法
- 3 型文法

### 0 型文法

$$
\alpha \rightarrow \beta
$$

无限制文法 (Unrestricted Grammar) / 短语结构文法 (Phrase Structure Grammar,PSG)。

- $\forall \alpha \rightarrow \beta \in P$ ， $\alpha$ 中至少包含 1 个非终结符。

由 0 型文法生成的语言称为 **0 型语言**。

### 1 型文法

$$
\alpha \rightarrow \beta
$$

上下文有关文法 (Context-Sensitive Grammar,CSG)。

- $\forall \alpha \rightarrow \beta \in P ,|\alpha|\leqslant|\beta|$
- 产生式的一般形式：
  $$
  \alpha_{1}A\alpha_{2}\rightarrow \alpha_{1}\beta \alpha_{2},(\beta \neq \varepsilon)
  $$
- 即要求上下文满足一定条件才可转换非终结符。
- CSG 中不包含空产生式。

由 1 型文法生成的语言称为 **上下文有关语言**。

### 2 型文法

$$
\alpha \rightarrow \beta
$$

上下文无关文法 (Context-Free Grammar,CFG)。

- $\forall \alpha \rightarrow \beta \in P ,\alpha \in V_{N}$
- 产生式的一般形式：
  $$
  A\rightarrow \beta
  $$

由 2 型文法生成的语言称为 **上下文无关语言**。

### 3 型文法

$$
\alpha \rightarrow \beta
$$

正则文法 (Regular Grammar,RG)。

- 右线性(Right linear)文法： $A\rightarrow wB$ 或 $A \rightarrow w$ 。
- 左线性(Left linear)文法： $A\rightarrow Bw$ 或 $A \rightarrow w$ 。
- 左右线性文法都称为正则文法。
- 产生式的右侧最多只有一个非终结符。

$$
（右线性文法 可类推至标识符）\\
\begin{align*}
S &\rightarrow a|b|c|d  \\
S &\rightarrow aT|bT|cT|dT  \\
T &\rightarrow a|b|c|d|0|1|2  \\
T &\rightarrow aT|bT|cT|dT|0T|1T|2T  \\
\end{align*}
$$

由 3 型文法生成的语言称为 **正则语言**。

正则文法能描述程序设计语言的多数单词。

#### 四种文法间的关系

- 逐级限制
  - 0 型文法： $\alpha$ 中至少包含 1 个非终结符。
  - 1 型文法（CSG）： $|\alpha|\leqslant|\beta|$
  - 2 型文法（CFG）： $\alpha \in V_{N}$
  - 3 型文法（RG）： $A\rightarrow Bw$ 或 $A \rightarrow wB$
- 逐级包含
  - 1 型文法必然满足 0 型文法。
  - 以此类推。

## 2.4 语法分析树

**语法分析树** 用图形方式展现了从文法的开始符号推导出相应语言中的符号串的过程。  
如果非终结符号 $A$ 有一个产生式 $A→XYZ$ ，那么在语法分析树中就可能有一个标号为 $A$ 的内部结点，该结点有三个子结点，从左向右的标号分别为 $X,Y,Z$ ：

![语法分析树](../pic/tree.svg "语法分析树")

给定一个上下文无关文法，该文法的一棵 **语法分析树** (parse tree) 是具有以下性质的树：

- **根结点** 的标号为文法的 **开始符号**。
- 每个 **叶子结点** 的标号为 **一个终结符号** 或 **$\varepsilon$**。
- 每个 **内部结点** 的标号为 **一个非终结符号**。
  - 该结点的标号对应产生式的左部 A 。
  - 该结点 **子结点的标号** 从左到右的构成对应产生式的右部 $\beta$ 。
- 如果 **非终结符号** A 是某个 **内部结点** 的标号，并且它的子结点的标号从左至右分别为 $X_{1},X_{2},\dots,X_{n}$ ，那么必然存在产生式 $A \rightarrow X_{1}X_{2}\dots X_{n}$ ，其中 $X_{1},X_{2},\dots,X_{n}$ ，既可以是终结符号，也可以是非终结符号。作为一个特殊情况，如果 $A→\varepsilon$ 是一个产生式，那么一个标号为 A 的结点可以只有一个标号为 $\varepsilon$ 的子结点。
  - 从左到右排列叶结点得到的符号串称为这棵树的 **结果** (yield) （或称产出）或 **边缘** (frontier) ，即从这棵语法分析树的根结点上的非终结符号推导得到的 **符号串**。

分析树是推导的 **图形化表示**。

给定一个推导：

$$
S \Rightarrow \alpha_{1} \Rightarrow \alpha_{2} \Rightarrow \dots \Rightarrow \alpha_{n}
$$

对于推导过程中得到的每个 **句型** $\alpha_{i}$ ，都可以构造出一个边缘为 $\alpha_{i}$ 的 **分析树**。

$$
\begin{align*}
E &\rightarrow E + E   \\
E &\rightarrow E * E   \\
E &\rightarrow - E     \\
E &\rightarrow ( E )   \\
E &\rightarrow id      \\
\end{align*}
$$

$$
E \Rightarrow -E \Rightarrow -(E) \Rightarrow -(E+E) \Rightarrow -(id+E)
$$

![推导过程示例](../pic/parseTreeExp.svg "推导过程示例")

一个文法的语言的另一个定义是指：  
任何能够由某棵语法分析树生成的符号串的集合。

为一个给定的终结符号串构建一棵语法分析树的过程称为对该符号串进行 **语法分析**。

### 2.4.1 短语

给定的句型，其分析树中的每一棵 **子树的边缘** 称为该句型的一个 **短语** (phrase)。

> 短语：  
> $-(E+E)$  
> $(E+E)$  
> $E+E$

如果子树只有父子两代结点（即子树高度为 2 ），那么这棵子树的边缘称为该句型的一个 **直接短语** (immediate phrase) 。

> 直接短语：  
> $E+E$

## 2.5 二义性

**二义性文法** (Ambiguous Grammar) ：如果一个文法可以为某个句子生成 **多棵分析树** ，则称这个文法是 **二义性** 的。

文法：

$$
\begin{align*}
S \rightarrow & if \; E \; then \; S         \\
            |& if \; E \; then \; S \; else \; S  \\
            |& other               \\
\end{align*}
$$

句型：

$$
if \; E_{1} \; then \; if \; E_{2} \; then \; S_{1} \; else \; S_{2}
$$

![二义性示例](../pic/ambiguityExmp.svg "二义性示例")

一般采用如下规则消除歧义：

- 新定义非终结符。
- 新定义的产生式。
- 新定义的消歧义规则。

> 如上句型二义可由如下消歧规则避免：
>
> 每个 `else` 和最近的尚未匹配的 `if` 匹配。

对于任意一个上下文无关文法， **不存在** 一个算法，判定它是 **无二义性** 的；
但能给出一组 **充分条件** ，满足这组充分条件的文法是无二义性的。  
