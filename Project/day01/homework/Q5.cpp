#include <iostream>
#include <map>
#include <string>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>
using namespace std;
using namespace wfrest;
using namespace protocol;

int main(int argc,char *argv[])
{
    HttpServer server;

    server.GET("/*",[](const HttpReq* req,HttpResp* resp){
        cout<<"-------请求行-------"<<endl;
        cout<<"method: "<<req->get_method()<<endl;
        cout<<"uri: "<<req->get_request_uri()<<endl;
        cout<<"version: "<<req->get_http_version()<<endl;
        cout<<"-------请求头-------"<<endl;
        HttpHeaderCursor cursor(req);
        string name;string value;
        while(cursor.next(name,value)){
            cout<<name<<":"<<value<<endl;
        }
        cout<<"\r\n";
    });

    server.POST("/*",[](const HttpReq* req,HttpResp* resp){
        cout<<"-------请求行-------"<<endl;
        cout<<"method: "<<req->get_method()<<endl;
        cout<<"uri: "<<req->get_request_uri()<<endl;
        cout<<"version: "<<req->get_http_version()<<endl;
        cout<<"-------请求头-------"<<endl;
        HttpHeaderCursor cursor(req);
        string name;string value;
        while(cursor.next(name,value)){
            cout<<name<<":"<<value<<endl;
        }
        cout<<"\r\n";
        cout<<"-------请求体-------"<<endl;
        //================请求体文本=====================
        cout<<"body: "<<req->body()<<endl;

        //================请求体二进制（get_parsed_body）=====================
        // const void* body_data=nullptr;
        // size_t body_len=0;
        // req->get_parsed_body(&body_data,&body_len);
        // if(body_len>0&&body_data!=nullptr){
        //     const unsigned char* byte_ptr=reinterpret_cast<const unsigned char*>(body_data);
        //     size_t print_len=body_len;
        //     for(size_t i=0;i<print_len;++i){
        //         cout<<byte_ptr[i]<<" ";
        //     }
        //     cout<<endl;
        // }else{
        //     cout<<"Body is empty"<<endl;
        // }

        //================请求体二进制（string）=====================
        // string binary_str=req->body();
        // size_t body_len=binary_str.size();

        // for(size_t i=0;i<body_len;++i){
        //     cout<<binary_str[i]<<" ";
        // }
        // cout<<endl;
    });


    if(server.start(8888)==0){
        getchar();
        server.stop();
    }else{
        cerr<<"ERROR:Server start failed"<<endl;
        exit(1);
    }
    
    return 0;
}

