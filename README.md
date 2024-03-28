# ESP32 Communication Check with SHT31 Sensor using I2C

This program is designed to check the communication between an ESP32 microcontroller and the SHT31 temperature and humidity sensor using the I2C protocol. The program performs a single reading from the sensor and then sends a message indicating that the data is no longer being read. Example to read temperature and humidity from sht31 sensor by ESP32. I implemented a simple protocol to read the sensor data with i2c in the main.c header file. This code can be integrated into esp-idf. More information about the sensor [can be found here.](https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf)

Here's a more engaging version of the installation steps for running ESP32 on Visual Studio Code (VSCode) with PlatformIO:

## Installation
To get started with ESP32 development on Visual Studio Code (VSCode) using PlatformIO, follow these steps:

- **Install the PlatformIO Extension:**
  Make sure you have the PlatformIO extension installed in VSCode. You can find and install it from the VSCode Marketplace.
- **Create a New Project:**
  Open VSCode, navigate to the PlatformIO menu, and select "New Project."
Choose the ESP32 board from the list and select the framework you want to use (e.g., Arduino, ESP-IDF).
- **PlatformIO Configuration:**
  - After creating the project, open the platformio.ini file in your project.
  - Ensure that the board, framework, and serial port configurations are correctly set for your ESP32.
- **Write Your Code:**
  Start writing your ESP32 program in the src/main.cpp file or any other file you create as needed.
- **Compile and Upload:**
  Use the PlatformIO menu or keyboard shortcut for compilation (Ctrl+Alt+B) and uploading the program to your ESP32 (Ctrl+Alt+U).
- **Monitor Serial Output:**
Once the upload is complete, open the serial monitor to view the output from your ESP32.
Use the PlatformIO menu or keyboard shortcut (Ctrl+Alt+M) to open the serial monitor.

By following these steps, you can easily run your ESP32 program on VSCode using PlatformIO. If you encounter any issues or need further assistance, feel free to ask!

### Usage
- Connect the ESP32 microcontroller to the SHT31 sensor using I2C.
- Upload the program to the ESP32 using PlatformIO.
- Open the serial monitor to view the communication status.
- The program will perform a single reading from the sensor and display the temperature and humidity values.
- Once the reading is complete, the program will send a message indicating that the data is no longer being read.

### Contributing
Contributions to this project are welcome. Feel free to fork the repository and submit pull requests.

### License
This project is licensed under the MIT License - see the LICENSE file for details.

### Contact
For any questions or feedback regarding this project. 
Please contact sangapanpanjaitan@gmail.com


**Free Software, Hell Yeah!**
