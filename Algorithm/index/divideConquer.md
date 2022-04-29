# 2. 分治法

## 2.1 概述

**分治法** (Divide and Conquer) 将一个复杂问题分解成若干个 **规模较小** ， **相互独立** ，**类型相同** 的子问题，然后将各子问题的解组合成原始问题的解。

- 规模较小：当规模小的时候将会容易得到求解答案。
- 相互独立：避免在递归的时候重复计算，提高效率。
- 类型相同：方便递归实现。

由于分治法的分治特性，因此其与递归常常伴随使用。  
每层递归中应用如下三个步骤：

- 分解 Divide
  - 将问题划分为一些子问题。
  - 子问题的形式与原问题一样，只是规模更小。
- 解决 Conquer
  - 递归地求解出子问题。
  - 如果子问题的规模足够小，则停止递归，直接求解。。
- 合并 Combine
  - 将子问题的解组合成原问题的解。

## 2.2 时间复杂度分析

分析分治算法可以得到如下递推关系式：

$T(n)=aT(n/b)+cn^{k}$

其表示规模为 $n$ 的问题被分成了 $a$ 个规模为 $n/b$ 的子问题， $cn^k$ 是进行问题分解及将各子问题的解合并成原始问题的解所需的工作量。

因此有：

$$
T(n)=
    \begin{cases}
        \Theta (n^{log_b{a}}),   & \text{如果 $a > b^{k}$}\\
        \Theta (n^{k}log{n}),   & \text{如果 $a = b^{k}$}\\
        \Theta (n^k),   & \text{如果 $a < b^{k}$}\\
    \end{cases}
$$

## 2.3 算法

### 2.3.1 最大子数组

分治策略可解决最大子数组问题。

假定要寻找子数组 `A[low..high]` 的最大子数组。使用分治策略意味着需要将子数组划分为两个规模尽量相等的子数组： `A[low..mid]` 与 `A[mid+1..high]`。

`A[low..high]` 的子数组必然是以下三种情况之一：

- 完全位于子数组 `A[low..mid]` 中。 `low <= i <=j <= mid`
- 完全位于子数组 `A[mid+1..high]` 中。 `mid+1 <= i <=j <= high`
- 跨越中点。 `low <= i <= mid <j <= high`

由于可以递归地求解 `A[low..mid]` 与 `A[mid+1..high]` 中的最大子数组，因此只需要求得 **跨越中点** 的最大子数组。

> 函数签名： `FIND_MAX_CROSSING_SUBARRAY(A,low,mid,high)`

```pascal {.line-numbers}
left_sum = INT_MINIMUM
sum = 0
for i = mid downto low
    sum = sum + A[i]
    if sum > left_sum
        left_sum - sum
        max_left = i
right_sum = INT_MINIMUM
sum = 0
for j = mid + 1 to high
    sum = sum + A[j]
    if sum > right_sum
        right_sum = sum
        max_right = j
return (max_left,max_right,left_sum+right_sum)
```

> 函数签名： `FIND_MAXIMUM_SUBARRAY(A,low,high)`

```pascal {.line-numbers}
if high == low
    return (low,high,A[low])
else mid = ⌊(low+high)/2⌋
    (left_low,left_high,left_sum) =
        FIND_MAXIMUM_SUBARRAY(A,low,mid)
    (right_low,right_high,right_sum) =
        FIND_MAXIMUM_SUBARRAY(A,mid+1,high)
    (cross_low,cross_high,cross_sum) =
        FIND_MAX_CROSSING_SUBARRAY(A,low,mid,high)
    if left_sum >= right_sum and left_sum >= cross_sum
        return (left_low,left_high,left_sum)
    else if right_sum >= left_sum and right_sum >= cross_sum
        return (right_low,right_high,right_sum)
    else
        return (cross_low,cross_high,cross_sum)
```

### 2.3.2 矩阵乘法的 Strassen 算法

一般地，有矩阵乘法的如下普遍算法：

$$
c_{ij} = \sum  _{k=1} ^n a_{ik} \cdot b_{kj}
$$

因此对于两 $n$ 阶矩阵相乘，有如下算法：

> 函数签名： `SQUARE_MATRIX_MULTIPLY(A,B)`  
> 复杂度： $\Theta(n^3)$

```pascal {.line-numbers}
n = A.rows
for i = 1 to n
    for j = 1 to n
        C[i][j]=0
        for k = 1 to n
            C[i][j] = C[i][j] +A[i][k] * B[k][j]
return C
```

对于计算矩阵积

$$C=A \cdot B$$

即

$$
\begin{bmatrix}
C_{11} & C_{12} \\
C_{21} & C_{22} \\
\end{bmatrix} =
\begin{bmatrix}
A_{11} & A_{12} \\
A_{21} & A_{22} \\
\end{bmatrix} \cdot
\begin{bmatrix}
B_{11} & B_{12} \\
B_{21} & B_{22} \\
\end{bmatrix}
$$

因此有如下直接的递归分治算法：

> 函数签名： `SQUARE_MATRIX_MULTIPLY_RECURSIVE(A,B)`  
> 复杂度： $\Theta(n^3)$

```pascal {.line-numbers}
n = A.rows
if n==1
    c[1][1] = a[1][1] * b[1][1]
else
    C_11 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_11,B_11)
        + SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_12,B_21)
    C_12 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_11,B_12)
        + SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_12,B_22)
    C_21 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_21,B_11)
        + SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_22,B_21)
    C_22 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_21,B_12)
        + SQUARE_MATRIX_MULTIPLY_RECURSIVE(A_22,B_22)
return C
```

> 使用下标代替子数组复制，可优化矩阵分解的时间。

Strassen 算法通过找出同类项的方式合并相同的积，以减少积运算。

> 复杂度： $\Theta(n^{lg^7})$

首先构创建如下矩阵：

$$
S_1 = B_{12} - B_{22} \\
S_2 = A_{11} + A_{12} \\
S_3 = A_{21} + A_{22} \\
S_4 = B_{21} - B_{11} \\
S_5 = A_{11} + A_{22} \\
S_6 = B_{11} + B_{22} \\
S_7 = A_{12} - A_{22} \\
S_8 = B_{21} + B_{22} \\
S_9 = A_{11} - A_{21} \\
S_{10} = B_{11} + B_{12} \\
$$

其次进行 7 次矩阵乘法：

$$
\begin{align*}
P_1 & = A_{11} \cdot S_1 = A_{11} \cdot B_{12} - A_{11} \cdot B_{22} \\
P_2 & = S_2 \cdot B_{22} = A_{11} \cdot B_{22} + A_{12} \cdot B_{22} \\
P_3 & = S_3 \cdot B_{11} = A_{21} \cdot B_{11} + A_{22} \cdot B_{11} \\
P_4 & = A_{22} \cdot S_4 = A_{22} \cdot B_{21} - A_{22} \cdot B_{11} \\
P_5 & = S_5 \cdot S_6 = A_{11} \cdot B_{11} + A_{11} \cdot B_{22} + A_{22} \cdot B_{11} + A_{22} \cdot B_{22} \\
P_6 & = S_7 \cdot S_8 = A_{12} \cdot B_{21} + A_{12} \cdot B_{22} - A_{22} \cdot B_{21} - A_{22} \cdot B_{22} \\
P_7 & = S_9 \cdot S_{10} = A_{11} \cdot B_{11} + A_{11} \cdot B_{12} - A_{21} \cdot B_{11} - A_{21} \cdot B_{12} \\
\end{align*}
$$

最终：

$$
\begin{align*}
C_{11} &= P_5 + P_4 - P_2 + P_6 \\
C_{12} &= P_1 + P_2 \\
C_{21} &= P_3 + P_4 \\
C_{22} &= P_5 + P_1 - P_3 - P_7 \\
\end{align*}
$$

可展开验证其正确性。
