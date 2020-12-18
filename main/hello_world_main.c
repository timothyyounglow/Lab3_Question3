/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

// Function which extracts the last 2 digits of any number
int extractNum(int num){
	int num0 = 0;
	int num1 = 0;
	int num10 = 0;
	num1 = num%10;
	num0 = num/10;
	num10 = num0%10;
	num10 = num10*10;
	int finalNum = num10 + num1;
	return finalNum;
}

// Function which calls the extractNum() function, takes its return value, and finds the remainder when divided by 15
int calcModulus(int num){
	int mod = extractNum(num)%15;
	return mod;
}


void app_main()
{
	
	
	int a = 816298153;
    printf("%d\n", a);

    /* Print chip information */
	
	
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP8266 chip with %d CPU cores, WiFi, ",
            chip_info.cores);

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");


// Value in countdown should always be the last 2 digits stored in variable a modulus 15
    for (int i = calcModulus(a); i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
	
	
}
