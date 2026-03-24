#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int arr1[2]={0};
    int arr2[2]={0};

    pipe(arr1);
    pipe(arr2);

    printf("%d %d %d %d\n",arr1[0],arr1[1],arr2[0],arr2[1]);

    return 0;
}

