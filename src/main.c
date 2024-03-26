#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2c.h"

#define I2C_SCL_IO          26
#define I2C_SDA_IO          27
#define I2C_NUM             I2C_NUM_0
#define I2C_TX_BUF_DISABLE  0
#define I2C_RX_BUF_DISABLE  0
#define I2C_FREQ_HZ         100000      // Req Hz rekomendasi

#define SHT31_SENSOR_ADDR   0x44
#define SHT31_MEASURE_HIGH  0x2130      // perintah pengukuran presisi tinggi
#define SHT31_READ          0xE000      // Membaca hasil pengukuran

static const char *TAG = "SHT31";

 esp_err_t i2c_init()                // esp_err_t ->Menangani err pada ESP-IDF
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_IO,
        .scl_io_num = I2C_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ
    };
    esp_err_t err = i2c_param_config(I2C_NUM, &conf);
    if (err != ESP_OK)
    {
        return err;
    }
    return i2c_driver_install(I2C_NUM, conf.mode, I2C_RX_BUF_DISABLE, I2C_TX_BUF_DISABLE, 0);
}
 esp_err_t sht31_init()
{
    esp_err_t err;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (SHT31_SENSOR_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, (SHT31_MEASURE_HIGH >> 8) & 0xFF, true);
    i2c_master_write_byte(cmd, SHT31_MEASURE_HIGH & 0xFF, true);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(I2C_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return err;
}
 esp_err_t sht3x_read(float *temperature, float *humidity)
{
    uint8_t raw_temp[4];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (SHT31_SENSOR_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, (SHT31_READ >> 8) & 0xFF, true);
    i2c_master_write_byte(cmd, SHT31_READ & 0xFF, true);
    i2c_master_stop(cmd);
    esp_err_t err = i2c_master_cmd_begin(I2C_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    if (err != ESP_OK)
    {
        return err;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (SHT31_SENSOR_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, raw_temp, 4, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(I2C_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    if (err != ESP_OK)
    {
        return err;
    }
    i2c_cmd_link_delete(cmd);
    *temperature = (float)(-45 + (175 * ((raw_temp[0] << 8) | raw_temp[1])) / 65535.0);
    *humidity = (float)(((raw_temp[0] << 8) | raw_temp[1]) * 100.0 / 65535.0);
    return ESP_OK;
}
void app_main()
{
    float temperature, humidity;
    esp_err_t err;
    err = i2c_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Tidak terhubung dengan I2C");
        return;
    }
    while (1)
    {
        err = sht31_init();
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "Tidak terhubung dengan SHT31");
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            continue;
        }

        err = sht3x_read(&temperature, &humidity);
        if (err == ESP_OK)
        {
            ESP_LOGI(TAG, "Temperatur: %.2f°C, Humidity: %.2f%%", temperature, humidity);
        }
        else
        {
            ESP_LOGE(TAG, "Gagal membaca sensor SHT31");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
