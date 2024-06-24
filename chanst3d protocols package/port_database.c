// 该文件为端口的测试文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char port[10];
    char device[10];
    int record_value;
    char last_update_time[20];
} PortInfo;

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    PortInfo ports[100]; // 假设有最多100个端口
    int port_count = 0;

    // 读取 .cpt 文件
    file = fopen("port_database.cpt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 跳过标题行
    fgets(line, MAX_LINE_LENGTH, file);

    // 读取文件内容
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL && port_count < 100) {
        sscanf(line, "%[^,],%[^,],%d,%s", ports[port_count].port, ports[port_count].device, &ports[port_count].record_value, ports[port_count].last_update_time);
        port_count++;
    }

    fclose(file);

    // 打印读取的内容
    printf("Port\tDevice\tRecord Value\tLast Update Time\n");
    for (int i = 0; i < port_count; i++) {
        printf("%s\t%s\t%d\t%s\n", ports[i].port, ports[i].device, ports[i].record_value, ports[i].last_update_time);
    }

    // TODO: 根据需要更新端口信息

    return 0;
}
