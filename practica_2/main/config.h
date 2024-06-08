/** \file config.h
 *  May 2024
 *  Maestría en SIstemas Embebidos - Sistemas embebidos distribuidos
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* versión ESP-IDF */
#define ESPIDF_v4 // comentar esta línea para la versión 5

/* configuración WIFI */
#define ESP_WIFI_SSID "ssid"     // CONFIG_ESP_WIFI_SSID  // "SSID wifi"
#define ESP_WIFI_PASS "pass"     // CONFIG_ESP_WIFI_PASS  // "pass wifi"

/*  Configuracion MQTT  */
#define PORT_MQTT 1883            //CONFIG_PORT_MQTT      // default
#define IP_BROKER_MQTT "192.168.0.87"    //CONFIG_IP_BROKER_MQTT // Broker MQTT
#define USER_MQTT "usuario"                   // Usuario de MQTT
#define PASSWD_MQTT "usuariopassword"         // Contraseña de MQTT

/*  configuración IO */
#define BLINK_GPIO 12  // port 2 para NodeMcu-23S
#define PWM_PORT 25    // puerto de salida de pwm

#define SAMPLES_SIZE 200

#endif
