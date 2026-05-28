#include <iostream>
#include <wfrest/HttpServer.h>

using namespace wfrest;

int main() {
    HttpServer server;

    // 注册一个简单的路由
    server.GET("/hello", [](const HttpReq *req, HttpResp *resp) {
        resp->String("Hello, wfrest is working perfectly!\n");
    });

    std::cout << "Server is running on http://localhost:8888/hello" << std::endl;

    // 启动并监听 8888 端口
    if (server.start(8888) == 0) {
        getchar(); // 终端敲回车可以优雅退出
        server.stop();
    } else {
        std::cerr << "Failed to start server!" << std::endl;
    }

    return 0;
}