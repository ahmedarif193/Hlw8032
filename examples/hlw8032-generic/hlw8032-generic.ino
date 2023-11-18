/**
 * @file hlw8032-generic.ino
 * @brief Simple Test for HLW8032 Library
 *
 * Basic example demonstrating the use of the HLW8032 library for power measurement.
 *
 * @author Ahmed ARIF
 * @email arif193@gmail.com
 * @version 1.0
 * @date Nov 18, 2023
 * Copyright (c) 2023 Ahmed ARIF
 * Licensed under LGPL-3.0, see <http://www.gnu.org/licenses/>.
 */
#include "Hlw8032.h"

Hlw8032 energyMeter;

void powerDataCallBack(int magic, float Vrms, float Irms, float P, float CF) {
  (void)magic;
  // Print each parameter to the serial monitor
  Serial.print("Vrms: ");
  Serial.print(Vrms);
  Serial.print(" V, Irms: ");
  Serial.print(Irms);
  Serial.print(" A, Power: ");
  Serial.print(P);
  Serial.print(" W, PF: ");
  Serial.print(CF);
  Serial.println(".");
}

void setup() {
  Serial.begin(250000);
  Serial.println("[HLW8032] Ready! ...");

  //assuming that Serial is connected to UART0 and Serial1 is connected to UART1
  Serial1.begin(4800, SERIAL_8E1);
  energyMeter.setVF(1.94); // Set the voltage factor for each meter
  energyMeter.onReceiveCallBack(powerDataCallBack);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    if (Serial1.available() > 0) {
      energyMeter.rxProcess(Serial1.read());
    }
  }
}
