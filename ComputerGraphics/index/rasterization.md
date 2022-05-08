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

### 4.1.2 视口变换矩阵形式

- 无视 $z$ 。
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

## 4.2 光栅化三角形

一般使用 **三角形** 为基础构建面。

> 为什么是三角形？
>
> - 最基础的多边形。
>   - 可以将任意多边形拆解为三角形。
> - 给出三顶点坐标，一定形成一个平面。
> - 三角形内外定义明确。
>   - 使用叉积即可计算点是否在三角形内。
>   - 其他多边形可能有凹凸问题。
> - 三角形差值算法可定义。
>   - 使用三顶点属性即可计算三角形内部任意一点属性。

![在屏幕上绘制三角形](../pic/rasterization.png)

由于三角形是 **连续** 的，而屏幕是 **离散** 的，因此需要通过特定的方式在屏幕上绘制三角形。

### 4.2.1 采样

**采样** 一个函数，就是将指定参数集带入连续函数，以获取一个解集，即将一个函数离散化。

常用的采样依据：

- **时间** （一维）
- **面积** （二维）
- **方向** （二维）
- **体积** （三维）

对于上图的三角形，采样依据为：

- 判断三角形在方格内的面积是否占方格面积的一半。
- 等价于判断方格中心点是否在三角形内。

$
inside(t,x,y)=
\begin{cases}
1 \quad \text{point(x,y) in triangle t}\\
0 \quad \text{otherwise}\\
\end{cases}
$

一般使用轴向包围盒 (Axis-aligned bounding boxes) 简化范围。

![包围盒](../pic/boundingBox.png)

## 4.3 反走样

**采样瑕疵** (Sampling Artifacts) 指图形学中不希望或无意的数据更改，包括：

- 走样 (Aliasing)  
  ![走样](../pic/aliasing.png)
- 摩尔纹 (Moire Pattern)  
  ![摩尔纹](../pic/moirePattern.png)
  - 去除图像的奇数行与奇数列，使之成为更小的图像。
- 车轮效应 (Wagon wheel effect)
  - 视觉上观测到的转动与实际转动方向不符。
- More...

### 4.3.1 走样成因

**走样** (Aliasing) 在图形学中即锯齿，是光栅化不可避免的副产物。

锯齿是线在光栅化时产生的失真，根本原因在于采样精度低于人眼精度。

更多参见 **数字图像处理** 。

#### 4.3.1.1 时域与频域

时域 (time domain) 指相对于 **时间** 的数学函数或信号的分析。频域 (frequency domain) 指相对于 **频率** 的数学函数或信号的分析。

时域图显示信号如何随时间变化，而频域图显示每个给定频段内有多少信号位于一定频率范围内。

傅里叶变换将时域转换为频域。  
逆傅里叶变换与之相对。

![傅里叶变换 by wikipedia](<../pic/fourier_transform_time_and_frequency_domains_(small)_from_wiki.gif>)

对于图像处理，时域不再指时间，而指空间中的位置。

![图像的时域图与频域图](../pic/time%26frequency.png)

可以使用傅里叶级数展开规律函数，但实际中不允许无限展开，这将产生精度问题。

![采样与傅里叶变换](../pic/sampling.png)

采样频率应与原函数频率相匹配，否则将出现失真。

#### 4.3.1.2 滤波

滤波 (filtering) 即抹除指定频率的信息。

![高通滤波](../pic/highPassFilter.png)  
![低通滤波](../pic/lowPassFilter.png)

滤波相当于卷积 (convolution)，亦相当于（加权）平均 (averaging) 。

![一维卷积](../pic/convolution.png)

图像时域上的卷积等价于图 像和卷积核在频域上的乘积。

![图像卷积](../pic/imageConvolution.png)

> 将图像压缩为原图的 $1/3$

- 盒滤波

![盒滤波](../pic/boxFilter.png)  
![盒滤波的频域图](../pic/boxFilterFeq.png)

### 4.3.2 模糊化处理

**模糊** (blurring) 即在采样前对原图进行模糊处理。

![模糊化处理](../pic/pre-filter.png)

## 4.4 深度缓冲
