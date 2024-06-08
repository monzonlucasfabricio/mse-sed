
#include "main.h"
#include "config.h"
const char *TAG = "MAIN";

/* Variables */
bool capturar = 0;

/*******************************************************************************
 Programa principal
******************************************************************************/
void app_main(void)
{
  /* Inicializaciones */
  char ip[50];
  char msg[10];
  int8_t rssi = 0;
  IO_gpioInit();
  WIFI_init();
  CRONO_delayMs(500);
  MQTT_init();
  MQTT_subscribe("p1/led/toggle");
  MQTT_subscribe("p1/cap");

  while(1){
      /* Loop */
      if (capturar == true)
      {
        rssi = WIFI_getRSSI();
        sprintf(msg,"%d",rssi);
        ESP_LOGI(TAG,"p1/rssi, mensaje %s", msg);
        MQTT_publish("p1/rssi",msg);
      }
      CRONO_delayMs(500);
  }

}
