#include "common.h"
#include <fcntl.h>
#include <wfrest/HttpServer.h>
#include <workflow/WFHttpServer.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;
using namespace std::placeholders;

WFFacilities::WaitGroup waitGroup(1);

void pread_callback(WFFileIOTask* preadTask,HttpResponse* resp,string filename){
    //这里已经读完文件了 干点收尾的活
    //--------------获取参数和返回值----------------
    FileIOArgs* args=preadTask->get_args();
    close(args->fd);
    long bytes=preadTask->get_retval();//实际读取的字节数

    //------------判断任务的状态 处理错误------------
    int state=preadTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, preadTask->get_error())<<endl;
        resp->set_status_code("500");
        resp->append_output_body("<html>500 Server Internal Error.</html>");
        return;
    }

    //-----------将文件内容追加到响应体中------------
    resp->add_header_pair("Content-Disposition",R"(attachment;
        filename=)"+filename);
    resp->append_output_body_nocopy(args->buf,bytes);
}

void process(WFHttpTask* httpTask){
    //----------------解析请求------------------
    HttpRequest* req=httpTask->get_req();
    //下载文件应该通过GET方法 下载的文件在uri中给出
    string uri=req->get_request_uri();
    // <scheme>://<authority><path>?<query>#<fragment>
    // get_request_uri给出的请求行中的路径部分 而非完整url
    // 即 <path>?<query>
    auto pos=uri.find('?');
    string path;
    if(pos!=string::npos){
        path=uri.substr(0,pos);
    }else{
        path=uri;
    }
    //路径映射 映射到服务器的真实路径
    if(path=="/"){
        path+="index.html";//展示服务器首页
    }
    path="resources"+path;
    //从uri中截取出文件名
    string filename=path.substr(path.find_last_of('/')+1);

    //-------------创建pread任务----------------
    //这里需要打开文件 如果打开失败需要通过响应头返回错误信息
    HttpResponse* resp=httpTask->get_resp();
    resp->add_header_pair("Server","Love_Lanlan_Server");
    int fd=open(path.c_str(),O_RDONLY);//以只读方式打开
    if(fd==-1){
        resp->set_status_code("404");
        resp->append_output_body(R"(
            <!DOCTYPE html>
            <html lang="zh-CN">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>404 Not Found - 页面找不到了</title>
                <style>
                    * {
                        margin: 0;
                        padding: 0;
                        box-sizing: border-box;
                        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
                    }

                    body {
                        background: linear-gradient(135deg, #0f172a 0%, #1e293b 100%);
                        height: 100vh;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        overflow: hidden;
                        color: #f8fafc;
                    }

                    /* 背景装饰浮动小球 */
                    .circle {
                        position: absolute;
                        border-radius: 50%;
                        background: linear-gradient(135deg, rgba(99, 102, 241, 0.15) 0%, rgba(168, 85, 247, 0.15) 100%);
                        backdrop-filter: blur(10px);
                        animation: float 8s infinite ease-in-out;
                        z-index: 1;
                    }

                    .circle-1 {
                        width: 300px;
                        height: 300px;
                        top: -10%,;
                        left: -5%;
                        animation-delay: 0s;
                    }

                    .circle-2 {
                        width: 200px;
                        height: 200px;
                        bottom: 5%;
                        right: -2%;
                        animation-delay: -4s;
                    }

                    /* 主体容器 */
                    .container {
                        text-align: center;
                        position: relative;
                        z-index: 10;
                        padding: 2rem;
                        max-width: 500px;
                        width: 90%;
                    }

                    /* 404 数字样式与动画 */
                    .error-code {
                        font-size: 8rem;
                        font-weight: 900;
                        line-height: 1;
                        background: linear-gradient(135deg, #6366f1 0%, #a855f7 100%);
                        -webkit-background-clip: text;
                        -webkit-text-fill-color: transparent;
                        margin-bottom: 1rem;
                        letter-spacing: -2px;
                        animation: pulse 4s infinite ease-in-out;
                    }

                    /* 提示标题 */
                    .error-title {
                        font-size: 1.75rem;
                        font-weight: 700;
                        margin-bottom: 1rem;
                        color: #f1f5f9;
                    }

                    /* 提示描述 */
                    .error-message {
                        font-size: 1rem;
                        color: #94a3b8;
                        margin-bottom: 2.5rem;
                        line-height: 1.6;
                    }

                    /* 按钮样式 */
                    .btn-home {
                        display: inline-block;
                        padding: 0.8rem 2rem;
                        font-size: 1rem;
                        font-weight: 600;
                        color: #ffffff;
                        text-decoration: none;
                        background: linear-gradient(135deg, #6366f1 0%, #a855f7 100%);
                        border-radius: 50px;
                        box-shadow: 0 4px 15px rgba(99, 102, 241, 0.4);
                        transition: all 0.3s ease;
                    }

                    .btn-home:hover {
                        transform: translateY(-3px);
                        box-shadow: 0 6px 20px rgba(99, 102, 241, 0.6);
                        opacity: 0.95;
                    }

                    .btn-home:active {
                        transform: translateY(-1px);
                    }

                    /* 动画效果定义 */
                    @keyframes float {
                        0%, 100% {
                            transform: translateY(0) scale(1);
                        }
                        50% {
                            transform: translateY(-20px) scale(1.05);
                        }
                    }

                    @keyframes pulse {
                        0%, 100% {
                            transform: scale(1);
                        }
                        50% {
                            transform: scale(1.03);
                        }
                    }

                    /* 针对小屏幕的微调 */
                    @media (max-width: 480px) {
                        .error-code {
                            font-size: 6rem;
                        }
                        .error-title {
                            font-size: 1.4rem;
                        }
                    }
                </style>
            </head>
            <body>

                <div class="circle circle-1"></div>
                <div class="circle circle-2"></div>

                <div class="container">
                    <div class="error-code">404</div>
                    <h1 class="error-title">抱歉，页面迷路了</h1>
                    <p class="error-message">
                        你访问的页面可能已经被移除、更名，或者由于输入的网址有误而暂时不可用。
                    </p>
                    <a href="/" class="btn-home">返回首页</a>
                </div>

            </body>
            </html>
        )");
        return;
    }
    //获取文件大小
    struct stat statbuf;
    fstat(fd,&statbuf);
    size_t size=statbuf.st_size;

    char* buf=(char*)malloc(size);
    assert(buf!=NULL&&"buf malloc failed\n");
    httpTask->set_callback([buf](WFHttpTask* httpTask){
        free(buf);
    });
    //创建读文件任务
    WFFileIOTask* preadTask=WFTaskFactory::create_pread_task(
        fd,buf,size,0,bind(pread_callback,_1,resp,filename)
    );

    //-----------将pread任务添加进序列-----------
    series_of(httpTask)->push_back(preadTask);
}


void sig_handler(int signo){
    waitGroup.done();
}

int main(int argc,char *argv[]){
    //通过信号结束进程
    signal(SIGINT,sig_handler);

    WFHttpServer server(process);
    if(server.start(8848)==0){
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"[ERROR]: Server Start Failed."<<endl;
        exit(1);
    }

    return 0;
}
