#ifndef __PICKLE_WIFI_H__
#define __PICKLE_WIFI_H__

  #include "config.h"
  #include <WiFi.h>
  
  IPAddress local_IP(OTA_IP);
  IPAddress gateway(192, 168, 103, 0);
  IPAddress subnet(255, 255, 255, 0);
  
  static bool connect_wifi(){
    // Configure the ESP with a static address
    WiFi.config(local_IP, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    return (WiFi.status() == WL_CONNECTED);
  }
  
  static bool is_wifi_connected(){
    return (WiFi.status() == WL_CONNECTED);
  }
  
  static void connect_to_wifi(void*){
    if(!connect_wifi()) while(!is_wifi_connected()){ delay(500); }

    /*
     // If the static IP doesn't work, try uncommenting these lines, and removing the static IP config, and check the inet group you did set (192.168.group.69)
     Serial.begin(115200);
     Serial.println(WiFi.localIP());
    */
    
    // No longer need this task
    vTaskDelete(NULL);
  }
  
  void setup_wifi(){
    xTaskCreatePinnedToCore(connect_to_wifi, "wifi_tsk", 10240, NULL, 3, NULL, 0);
  }

#endif // __PICKLE_WIFI_H__
