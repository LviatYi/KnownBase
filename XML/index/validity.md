# 3. 有效性

XML 允许设定规则以定义文档是否有效。

## 3.1 DTD

文档定义类型 (DTD,Document Type Definition) 是一种 XML 文档验证机制，是一种不同于 XML 语法的另一种语法。

用 DTD 声明的元素、属性及其类型，可以使元素、属性按一定的要求在 XML 中出现，以达到验证 XML 文档的目的。这样 XML 就离不开 DTD 限定的框架，否则就为无效。

一般地，有如下方式应用 DTD：

- 内部 DTD
  - DTD 部署与文档内部。  
    `<!DOCTYPE root-element [element-declarations]>`
- 外部 DTD
  - DTD 以独立文件形式存在。  
    `<!DOCTYPE root-element SYSTEM "uri">`  
    `<!DOCTYPE root-element PUBLIC "DTD_Name" "uri">`
- 混合方式
  - 同时使用上述两种方式。

### 3.1.1 构建模块

所有的 XML 文档（以及 HTML 文档）均由以下简单的构建模块构成：

- 元素
- 属性
- 实体
- PCDATA
  - 被解析的字符数据 (parsed character data)
  - 被解析为标签与文本。
- CDATA
  - 不被解析的字符数据 (character data)
  - 仅被解析为文本。

### 3.1.2 DTD 元素

DTD 的元素声明使用如下语法：

```xml
<!ELEMENT element-name category>
或
<!ELEMENT element-name (element-content)>
```

其中 `category` 或 `(element-content)` 可为：

- `EMPTY` 空元素。
- `ANY` 可包含任何可解析数据的组合。
- `(#PCDATA)` PCDATA。
- `(childlist)` 子元素序列。
  - 表示其按照顺序包含一系列子元素。用 `,` 隔开。
  - 元素名后加上控制符号，可控制元素的出现行为。
    - `(null)` 仅出现一次。
    - `+` 最少出现一次。
    - `*` 0 次或多次。
    - `?` 0 次或 1 次。
    - `(elem1|elem2)` 二选一地。

### 3.1.3 DTD 属性

DTD 的属性声明使用如下语法：

```xml
<!ATTLIST element-name attribute-name attribute-type attribute-value>
DTD 实例:
<!ATTLIST payment type CDATA "check">
XML 实例:
<payment type="check" />
```

其中 `attribute-type` 可为：

- `CDATA` 值为字符数据 (character data)。
- `(en1|en2|..)` 此值是枚举列表中的一个值。
- `ID` 值为唯一的 id。
- `IDREF` 值为另外一个元素的 id。
- `IDREFS` 值为其他 id 的列表。
- `NMTOKEN` 值为合法的 XML 名称。
- `NMTOKENS` 值为合法的 XML 名称的列表。
- `ENTITY` 值是一个实体。
- `ENTITIES` 值是一个实体列表。
- `NOTATION` 此值是符号的名称。
- `xml:` 值是一个预定义的 XML 值。

其中 `attribute-value` 可为：

- `value` 属性的默认值。
- `#REQUIRED` 属性值是必需的。
- `#IMPLIED` 属性不是必需的。
- `#FIXED value` 属性值是固定的。

### 3.1.4 DTD 实体

DTD 的实体声明使用如下语法：

```xml
<!ENTITY entity-name "entity-value">
或
<!ENTITY entity-name SYSTEM|PUBLIC "uri">
```

实例：

```XML
<!ENTITY writer "Lviat Yi.">
<!ENTITY mailto "mailto:lviatyi@foxmail.com">
<author>&writer;&mailto;</author>
```

## 3.2 Schema
