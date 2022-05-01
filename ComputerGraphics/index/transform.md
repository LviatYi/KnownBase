# 3. 变换

## 3.1 变换概述

变换主要分为两种应用：

- **Modeling** 模型变换
- **Viewing** 视图变换

变换在各种方面都有广泛应用。

## 3.2 2D 变换

### 3.2.1 2D 缩放

![缩放变换](../pic/scale.png)

#### 2D 缩放数学形式

对于缩放后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = s_x x\\
y' = s_y y\\
$$

#### 2D 缩放矩阵形式

$$
\begin{bmatrix}
    x'\\ y'\\
\end{bmatrix}=
\begin{bmatrix}
    s_x &0\\0&s_y \\
\end{bmatrix}
\begin{bmatrix}
    x\\ y\\
\end{bmatrix}
$$

- 当 $s_x=s_y$ 时，为等比（锁定纵横比）缩放。
- 当 $s_x <0$ 或 $s_y<0$ 时，为镜像缩放。

### 3.2.2 2D 切变

![切变](../pic/shear.png)

#### 2D 切变数学形式

对于以斜率 $k$ 切变后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = x + kx\\
y' = y\\
$$

#### 2D 切变矩阵形式

$$
\begin{bmatrix}
    x' \\
    y' \\
\end{bmatrix}=
\begin{bmatrix}
    1 &k \\
    0 &1 \\
\end{bmatrix}
\begin{bmatrix}
    x \\
    y \\
\end{bmatrix}
$$

或

$$
\begin{bmatrix}
    x' \\
    y' \\
\end{bmatrix}=
\begin{bmatrix}
    1 &0 \\
    k &1 \\
\end{bmatrix}
\begin{bmatrix}
    x \\
    y \\
\end{bmatrix}
$$

### 3.2.3 2D 旋转

![旋转](../pic/rotation.png)

#### 2D 旋转数学形式

对于旋转顺时针 $\theta$ 后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = x \cos{\theta} -y sin{\theta}\\
y' = x \sin{\theta} +y cos{\theta}\\
$$

#### 2D 旋转矩阵形式

$$
\begin{bmatrix}
    x' \\
    y' \\
\end{bmatrix}=
\begin{bmatrix}
    \cos{\theta} & -\sin{\theta} \\
    \sin{\theta} & \cos{\theta} \\
\end{bmatrix}
\begin{bmatrix}
    x \\
    y \\
\end{bmatrix}
$$

> Games101 使用了一下方法求解转换矩阵。首先设：
>
> $
> \begin{bmatrix}
> x' \\
> y' \\
> \end{bmatrix}=
> \begin{bmatrix}
> A & B \\
> C & D \\
> \end{bmatrix}
> \begin{bmatrix}
> x \\
> y \\
> \end{bmatrix}
> $
>
> 然后以矩阵 $(0,1),(1,0)$ 旋转 $\theta$ 为例，带入 $(0,1),(1,0)$ 两点可算出 $A B C D$ 。

### 3.2.4 2D 线性变换

若已知数学形式的转换方程为以下形式：

$
x' = ax +by \\
y' = cx +dy \\
$

则为线性变换，对应的转换矩阵：

$
\begin{bmatrix}
    x' \\
    y' \\
\end{bmatrix}=
\begin{bmatrix}
    a & b \\
    c & d \\
\end{bmatrix}
\begin{bmatrix}
    x \\
    y \\
\end{bmatrix}
$

## 3.3 齐次坐标

### 3.3.1 2D 平移变换

![平移](../pic/translation.png)

#### 2D 平移数学形式

对于平移 $(t_x,t_y)$ 后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = x + t_x\\
y' = y + t_y\\
$$

#### 2D 平移矩阵形式

平移变换无法直接转换为矩阵乘法形式：

$$
\begin{bmatrix}
    x' \\
    y' \\
\end{bmatrix}=
\begin{bmatrix}
    1 & 0 \\
    0 & 1 \\
\end{bmatrix}
\begin{bmatrix}
    x \\
    y \\
\end{bmatrix}+
\begin{bmatrix}
    t_x \\
    t_y \\
\end{bmatrix}
$$

因此其不是线性变换，但我们不希望平移成为一个特殊情况，因此定义齐次坐标。

### 3.3.2 齐次坐标概念

增加一个维度，以促成「大一统理论」。

设 2D 点坐标 $(x,y,1)^T$  
设 2D 向量 $(x,y,0)^T$

因此线性变换与平移变换的矩阵表示将统一。定义仿射变换：

$$
\begin{pmatrix}
    x' \\
    y' \\
\end{pmatrix}=
\begin{pmatrix}
    a & b \\
    c & d \\
\end{pmatrix}
\begin{pmatrix}
    x \\
    y \\
\end{pmatrix}+
\begin{pmatrix}
    t_x \\
    t_y \\
\end{pmatrix}
$$

齐次坐标下点的仿射变换：

$$
\begin{pmatrix}
    x'\\ y'\\ 1\\
\end{pmatrix}=
\begin{pmatrix}
    a & b & t_x \\
    c & d & t_y \\
    0 & 0 & 1 \\
\end{pmatrix}
\begin{pmatrix}
    x \\ y \\ 1 \\
\end{pmatrix}=
\begin{pmatrix}
    ax + by + t_x \\
    cx + dy + t_y \\
    1 \\
\end{pmatrix}
$$

#### 第三个维度的意义

对于平移变换，坐标与向量具有不同的表现。

因此简单来说，用第三个维度的 0 或 1 表示可加以区分。

实际上第三个维度可被赋予数学意义：

- 向量 + 向量 = 向量
  - 0+0=0
- 点 - 点 = 向量
  - 1-1=0
- 点 + 向量 = 点
  - 1+0=1
- 点 + 点 = **点（扩展）**
  - 1+1=2

定义 3 行 1 列矩阵 $
\begin{pmatrix}
    x\\ y\\ w\\
\end{pmatrix}
$ 为 2D 点 $
\begin{pmatrix}
    x/w\\ y/w\\ 1\\
\end{pmatrix}
$ ，其中 $w \neq 0$

## 3.4 逆变换

![逆变换](../pic/inverse.png)

在矩阵意义和几何意义上，逆变换 $M^{-1}$ 是变换 $M$ 的逆。

对于旋转变换的逆变换，恰好为旋转变换的转置变换。

$
R(\theta)=
\begin{pmatrix}
    \cos{\theta}&-\sin{\theta} \\
    \sin{\theta}& \cos{\theta} \\
\end{pmatrix}\\
R(-\theta)=
\begin{pmatrix}
    \cos{-\theta}&-\sin{-\theta} \\
    \sin{-\theta}& \cos{-\theta} \\
\end{pmatrix}=
\begin{pmatrix}
    \cos{\theta}&\sin{\theta} \\
    -\sin{\theta}& \cos{\theta} \\
\end{pmatrix}
$

即

$
R(-\theta)=R(\theta)^{-1}
$

> 如果一个矩阵的逆等于其转置矩阵，则该矩阵为 **正交矩阵**。

## 3.5 组合变换

将图像连续地进行变换 $A_1,A_2,\dots ,A_n$ ，则可描述为矩阵形式：

$$
A_n(...A_2(A_1(x))) =
 A_n\dots A_2 \cdot A_1 \cdot
\begin{pmatrix}
    x \\y \\1 \\
\end{pmatrix}
$$

齐次坐标抹消了组合不同仿射变换的鸿沟，使矩阵表示丰富的组合变换变为可能。

将变换视为组合变换后进行分解可以简化分解过程。

如对于将某图像围绕某点 $c$ 进行旋转，可视为将某图像沿向量 $c$ 进行平移，再围绕某点 $c$ 进行旋转。

![围绕点 C 进行旋转](../pic/rotateAroundC.png)

因此有如下解决方案：

$R(\alpha ,c) = T(c)\cdot R(\alpha) \cdot T(-c)$

## 3.6 3D 变换

### 3.6.1 3D 齐次坐标

设 3D 点坐标 $(x,y,z,1)^T$  
设 3D 向量 $(x,y,z,0)^T$

定义 4 行 1 列矩阵 $
\begin{pmatrix}
    x\\ y\\ z\\ w\\
\end{pmatrix}
$ 为 3D 点 $
\begin{pmatrix}
    x/w\\ y/w\\ z/w \\ 1\\
\end{pmatrix}
$ ，其中 $w \neq 0$

### 3.6.2 3D 仿射变换

#### 3D 点的仿射变换

$$
\begin{pmatrix}
    x'\\ y'\\ z'\\ 1\\
\end{pmatrix}=
\begin{pmatrix}
    a & b & c & t_x \\
    d & e & f & t_y \\
    g & h & i & t_z \\
    0 & 0 & 0 & 1 \\
\end{pmatrix}
\begin{pmatrix}
    x \\ y \\ z \\ 1 \\
\end{pmatrix}=
\begin{pmatrix}
    ax + by + cz + t_x \\
    dx + ey + fz + t_y \\
    gx + hy + iz + t_z \\
    1 \\
\end{pmatrix}
$$

#### 3D 点的缩放变换

$
S(s_x,s_y,s_z) =
\begin{pmatrix}
    s_x & 0 & 0 & 0 \\
    0 & s_y & 0 & 0 \\
    0 & 0 & s_z & 0 \\
    0 & 0 & 0 & 1 \\
\end{pmatrix}
$

#### 3D 点的平移变换

$
T(t_x,t_y,t_z) =
\begin{pmatrix}
    1 & 0 & 0 & t_x \\
    0 & 1 & 0 & t_y \\
    0 & 0 & 1 & t_z \\
    0 & 0 & 0 & 1 \\
\end{pmatrix}
$

#### 3D 点的旋转变换

绕任意轴的 3D 旋转都可分解为分别绕 $x$、$y$、$z$ 轴的选择

$$
R_{xyz}(\alpha , \beta , \gamma)=
R_{x}(\alpha)R_{y} (\beta)R_{z} (\gamma)
$$

## 3.7 观测变换

观测变换 (Viewing transformation) 。

### 3.7.1 视图变换

### 3.7.2 投影变换

#### 正交投影

#### 透视投影
