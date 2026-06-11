#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <alibabacloud/oss/model/PutObjectRequest.h>
#include <cstdlib>
#include <iostream>
#include <alibabacloud/oss/OssClient.h>

using namespace std;
using namespace AlibabaCloud::OSS;

int main(int argc,char *argv[])
{
    // 1.初始化网络等资源
    InitializeSdk();

    // 2.设置OSS账号信息，创建OSSClient
    string endpoint="oss-cn-wuhan-lr.aliyuncs.com";
    string accessKeyId=getenv("ALIBABA_CLOUD_ACCESS_KEY_ID");
    string accessKeySecret=getenv("ALIBABA_CLOUD_ACCESS_KEY_SECRET");
    string region="cn-wuhan";
    ClientConfiguration conf;
    OssClient client(endpoint,accessKeyId,accessKeySecret,conf);
    client.SetRegion(region);

    // 3.上传文件
    string bucketName="velo-use-20260611";
    string objectName="dir.demo1.txt";
    string content="Hello AlibabaCloud OSS";
    shared_ptr<iostream>stream=make_shared<stringstream>(move(content));
    PutObjectRequest request(bucketName,objectName,stream);
    auto outcome=client.PutObject(request);

    // 4.错误处理
    if(!outcome.isSuccess()){
        cout<<"PutObject Failed"<<", code:"<<outcome.error().Code()
            <<", message:"<<outcome.error().Message()
            <<", requestId:"<<outcome.error().RequestId()<<endl;
        exit(1);
    }

    // 5.释放网络等资源
    ShutdownSdk();

    return 0;
}
