#include "acl_cpp/lib_acl.hpp"
//https://acl-dev.cn/2015/02/10/redis_client/
acl::redis_client_cluster cluster;
acl::string value("自古美女爱英雄");

void xyz(acl::redis_string &cmd_string, acl::redis_key &cmd_key, bool &exitFlag) {
    const char *key = "测试";
    while (!exitFlag) {
        if (!cmd_key.exists(key)) {
            printf("key not exists, insert.\r\n");
            cmd_string.set(key, "自古美女爱英雄");
        }
        else
        {
            acl::string buf;
            cmd_string.get(key, buf);
            printf("get key: %s ok, value: %s.\r\n", key, value.c_str());
            cmd_key.del(key);
        }
    }
}

int main(int argc, char **argv) {
    static bool exitFlag = false;
    cluster.set("10.18.150.158:6490", 0, 10, 120);
    cluster.set_password("default", "fe1743934d1ea8006ce75c0c77c7c5e8");
    acl::redis_string cmd_string;
    acl::redis_key  cmd_key;
    cmd_key.set_cluster(&cluster);
    cmd_string.set_cluster(&cluster);
    xyz(cmd_string, cmd_key, exitFlag);
    return 0;
}