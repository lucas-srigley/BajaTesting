#include <SPI.h>
#include <SD.h>
const int chipSelect = BUILTIN_SDCARD; // Use Teensy's built-in SD card slot
 
void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);

  // Initialize the SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  Serial.println("SD card initialized successfully.");
}

void loop() {
  // Data to be written to the SD card
  String dataToWrite = "Hello, SD Card from Teensy 3.5!";
  
  // Create a file on the SD card
  File dataFile = SD.open("data.txt", FILE_WRITE);
  
  if (dataFile) {
    // Write data to the file
    dataFile.println(dataToWrite);
    dataFile.close();

    Serial.println("Data written to SD card.");
  } else {
    Serial.println("Error opening file for writing.");
  }

  // Delay for a while
  delay(10000); // Change this delay as needed
}
