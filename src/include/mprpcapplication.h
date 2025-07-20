#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// mprpc框架的基础类，负责框架的一些初始化操作


// RPC 框架的主入口类定义
class MprpcApplication
{
public:
    static void Init(int argc, char **argv); 
    static MprpcApplication& GetInstance(); // 获取 MprpcApplication 的唯一实例 (单例模式)
    static MprpcConfig& GetConfig(); //  获取已经初始化好的配置类实例（m_config）

private:
    static MprpcConfig m_config; // 一个静态对象，用于保存整个 RPC 框架的配置状态

    // 构造函数私有化 + 拷贝控制删除
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};