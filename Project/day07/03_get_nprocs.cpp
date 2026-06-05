#include <iostream>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[])
{
    // 方法1：GNU 扩展，获取当前可用的 CPU 核心数
    int nprocs = get_nprocs();
    std::cout << "可用 CPU 核心数 (get_nprocs): " << nprocs << std::endl;

    // 方法2：GNU 扩展，获取系统配置的 CPU 核心数（含离线核心）
    int nprocs_conf = get_nprocs_conf();
    std::cout << "配置 CPU 核心数 (get_nprocs_conf): " << nprocs_conf << std::endl;

    // 方法3：POSIX 接口，获取在线核心数
    long nprocs_online = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs_online != -1) {
        std::cout << "在线 CPU 核心数 (sysconf _SC_NPROCESSORS_ONLN): "
                  << nprocs_online << std::endl;
    }

    // 方法4：POSIX 接口，获取配置总核心数
    long nprocs_configured = sysconf(_SC_NPROCESSORS_CONF);
    if (nprocs_configured != -1) {
        std::cout << "配置 CPU 核心数 (sysconf _SC_NPROCESSORS_CONF): "
                  << nprocs_configured << std::endl;
    }

    return 0;
}
