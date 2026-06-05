#pragma once

#include <string>

// 成功页专用 CSS（绿色调，与 error_pages.h 的蓝紫色调互补）
static const char* CSS_SUCCESS = R"(
    <style>
        * {
            margin: 0; padding: 0;
            box-sizing: border-box;
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
        }
        body {
            background: linear-gradient(135deg, #064e3b 0%, #065f46 100%);
            height: 100vh; display: flex; justify-content: center; align-items: center;
            overflow: hidden; color: #f8fafc;
        }
        .circle {
            position: absolute; border-radius: 50%;
            background: linear-gradient(135deg, rgba(16,185,129,0.15) 0%, rgba(52,211,153,0.15) 100%);
            backdrop-filter: blur(10px);
            animation: float 8s infinite ease-in-out; z-index: 1;
        }
        .circle-1 { width:300px; height:300px; top:-10%; left:-5%; animation-delay:0s; }
        .circle-2 { width:200px; height:200px; bottom:5%; right:-2%; animation-delay:-4s; }
        .container {
            text-align: center; position: relative; z-index: 10;
            padding: 2rem; max-width: 500px; width: 90%;
        }
        .result-icon {
            font-size: 6rem; margin-bottom: 1rem;
            animation: pulse 2s infinite ease-in-out;
        }
        .result-title {
            font-size: 1.75rem; font-weight: 700;
            margin-bottom: 1rem; color: #f1f5f9;
        }
        .result-message {
            font-size: 1rem; color: #a7f3d0;
            margin-bottom: 2.5rem; line-height: 1.6;
        }
        .btn-home {
            display: inline-block; padding: 0.8rem 2rem; font-size: 1rem;
            font-weight: 600; color: #064e3b; text-decoration: none;
            background: linear-gradient(135deg, #34d399 0%, #10b981 100%);
            border-radius: 50px;
            box-shadow: 0 4px 15px rgba(16,185,129,0.4);
            transition: all 0.3s ease;
        }
        .btn-home:hover {
            transform: translateY(-3px);
            box-shadow: 0 6px 20px rgba(16,185,129,0.6);
        }
        .btn-home:active { transform: translateY(-1px); }
        @keyframes float {
            0%,100% { transform: translateY(0) scale(1); }
            50%     { transform: translateY(-20px) scale(1.05); }
        }
        @keyframes pulse {
            0%,100% { transform: scale(1); }
            50%     { transform: scale(1.05); }
        }
        @media (max-width:480px) {
            .result-icon { font-size:4rem; }
            .result-title { font-size:1.4rem; }
        }
    </style>
)";

// 成功页生成函数
static std::string success_page(const std::string& title, const std::string& message) {
    return std::string("<!DOCTYPE html>\n<html lang=\"zh-CN\">\n<head>\n"
           "<meta charset=\"UTF-8\">\n"
           "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
           "<title>") + title + "</title>\n"
           + CSS_SUCCESS + "\n</head>\n<body>\n"
           "  <div class=\"circle circle-1\"></div>\n"
           "  <div class=\"circle circle-2\"></div>\n"
           "  <div class=\"container\">\n"
           "    <div class=\"result-icon\">&#10004;</div>\n"
           "    <h1 class=\"result-title\">" + title + "</h1>\n"
           "    <p class=\"result-message\">" + message + "</p>\n"
           "    <a href=\"/\" class=\"btn-home\">返回首页</a>\n"
           "  </div>\n</body>\n</html>";
}

// 常用成功状态码
#define R_200 success_page("操作成功",     "请求已成功处理。")
#define R_201 success_page("注册成功",     "账号已创建，快去登录吧！")
