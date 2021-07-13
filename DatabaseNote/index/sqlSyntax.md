# SQL 语法手册

用到的词汇或符号：

| 符号                      | 含义                |
| ------------------------- | ------------------- |
| `< 必选 >`                | 必选                |
| `[ 可选 ]`                | 可选                |
| `{ 可出现 0 次或者多次 }` | 可出现 0 次或者多次 |

## 数据定义

### <a id="CreateDatabase">定义数据库</a>

```SQL
CREATE DATABASE <数据库名>;
```

新建名为 `<数据库名>` 的数据库。

---

### <a id="UseDatabase">使用数据库</a>

```SQL
USE <数据库名>;
```

选择 `<数据库名>` 作为当前操作的数据库。  
一旦选定，若不对操作的数据库对象加以限定，则其后命令均是针对当前数据库中的表或视图进行的。

---

### <a id="AlterDatabase">修改数据库</a>

```SQL
ALTER DATABASE <数据库名>;
```

对指定的数据库的数据文件和日志文件等进行修改。

```SQL
ALTER DATABASE test_db
{
    DEFAULT CHARACTER SET gb2312
};
```

---

### <a id="DropDatabase">删除数据库</a>

```SQL
DROP DATABASE <数据库名>;
```

删除名为 `<数据库名>` 的数据库。

---

### <a id="CreateTable">定义基本表</a>

```SQL
CREATE TABLE <基本表名>
    (
        <列名> <数据类型> [<列级完整性约束>]
        {，<列名> <数据类型> [<列级完整性约束>] }
        [ ，<表级完整性约束> ]
   );
```

其中列级完整性约束的作用范围仅限于该列，而表级完整性约束的作用范围是整个表。

列级完整性约束：

|    关键字     | 意义                         |
| :-----------: | ---------------------------- |
|  `NOT NULL`   | 限制列取值不能为空。         |
|   `DEFAULT`   | 指定列的默认值。             |
|   `UNIQUE`    | 限制列的取值不能重复。       |
|    `CHECK`    | 限制列的取值范围。           |
| `PRIMARY KEY` | 指定本列为主码。             |
| `FOREIGN KEY` | 指定本列为引用其他表的外码。 |

`FOREIGN KEY` 格式为：

```SQL
[ FOREIGN KEY (<外码列名>)] REFERENCE <外表名>(<外表列名>);
```

---

### <a id="AlterTable">修改基本表</a>

```SQL
ALTER TABLE <基本表名>;
```

选择并准备修改名为 `<基本表名>` 的基本表。

允许对基本表进行如下操作：

```SQL
ALTER COLUMN <列名> <新数据类型>[NULL | NOT NULL];-- 修改已有列定义
ADD <列名> <数据类型> [约束];-- 增加新列
DROP COLUMN <列名>;-- 删除列
ADD [CONSTRAINT <约束名>] <约束定义>;-- 添加约束
DROP CONSTRAINT <约束名>;-- 删除约束
```

---

### <a id="DropTable">删除基本表</a>

```SQL
DROP TABLE <基本表名>;
```

删除名为 `<基本表名>` 的基本表。

注意：不能删除系统表和有外码约束所参照的表。

---

### <a id="CreateIndex">建立索引</a>

```SQL
CREATE  [ UNIQUE ] [ CLUSTERED |  NONCLUSTERED ] INDEX <索引名>;
ON <基本表名>(
    <列名> [ ASC | DESC ]
    [ { ,<列名> [ ASC | DESC ] } ]
    );
```

建立名为 `<索引名>` 的索引。

`UNIQUE` 表示创建的是唯一索引。

`CLUSTERED` 用于指定创建聚簇索引， `NONCLUSTERED` 用于指定创建非聚簇索引。默认创建的是非聚簇索引。

复合索引各列之间要用逗号 `,` 分隔，每个列后面还可以用 `ASC` 或 `DESC` 表示按索引值按升序或降序排列。默认排序方式为 `ASC` 。

---

### <a id="DropIndex">删除索引</a>

```SQL
DROP INDEX <基本表名>.<索引名>;
```

删除基本表 `<基本表名>` 下名为 `<索引名>` 的索引。

---

### <a id="CreateView">定义视图</a>

```SQL
CREATE VIEW <视图名> [( <列名> [, <列名> ])]
AS <SELECT 查询语句>;
```

建立名为 `<视图名>` 的视图，其可能有多列，且列名以 `( <列名> [, <列名> ])` 命名。  
数据来源于 `<SELECT 查询语句>`

> ```SQL
> CREATE VIEW v_students_info
> (s_id,s_name,d_id,s_age,s_sex,s_height,s_date)
> AS SELECT id,name,dept_id,age,sex,height,login_date
> FROM tb_students_info;
> ```

---

### <a id="AlterView">修改视图</a>

```SQL
ALTER VIEW <视图名>
[(<列名>[，<列名> ])]
AS
<SELECT 查询语句>;
```

按照新的数据来源或新的选择条件修改名为 `<视图名>` 的视图。

---

### <a id="DropView">删除视图</a>

```SQL
DROP VIEW <视图名>;
```

删除名为 `<视图名>` 的视图。

注意：请优先删除子视图。

---

## 数据查询

### <a id="Select">`SELECT` 选择列</a>

```SQL
SELECT [ * | DISTINCT] <目标列表达式> [AS <别名>] { , <目标列表达式> [AS <别名>] }
FROM <表名或视图名> { , <表名或视图名>  }
[ WHERE <条件表达式> ]-- WHERE 子句，指定查询条件
[ GROUP BY <列名 1 > ]-- GROUP BY 子句，指定分组表达式
[ HAVING <条件表达式> ]-- HAVING 子句，指定分组过滤条件
[ ORDER BY <列名 2 > [ ASC | DESC ]]-- ORDER 子句，指定排序表达式和顺序
```

`*` 关键字等价于 `ALL` 关键字，用于选择所有。  
`DISTINCT` 关键字用于去除重复行。

> 关系表中不允许出现相同的元组，但是投影到指定的某些列上时，可能会出现相同行。  

`<目标列表达式>` 一般为列名，也允许出现计算表达式。  
计算表达式可以使用 `CASE` 语句替换结果。  

```SQL
SELECT 商品编号，商品名称， 
价格等级= 
    CASE 
        WHEN 单价 IS NULL THEN '尚未定价'
        WHEN 单价< 20 THEN '低'
        WHEN 单价>=20 AND 单价<=50 THEN '中'
        WHEN 单价>50 AND 单价<=100 THEN '较高'
        ELSE '高'
    END
FROM SPB
```

---

### <a id="Where">`WHERE` 选择行</a>

```SQL
WHERE <条件表达式>
```

`WHERE` 子句必须紧跟 `FROM` 子句之后。

构成 `WHERE` 子句的条件表达式的运算符也称 **谓词** 。  
谓词包括：

| 查询条件 | 谓词                                       |
| -------- | ------------------------------------------ |
| 比较运算 | `<=` `<` `=` `>=` `>` `<> OR !=` `!<` `!>` |
| 指定范围 | `BETWEEN AND` `NOT BETWEEN AND`            |
| 确定集合 | `IN` `NOT IN`                              |
| 字符匹配 | `LIKE` `NOT LIKE`                          |
| 空值比较 | `IS NULL` `IS NOT NULL`                    |
| 逻辑运算 | `AND` `OR` `NOT`                           |

---

### <a id=""></a>

```SQL

```

