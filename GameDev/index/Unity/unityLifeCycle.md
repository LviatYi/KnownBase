# Unity 生命周期

Unity 生命周期现称 **事件函数** 是 Unity 脚本从唤醒到销毁的过程。

![UnityEventFunction](https://docs.unity3d.com/uploads/Main/monobehaviour_flowchart.svg)

Unity 提供保证，将在某些时机调用 MonoBehaviour 子类的事件函数。

Unity 的各个事件函数可能部分包含如下特性：

- 调用者角色
  - **用户回调** 用户可调用的。
  - **内部函数** 由 Unity 内部调用的。
  - **内部多线程函数** 由 Unity 内部多线程调用的。
- 调用方式
  - **仅首次** 仅被调用一次。
  - **仅激活时** 仅当 GameObject 激活时调用。
  - **仅启用时** 仅当组件启用时调用。

## `Awake`

- 用户回调
- 仅首次
- 仅激活时
- 始终在任何 `Start` 函数前调用。

当 GameObject 被 `Instantiated` 或激活时立即调用。

在 Awake 被调用前，所有 GameObject 皆已完成初始化，这意味着 GameObject 及其组件都已经存在，可以使用 `GetComponent<>()` 或 `FindWithTag()` ，但不保证组件内部的成员已完成初始化。

用于初始化脚本，不建议在此函数内访问其他脚本的成员。

```Csharp
MyComponent myComponent;
Float someValue;

void Awake () {
    // Okay
    myComponent = GetComponent<MyComponent>();
    // Not allowed
    myFloat = GetComponent<MyComponent>().someValue;
}
```

## `OnEnable`

- 用户回调
- 仅激活时
- 仅启用时
- 始终在任何 `Start` 函数前调用。

当 GameObject 被激活时立即调用。

## `Reset`

- 用户回调
- 仅首次
- 仅脚本首次附加到对象时。

一般用于首次附加到对象时初始化脚本属性。也可手动调用 `Reset()` 。

## `Start`

- 用户回调
- 仅启用时
- 始终在任何 `Update` 函数前调用。

用于处理依赖，可以调用其他对象中由 `Awake()` 初始化完成的成员。

## `FixedUpdate`

- 用户回调

`FixUpdate()` 按固定频率被调用，通常比 `Update()` 更频繁地调用。

如果帧速率较低，则每帧可以调用多次，如果帧速率较高，则可能根本不会在帧之间调用它。

所有物理计算和 `Update()` 都会在 `FixUpdate()` 后立即进行。在 `FixUpdate()` 中应用移动计算时，不需要将值乘以时间。这是因为 `FixUpdate()` 是在可靠的计时器上调用的，与帧速率无关。

## `Update()`

- 用户回调

每帧调用一次。

不同组件的 `Update()` 执行顺序是非预期的，除非在 **脚本执行顺序面板** 中手动控制调用顺序。

## `LateUpdate()`

- 用户回调
- 始终在任何 `Update` 函数后调用。

每帧调用一次。
用于处理跟随性摄像头。

<!-- ## `OnStateMachineEnter/Exit` -->
