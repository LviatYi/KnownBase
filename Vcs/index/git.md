# Git CheetSheet

一些常用 Git 命令的记录。

- 取消跟踪，但保留本地更改.

`git rm --cached $FILE$`
`git rm --cached -r $DIRECTORY$`

- 本地强制推断为未更新.

`git update-index --no-assume-unchanged $FILE$`
`git ls-files -z $DIRECTORY$ | xargs -0 git update-index --no-assume-unchanged`

- 本地推断未更新的文件.

`git ls-files -v | grep '^h\ '`
