# LviatYi 技术文档规范

## 文档属性

作者：LviatYi  
最后更新时间： 2022/11/05

## 符号约定

### 字符符号约定

---

### 文本串约定

- **\_zh** 以中文形式，默认地区 中国大陆
- **\_en** 以英文形式，默认地区 美国
- **subject_name** 项目 / 学科名称
- **category_name** 分类名称

---

## 文件树结构

### 根目录名称

$$
subject\underline{\hspace{5px}} name \underline{\hspace{5px}} en
$$

Pascal 法。

---

### 概述文件

子项目根目录必须放置概述文件。

#### 概述文件名称

$$
subject\underline{\hspace{5px}} name\underline{\hspace{5px}} en[+ category\underline{\hspace{5px}} name \underline{\hspace{5px}} en]
$$

以 **-** 分隔单词，全小写。

#### 概述文件结构

- 目录
- 项目概述
- 学科概述
- 资料
  - 文献
  - 视频

---

## 文件版本号

`v1.00` 前为构建过程中版本，以如下公式反映构建进度：

$$
V_{版本号}=C_{已完成内容量}/C_{目标内容量}
$$

`v1.00` 后为维护版本。

## Markdown 文档编写时规范

Markdown 文档编写时规范参考：

[Markdown Style Guide][styleguideline]

[styleguideline]: ../Markdown/markdown-style-guide/index.md
