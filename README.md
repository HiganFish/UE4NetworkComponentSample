运行截图
![](https://github.com/HiganFish/UE4NetworkComponentSample/blob/master/IMAGES/run.png)

修改项目中的`LoginManager.cpp`的Ip和Port 编译运行后点击登录

# nc演示服务器
服务器即收到序列化后的数据

```
[root@cat ~]# nc -kl 8700 > data.hex
^C
[root@cat ~]# hexdump data.hex 
0000000 0018 0000 4567 0123 0101 0000 3b00 0000
0000010 3100 3332 3123 3332                    
0000018

// LoginNetworkPackage.cpp中默认的头部数据段
// 调用父类的SerializeHeaderToBuffer即可生成默认的序列化部分

// 包序列化后的总字节数
uint32_t PackageSize_;  0x00 00 00 18
uint32_t player_id_; 0x01 23 45 67
// 包的种类
PackageCode package_code_; 0x01
// 包的序号
uint32_t no_; 0x00 00 00 01
// 校验和
uint32_t checksum; 0x 00 00 00 3b


// LoginNetworkPackage.h 用户自定义body authentication_key_
// std::sting authentication_key_  31 32 33 23 31 32 33  (123#123)
```

# C++服务器
使用了自己的库higan

代码文件 `LoginGateServer.cpp`OnMessage回调函数只会返回接收到的16进制数据 不影响NetworkPackageBase的代码阅读

其余四个代码文件与UE4中代码部分几乎完全相同 仅仅在UE4项目中LoginNetworkPackage.h添加了宏`#define UE4` 启用UE4部分的 诸如uint8_t到uint8的替换宏
```
2020-10-14 00:41:47.074739 [pid: 26394] [INFO ] [TcpServer.cpp:31 - Start] server: LoginGateServer, listen on 0.0.0.0:8700
2020-10-14 00:43:55.404389 [pid: 26394] [INFO ] [TcpServer.cpp:48 - OnNewConnection] a new connection: LoginGateServer-192.168.80.1:9584 create
2020-10-14 00:43:55.404710 [pid: 26394] [INFO ] [LoginGateServer.cpp:31 - OnMessage] LoginGateServer-192.168.80.1:9584 authentication key 123#123
2020-10-14 00:43:55.404737 [pid: 26394] [INFO ] [TcpServer.cpp:83 - RemoveConnectionInLoop] erase a connection LoginGateServer-192.168.80.1:9584

```