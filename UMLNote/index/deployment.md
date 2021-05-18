# 13. 部署图

部署图描述系统运行时的结构，展示了硬件的配置及其软件如何部署到网络结构中。

## 13.1 部署图元素

### 13.1.1 节点

UML 使用立方体表示一个普通节点。  

```PlantUML
@startuml Disployment

Node node

@enduml
```

实际上，节点可以细分出很多元素。  

```PlantUML
@startuml
actor actor
agent agent
artifact artifact
boundary boundary
card card
cloud cloud
component component
control control
database database
entity entity
file file
folder folder
frame frame
interface  interface
package package
queue queue
stack stack
rectangle rectangle
storage storage
usecase usecase
@enduml
```

允许使用构造型对 node 的类型做补充。  

### 13.1.2 连接

一般用实现连接构件。  
并在直接连接上添加信息。  
