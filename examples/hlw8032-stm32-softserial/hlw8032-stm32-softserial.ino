#include "SoftwareSerial.h"
#include "Hlw8032.h"

SoftwareSerial serialPorts[] = {
  SoftwareSerial(PB9, PB8),
  SoftwareSerial(PA0, PA1),
  SoftwareSerial(PA2, PA3),
  SoftwareSerial(PA4, PA5),
  SoftwareSerial(PA6, PA7),
  SoftwareSerial(PB0, PB1),
  SoftwareSerial(PB2, PB3),
  SoftwareSerial(PB4, PB5)
};
Hlw8032 energyMeters[8];

void powerDataCallBack(int magic, float Vrms, float Irms, float P, float CF) {
  // Print each parameter to the serial monitor
  Serial.print("from Index ");
  Serial.print(magic);
  Serial.print("; Vrms: ");
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

  #ifdef TIM4_BASE
Serial.println(" this stm32 have : TIM4");
  #endif
  #ifdef TIM18_BASE
Serial.println(" this stm32 have : TIM18");
  #endif
  #ifdef TIM7_BASE
Serial.println(" this stm32 have : TIM7");
  #endif
  #ifdef TIM6_BASE
Serial.println(" this stm32 have : TIM6");
  #endif
  #ifdef TIM22_BASE
Serial.println(" this stm32 have : TIM22");
  #endif
  #ifdef TIM21_BASE
Serial.println(" this stm32 have : TIM21");
  #endif
  #ifdef TIM17_BASE
Serial.println(" this stm32 have : TIM17");
  #endif
  #ifdef TIM16_BASE
Serial.println(" this stm32 have : TIM16");
  #endif
  #ifdef TIM15_BASE
Serial.println(" this stm32 have : TIM15");
  #endif
  #ifdef TIM14_BASE
Serial.println(" this stm32 have : TIM14");
  #endif
  #ifdef TIM13_BASE
Serial.println(" this stm32 have : TIM13");
  #endif
  #ifdef TIM11_BASE
Serial.println(" this stm32 have : TIM11");
  #endif
  #ifdef TIM10_BASE
Serial.println(" this stm32 have : TIM10");
  #endif
  #ifdef TIM12_BASE
Serial.println(" this stm32 have : TIM12");
  #endif
  #ifdef TIM19_BASE
Serial.println(" this stm32 have : TIM19");
  #endif
  #ifdef TIM9_BASE
Serial.println(" this stm32 have : TIM9");
  #endif
  #ifdef TIM5_BASE
Serial.println(" this stm32 have : TIM5");
  #endif
  #ifdef TIM3_BASE
Serial.println(" this stm32 have : TIM3");
  #endif
  #ifdef TIM2_BASE
Serial.println(" this stm32 have : TIM2");
  #endif
  #ifdef TIM20_BASE
Serial.println(" this stm32 have : TIM20");
  #endif
  #ifdef TIM8_BASE
Serial.println(" this stm32 have : TIM8");
  #endif
  #ifdef TIM1_BASE
Serial.println(" this stm32 have : TIM1");
  #endif

  for (int i = 0; i < 5; i++) {
    serialPorts[i].begin(4800, SERIAL_8E1);
    energyMeters[i].setVF(1.94); // Set the voltage factor for each meter
    energyMeters[i].setMagic(i);
    energyMeters[i].onReceiveCallBack(powerDataCallBack);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    if (serialPorts[i].available() > 0) {
      energyMeters[i].rxProcess(serialPorts[i].read());
    }
  }
}
