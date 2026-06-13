// ┌──────────────────────────────────────────────────────┐
// │                    API Gateway                       │
// │                                                      │
// │  POST /auth/register  ──RPC──→ AuthService.Register  │
// │  POST /auth/login     ──RPC──→ AuthService.Login     │
// │  GET  /user/me        ──RPC──→ AuthService.GetUser   │
// │  GET  /files          ──RPC──→ FileService.ListFiles │
// │                                                      │
// │  POST /files          留在网关，直接处理                │
// │  GET  /file/{id}      留在网关，直接处理                │
// │       ↓                                              │
// │  ./storage/  +  OSS  +  MQ  (全在网关进程内)           │
// └──────────┬───────────────────┬───────────────────────┘
//            │ sRPC              │ sRPC
//            ▼                  ▼
//    ┌──────────────┐   ┌──────────────┐
//    │ Auth Service │   │ File Service │
//    │              │   │              │
//    │ Register     │   │ ListFiles    │
//    │ Login        │   │              │
//    │ GetUserInfo  │   │ 连接:         │
//    │              │   │  MySQL       │
//    │ 连接: MySQL   │   │  tbl_file    │
//    │  tbl_user    │   │              │
//    └──────────────┘   └──────────────┘
