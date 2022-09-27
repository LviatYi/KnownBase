# Unity 最佳实践

## 文件结构

一般地，Unity 项目需遵循以下规则：

- 将命名约定和文件夹结构规范化。  
  使用样式指南或项目模板规范化团队行为。
- 不要轻易改动命名约定。  
  如不可避免，需要负责更新原有资产。
- 不要在文件与文件夹名称中使用空格。
- 单独的测试区域或沙盒区域。  
  为非生产场景和试验创建单独的文件夹。
- 避免在根目录使用额外文件夹。  
  通常需要将内容文件放在 Assets 文件夹中。
- 将内部资产与第三方资产分开。  
  第三方资产可能具有自己的项目结构。分开以避免混乱。

Unity 中没有最完美的文件结构可供参考，这并不意味着可以随意存放文件，而是视项目规模等因素形成自己的习惯。

推荐的结构：

```java
└─ Assets
    ├─ Resources
    │  ├─ Prefab
    │  ├─ Meterial
    │  ├─ Model
    │  ├─ Audio
    │  │  ├─ Sound
    │  │  └─ Music
    │  ├─ Texture
    │  ├─ Animation
    │  ├─ Font
    │  ├─ Sprite
    │  │  └─ Tile
    │  ├─ Terrain
    │  ├─ Config
    │  └─ ScriptableObject
    ├─ Scripts
    ├─ Game
    │  ├─ Camera
    │  └─ UI
    ├─ Scenes
    ├─ UI Toolkit
    ├─ Editor
    ├─ Test
    └─ Third
```

## 版本控制

对于 Unity 项目的版本控制有以下几点需注意：

- 空文件夹可能不被 git 等版本控制工具管理。
  - 可以在空文件夹中放置 .keep 文件（一个空文件）避免。
  - Plastic SCM 能够处理空文件。
- .meta 文件是自动生成的，但这类文件不应被版本控制忽略。

## 命名约定

### 资产命名

资产命名应具有可辨识性。

尽可能少地使用下划线 `_`，使它能够表示一些特殊含义。

### 代码命名

详情参考 [C# 命名约定][csharpcodeconvention]。

## 拆分资产

单个大型场景不适合协作。使用如下方法提高合作效率：

- 将大型场景划分为小场景。
- 将工作分解为预制件。
- 使用 [智能合并](https://docs.unity3d.com/Manual/SmartMerge.html) 处理冲突

## 使用预设

通过创建 Prefab ，可以提高复用性，便于项目管理。

[csharpcodeconvention]: ../../../CSharp/index/csharpCodeConvention.md
