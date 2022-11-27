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

- `Name` 属性名用于在 Shader 中访问的标识符。
- `display name` Editor 显示名编辑器中的显示名称。
- `PropertyType` 类型编辑器中的类型。
- `DefaultValue` 默认值

```unityShader
Properties {
  _Color ("Color", Color) = (1,1,1,1)
  _Glossiness ("Smoothness", Range(0,1)) = 0.5
}
```

See-also [SL-Properties | Unity][sl-properties]

![所有 ShaderLab 支持的属性](../../pic/shaderLabProperties.png)

![所有 ShaderLab 支持的属性在检视窗口](/assets/shaderPropertiesInspector.png)

Unity 支持重载默认的材质编辑面板。

#### SubShader

line 6 `SubShader{}`

定义了 LOD 、一系列 **通道 `Pass`** 以及可选的 **标签 `tags`** 和 **命令 `commands`** 。

每个 Unity Shader 最少 1 个。当 Unity 加载 Unity Shader 时，将扫描所有 SubShader 语义块，然后选择首个可以在目标平台运行的 SubShader，否则使用 Fallback 定义的 Unity Shader。

- **命令** 将 GPU 指令或着色器代码添加到 SubShader。主要分为以下类别：

  - 用于在 GPU 上设置渲染状态的命令。
  - 用于创建具有特定用途的通道。
  - 如果使用旧版「fixed function style」命令，无需编写 HLSL 也可创建着色器程序。

  | 命令名称 | 解释 |
  | --- | --- |
  | AlphaToMask | 设置 alpha-to-coverage 模式 |
  | Blend | 启用和配置 alpha 混合 |
  | BlendOp | 设置 Blend 命令使用的操作 |
  | ColorMask | 设置颜色通道写入掩码 |
  | Conservative | 启用和禁用保守光栅化 |
  | Cull | 设置多边形剔除模式 |
  | Offset | 设置多边形深度偏移 |
  | Stencil | 配置模板测试，以及向模板缓冲区写入的内容 |
  | ZClip | 设置深度剪辑模式 |
  | ZTest | 设置深度测试模式 |
  | ZWrite | 设置深度缓冲区写入模式 |
  | UsePass | 定义一个通道，它从另一个 Shader 对象导入指定的通道的内容 |
  | GrabPass | 创建一个通道，将屏幕内容抓取到纹理中，以便在之后的通道中使用 |

  See-also [Shaderlab Commands | Unity][shaderlab-commands]

- **标签** 是一个 **键值对**，其键与值都是字符串。  
  Unity 具有一系列预定义的标签，也可以自定义标签。

  | 标签名称 | 说明 |
  | --- | --- |
  | Queue | 向 Unity 告知要用于它渲染的几何体的渲染队列。渲染队列是确定 Unity 渲染几何体的顺序的因素之一 |
  | RenderType | 可覆盖 Shader 对象的行为 可用于着色器替换 |
  | ForceNoShadowCasting | 阻止子着色器中的几何体投射（有时是接收）阴影。确切行为取决于渲染管线和渲染路径 |
  | DisableBatching | 阻止 Unity 将动态批处理应用于使用此子着色器的几何体 |
  | IgnoreProjector | （仅内置渲染管线）向 Unity 告知几何体是否受投影器影响 |
  | PreviewType | 告知 Unity 编辑器如何在材质 Inspector 中显示使用此子着色器的材质 |
  | CanUseSpriteAtlas | 在使用 Legacy Sprite Packer 的项目中使用此子着色器标签可警告用户着色器依赖于原始纹理坐标，因此不应将其纹理打包到图集中 |

  See-also [Shaderlab Tags | Unity][shaderlab-tags]

  标签可以通过 C# 访问。

  ```Csharp
  Renderer myRenderer = GetComponent<Renderer>();
  string tagValue = myRenderer.material.GetTag(ExampleTagName, true, "Tag not found");
  ```

- **通道** 定义了一次完整的渲染流程。  
  过多的 `Pass` 数量将造成渲染性能下降。

  Pass 示例：

  ```unityShader
  Pass {
    Name "ExamplePassName" // Pass 名称
    Tags { "ExampleTagKey" = "ExampleTagValue" }

    // Commands

    // HLSL Code
  }
  ```

  通过定义名称可以使用 UsePass 命令在其他 Unity Shader 中使用该 Pass。在内部，Unity 将名称转换为 **大写**。

  通道可使用 **通道标签**，与 **SubShader 标签** 不同，因此 SubShader 中的预定义标签不能与通道预定义标签混用。  
  通道预定义标签包括：

  | 标签名称    | 说明                                         |
  | ----------- | -------------------------------------------- |
  | `LightMode` | 用于所有渲染管线。其他通道标签因渲染管线而异 |

  See-also [Shaderlab Pass Tags | Unity][shaderlab-passtags]

#### Fallback

line 12 `Fallback "name"`

设定回退 shader ，当不存在可用 SubShader 时，调用指定 shader。

设定 `Off` 时取消回退。

#### Catagory

`Catagory{}` 语义块用于定义一个空间，用于将某个命令的生命周期限定在块内。

### Unity Shader 形式

可编程管线的着色器包括：

- 表面着色器
  - 善于处理复杂的光照情况。
  - 损失一定性能。
- 顶点 / 片元着色器
  - 更加灵活的渲染效果。

不可编程管线的着色器包括：

- 固定函数着色器

固定函数着色器为非常老旧的设备提供支持。

#### 表面着色器

**表面着色器 (Surface shader)** 是 Unity 提供的顶点、片元着色器的一层抽象，其提供对光照细节的处理。

表面着色器定义于 SubShader 语义块。建议使用 HLSL 作为 Shader 语言，Unity 内部提供了转换，将 HLSL 转换为 CG。而 CG 本身已经渐渐被淘汰。

Shader 语句由 `HLSLPROGRAM` 起始，由 `ENDHLSL` 结尾。

```unityShader
Shader "Custom/Simple Surface Shader" {
  SubShader {
    Tags { "RenderType" = "Opaque" }

    HLSLPROGRAM
    #pragma surface surf Lambert
    struct Input {
      float4 color : COLOR;
    };
    void surf ( Input IN , inout SurfaceOutput o ) {
      o.Albedo = 1;
    }
    ENDHLSL
  }
  Fallback "Diffuse"
}
```

#### 顶点 / 片元着色器

顶点 / 片元着色器 (Vertex/Fragment Shader) 具有更复杂的功能与更高的灵活性。

顶点 / 片元着色器定义于 Pass 语义块。

```unityShader
Shader "Custom/Simple VertexFragment Shader" {
  SubShader {
    Pass {
      HLSLPROGRAM
      #pragma vertex vert
      #pragma fragment frag

      float4 vert(float4 v : POSITION) : SV_POSITION {
        return mul( UNITY_MATRIX_MVP , v);
      }

      fixed4 frag() : SV_Target {
        return fixed4( 1.0 , 0.0 , 0.0 , 1.0 );
      }

      ENDHLSL
    }
  }
}
```

[sl-properties]: https://docs.unity3d.com/Manual/SL-Properties.html
[shaderlab-commands]: https://docs.unity3d.com/Manual/shader-shaderlab-commands.html
[shaderlab-tags]: https://docs.unity3d.com/cn/current/Manual/SL-SubShaderTags.html
[shaderlab-passtags]: https://docs.unity3d.com/cn/current/Manual/SL-PassTags.html
