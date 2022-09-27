# 6. 文档体系

## 6.1 结构

推荐 软件手册是一部完整的书，采用下面的结构。

- **简介**（Introduction）： [必备] [文件] 提供对产品和文档本身的总体的、扼要的说明
- **快速上手**（Getting Started）：[可选] [文件] 如何最快速地使用产品
- **入门篇**（Basics）： [必备] [目录] 又称”使用篇“，提供初级的使用教程
  - **环境准备**（Prerequisite）：[必备] [文件] 软件使用需要满足的前置条件
  - **安装**（Installation）：[可选] [文件] 软件的安装方法
  - **设置**（Configuration）：[必备] [文件] 软件的设置
- **进阶篇**（Advanced)：[可选] [目录] 又称”开发篇“，提供中高级的开发教程
- **API**（Reference）：[可选] [目录|文件] 软件 API 的逐一介绍
- **FAQ**：[可选] [文件] 常见问题解答
- **附录**（Appendix）：[可选] [目录] 不属于教程本身、但对阅读教程有帮助的内容
  - **Glossary**：[可选] [文件] 名词解释
  - **Recipes**：[可选] [文件] 最佳实践
  - **Troubleshooting**：[可选] [文件] 故障处理
  - **ChangeLog**：[可选] [文件] 版本说明
  - **Feedback**：[可选] [文件] 反馈方式

下面是两个真实范例，可参考。

- [Redux 手册][Redux-Manual]
- [Atom 手册][Atom-Manual]

## 6.2 文件名

必须 如果文件夹下有 README 文件且标注了文件名命名规范（README 规范），则 README 规范视作优先级最高的规范。  
如果否，则遵守其下规范。  

### 6.2.1 必须 文档的文件名不得含有空格与全角字符

文件名必须使用半角字符。这意味着，中文不能用于文件名。  

> 错误： 名词解释.md
>  
> 正确： glossary.md

### 6.2.2 推荐 文件名只使用小写字母

> 正确：TroubleShooting.md
>  
> 推荐：troubleshooting.md

为了醒目，某些说明文件的文件名，可以使用大写字母，比如 `README` 、 `LICENSE` 。

### 6.2.3 推荐 文件名包含多个单词时，单词之间使用半角的连词线（ `-` ）分隔

> 正确：advanced_usage.md
>  
> 推荐：advanced-usage.md

请分别双击选中 `usage` 以观察其中区别。  

## 6.3 文件夹名

### 6.3.1 必须 文件夹名不得含有空格与全角字符

> 错误：文件
>  
> 正确：Document

### 6.3.2 推荐 主要文件夹使用大写字母作为开头

> 推荐：Document

### 6.3.3 推荐 附属文件夹只使用小写字母，不使用大写字母

> 正确：asset
>  
> 推荐：Asset

### 6.3.4 推荐 文件夹名包含多个单词时，单词之间使用半角的连词线（ `-` ）分隔

> 正确：Markdownstyleguide
>  
> 推荐：Markdown-style-guide

[Redux-Manual]:https://redux.js.org/introduction/getting-started
[Atom-Manual]:http://flight-manual.atom.io/