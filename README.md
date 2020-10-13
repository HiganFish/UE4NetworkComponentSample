修改项目中的`LoginManager.cpp`的Ip和Port 编译运行后点击登录

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