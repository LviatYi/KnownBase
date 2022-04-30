# 2. 向量与线性代数

## 2.1 常用符号表示

![一个矩阵](../pic/matrixOf4%263.png)

$
A=
\begin{pmatrix} x \\ y \\ \end{pmatrix}
$

$
A^T=
\begin{pmatrix} x , y\\ \end{pmatrix} \\
转置矩阵
$

$
\lVert A \rVert = \sqrt{x^2 + y^2} \\
向量位移距离
$

## 2.2 向量计算

### 2.2.1 点乘 Dot Product

#### 点乘定义

$$
\vec{a} \cdot \vec{b} =
    \lVert \vec{a} \rVert \lVert \vec{b} \rVert \cos{\theta}
$$

$
\cos{\theta} =
    \dfrac{\vec{a} \cdot \vec{b}}{\lVert \vec{a} \rVert \lVert \vec{b} \rVert }
$

$
\cos{\theta} =
    \hat{a} \cdot \hat{b} \quad (单位向量情况下)
$

$$
\vec{a} \cdot \vec{b} =
    \begin{pmatrix} x_a \\ y_a \\ \end{pmatrix} \cdot
    \begin{pmatrix} x_b \\ y_b \\ \end{pmatrix} =
    x_a x_b + y_a y_b
$$

#### 点乘运算法则

$
\begin{aligned}
& \vec{a} \cdot \vec{b} =
    \vec{b} \cdot \vec{a} \\
& \vec{a} \cdot( \vec{b} + \vec{c} ) =
    \vec{a} \cdot \vec{b} +\vec{a} \cdot \vec{c}  \\
& (k\vec{a}) \cdot \vec{b} =
    \vec{a} \cdot (k\vec{b}) =
    k(\vec{a} \cdot \vec{b})\\
\end{aligned}
$

#### 点乘用途

- 计算两向量间夹角余弦值。
- 计算两向量间夹角。
- 将一个向量投影到另一向量上。
- 向量分解。

![向量分解](../pic/decomposeVector.png)

$\vec{b}_{\perp}=k \hat{a}$  
$k=\lVert \vec{b}_{\perp} \rVert=\lVert \vec{b} \rVert \cos{\theta}$

- 判断两向量朝向是否一致。
- 判断两向量接近程度。

![判断向量朝向](../pic/determineTowards.png)

### 2.2.2 叉乘 Cross Product

#### 叉乘定义

设：

$$
\vec{c} = \vec{a} \times \vec{b}
$$

则：

$$
\lVert \vec{c} \rVert=
    \lVert \vec{a} \rVert \lVert \vec{b} \rVert \sin{\phi}\\
\vec{c} \perp \vec{a}\\
\vec{c} \perp \vec{b}\\
$$

其方向可由右手定则判断。

![叉乘](../pic/crossProduct.png)

$
\vec{a} \times \vec{b} =
    - \vec{b} \times \vec{a}
$

$
\sin{\theta} =
    \dfrac{\lVert \vec{a} \times \vec{b} \rVert}{\lVert \vec{a} \rVert \lVert \vec{b} \rVert }
$

$$
\vec{c} = \vec{a} \times \vec{b} =
    \begin{vmatrix} i&j&k \\ a_x&a_y&a_z \\ b_x&b_y&b_z \\ \end{vmatrix}
$$
