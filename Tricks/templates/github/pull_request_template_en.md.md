## BackGround

IdeaC is not only open source, but also commercially free. For Haxe users, this is obviously a sufficient condition to choose IntelliJ.  

However, intellij-haxe does not currently support debugging in IdeaC, with the reason being 

> "IDEA Community Edition currently will not start an IDE-based debugging session. For that, IDEA Ultimate is required." 

But in fact, it is feasible. (At least in my DAP protocol implementation, IdeaC can also start a debugging session).

## Feature

These submissions are designed to provide these features:

- WHAT_THESE_COMMITS_PROVIDE

## Key Changes

- **Delete**:

    in `src\main\resources\META-INF\plugin.xml`

    ```xml
    <depends optional="true" config-file="debugger-support.xml">com.intellij.modules.ultimate</depends>
    ```
  - The `xdebugger` module is not only provided when `com.intellij.modules.ultimate` is enable.

I think this change will help more community users choose Intellij-haxe, because debugging is a very necessary feature for a programming language.

I have currently experimented with this change on my branch, which implements a debugger that complies with the DAP protocol, and found that it is feasible. But I have not conducted any tests on the debugger implementation in the original repository.
