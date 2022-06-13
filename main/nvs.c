/* Non-Volatile Storage (NVS) Read and Write a Value - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>

#define STRLN 65


void app_main(void)
{
      // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );


    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        printf("nvs_open Done\n");

        // Read
        printf("Reading restart counter from NVS ... ");
        
        // char msg_get[STRLN]="                ";
        // char new_msg[STRLN] = "Blablablabla";
        ts_credentials my_struct;
        strcpy(my_struct.msg_get, "  ");
        strcpy(my_struct.new_msg,"gnagnagna");
        printf("\n-->get MSG_GET = %s\n", my_struct.msg_get);
        printf("\n-->set NEW_MSG = %s\n", my_struct.new_msg);

        //size_t size = sizeof(msg_get);
        size_t size =(size_t)(STRLN); 
        
        err = nvs_get_str(my_handle, "msg", my_struct.msg_get, &size);
        my_struct.msg_get[STREND]=0; // au cas ou
        printf("\nset NEW_MSG = %s\n", my_struct.new_msg); 
        
        printf("\nget MSG_GET = %s\n", my_struct.msg_get);
        printf("\nset NEW_MSG = %s\n", my_struct.new_msg);
        err = nvs_set_str(my_handle, "msg", my_struct.new_msg);
        printf("set NEW_MSG = %s\n", my_struct.new_msg);

        switch (err) {
            case ESP_OK:
               printf("ESP_OK nvs_set_str \n");
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }

        // Write
        //printf("Updating restart msg in NVS ... ");
        //restart_counter++;

       // err = nvs_set_i32(my_handle, "restart_counter", restart_counter);
        //printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

       

        // Commit written value.
        // After setting any values, nvs_commit() must be called to ensure changes are written
        // to flash storage. Implementations may write to storage at other times,
        // but this is not guaranteed.
        //printf("Committing updates in NVS ... ");
        vTaskDelay(100/ portTICK_PERIOD_MS);
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "nvs_commit  Done\n");
        // Close
        vTaskDelay(100/ portTICK_PERIOD_MS);
        nvs_close(my_handle);
    }

    printf("\n");

    // Restart module
    for (int i = 5; i >= 0; i--) {
        printf("Blocking in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    fflush(stdout);
    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //esp_restart();
    }
}
