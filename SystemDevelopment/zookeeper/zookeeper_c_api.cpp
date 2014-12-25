#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zookeeper/zookeeper.h>


int main() {
    const char *host = "127.0.0.1:2181";
    zhandle_t *zk_handler = zookeeper_init(host, global_watcher, timeout, 0, "client service", 0);
    if (zk_handler == NULL) {
        printf("error when conneting to server");
        exit(0);
    }
    
}
