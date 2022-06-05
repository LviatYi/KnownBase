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

### 3.1.1 DTD 构建模块

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
    - `child` 出现一次。
    - `child+` 最少出现一次。
    - `child*` 0 次或多次。
    - `child?` 0 次或 1 次。
    - `(child1|child2)` 二选一地。

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

XML Schema 是 DTD 的基于 XML 的替代方法，也被称为 XSD (XML Schema Definition)，比 DTD 更强大：

- XML Schema 是用 XML 编写的。
- XML Schema 可扩展到添加。
- XML Schema 支持数据类型。
- XML Schema 支持命名空间。

### 3.2.1 Schema 根元素与引用

#### 3.2.1.1 `<schema>`

`<schema>` 是 XSD 的根元素，其通常如下所示：

```xml
<xs:schema
  xmlns:xs="http://www.w3.org/2001/XMLSchema"
  targetNamespace="https://www.w3shcools.com"
  xmlns="https://www.w3shcools.com"
  elementFormDefault="qualified">
  ...
</xs:schema>
```

其中：

- `xmlns:xs` 指明 `xs` 命名空间。
- `targetNamespace` 指明元素来自的命名空间。
- `xmlns` 指明默认命名空间。
- `elementFormDefault` 指明此 schema 中声明的 XML 实例文档使用的任何元素都必须是命名空间限定的。

#### 3.2.1.2 引用 Schema

在某个 XML 文档引用 XML schema：

```xml
<?xml version="1.0"?>

<note xmlns="https://www.w3schools.com"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:schemaLocation="https://www.w3schools.com note.xsd">
  <to>Tove</to>
  <from>Jani</from>
  <heading>Reminder</heading>
  <body>Don't forget me this weekend!</body>
</note>
```

其中：

- `xmlns` 指明默认命名空间。
- `xmlns:xsi` 是默认用于 XSD 的命名空间。
- `xsi:schemaLocation` 是一个用空格分隔的键值对。key 表示要使用的命名空间，value 表示 xsd 文件位置。

### 3.2.2 Schema 简单元素

简单元素是只能包含文本的 XML 元素。它不能包含任何其他元素或属性。

文本可具有不同类型，包括布尔值、字符串或日期等。

```xml
<xs:element name="elem_name" type="elem_type"/>
```

其中 `elem_type` 可为：

- `xs:string`
- `xs:decimal`
- `xs:integer`
- `xs:boolean`
- `xs:date`
- `xs:time`

简单元素还可定义默认值和固定值：

- `default="default_value"` 默认值。
- `fixed="fixed_value"` 固定值。

### 3.2.3 Schema 属性

简单元素不能具有属性。如果元素具有属性，则将其视为复杂类型。但属性本身始终声明为简单类型。

```xml
<xs:attribute name="attr_name" type="attr_type"/>
```

其中 `attr_type` 可为：

- `xs:string`
- `xs:decimal`
- `xs:integer`
- `xs:boolean`
- `xs:date`
- `xs:time`

属性可定义默认值和固定值：

- `default="default_value"` 默认值。
- `fixed="fixed_value"` 固定值。

属性可具有可选性或必需性，默认为可选的：

- `use="required"` 必需的。

### 3.2.4 Schema 约束

约束用于定义 XML 元素或属性的可接受值。对 XML 元素的限制称为 Facets。

#### 范围约束

```xml
<xs:element name="elem_name">
  <xs:simpleType>
    <xs:restriction base="xs:integer">
      <xs:minInclusive value="mix_value"/>
      <xs:maxInclusive value="max_value"/>
    </xs:restriction>
  </xs:simpleType>
</xs:element>
```

#### 枚举约束

```xml
<xs:element name="elem_name">
  <xs:simpleType>
    <xs:restriction base="xs:string">
      <xs:enumeration value="enum1"/>
      <xs:enumeration value="enum2"/>
      <xs:enumeration value="enum3"/>
    </xs:restriction>
  </xs:simpleType>
</xs:element>
```

#### 模式约束

```xml
<xs:element name="elem_name">
  <xs:simpleType>
    <xs:restriction base="xs:string">
      <xs:pattern value="pattern"/>
    </xs:restriction>
  </xs:simpleType>
</xs:element>
```

其中 `pattern` 为模式串。

- `[a-zA-Z]` 允许 a 到 z 的小写或大写字母。
- `()*` 括号内可重复 0 或多次。
- `()+` 括号内可重复 1 或多次。
- `|` 枚举的。
- `{n}` 前者的数量为 n 次。

#### 空白符约束

```xml
<xs:element name="elem_name">
  <xs:simpleType>
    <xs:restriction base="xs:string">
      <xs:whiteSpace value="preserve|replace|collapse"/>
    </xs:restriction>
  </xs:simpleType>
</xs:element>
```

- `preserve` 将允许任何空白符（换行符、制表符、回车符、空格）。
- `replace` 将所有空白符替换为空格。
- `collapse` 将折叠多余的空白符至单个空格。

#### 长度约束

```xml
<xs:element name="elem_name">
  <xs:simpleType>
    <xs:restriction base="xs:string">
      <xs:xs:length value="length"/>
      <xs:xs:minLength value="minLength"/>
      <xs:xs:maxLength value="maxLength"/>
    </xs:restriction>
  </xs:simpleType>
</xs:element>
```

- `length` 固定长度。
- `minLength` 最小长度。
- `maxLength` 最大长度。

#### 所有约束

|       约束       |                       定义                       |
| :--------------: | :----------------------------------------------: |
|  `enumeration`   |                定义枚举的可接受值                |
| `fractionDigits` |     指定允许的最大小数位数，必须等于或大于零     |
|     `length`     | 指定允许的确切字符数或列表项数，必须等于或大于零 |
|  `maxExclusive`  |        指定数值的上限（该值必须小于此值）        |
|  `maxInclusive`  |     指定数值的上限（该值必须小于或等于该值）     |
|   `maxLength`    | 指定允许的最大字符数或列表项数，必须等于或大于零 |
|  `minExclusive`  |        指定数值的下限（该值必须大于该值）        |
|  `minInclusive`  |     指定数值的下限（该值必须大于或等于该值）     |
|   `minLength`    | 指定允许的最小字符数或列表项数，必须等于或大于零 |
|    `pattern`     |             定义可接受的字符的模式串             |
|  `totalDigits`   |          指定允许的确切位数。必须大于零          |
|   `whiteSpace`   | 指定如何处理空白（换行符、制表符、空格和回车符） |

### 3.2.5 Schema 复杂元素

复杂元素是包含其他元素和（或）属性的 XML 元素。

有四种复杂元素：

- 空元素。
- 仅包含其他元素的元素。
- 仅包含文本的元素。
- 同时包含其他元素和文本的元素。

这些元素中的每一个也可能包含属性。

一般有两种复杂元素的表示法：

- 内嵌类型

  ```xml
  <xs:element name="elem_name">
  <xs:complexType>
    <xs:sequence>
      <xs:element name="subElem1_name" type="subElem_type"/>
      <xs:element name="subElem2_name" type="subElem_type"/>
    </xs:sequence>
  </xs:complexType>
  </xs:element>
  ```

- 引入类型

  ```xml
  <xs:element name="elem_name" type="elem_type"/>

  <xs:complexType name="elem_type">
    <xs:sequence>
      <xs:element name="subElem1_name" type="subElem_type"/>
      <xs:element name="subElem2_name" type="subElem_type"/>
    </xs:sequence>
  </xs:complexType>
  ```

  - 具有可复用性。

可以使复杂类型基于现有的复杂类型：

```xml
<xs:complexType name="more_complex">
  <xs:complexContent>
    <xs:extension base="elem_type">
      <xs:sequence>
        <xs:element name="more_elem1" type="elem_type"/>
        <xs:element name="more_elem2" type="elem_type"/>
      </xs:sequence>
    </xs:extension>
  </xs:complexContent>
</xs:complexType>
```

#### 空元素

空的复杂元素只有属性而没有内容。

定义空元素只需使 `complexContent` 内不包含任何元素。

```xml
<xs:element name="elem_name">
  <xs:complexType>
    <xs:complexContent>
      <xs:restriction base="xs:integer">
        <xs:attribute name="attribute" type="attribute"/>
      </xs:restriction>
    </xs:complexContent>
  </xs:complexType>
</xs:element>
```

或

```xml
<xs:element name="elem_name">
  <xs:complexType>
    <xs:attribute name="attribute" type="attribute"/>
  </xs:complexType>
</xs:element>
```

#### 仅元素的复杂元素

仅元素复杂类型仅包含元素。

```xml
<xs:element name="elem_name">
  <xs:complexType>
    <xs:sequence>
      <xs:element name="elem1_name" type="elem_type"/>
      <xs:element name="elem2_name" type="elem_type"/>
    </xs:sequence>
  </xs:complexType>
</xs:element>
```

#### 纯文本元素

纯文本指仅包含简单内容（文本和属性），其用 `simpleContent` 元素表示。  
使用简单内容时，必须在其内定义 `extension` 或 `restriction`。

```xml
<xs:element name="elem_name">
  <xs:complexType>
    <xs:simpleContent>
      <xs:extension base="basetype">
        ....
        ....
      </xs:extension>
    </xs:simpleContent>
  </xs:complexType>
</xs:element>
```

或

```xml
<xs:element name="elem_name">
  <xs:complexType>
    <xs:simpleContent>
      <xs:restriction base="basetype">
        ....
        ....
      </xs:restriction>
    </xs:simpleContent>
  </xs:complexType>
</xs:element>
```

#### 混合内容元素

> ```xml
> <letter>
>   Dear Mr. <name>John Smith</name>.
>   Your order <orderid>1032</orderid>
>   will be shipped on <shipdate>2001-07-13</shipdate>.
> </letter>
> ```

混合内容元素具有 `mixed` 选项。

- `true` 允许字符数据显示在元素之间。

```xml
<xs:element name="letter">
  <xs:complexType mixed="true">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="orderid" type="xs:positiveInteger"/>
      <xs:element name="shipdate" type="xs:date"/>
    </xs:sequence>
  </xs:complexType>
</xs:element>
```

### 3.2.6 Schema 指示符

指示符控制如何使用元素。

指示符包含：

- 顺序指示符
  - `all` 可以按任何顺序出现，且有且仅有一次。
  - `choice` 只能选择一个元素。
  - `sequence` 必须按照指定顺序出现。
- 出现指示符
  - `maxOccurs` 指定最多出现次数，可以为 `unbounded`。
  - `minOccurs` 指定最少出现次数。
- 分组指示符

  - `group` 定义相关的元素集。
    - 必须定义顺序指示符修饰的元素。
  - `attributeGroup` 定义相关的属性集。

    - 可以在另一个定义中引用属性组。

    ```xml
      <xs:attributeGroup name="personattrgroup">
        <xs:attribute name="firstname" type="xs:string"/>
        <xs:attribute name="lastname" type="xs:string"/>
        <xs:attribute name="birthday" type="xs:date"/>
      </xs:attributeGroup>

      <xs:element name="person">
        <xs:complexType>
          <xs:attributeGroup ref="personattrgroup"/>
        </xs:complexType>
      </xs:element>
    ```

### 3.2.7 Schema `any` 元素

`any` 元素允许使用 XSD 未指定的元素扩展 XML 文档。

```xml
<!-- person.xsd -->
<xs:element name="person">
  <xs:complexType>
    <xs:sequence>
      <xs:element name="firstname" type="xs:string"/>
      <xs:element name="lastname" type="xs:string"/>
      <xs:any minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>
</xs:element>
```

```xml
<!-- children.xsd -->
<?xml version="1.0" encoding="UTF-8"?>

<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"
targetNamespace="https://www.w3schools.com"
xmlns="https://www.w3schools.com"
elementFormDefault="qualified">
  <xs:element name="children">
    <xs:complexType>
      <xs:sequence>
        <xs:element name="childname" type="xs:string"
        maxOccurs="unbounded"/>
      </xs:sequence>
    </xs:complexType>
  </xs:element>
</xs:schema>
```

```xml
<!-- myfamily.xml -->
<?xml version="1.0" encoding="UTF-8"?>

<persons xmlns="http://www.microsoft.com"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:schemaLocation="http://www.microsoft.com family.xsd
https://www.w3schools.com children.xsd">
  <person>
    <firstname>Hege</firstname>
    <lastname>Refsnes</lastname>
    <children>
      <childname>Cecilie</childname>
    </children>
  </person>

  <person>
    <firstname>Stale</firstname>
    <lastname>Refsnes</lastname>
  </person>
</persons>
```

### 3.2.8 Schema `anyAttribute` 元素

`anyAttribute` 元素允许使用 XSD 未指定的属性扩展 XML 文档。

```xml
<!-- family.xsd -->
<xs:element name="person">
  <xs:complexType>
    <xs:sequence>
      <xs:element name="firstname" type="xs:string"/>
      <xs:element name="lastname" type="xs:string"/>
    </xs:sequence>
    <xs:anyAttribute/>
  </xs:complexType>
</xs:element>
```

```xml
<!-- attribute.xsd -->
<?xml version="1.0" encoding="UTF-8"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"
targetNamespace="https://www.w3schools.com"
xmlns="https://www.w3schools.com"
elementFormDefault="qualified">

  <xs:attribute name="eyecolor">
    <xs:simpleType>
      <xs:restriction base="xs:string">
        <xs:pattern value="blue|brown|green|grey"/>
      </xs:restriction>
    </xs:simpleType>
  </xs:attribute>
</xs:schema>
```

```xml
<!-- myfamily.xml -->
<?xml version="1.0" encoding="UTF-8"?>

<persons xmlns="http://www.microsoft.com"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:SchemaLocation="http://www.microsoft.com family.xsd
https://www.w3schools.com attribute.xsd">

  <person eyecolor="green">
    <firstname>Hege</firstname>
    <lastname>Refsnes</lastname>
  </person>

  <person eyecolor="blue">
    <firstname>Stale</firstname>
    <lastname>Refsnes</lastname>
  </person>
</persons>
```

### 3.2.9 Schema 元素替换

Schema 允许将一个元素替换为另一个元素。

使用 `substitute` 允许替换相同 `name` 的元素。

```xml
<xs:element name="name" type="xs:string"/>
<xs:element name="navn" substitutionGroup="name"/>

<xs:complexType name="custinfo">
  <xs:sequence>
    <xs:element ref="name"/>
  </xs:sequence>
</xs:complexType>

<xs:element name="customer" type="custinfo"/>
<xs:element name="kunde" substitutionGroup="customer"/>
```

```xml
<customer>
  <name>John Smith</name>
</customer>
或
<kunde>
  <navn>John Smith</navn>
</kunde>
```

使用 `block="substitution"` 可以禁用替换。

```xml
<xs:element name="name" type="xs:string"/>
```

可替换元素的类型必须与 head 元素一致或派生自 head 元素。当一致时不需指定替换元素的类型。

替换组中的所有元素（head 元素和可替换元素）都必须声明为全局元素（Schema 元素的直接子元素，而非嵌套在其他元素中的元素），否则它将不起作用！
