# 奇技淫巧

## 获取 电信 天翼网关 超级管理员密码

环境：

- 安卓
- 小翼管家
  - 4.0.0
- HttpCanary
  - 3.3.6
  - 抓包工具
- MT 管理器
  - 添加证书
- Lsposed
- TrustMeAlready
  - xposed 模块。
  - 绕过证书检查。

步骤：

0. MT 管理器 添加导出的系统级证书至 `/system/etc/security/cacerts` 。
1. TrustMeAlready 启用模块，并在 小翼管家 中启用。
2. 使用 HttpCanary 开始抓包。
3. 在 小翼管家 中对网关进行任意操作。
4. 抓取发向 https 链接中带有 `device/api?token=` 的数据包，长按后点击 编辑重发。
5. 编辑 body，使用如下内容：

   ```json
   {
     "Params": [],
     "MethodName": "GetTAPasswd",
     "RPCMethod": "CallMethod",
     "ObjectPath": "/com/ctc/igd1/Telecom/System",
     "InterfaceName": "com.ctc.igd1.SysCmd",
     "ServiceName": "com.ctc.igd1"
   }
   ```

6. 在 response 中得到 Params 结点中的首个元素即密码。
