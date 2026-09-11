#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

//use the following command to resize your image before generating the byte array
//ffmpeg -i input.jpg -vf "scale=240:240:force_original_aspect_ratio=increase,crop=240:240" output.png


//include your byte array down here (image2cpp was used to create the byte array)
//include only one per sketch because of small storage

//#include "small_pixel_mouse.h" //tft.drawRGBBitmap(0, 0, epd_bitmap_small_pixel_mouse, 240, 240); //draw using this when the .h file is included
//#include "small_pixel_earth.h"
//#include "small_pixel_waves.h"
//#include "small_pixel_rocket.h"
//#include "small_pixel_colorful.h"

#define TFT_SCLK 18
#define TFT_MOSI 23
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 4
#define TFT_BL 27

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define SD_CS 0

const int imgWidth  = 240;
const int imgHeight = 240;
const int bytesPerPixel = 2;                 // RGB565 = 2 bytes/pixel
const int rowBytes = imgWidth * bytesPerPixel; // 480 bytes = one row

const int rowsPerChunk = 8;
const int chunkBytes = rowBytes * rowsPerChunk;
uint8_t chunkBuffer[chunkBytes];

const char* mouseFile = "/Images/Mouse.bin";
const char* earthFile = "/Images/Earth.bin";
const char* waveFile = "/Images/Waves.bin";
const char* rocketFile = "/Images/Rocket.bin";
const char* carpetFile = "/Images/Carpet.bin"; //matches to small_pixel_colorful.h

void setup() {

  Serial.begin(115200);

  //tft display

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  SPI.begin(TFT_SCLK, -1, TFT_MOSI, SD_CS);

  tft.init(240, 240);
  tft.setRotation(3);

  //SD card

  if(!SD.begin(SD_CS)) Serial.print("SD initialization failed!");

  Serial.println("Select image");
  Serial.printf("1.Mouse\n2.Earth\n3.Waves\n4.Rocket\n5.Carpet\n");
  
}

void loop() {
  
  int choice = Serial.parseInt();

  if(choice){

    switch(choice){

      case 1: readFile(mouseFile); break;
      case 2: readFile(earthFile); break;
      case 3: readFile(waveFile); break;
      case 4: readFile(rocketFile); break;
      case 5: readFile(carpetFile); break;

      default: break;

    }

    choice = 0;
    Serial.println("Done!");

  }

}

// void writeFile(const char* path){

//   File f = SD.open(path, FILE_WRITE);

//   if(f){

//     const uint8_t* dataPtr = (const uint8_t*)epd_bitmap_small_pixel_mouse; //Name of your byte array inside the .h file
//     size_t totalBytes = sizeof(epd_bitmap_small_pixel_mouse);

//     const uint32_t chunkSize = 512;
//     uint32_t remaining = totalBytes;
//     const uint8_t* writePtr = dataPtr;

//     while(remaining > 0){

//       uint32_t toWrite = min(remaining, chunkSize);
//       f.write(writePtr, toWrite);
//       writePtr += toWrite;
//       remaining -= toWrite;

//     }

//     //f.flush(); no need here
//     f.close();

//   }

// }

void readFile(const char* path){

  File f = SD.open(path, FILE_READ);

  if(f){

    int y = 0;

    while(y < imgHeight){

      f.read(chunkBuffer, chunkBytes);

      tft.drawRGBBitmap(0, y, (uint16_t*)chunkBuffer, imgWidth, rowsPerChunk);

      y += rowsPerChunk;

    }

    f.close();

  }

}
