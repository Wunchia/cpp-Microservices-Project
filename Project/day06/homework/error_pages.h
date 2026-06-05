#pragma once

#include <string>
#include <sstream>

// 所有错误页共享的 CSS 样式（从原 R_404 提取，去除特定文案）
static const char* CSS_COMMON = R"(
    <style>
        * {
            margin: 0; padding: 0;
            box-sizing: border-box;
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
        }
        body {
            background: linear-gradient(135deg, #0f172a 0%, #1e293b 100%);
            height: 100vh; display: flex; justify-content: center; align-items: center;
            overflow: hidden; color: #f8fafc;
        }
        .circle {
            position: absolute; border-radius: 50%;
            background: linear-gradient(135deg, rgba(99,102,241,0.15) 0%, rgba(168,85,247,0.15) 100%);
            backdrop-filter: blur(10px);
            animation: float 8s infinite ease-in-out; z-index: 1;
        }
        .circle-1 { width:300px; height:300px; top:-10%; left:-5%; animation-delay:0s; }
        .circle-2 { width:200px; height:200px; bottom:5%; right:-2%; animation-delay:-4s; }
        .container {
            text-align: center; position: relative; z-index: 10;
            padding: 2rem; max-width: 500px; width: 90%;
        }
        .error-code {
            font-size: 8rem; font-weight: 900; line-height: 1;
            background: linear-gradient(135deg, #6366f1 0%, #a855f7 100%);
            -webkit-background-clip: text; -webkit-text-fill-color: transparent;
            margin-bottom: 1rem; letter-spacing: -2px;
            animation: pulse 4s infinite ease-in-out;
        }
        .error-title {
            font-size: 1.75rem; font-weight: 700;
            margin-bottom: 1rem; color: #f1f5f9;
        }
        .error-message {
            font-size: 1rem; color: #94a3b8;
            margin-bottom: 2.5rem; line-height: 1.6;
        }
        .btn-home {
            display: inline-block; padding: 0.8rem 2rem; font-size: 1rem;
            font-weight: 600; color: #fff; text-decoration: none;
            background: linear-gradient(135deg, #6366f1 0%, #a855f7 100%);
            border-radius: 50px;
            box-shadow: 0 4px 15px rgba(99,102,241,0.4);
            transition: all 0.3s ease;
        }
        .btn-home:hover {
            transform: translateY(-3px);
            box-shadow: 0 6px 20px rgba(99,102,241,0.6);
        }
        .btn-home:active { transform: translateY(-1px); }
        @keyframes float {
            0%,100% { transform: translateY(0) scale(1); }
            50%     { transform: translateY(-20px) scale(1.05); }
        }
        @keyframes pulse {
            0%,100% { transform: scale(1); }
            50%     { transform: scale(1.03); }
        }
        @media (max-width:480px) {
            .error-code { font-size:6rem; }
            .error-title { font-size:1.4rem; }
        }
    </style>
)";

// 根据状态码、标题、描述生成统一的错误页 HTML
static std::string error_page(int code, const std::string& title, const std::string& message) {
    return std::string("<!DOCTYPE html>\n<html lang=\"zh-CN\">\n<head>\n"
           "<meta charset=\"UTF-8\">\n"
           "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
           "<title>") + std::to_string(code) + " - " + title + "</title>\n"
           + CSS_COMMON + "\n</head>\n<body>\n"
           "  <div class=\"circle circle-1\"></div>\n"
           "  <div class=\"circle circle-2\"></div>\n"
           "  <div class=\"container\">\n"
           "    <div class=\"error-code\">" + std::to_string(code) + "</div>\n"
           "    <h1 class=\"error-title\">" + title + "</h1>\n"
           "    <p class=\"error-message\">" + message + "</p>\n"
           "    <a href=\"/\" class=\"btn-home\">返回首页</a>\n"
           "  </div>\n</body>\n</html>";
}

// 以下是便捷常量，直接复用 error_page()
#define R_400 error_page(400, "请求参数错误",       "请检查用户名和密码是否填写完整。")
#define R_401 error_page(401, "未授权访问",         "请先登录后再尝试此操作。")
#define R_404 error_page(404, "抱歉，页面迷路了",   "你访问的页面可能已经被移除、更名，或者由于输入的网址有误而暂时不可用。")
#define R_409 error_page(409, "用户名已存在",       "该用户名已被注册，请换一个试试。")
#define R_500 error_page(500, "服务器内部错误",     "服务器开小差了，请稍后再试。")
