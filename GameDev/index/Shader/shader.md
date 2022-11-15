# Unity Shader Note

## 渲染管线

**渲染管线** 即 **渲染流水线** ，是显卡内部处理图形信号且相互独立的并行处理单元。

渲染管线在概念上总体分为三个阶段：

- 应用阶段 (Application Stage)
  - 应用阶段由开发者主导。
  - 开发者将确定：
    - 摄像机位置、场景中的物体、所使用的光源、视角类型等场景数据。
    - 粗粒度剔除，剔除不可见物体。
    - 设置渲染状态，即材质、纹理、所使用的 Shader 等。
  - 此阶段输出 **渲染图元** (rendering primitives) ，即点、线、面等。
- 几何阶段 (Geometry Stage)
  - 几何阶段确定与几何相关的工作，如将顶点坐标变换到屏幕空间。
  - 此阶段输出 **顶点信息** 。
- 光栅化阶段 (Rasterizer Stage)
  - 几何阶段将利用顶点信息绘制屏幕上的像素，以渲染出最终的图像。

![渲染管线阶段](http://static.zybuluo.com/candycat/c0opg7bab4cwzyok5vek52hs/%E6%A6%82%E5%BF%B5%E6%B5%81%E6%B0%B4%E7%BA%BF.png)

实践中，渲染管线将更加细化且复杂。

### 应用阶段

应用阶段大致分为 3 个阶段：

- 加载网格、纹理等数据至显存。
- 设置渲染状态。
- 调用 DrawCall。
  - DrawCall 是一个由 CPU 发起，GPU 接受的命令，其指定一个需要渲染的图元列表。

### 几何阶段与光栅化阶段

![几何阶段与光栅化阶段](http://static.zybuluo.com/candycat/jundxsf604yuoy2zr3r1qkzp/GPU%E6%B5%81%E6%B0%B4%E7%BA%BF.png)

上图中，颜色表示了不同阶段的可配置性或可编程性：

- **绿色** 表示该流水线阶段是完全可编程控制的。
- **黄色** 表示该流水线阶段可以配置但不是可编程的。
- **蓝色** 表示该流水线阶段是由 GPU 固定实现的，开发者没有任何控制权。
- **实线** 表示该 Shader 必须由开发者编程实现。
- **虚线** 表示该 Shader 是可选的。

#### 顶点着色器

**顶点着色器** (Vertex Shader) 。

- 输入来自 CPU。
- 处理单位是顶点，这意味着每个输入的顶点都会调用一次顶点着色器。
- 主要工作：
  - 坐标变换
  - 逐顶点光照

坐标变换即对顶点坐标进行某种变换。

顶点着色器必须把顶点坐标从模型空间转换到 **齐次裁剪空间** ，最终得到归一化的设备坐标 (Normalized Device Coordinates,NDC)。

#### 裁剪

**裁剪** (Clipping) 剔除不在摄像机视野的物体。

图元与摄像机视野有 3 种关系：

- 完全在视野内
- 部分在视野内
- 完全在视野外

裁剪将部分在视野内的图元进行处理，形成新的裁剪后图元。

由于已形成 NDC，裁剪变得相对容易：

![裁剪](http://static.zybuluo.com/candycat/08cvo0uahel9ygds4xkwrczp/Clipping.png)

#### 屏幕映射

**屏幕映射** (Screen Mapping) 将三维的图元坐标转换到二维的屏幕坐标。

屏幕映射仅处理图元坐标的 x 与 y 值，而 z 值将作为深度坐标，与屏幕坐标系形成 **窗口坐标系**。

#### 三角形设置

从此开始进入光栅化阶段。

**三角形设置** (Triangle Setup) 阶段会计算光栅化一个三角形网格所需的信息。

输入三角网格的顶点，输出光栅化三角形网格所需要的信息。

#### 三角形遍历

**三角形遍历** (Triangle Traversal) ，也称为 **扫描变换** (Scan Conversion)，检查每个像素是否被一个三角网格覆盖。如果被覆盖则生成一个 **片元** (fragment)。

三角形遍历阶段会根据上一个阶段的计算结果判断三角形覆盖了哪些像素，并根据顶点信息对覆盖区域进行插值。

![三角形遍历](http://static.zybuluo.com/candycat/1ltkl388mkbbzbfgzm28f6gy/TriangleSetupAndTraversal.png)

一个片元并不是真正意义上的像素，而是包含了很多状态的集合。这些由插值所生成的状态用于后续计算每个像素的最终颜色，状态包括：

- 屏幕坐标
- 深度信息
- 其他从几何阶段输出的顶点信息：
  - 法线
  - 纹理坐标等

#### 片元着色器

**片元着色器** (Fragment Shader) 输入上阶段的片元状态集合，输出片元的输出颜色。

#### 逐片元操作

**逐片元操作** (Per-Fragment Operations) 也称 **输出合并阶段** (Output-Merger)。

这一阶段的主要任务：

- 决定每个片元的可见性。
- 如果片元可见，则合并片元的颜色值和存储在颜色缓冲区的颜色。

片元需要通过模板测试、深度测试等，以判断是否可见。

![可见性测试](http://static.zybuluo.com/candycat/28t2ora2kenj1uudwfgfig95/Stencil%20Test_Depth%20Test.png)

- 模板测试 Stencil Test
  - 将该片元在模板缓冲区中的模板值与参考值相比较。
  - 用于限制渲染区域。
- 深度测试 Depth Test
  - 将该片元在深度缓冲区的深度值与当前深度值相比较。

通过测试后进行合并操作。

不同物体渲染后可能叠加在相同的像素上，对于不透明物体，可以关闭 **混合** (Blend) 操作。而对于半透明物体，则需要使用混合操作。

![混合操作](http://static.zybuluo.com/candycat/28t2ora2kenj1uudwfgfig95/Stencil%20Test_Depth%20Test.png)

## Unity Shader

Unity 提供了 Unity Shader 以提高 Shader 开发效率。

Unity Shader 与材质 (Meterial) 共同配合以渲染对象。

### ShaderLab

Unity Shader 是 Unity 提供的高层级渲染抽象层。

![Unity Shader](http://static.zybuluo.com/candycat/mfyfmiwipc220l4v8iowww6k/shaderlab_abstract.png)

ShaderLab 是一种用于编写 Unity Shader 的说明性语言，描述了显示一个材质所需的所有定义，而不仅仅是着色器代码。

Unity 将根据所使用的平台将 ShaderLab 编译成真正的代码和 Shader 文件。

### Unity Shader 结构

```unityShader {.line-numbers}
// Unity Shader 的基础结构
Shader "ShaderName" {
  Properties {
    // 属性
  }
  SubShader{
    // 显卡 A 使用的子着色器
  }
  SubShader{
    // 显卡 B 使用的子着色器
  }
  Fallback "VertexLit"
}
```

#### Shader Name

line 2 `Shader "ShaderName"`

定义 Shader 名称，可同时定义下拉列表，如 "Custom/ShaderName"

#### 属性块

line 3 `Properties{}`

定义 Shader 属性，这些属性将出现在编辑器的材质面板中。

属性使用如下语法：

`Name ("display name", PropertyType) = DefaultValue`

- `Name` 属性名
  用于在 Shader 中访问的标识符。
- `display name` Editor 显示名
  编辑器中的显示名称。
- `PropertyType` 类型
  编辑器中的类型。
- `DefaultValue` 默认值

```unityShader
Properties {
  _Color ("Color", Color) = (1,1,1,1)
  _Glossiness ("Smoothness", Range(0,1)) = 0.5
}
```

See-also [SL-Properties | Unity](https://docs.unity3d.com/Manual/SL-Properties.html)
