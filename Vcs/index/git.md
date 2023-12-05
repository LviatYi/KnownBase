# Git CheatSheet

一些常用 Git 命令的记录。

- 取消跟踪，但保留本地更改.

`git rm --cached $FILE$`  
`git rm --cached -r $DIRECTORY$`

- 本地强制推断为未更新.

`git update-index --no-assume-unchanged $FILE$`  
`git ls-files -z $DIRECTORY$ | xargs -0 git update-index --no-assume-unchanged`

- 本地推断未更新的文件.

`git ls-files -v | grep '^h\ '`

- 重写 git 缓存.

`git rm -r --cached .`  
`git add .`

- 添加远端

添加远端意味着新增一个新的 fetch pull push 地址，并允许通过指定远端名 $REMOTE_NAME$ 来推送到目标远端。

`git remote add $REMOTE_NAME$ $REMOTE_URL$`  
`git pull $REMOTE_NAME$`  
`git push $REMOTE_NAME$`

- 设置远端 url

设置远端 url 允许为远端添加仓库地址，以同时 push 到远端的多个 url 仓库。  
实现 **镜像** 操作，但同一个远端只允许存在一条 fetch-url。

`git remote get-url $REMOTE_NAME$`  
`git remote set-url --add $REMOTE_NAME$ $REMOTE_URL$`  
`git remote set-url --delete $REMOTE_NAME$ $REMOTE_URL$`
