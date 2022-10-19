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




- 几何阶段



- 光栅化阶段




