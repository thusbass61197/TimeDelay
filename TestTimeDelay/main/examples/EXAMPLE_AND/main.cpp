/* EXAMPLE_AND/main.cpp - Application main entry point */

/*
 * Copyright (c) 2017 Intel Corporation
 * Additional Copyright (c) 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"

static const char * const TAG = "EXAMPLE_AND";


#define BUTTON_I1 GPIO_NUM_26        // Pin 26.
#define BUTTON_I2 GPIO_NUM_32        // Pin 32.
#define BUTTON_I3 GPIO_NUM_39        // Pin 39.
#define GPIO_Q1 GPIO_NUM_19            // Pin 19.




/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{

	//https://www.xplore-dna.net/mod/page/view.php?id=153

    ESP_LOGI(TAG, "Initializing EXAMPLE_AND ...");

    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_reset_pin(GPIO_Q1);

    gpio_reset_pin(BUTTON_I1);
    gpio_reset_pin(BUTTON_I2);
    gpio_reset_pin(BUTTON_I3);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GPIO_Q1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_I1, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_I2, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_I3, GPIO_MODE_INPUT);

    gpio_set_level(GPIO_Q1, 0); //set to 0 at Reset.





    while (true) // Endlos-Schleife
    {
        // Eingang lesen, das not wird gebraucht weil die Eingaenge bei losgelassenem Taster auf 3.3V sind, und der Taster auf GND schaltet.
        bool I1 = not gpio_get_level(BUTTON_I1);
        bool I2 = not gpio_get_level(BUTTON_I2);
        bool I3 = not gpio_get_level(BUTTON_I3);



        // Ausgaenge setzen
        gpio_set_level(GPIO_Q1, I1 and I2 not I3); //Verwendung des AND aus der IEC IEC 61131; auch in C++ vorhanden, in C nicht not

        // 100ms warten  = Intervallzeit des Tasks
        vTaskDelay(100 / portTICK_PERIOD_MS); // 100ms cycle for Test.
    }
}

