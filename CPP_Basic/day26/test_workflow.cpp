#include <iostream>
#include <string>
#include <workflow/Workflow.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>

// HTTP 任务的回调函数
void http_callback(WFHttpTask *task) {
    int state = task->get_state();
    int error = task->get_error();
    
    // 检查任务是否成功执行
    if (state != WFT_STATE_SUCCESS) {
        std::cerr << "Task failed! State: " << state << ", Error: " << error << std::endl;
        return;
    }

    protocol::HttpResponse *resp = task->get_resp();
    const void *body_ptr;
    size_t body_len;
    if(resp->get_parsed_body(&body_ptr, &body_len)){
        std::string body((const char *)body_ptr,body_len);
        std::cout << "--- Http Response Body ---" << std::endl;
        std::cout << body.substr(0, 500) << "..." << std::endl; // 只打印前500个字符
        std::cout << "--------------------------" << std::endl;
    }else{
        std::cout << "No parsed body in the response." << std::endl;
    }
}

int main() {
    // 1. 创建一个 HTTP 异步任务，传入 URL、重试次数、重定向次数以及回调函数
    WFHttpTask *task = WFTaskFactory::create_http_task("https://www.baidu.com", 2, 2, http_callback);
    
    std::cout << "Starting HTTP request..." << std::endl;
    
    // 2. 启动任务（非阻塞，立刻返回）。Workflow 会在后台线程池中处理网络 I/O
    task->start();
    
    // 3. 阻塞等待所有后台任务结束再退出进程（否则 main 结束了，后台线程也会被销毁）
    getchar(); 
    return 0;
}