/* 
 *   Copyright (C) 2024 dingmos. All rights reserved.
 */

#include "hal/hal.h"
#include <AsyncUDP.h> 
#include <WiFi.h>

#define WL_UDP_PORT 2333


static wl_parm_cb g_wl_cb = NULL;

AsyncUDP udp; 
bool wl_param_inited = false;
void on_udp_packet_cb(AsyncUDPPacket packet) 
{
    char *pd = (char*)(packet.data());
    log_d("udp msg: %s", pd);

    if (g_wl_cb != NULL) {
        g_wl_cb(pd);
    }
    // packet.print("reply data");
}

static int wl_setup_udp(uint16_t port) 
{
    int retry_cnt = 0;
    int max_retry_cnt = 10;
    if (WiFi.status() != WL_CONNECTED) {
        if (HAL::setup_wifi()) {
            log_e("setup WiFi failed.");
            return 1;
        }
    }

    log_i("IP address: %s", WiFi.localIP().toString());


    while (!udp.listen(port) && retry_cnt < max_retry_cnt) {
        Serial.print(".");
        retry_cnt++;
        delay(100);
    }

    if (!udp.listen(port)) {
        printf("Listen port %u timeout.\n", port);
        return -1;
    }

    while (!udp.listen(port)) { }
    udp.onPacket(on_udp_packet_cb); //注册收到数据包事件

    wl_param_inited = true;
    return 0;
}

int HAL::wireless_param_init(wl_parm_cb cb)
{
    int rc = 0;
    rc = wl_setup_udp(WL_UDP_PORT);

    if (!rc) {
        g_wl_cb = cb;
    }

    return rc;
}