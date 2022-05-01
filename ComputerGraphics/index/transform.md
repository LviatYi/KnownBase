# 3. 变换

## 3.1 变换概述

变换主要分为两种应用：

- **Modeling** 模型变换
- **Viewing** 视图变换

变换在各种方面都有广泛应用。

## 3.2 2D 变换

### 3.2.1 缩放

![缩放变换](../pic/scale.png)

#### 缩放数学形式

对于缩放后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = s_x x\\
y' = s_y y\\
$$

#### 缩放矩阵形式

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

### 3.2.2 切变

![切变](../pic/shear.png)

#### 切变数学形式

对于以斜率 $k$ 切变后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = x + kx\\
y' = y\\
$$

#### 切变矩阵形式

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

### 3.2.3 旋转

![旋转](../pic/rotation.png)

#### 旋转数学形式

对于旋转顺时针 $\theta$ 后的图像上的任一点 $(x',y')$ 在原图像上有与其对应点 $(x,y)$ 满足以下条件：

$$
x' = x \cos{\theta} -y sin{\theta}\\
y' = x \sin{\theta} +y cos{\theta}\\
$$

#### 旋转矩阵形式

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

### 3.2.4 线性变换

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

## 3.4 组合变换

## 3.5 3D 变换
