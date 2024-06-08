
#include "config.h"
#include "main.h"

const char *TAG = "MAIN";
uint8_t grabar = 0;
/*******************************************************************************
 Programa principal
******************************************************************************/
extern volatile int samples[SAMPLES_SIZE];

void app_main(void)
{
  int n = 0;
  /* Inicializaciones */
  IO_adcInit();
  IO_gpioInit();
  IO_pwmInit();
  CRONO_timerInit();

  /* NO USAR ADC2 SI SE VA A USAR EL WIFI */
  WIFI_init();
  MQTT_init();

  MQTT_subscribe("p2/brilloled");
  MQTT_subscribe("p2/ldr_sampling");

/* ===================== FUNCIONA ======================*/
  // CRONO_delayMs(500);
  // CRONO_timerStart(20);
  // ESP_LOGI(TAG, "INICIAR GRABACION" );
  // while(CRONO_GetN() < SAMPLES_SIZE)
  // {
  //   IO_toggleLed();
  //   CRONO_delayMs(500);
  // }
  // ESP_LOGI(TAG, "FINALIZAR GRABACION" );
	// CRONO_timerStop();
  
  // IO_monitorPause("pause\n");

  // ESP_LOGI(TAG, "PLAYBACK INIT" );
  // for (n=0; n < SAMPLES_SIZE; n++)
  // {
  //   IO_pwmSet(samples[n] / 4096.0 * 100);
  //   IO_monitorStem(samples[n]);
  //   CRONO_delayMs(20);
  // }
  // IO_pwmSet(0);
  // ESP_LOGI(TAG, "PLAYBACK FINISH" );
/* ===================== FUNCIONA ======================*/
  n = 0;
  uint8_t grabando = false;

  while(1)
  {
        /* Loop */
    /* ===================== FUNCIONA ======================*/
    //   uint16_t data = IO_readAdc();
    //   IO_monitorStem(data);
    //   IO_toggleLed();
    //   ESP_LOGI(TAG, "%i\n",data);
    //   CRONO_delayMs(500);
    // }
    /* ===================== FUNCIONA ======================*/


    if (grabar == 1)
    {
      ESP_LOGI(TAG, "INICIAR GRABACION" );
      MQTT_publish("p2/ldr_activo","1");
      CRONO_timerStart(100);
      grabar = 0;
      grabando = true;
    }
    else if (grabar == 2)
    {
      ESP_LOGI(TAG, "FINALIZAR GRABACION" );
      MQTT_publish("p2/ldr_activo","0");
      CRONO_timerStop();
      CRONO_SetN(0);
      grabando = false;
      grabar = 0;
    }
    else if (grabar == 0)
    {
      /* IDLE */
    }
    
    if(CRONO_GetN() < SAMPLES_SIZE && grabando == true)
    {
      IO_toggleLed();
    }

    CRONO_delayMs(200);
  }
}
