#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024

// 定义一个结构体来存储端口信息
typedef struct {
    char port[10];
    char device[10];
    int record_value;
    char last_update_time[20];
} PortInfo;

// 函数声明
void append_port_info_to_file(const char *filename, const PortInfo *port_info);

int main() {
    // 示例：创建一个PortInfo实例并填充数据
    PortInfo new_port = {"GPIO8", "Output", 1, ""};

    // 获取当前时间并格式化
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(new_port.last_update_time, sizeof(new_port.last_update_time), "%Y-%m-%d %H:%M:%S", timeinfo);

    // 追加新的端口信息到文件
    append_port_info_to_file("port_database.cpt", &new_port);

    return 0;
}

// 实现函数：追加端口信息到文件
void append_port_info_to_file(const char *filename, const PortInfo *port_info) {
    FILE *file = fopen(filename, "a"); // 以追加模式打开文件
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 将端口信息写入文件
    fprintf(file, "%s,%s,%d,%s\n", port_info->port, port_info->device, port_info->record_value, port_info->last_update_time);

    // 关闭文件
    fclose(file);
}
