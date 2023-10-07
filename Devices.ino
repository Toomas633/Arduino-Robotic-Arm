#include <SoftwareSerial.h>



void setup() {
  Serial.begin(9600);    // Serial monitor
  BTSerial.begin(9600);  // HC-05 Bluetooth module

  Serial.println("Scanning for Bluetooth devices...");
  BTSerial.println("AT+INQ"); // Send inquiry command to HC-05
}

void loop() {
  static int deviceNumber = 1;
  
  if (BTSerial.available()) {
    char c = BTSerial.read();
    if (c == '\n') {
      Serial.println(); // Start a new line for user input
      Serial.print("Enter the number of the device to connect to: ");
      while (!Serial.available()) {
        // Wait for user input
      }
      int selectedDevice = Serial.parseInt();
      Serial.println(selectedDevice);
      
      // Now you can use the selectedDevice variable to connect to the chosen device.
      // For example, you can store the device's address in an array and use it for connection.
      
      // Reset the deviceNumber for the next scan
      deviceNumber = 1;
      
      // Restart the inquiry
      BTSerial.println("AT+INQ");
    } else {
      Serial.print(deviceNumber++);
      Serial.print(": ");
      Serial.write(c);
    }
  }
}
