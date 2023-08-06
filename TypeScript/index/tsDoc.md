# TSDoc

## 概述

TSDoc 是一个标准化 TypeScript 代码中使用的文档注释的建议，以便不同的工具可以提取内容而不会被彼此的标记混淆。

规范化的 TSDoc 无疑拥有更强的人机可读性。

## 标签

### `@alpha`

- **Discretionary**
- **修饰符**

API 处于 alpha 待发布阶段。

未发布。

可能会在公开发布时删除声明。

### `@beta`

- **Discretionary**
- **修饰符**
- 同义：
  - `@experimental`

API 处于 beta 待发布阶段。

小范围发布。注意随时可能发生 API 更改。

可能会在公开发布时删除声明。

### `@decoratora`

- **Extended**
- **块**

装饰器。

### `@deprecated`

- **Core**
- **块**

API 是废弃的，不再受支持，并且可能在未来版本中删除。

递归的，当一个类被废弃，其所有成员都将被废弃。

### `@defaultValue`

- **Extended**
- **块**

默认值。

仅类或接口的成员或属性。

### `@eventProperty`

- **Extended**
- **修饰符**

事件属性。

通常是一个返回类型具有 `addHandler()` 和 `removeHandler()` 的成员。

仅类或接口的成员或属性。

### `@example`

- **Extended**
- **块**

示例。

提示如何使用 API。

仅类或接口的成员或属性。

### `@experimental`

- **Discretionary**
- **修饰符**
- 同义：
  - `@experimental`

### `@inheritDoc`

- **Extended**
- **内联**

用于通过从另一个 API 项目复制 API 项目的文档来自动生成该文档。  
内联标记参数包含对其他项的引用，该项可能是不相关的类，甚至可能是从单独的 NPM 包导入的。

### `@internal`

- **Discretionary**
- **修饰符**

内部的。

提示此 API 不打算供第三方开发人员使用。

可能会在公开发布时删除声明。

在一些实现中，可以允许某些指定的包使用内部 API 项，例如因为这些包是同一产品的组件。

### `@label`

- **Core**
- **内联**

声明一个标签。

以便可以使用 TSDoc 声明引用符号中的选择器来引用它。

```TypeScript
export interface Interface {
  /**
   * Shortest name:  {@link InterfaceL1.(:STRING_INDEXER)}
   * Full name:      {@link (InterfaceL1:interface).(:STRING_INDEXER)}
   *
   * {@label STRING_INDEXER}
   */
  [key: string]: number;

  /**
   * Shortest name:  {@link InterfaceL1.(:NUMBER_INDEXER)}
   * Full name:      {@link (InterfaceL1:interface).(:NUMBER_INDEXER)}
   *
   * {@label NUMBER_INDEXER}
   */
  [key: number]: number;

  /**
   * Shortest name:  {@link InterfaceL1.(:FUNCTOR)}
   * Full name:      {@link (InterfaceL1:interface).(:FUNCTOR)}
   *
   * {@label FUNCTOR}
   */
  (source: string, subString: string): boolean;

  /**
   * Shortest name:  {@link InterfaceL1.(:CONSTRUCTOR)}
   * Full name:      {@link (InterfaceL1:interface).(:CONSTRUCTOR)}
   *
   * {@label CONSTRUCTOR}
   */
  new (hour: number, minute: number);
}
```

### `@link`

- **Core**
- **内联**

事件属性。

创建指向文档系统中其他页面或一般互联网 URL 的超链接，也可以引用一个 API 项目。

### `@override`

- **Extended**
- **修饰符**

覆写。

显式指示此定义将覆写从基类继承的定义。

### `@packageDocumentation`

- **Core**
- **修饰符**

描述整个 NPM 包的文档注释（而不是属于该包的单个 API 项）。

应位于充当包入口点的 `.d.ts` 文件中，并且是该文件中遇到的第一个注释。包含 `@packageDocumentation` 标记的注释永远不应该用于描述单个 API 项。

### `@param`

- **Core**
- **块**

函数形式参数。

通常是一个返回类型具有 `addHandler()` 和 `removeHandler()` 的成员。

仅类或接口的成员或属性。

### `@privateRemarks`

- **Core**
- **块**

不向公众开放的的附加文档。

### `@public`

- **Discretionary**
- **修饰符**

API 处于公开阶段。

它已正式发布给第三方开发者，并且其签名保证稳定（例如遵循语义版本控制规则）。

### `@readonly`

- **Extended**
- **修饰符**

只读。

以需求行为为准，无论是否这个 API 在程序中被 `readonly` 修饰。如一个总是抛出异常的 `setter`，提示该属性无法分配。

### `@remarks`

- **Core**
- **块**

摘要。

提供概述性信息，如果需要，可以使用 `@summary` 提供更详细信息。

### `@returns`

- **Core**
- **块**

返回值。

### `@sealed`

- **Extended**
- **修饰符**

密封的。

对于类，提示不允许继承该类。  
对于成员函数或属性，提示子类不允许覆写。

### `@see`

- **Extended**
- **块**

引用。

### `@throws`

- **Extended**
- **块**

函数或属性可能引发的异常类型。

如果可能抛出多种异常，应使用多个 `@throws` 一一对应。

### `@typeParam`

- **Core**
- **块**

泛型参数。

### `@virtual`

- **Extended**
- **修饰符**

虚的。

对于成员函数或属性，提示子类允许覆写。
