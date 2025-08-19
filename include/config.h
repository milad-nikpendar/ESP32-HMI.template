#ifndef HW_CONFIG_H
#define HW_CONFIG_H

// #include the libraries you want to use

// #define the Components gpio pin
// HMI V2.0.0

//*******************
//*** SD SPI Mode ***
#define SD_MISO   16
#define SD_MOSI   17
#define SD_SCK    18
#define SD_CS     13
#define SD_CD     39

//********************
//*** SD SDIO Mode ***
//#define SD_DATA0   2
//#define SD_DATA1   4
//#define SD_DATA2  12
//#define SD_DATA3  13
//#define SD_CMD    15
//#define SD_SCK    14
//#define SD_CD     39

//*******************
//*** TFT SPI Pin ***
#define TFT_MISO  16
#define TFT_MOSI  17
#define TFT_SCLK  18
#define TFT_CS    21
#define TFT_DC     5
#define TFT_RST   -1
// Copy this lines to User_Setup.h tft_eSPI library

//********************
//*** Optional Pin ***
#define TFT_LED    27
#define BuzzerPin  25
#define WS2812Pin  26

//*******************
//**** Touch Pin ****
#define TCH_IRQ   36
#define TCH_CS    19

//*******************
//******* I2C *******
#define I2C_SDA   23
#define I2C_SCL   22

#endif //HW_CONFIG_H
