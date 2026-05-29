#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <iostream>
#include <string>
#include <map>
#include <functional>

// ==================== 1. 请求类声明 ====================
class HttpReq {
public:
    // 模拟数据，供测试打印
    std::string get_request_uri() const { return "/index.html?id=1&name=vincio"; }
    std::string full_path() const { return "/var/www/html/index.html"; }
    std::string match_path() const { return "/*"; }
    std::string current_path() const { return "."; }
    
    // 返回查询参数列表
    const std::map<std::string, std::string>& query_list() const {
        static std::map<std::string, std::string> mock_query = {
            {"id", "1"},
            {"name", "vincio"}
        };
        return mock_query;
    }
};

// ==================== 2. 响应类声明 ====================
class HttpResp {
    // 留空，后续可以添加 set_status, set_body 等方法
};

// ==================== 3. 服务器类声明 ====================
class HttpServer {
public:
    using Handler = std::function<void(const HttpReq*, HttpResp*)>;

    HttpServer() : is_running_(false) {}
    ~HttpServer() { stop(); }

    // 注册 GET 路由
    void GET(const std::string& path, Handler handler) {
        std::cout << "[Config] 注册路由成功: GET -> " << path << std::endl;
        // 实际开发中，需要把 path 和 handler 存入一个 map 路由表中
        handler_ = handler; 
    }

    // 启动服务器，绑定端口
    int start(int port) {
        std::cout << "[Server] 正在端口 " << port << " 上启动服务器..." << std::endl;
        
        // TODO: 这里编写你的底层网络代码
        // 1. int listen_fd = socket(...);
        // 2. bind(...); listen(...);
        // 3. 创建 epoll 实例，将 listen_fd 注册进去
        // 4. 开启底层线程或事件循环
        
        is_running_ = true;
        std::cout << "[Server] 服务器启动成功！按回车键(Enter)可以停止服务器。" << std::endl;
        
        // 模拟触发一次回调（仅供测试验证你的 main 函数逻辑是否通畅）
        if (handler_) {
            std::cout << "\n--- [测试] 模拟收到一个 HTTP GET 请求 ---" << std::endl;
            HttpReq mock_req;
            HttpResp mock_resp;
            handler_(&mock_req, &mock_resp);
            std::cout << "---------------------------------------\n" << std::endl;
        }

        return 0; // 返回0代表启动成功
    }

    // 停止服务器
    void stop() {
        if (is_running_) {
            std::cout << "[Server] 正在停止服务器并清理资源..." << std::endl;
            // TODO: 关闭 epollfd, 关闭 listen_fd, 销毁线程池等
            is_running_ = false;
            std::cout << "[Server] 服务器已安全关闭。" << std::endl;
        }
    }

private:
    bool is_running_;
    Handler handler_; // 临时存放单路由回调，后续应改为路由表 map<string, Handler>
};

#endif // HTTP_SERVER_H