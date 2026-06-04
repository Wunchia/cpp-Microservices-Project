#include "common.h"
#include <openssl/evp.h>

//计算hash
void sha256(const char* data){
    EVP_MD_CTX* ctx=EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    EVP_DigestInit_ex(ctx, EVP_sha256(),NULL);//初始化上下文
    EVP_DigestUpdate(ctx, data, strlen(data));//更新上下文
    EVP_DigestFinal_ex(ctx, hash, &hash_len);//计算哈希值

    printf("SHA-256:");
    for(int i=0;i<hash_len;i++){
        printf("%02x",hash[i]);
    }
    printf("\n");

    //释放上下文
    EVP_MD_CTX_free(ctx);
}

int main(){
    const char* data="Vincio loves lanlan";
    sha256(data);
    return 0;
}
