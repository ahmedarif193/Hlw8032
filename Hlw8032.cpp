#include "Hlw8032.h"

Hlw8032::Hlw8032() {
  VF = VolR1 / VolR2;
}

void Hlw8032::onReceiveCallBack(PowerDataCallback callback) {
  _callback = callback;
}

void Hlw8032::rxProcess(uint8_t data) {
  static uint8_t buffer[24];
  static int index = 0;
  static bool headerFound = false;
  static byte check = 0;
  // Check for the start of the frame
  if (data == 0x55) {
    headerFound = true;
    buffer[0] = data;  // Store the first header byte
  } else if (data == 0x5A && headerFound) {
    headerFound = false;  // Reset the header flag
    buffer[1] = data;     // Store the second header byte
    index = 2;            // Start storing the data from here
  } else if (index >= 2 && index < 24) {
    buffer[index++] = data;  // Continue storing data
    
    // Check if the frame is complete
    if (index == 24) {
      
      if (check == buffer[23]) { //Checksum(buffer) equivalent
        processFrame(buffer);
      } else {
        // Handle checksum error, if necessary
      }
      index = 0;  // Reset for the next frame
      check = 0;
    }else{
      check += data;//other than the crc itself or the headers should be calculated
    }
  } else {
    // Reset if we don't get the expected header
    headerFound = false;
    index = 0;
  }
}

void Hlw8032::processFrame(uint8_t *frame) {
  // Extract data from the frame
  uint32_t Uk = (frame[2] << 16) | (frame[3] << 8) | frame[4];
  uint32_t Ut = (frame[5] << 16) | (frame[6] << 8) | frame[7];
  uint32_t Ik = (frame[8] << 16) | (frame[9] << 8) | frame[10];
  uint32_t It = (frame[11] << 16) | (frame[12] << 8) | frame[13];
  uint32_t Pk = (frame[14] << 16) | (frame[15] << 8) | frame[16];
  uint32_t Pt = (frame[17] << 16) | (frame[18] << 8) | frame[19];
  uint32_t CF = (frame[20] << 8) | frame[21];
  float Vrms = (Uk / Ut) * VF;
  double Irms = (float)Ik / It / Ri;

  Serial.print("Ik: ");
  Serial.print(Ik);
  Serial.print(" It: ");
  Serial.println(It);
  double P = (double)Pk * AdjustedRv2_Rv1_Tv / (Pt * Ri);

  if (_callback) {
    _callback(Vrms, Irms, P, CF);  // Pass the data to the callback
  }
}