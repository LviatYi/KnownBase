# Serde 源码研读笔记

![CC BY-SA 4.0][badge-CCBYSA4]

[**CC BY-SA 4.0**][CCBYSA4]

## Overview

目标版本：

- **serde**: 1.0.219
- **serde_json**: 1.0.143

## Topic terms list

主要角色：

- **业务调用者 User** 将 **_Rust 数据结构_** 与 **_数据格式_**（json\bincode\postcard\etc.）相互转化的实际需求者。
- **序列化框架库 Serde** (serde) 制定 **_数据结构_** 与 **_数据格式_** 互转约定的 抽象中间层。
- **序列化器库 SerdeLib** (serde_json, serde_yaml, bincode, etc.) 实现 **_数据格式_** 与 **_数据结构_** 互转的具体工具。
  - 数据格式标准的表达者，并遵循 Serde 约定。
  - 应提供便捷的 Api 以调用，可选地提供中间类型（如 `serde_json::Value`）以便于处理。

测试代码：

```rust
#[cfg(test)]
#[allow(dead_code)]
mod tests {
    use std::fmt;
    use serde::de::{MapAccess, Visitor};
    use serde::ser::SerializeStruct;
    use serde::{de, Deserialize, Deserializer, Serialize, Serializer};

    #[test]
    fn test_to_json() {
        struct Data {
            id: u32,
            name: String,
        }
        impl Serialize for Data {
            fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
            where
                S: Serializer,
            {
                let mut state = serializer.serialize_struct("Data", 2)?;
                state.serialize_field("id", &self.id)?;
                state.serialize_field("name", &self.name)?;
                state.end()
            }
        }

        let data = Data {
            id: 1,
            name: "Test".to_string(),
        };

        let str = serde_json::to_string(&data).unwrap();
        println!("{}", str);
    }

    #[test]
    fn test_from_json() {
        #[derive(Debug)]
        struct Data {
            id: u32,
            name: String,
        }

        impl<'de> Deserialize<'de> for Data {
            fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
            where
                D: Deserializer<'de>,
            {
                enum Field { Id, Name }

                struct DataVisitor;

                impl<'de> Visitor<'de> for DataVisitor {
                    type Value = Data;

                    fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                        formatter.write_str("struct Data")
                    }

                    fn visit_map<V>(self, mut map: V) -> Result<Data, V::Error>
                    where
                        V: MapAccess<'de>,
                    {
                        let mut id = None;
                        let mut name = None;
                        while let Some(key) = map.next_key()? {
                            match key {
                                Field::Id => {
                                    if id.is_some() {
                                        return Err(de::Error::duplicate_field("id"));
                                    }
                                    id = Some(map.next_value()?);
                                }
                                Field::Name => {
                                    if name.is_some() {
                                        return Err(de::Error::duplicate_field("name"));
                                    }
                                    name = Some(map.next_value()?);
                                }
                            }
                        }
                        let id = id.ok_or_else(|| de::Error::missing_field("id"))?;
                        let name = name.ok_or_else(|| de::Error::missing_field("name"))?;
                        Ok(Data { id, name })
                    }
                }

                const FIELDS: &[&str] = &["id", "name"];
                impl<'de> Deserialize<'de> for Field {
                    fn deserialize<D>(deserializer: D) -> Result<Field, D::Error>
                    where
                        D: Deserializer<'de>,
                    {
                        struct FieldVisitor;

                        impl<'de> Visitor<'de> for FieldVisitor {
                            type Value = Field;

                            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                                formatter.write_str("`id` or `name`")
                            }

                            fn visit_str<E>(self, value: &str) -> Result<Field, E>
                            where
                                E: de::Error,
                            {
                                match value {
                                    "id" => Ok(Field::Id),
                                    "name" => Ok(Field::Name),
                                    _ => Err(de::Error::unknown_field(value, FIELDS)),
                                }
                            }
                        }

                        deserializer.deserialize_identifier(FieldVisitor)
                    }
                }

                deserializer.deserialize_struct("Data", FIELDS, DataVisitor)
            }
        }

        let str = r#"{"id":1,"name":"Test"}"#;
        let data: Data = serde_json::from_str(str).unwrap();
        println!("{:?}", data);
    }
}
```

在阅读源码时，要注意：

- 为结构体实现 Deserialize 明显比实现 Serialize 复杂得多。从哲学观角度，Deserialize 面临的情况显然是更「未知」且动态的。而 Serialize 则是更「已知」且静态的，可以直接通过确定的数据结构生成稳定的输出。
- **类型驱动分派**：`Deserialize::deserialize()` 的入口统一，但调用方期望的目标类型决定了具体走哪套 Visitor 回调与访问路径。阅读源码时，要从调用点倒推目标类型。

在使用 Serde 及其生态时，要注意：

- 优先使用宏实现 `#[derive(Serialize, Deserialize)]`，仅在热路径或复杂协议（如自定义错误/顺序/多态）时手写 impl。
- 手写时，尽量覆盖最小必要的 `visit_*`，避免在 `visit_any` 路径上承担过多格式判断。

## Key types

### `serde` Serialize

`ser\mod.rs trait` 具备序列化功能的 trait。

**User** 需对 任何希望被 序列化为某种数据格式 的数据结构 实现该 trait。如 `impl Serialize for Path`

- serialize()

```rust
fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
where
    S: Serializer;
```

作为 **User**，定制 Serialize 时应该了解 **序列化器** 的能力：

- Serializer 提供的方法。
- SerializeSeq、SerializeStruct 等辅助 trait 提供的方法。

### `serde` Serializer

`ser\mod.rs trait` 序列化器，用于将数据结构转换为某种格式数据。

**SerdeLib** 提供了针对各类数据格式的实现。

一般地，该结构内应包含 Writer 作为输出目标。如 `Vec<u8>`。

> 在 serde_json 库中，Serializer 内部还包含一个实现了 `Formatter trait` 的 formatter（CompactFormatter 或 PrettyFormatter），作为向 Writer 的实际写入者，控制输出格式。

- serialize_bool()

```rust
fn serialize_bool(self, v: bool) -> Result<Self::Ok, Self::Error>;
```

- serialize_i32()
- serialize_seq()
- ...

注意到，`serialize_*` 等方法消耗值。但实际上，常见使用 **可变引用** 作为 Self 进行实现。如在 `serde_json` 库中，Serializer 是通过可变引用传递的：

```rust
impl<'a, W, F> ser::Serializer for &'a mut Serializer<W, F>
```

作为 **User**，一般无需直接与 Serializer 交互，而是通过调用 `serde_json::to_string(&data)` 等函数间接使用它提供的服务。
作为 **SerdeLib**，实现 Serializer 时应该了解 **序列化框架** 所约定的调用时机、参数含义。

### `serde` Deserialize

`de\mod.rs trait` 具备反序列化功能的 trait。

**User** 需对 任何希望从 某种数据格式 反序列化而来的 数据结构 实现该 trait。如 `impl Deserialize for Path`

- deserialize()

```rust
fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
where
    D: Deserializer<'de>;
```

作为 **User**，定制 Deserialize 时应该了解 **反序列化器** 与 **数据访问者** 的能力：

- Deserializer 提供的方法。
- Visitor 提供的方法。
- MapAccess、SeqAccess 等辅助 trait 提供的方法。

### `serde` Deserializer

`de\mod.rs trait` 反序列化器，用于将某种格式数据转换为数据结构。

**SerdeLib** 提供了针对各类数据格式的实现。

一般地，该结构内应包含 Reader 作为输入来源，其提供从文本中提取内容的能力。

- deserialize_bool()

```rust
fn deserialize_bool<V>(self, visitor: V) -> Result<V::Value, Self::Error>
where
    V: Visitor<'de>;
```

- deserialize_i32()
- deserialize_seq()
- deserialize_struct()
- ...

作为 **User**，一般无需直接与 Deserializer 交互，而是通过调用 `serde_json::from_str(&str)` 等函数间接使用它提供的服务。
作为 **SerdeLib**，实现 Deserializer 时应该了解 **序列化框架** 所约定的调用时机、参数含义。

### `serde` Visitor

`de\mod.rs trait` 访问者，用于指导 Deserializer 如何将数据格式内容转换为数据结构。

- visit_bool()

```rust
fn visit_bool<E>(self, v: bool) -> Result<Self::Value, E>
where
    E: Error,
{
    Err(Error::invalid_type(Unexpected::Bool(v), &self))
}
```

- visit_i32()
- visit_seq()
- visit_map()
- ...

## Terms list

[badge-CCBYSA4]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
[CCBYSA4]: https://creativecommons.org/licenses/by-sa/4.0/
