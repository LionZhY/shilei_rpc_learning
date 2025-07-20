#pragma once
#include <google/protobuf/service.h>
#include <string>


/* RpcController 是用于传递调用状态信息的类，属于客户端和服务端通用接口： */

class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();

    void Reset();                   // 重置控制器状态
    bool Failed() const;            // 判断是否发生错误
    std::string ErrorText() const;  // 获取具体的错误信息
    void SetFailed(const std::string& reason); // 设置错误状态和错误信息，用于通知上层调用失败的原因

    // 目前未实现具体的功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);


private:
    bool m_failed; // RPC方法执行过程中的状态  // 是否调用失败
    std::string m_errText; // RPC方法执行过程中的错误信息
};