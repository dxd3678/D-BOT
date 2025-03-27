/**
  *   Copyright (C) 2025 dingmos. All rights reserved.
  * @file    network.cpp
  * @author  dingmos
*/
#include "hal.h"
#include "WiFiManager.h"


WiFiManager wm;

void config_mode_cb(WiFiManager *wifi_manager)
{
    log_i("Entered config mode...");
    log_i("%s", WiFi.softAPIP().toString().c_str());

    log_i("%s", wifi_manager->getConfigPortalSSID().c_str());
}


void save_config_cb()
{
    log_i("配置已保存，准备重启");
    ESP.restart();
}

int HAL::network_init(void)
{
    String macAddress = WiFi.macAddress();
    macAddress.replace(":", "");
    String apName = "DBOT_" + macAddress.substring(macAddress.length() - 6);

    wm.setAPCallback(config_mode_cb);
    wm.setSaveConfigCallback(save_config_cb);
    wm.setConfigPortalTimeout(300);

    if (!wm.autoConnect(apName.c_str())) {
        log_e("配置超时，重启设备");
        ESP.restart();
    }

    log_i("网络连接成功！");
    return 0;
}

std::string HAL::get_wifi_ssid(void)
{
    return std::string(wm.getWiFiSSID().c_str());
}

std::string HAL::get_wifi_passwd(void)
{
    return std::string(wm.getWiFiPass().c_str());
}