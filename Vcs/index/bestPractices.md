# 版本控制最佳实践

## 约定式提交

约定式提交规范是一种基于提交信息的轻量级约定，用于提升版本控制附带信息的人机可读性，从而提高可追溯性与易维护性。

提交附带信息应遵循如下结构：

```shell
<type 类型>([scope 范围]): <description 描述>
<BLANKLINE 空白行>
[body 正文]
<BLANKLINE 空白行>
[footer 脚注]

# 标记示例
# <必选>
# [可选]
```

### 类型 type

表达了此次提交的功能性含义。

类型必须是以下可选项之一：

- **build**  
  影响构建系统或外部依赖项的更改。
- **ci**: 更改了 CI 的配置文件与脚本 (example **scopes**: Travis, Circle, BrowserStack, SauceLabs)
- **docs**: 文档相关的更改。
- **feat**: 添加了一个新的功能 (feature)。
- **fix**: 修复了一个 Bug。
- **perf**: 提升了性能的修复。
- **refactor**: 代码重构，既未修复 bug 亦未新增功能。
- **style**: 风格化代码，未更改任何具有语义的代码。
- **test**: 添加缺失的测试或修正现有的测试。
- **revert**: 用于撤销过往的提交。**正文 body** 中必须包含回退的版本号或版本哈希。

当提交了破坏式变更时，必须在 **类型 type** 后添加 `!`，否则提交必须包含 `BREAKING CHANGE` 脚注。

```shell
feat!: send an email to the customer when a product is shipped
```

### 范围 scope

指定了提交更改影响的范围。

### 描述 description

简短地描述了提交的目的。

- 使用命令式的语态。
- 使用正在进行的时态。
- 首字母不要大写。
- 结尾不需要标点符号。
- 一般不超过 50 个字。

### 正文 body

详细地描述了提交的细节。

- 语法与 **描述 description** 中相同。
- 字数一般不受限制。
- 包括动机与先前的行为变化和对比。

### 脚注 footer

以 `token: value` 形式标识了提交需要附带的属性。

- 除了 `BREAKING CHANGE`，脚注的 token 必须使用 `-` 作为连字符。
- 脚注必须使用 `:<space>` 或 `<space>#` 作为 token 与 value 的分隔符。
- 如果提交了破坏式变更，若没有在 **类型 type** 后添加 `!` ，则必须包含 `BREAKING CHANGE` 脚注。
