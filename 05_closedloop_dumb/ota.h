#ifndef __PICKLE_OTA_H__
#define __PICKLE_OTA_H__

  #include "pickle_wifi.h"
  #include "config.h"
  
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <AsyncElegantOTA.h> // Modified version: https://github.com/Rad-hi/AsyncElegantOTA

  bool OTA_want_to_update(){
    return AsyncElegantOTA.want_to_update();
  }
  
  void OTA_can_update(){
    AsyncElegantOTA.can_update();
  }
  
  AsyncWebServer server(80);
  static void ota_task(void*){
     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "192.168.1.69/update");
    });
      
    // Start the server
    AsyncElegantOTA.begin(&server);
    server.begin();
  
    while(1){
      // If you need to do something when an OTA is requested, you can do it here before letting an OTA happen
      if(OTA_want_to_update()){
        OTA_can_update();
      }
      delay(50); 
    }
  }
  
  void setup_OTA_firmware_update(){
    // Start the OTA task
    xTaskCreatePinnedToCore(ota_task, "ota_tsk", 10240, NULL, 1, NULL, 0);
  }

#endif // __PICKLE_OTA_H__
