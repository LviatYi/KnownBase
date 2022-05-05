# 4. 光栅化

## 4.1 视口变换

### 4.1.1 屏幕

**屏幕** 定义为：

- 一个像素构成的数组。
  - 其大小定义为 **分辨率**。
- 一种典型的光栅成像设备。

在屏幕上绘制即光栅化。

**像素** (Pixel,picture element) 指：

- 一个拥有独立颜色的最小显示单位。
  - 即一个像素内颜色没有差异。
- 由 RGB 表示 (red , green , blue) 。

一般地，用整数坐标表示像素位置。

![像素位置](../pic/posOfPixel.png)

此处使用以下规则表示像素位置：

- 使用像素方块的左下角顶点表示其位置。
- 从 (0,0) 起始。

上图中蓝色像素位置：(2,1)

### 4.1.2 视口变换

- 无视 z 。
- 将 $xy$ 面由 $[-1,1]^2$ 缩放并平移至 $[0,width]\times[0,height]^2$。

$
M_\text{viewport} =
\begin{pmatrix}
\frac{\text{width}}{2}&0&0&\frac{\text{width}}{2}\\
0&\frac{\text{height}}{2}&0&\frac{\text{height}}{2}\\
0&0&1&0\\
0&0&0&1\\
\end{pmatrix}
$
