#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <iostream>
#include <alibabacloud/oss/OssClient.h>

using namespace std;
using namespace AlibabaCloud::OSS;

int main(int argc,char *argv[])
{
    //初始化网络等资源
    InitializeSdk();

    //设置OSS账号信息，创建OssClient对象
    string endpoint="";
    string accessKeyId=getenv("ALIBABA_CLOUD_ACCESS_KEY_ID");
    string accessKeySecret=getenv("ALIBABA_CLOUD_ACCESS_KEY_SECRET");
    string region="cn-wuhan";
    ClientConfiguration conf;
    OssClient client(endpoint,accessKeyId,accessKeySecret,conf);
    client.SetRegion(region);

    //上传文件
    string bucketName="";
    string objectName="dir/demo2.txt";
    auto outcome=client.PutObject(bucketName,objectName,"a.txt");

    //处理错误


    //释放网络等资源
    ShutdownSdk();
    return 0;
}
