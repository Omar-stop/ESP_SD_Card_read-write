# ESP_SD_Card_read-write
A simple project demonstrating how to write image files to an SD card using an ESP32, and how to load the images from the SD card to an ST7789 display.

You cannot use the same SC/CC (i.e. chip select) pin for multiple devices that communicate using SPI on the ESP. In this case I meant the SD Card module and the ST7789 display.
The write function is not generalized because each .h file had a different Byte Array name, this can resolved by unifying the Byte Array names.
The "chunkSize" constant in the write function can be modified to increase the write speed.
The "rowsPerChunk" constant can be modified to increase the loading speed of the image from the SD Card to the ST7789 display.

I hope this helps.
