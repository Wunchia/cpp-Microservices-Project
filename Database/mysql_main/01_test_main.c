#include <my_header.h>
#include <mysql/mysql.h>

/*Usage: */
int main(int argc, char *argv[])
{
    // 数据库初始化
    MYSQL *pconn = mysql_init(NULL);
    if (pconn == NULL)
    {
        printf("初始化失败：%s\n", mysql_error(pconn));
        return -1;
    }

    // 建立连接
    if (NULL == mysql_real_connect(pconn, "localhost", "root", "123456", "test_main", 0, NULL, 0))
    {
        printf("连接失败：%s\n", mysql_error(pconn));
        return -1;
    }

    char *temp[10] = {"张三", "李四", "王五", "赵六", "吴氏",
                      "哩哩", "空灵", "安妮", "景天", "花生"};
    // 对数据库表中的数据进行增删改查
    for (int idx = 1; idx <= 10; ++idx)
    {
        char arr[100]={0};
        //字符串要用单引号 具体的数据库可能也能用双引号 sql标准要求单引号
        sprintf(arr,"insert into person values (%d,'%s',%d)",
                idx,temp[idx-1],idx+10);
        int ret = mysql_query(pconn,arr);
        if (ret != 0)
        {
            printf("查询失败：%s\n", mysql_error(pconn));
            return -1;
        }
    }

    //对数据库表中的数据进行增删改查
    int ret=mysql_query(pconn,"select * from person");
    if(ret!=0){
        printf("查询失败：%s\n",mysql_error(pconn));
        return -1;
    }

    // 获取查询的结果
    MYSQL_RES *pres = mysql_store_result(pconn);
    if (pres == NULL)
    {
        printf("查询结果失败：%s\n", mysql_error(pconn));
        return -1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(pres)))
    { // 得到行
        // 得到列数，遍历每一行的列
        for (int idx = 0; idx < mysql_num_fields(pres); ++idx)
        {
            // 对于每一行而言，打印这一行的每一列
            printf("%s \t", row[idx]);
        }
        printf("\n");
    }

    // 两个资源的释放
    mysql_free_result(pres);
    mysql_close(pconn);

    return 0;
}
