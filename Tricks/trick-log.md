# 奇技淫巧

## Zerotier 自建服务器

环境：

- 公网 云服务器

步骤：

首先进行云服务器搭建。

1. 云服务器：
   - `curl -s https://install.zerotier.com | sudo bash`
   - 防火墙 9993(udp) 端口打开
   - `cd /var/lib/zerotier-one`
   - `zerotier-idtool initmoon indentity.public >>moon.json`
   - 编辑 **moon.json** 编辑 `roots.stableEndpoints` 加入 `云服务器ip/9993端口`
     - `"stableEndpoints": ["50.0.0.1"/9993]`
   - `zerotier-idtool genmoon moon.json`
     - 输出一个 0 开头的 moon 文件
     - 如 `wrote 000000d771b8d817.moon`
   - `mkdir /var/lib/zerotier-one/moons.d`
   - `cp 000000d771b8d817.moon ./moons.d/`
   - `systemctl restart zerotier-one`

其次终端加入云服务器。

- `zerotier-cli orbit d771b8d817 d771b8d817`
- 将 moons.d 复制到：
  - Linux `/var/lib/zerotier-one/moons.d/`
  - Windows `C:\ProgramData\ZeroTier\One\moons.d\`
  - MacOS `/Library/Application Support/ZeroTier/One/zerotier-one/moons.d/`

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

1. MT 管理器 添加导出的系统级证书至 `/system/etc/security/cacerts` 。
1. TrustMeAlready 启用模块，并在 小翼管家 中启用。
1. 使用 HttpCanary 开始抓包。
1. 在 小翼管家 中对网关进行任意操作。
1. 抓取发向 https 链接中带有 `device/api?token=` 的数据包，长按后点击 编辑重发。
1. 编辑 body，使用如下内容：

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

1. 在 response 中得到 Params 结点中的首个元素即密码。
