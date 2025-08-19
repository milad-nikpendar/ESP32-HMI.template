/*
   hmi_esp32_functions header V1.0.0
   Created by Milad Nikpendar
*/
#ifndef HMI_ESP32_FUNCTIONS_H
#define HMI_ESP32_FUNCTIONS_H
#include <Arduino.h>

#ifndef DELAY
#define DELAY(a) vTaskDelay((a) / portTICK_PERIOD_MS);
#endif

#ifndef VOID
#define VOID
#endif

#ifndef SETUP
#define SETUP()
#endif

#ifndef LOOP
#define LOOP() for (;;)
#endif

String humanReadableSize(const size_t bytes, int num = 0)
{
  if (bytes < 1024)
    return String((float)bytes, num) + " B";
  else if (bytes < (1024 * 1024))
    return String((float)bytes / 1024.0, num) + " KB";
  else if (bytes < (1024 * 1024 * 1024))
    return String((float)bytes / 1024.0 / 1024.0, num) + " MB";
  else
    return String((float)bytes / 1024.0 / 1024.0 / 1024.0, num) + " GB";
}
void displayFreeHeap2()
{
  Serial.printf("\nHeap size: %d\n", ESP.getHeapSize());
  Serial.printf("Free Heap: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  Serial.printf("Min Free Heap: %d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT));
  Serial.printf("Max Alloc Heap: %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
}
void displayFreeHeap()
{
  Serial.print("[RAM Log] SIZE: \t");
  Serial.print(humanReadableSize(ESP.getHeapSize(), 0));
  Serial.print(" \tRAM: ");
  Serial.print(humanReadableSize(ESP.getFreeHeap(), 0));
  Serial.print(" \tALLOC: ");
  Serial.println(humanReadableSize(ESP.getMaxAllocHeap(), 0));
}
String chipID()
{
  uint32_t chipId = 0;
  for (int i = 0; i < 17; i = i + 8)
  {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  uint8_t baseMac[6];
  // Get MAC address for WiFi station
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  char baseMacChr[18] = {0};
  sprintf(baseMacChr, "%02X%02X%02X", baseMac[3], baseMac[4], baseMac[5]);

  return String(chipId) + String(baseMacChr);
}
void chipInfo()
{
  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: \t");
  Serial.println(chipID());
  Serial.print("SDK: \t");
  Serial.println(ESP.getSdkVersion());
  Serial.print("CPU FREQ: \t");
  Serial.print(getCpuFrequencyMhz());
  Serial.println("MHz");
  Serial.print("APB FREQ: \t");
  Serial.print(getApbFrequency() / 1000000.0, 1);
  Serial.println("MHz");
  Serial.print("FLASH SIZE: \t");
  Serial.println(humanReadableSize(ESP.getFlashChipSize(), 3));
  Serial.print("OTA Size: \t");
  Serial.println(humanReadableSize(ESP.getFreeSketchSpace(), 3));
  Serial.print("Sketch Size: \t");
  Serial.println(humanReadableSize(ESP.getSketchSize(), 3));
  Serial.print("RAM SIZE: \t");
  Serial.println(humanReadableSize(ESP.getHeapSize(), 0));
  Serial.print("FREE RAM: \t");
  Serial.println(humanReadableSize(ESP.getFreeHeap(), 0));
  Serial.print("MAX RAM ALLOC: \t");
  Serial.println(humanReadableSize(ESP.getMaxAllocHeap(), 0));
  Serial.print("FREE PSRAM: \t");
  Serial.println(humanReadableSize(ESP.getFreePsram(), 0));
}

// Function to format size in bytes to human-readable format
const char *formatSize(uint64_t bytes)
{
  static char output[20];
  if (bytes < 1024)
    snprintf(output, sizeof(output), "%llu B", bytes);
  else if (bytes < 1024 * 1024)
    snprintf(output, sizeof(output), "%.1f KB", bytes / 1024.0);
  else if (bytes < 1024 * 1024 * 1024)
    snprintf(output, sizeof(output), "%.1f MB", bytes / (1024.0 * 1024));
  else
    snprintf(output, sizeof(output), "%.1f GB", bytes / (1024.0 * 1024 * 1024));

  return output;
}
#endif // HMI_ESP32_FUNCTIONS_H
