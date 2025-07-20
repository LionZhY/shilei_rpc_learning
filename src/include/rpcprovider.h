#pragma once
#include "google/protobuf/service.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include <functional>
#include <google/protobuf/descriptor.h>
#include <unordered_map>



// 框架提供的专门发布rpc服务的网络对象类
class RpcProvider
{
/* 
    RpcProvider 负责：
        注册（发布）服务对象（即实现了 Protobuf Service 接口的业务服务）
        启动网络服务，监听客户端请求
        接收并解析请求，调用对应的服务方法
        序列化响应并发送给客户端
*/


public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口

    // 注册并发布一个RPC服务对象 (外部调用此函数，将自己实现的业务服务注册进框架)
    void NotifyService(google::protobuf::Service *service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();

    
private:
    // 组合EventLoop  
    muduo::net::EventLoop m_eventLoop; // Muduo事件循环对象，负责IO多路复用和事件分发

    // service服务类型信息 保存某个服务实例及其所有可调用方法的信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap; // 保存服务方法
    };


    // 存储所有注册成功的服务对象，和其服务方法的信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);

    // 已建立连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);

    // Closure的回调操作，发送 RPC 响应，序列化 protobuf 消息并通过网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message*);
    
};