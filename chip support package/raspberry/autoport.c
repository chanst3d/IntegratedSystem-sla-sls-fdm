#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "port_register.h" // 包含端口信息记录的头文件

#define PORT_COUNT 30 // 假设树莓派有30个GPIO端口

int main() {
    stdio_init_all();

    // 初始化所有GPIO引脚
    for (int pin = 0; pin < PORT_COUNT; ++pin) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN); // 设置为输入模式
    }

    // 获取当前时间并格式化
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // 扫描所有GPIO引脚并记录信息
    for (int pin = 0; pin < PORT_COUNT; ++pin) {
        PortInfo port_info = {"GPIO", "", 0, ""};
        snprintf(port_info.port, sizeof(port_info.port), "GPIO%d", pin);
        port_info.device[0] = '\0'; // 未知的设备类型
        port_info.record_value = gpio_get(pin); // 读取引脚状态
        strftime(port_info.last_update_time, sizeof(port_info.last_update_time), "%Y-%m-%d %H:%M:%S", timeinfo);

        // 调用函数追加新的端口信息到文件
        append_port_info_to_file("port_database.cpt", &port_info);
    }

    return 0;
}
