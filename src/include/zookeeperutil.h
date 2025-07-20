#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

/* 
ZkClient 作为一个ZooKeeper 客户端的封装类，负责：
    启动并连接 ZooKeeper 服务
    创建 ZooKeeper 的节点（znode）
    读取节点数据
*/



// 封装的zk客户端类
class ZkClient
{
public:
    ZkClient();
    ~ZkClient();

    
    void Start(); // zkclient启动 并连接 ZooKeeper 服务器 zkserver

    // 在 zkserver 上根据指定的 path 创建 znode 节点
    void Create(const char *path, // 节点路径，比如 "/service/node1"
                const char *data, // 节点保存的数据
                int datalen,      // 数据长度
                int state=0);     // 节点类型，默认是 0（持久节点），也可指定临时节点等

    
    std::string GetData(const char *path); // 获取指定路径节点的数据内容

private:
    // zk的客户端会话句柄
    zhandle_t *m_zhandle;
};