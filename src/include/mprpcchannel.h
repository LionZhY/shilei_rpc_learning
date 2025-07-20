#pragma once

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>



/* MprpcChannel 是客户端调用逻辑的核心模块，是整个远程调用路径的关键接口。*/


class MprpcChannel : public google::protobuf::RpcChannel //  继承自 RpcChannel（Protobuf 的远程调用通道接口）
{
public:
    // Protobuf 设计的理念是：
    // 客户端调用远程服务时，stub（代理类）会将请求传给 RpcChannel 的 CallMethod()，由其进行实际的发送。
    // 因此：你只要实现 CallMethod()，就能实现完整的 RPC 客户端调用。


    // 所有通过stub代理对象调用的rpc方法，都走到这里了，统一做rpc方法调用的数据数据序列化和网络发送 
    void CallMethod(const google::protobuf::MethodDescriptor* method,   // 调用哪个服务，哪个方法
                          google::protobuf::RpcController* controller,  // 上下文控制器
                          const google::protobuf::Message* request,     // 请求参数
                          google::protobuf::Message* response,          // 请求响应
                          google::protobuf:: Closure* done);            // 回调

    // stub.Login(...) 会把调用转发给 MprpcChannel::CallMethod()
    
};