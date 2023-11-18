
typedef void (*PowerDataCallback)(float Vrms, float Irms, float P, float CF);

const float Rv2_Rv1_Tv = 511E-3;  // Voltage constant
const float Ri = 20;              // Current constant

// Calculated Vrms from your output
float CalculatedVrms = 62.04;

// Real Vrms from measurement
float RealVrms = 234.4;

// Calculate adjustment factor for voltage
float AdjustmentFactorV = RealVrms / CalculatedVrms;

// Adjusted voltage constant
float AdjustedRv2_Rv1_Tv = Rv2_Rv1_Tv * AdjustmentFactorV;

class Hlw8032 {
public:
  // Constructor
  Hlw8032();
  void setVF(float data){
    VF=data;
  }
  void setCF(float data){
    CurrentRF=data;
  }
  // Method to set the callback function
  void onReceiveCallBack(PowerDataCallback callback);

  // Method to process received data
  void rxProcess(uint8_t data);

  // Other methods can be added here for additional functionality

private:
  bool Checksum(uint8_t *frame) {
    
    byte check = 0;
    for (byte a = 2; a <= 22; a++) {
      check += frame[a];
    }
    return check == frame[23];
  }
  float VF;

  uint32_t VolR1 = 1880000;  //Voltage divider Upstream resistors 470K*4  1880K
  uint32_t VolR2 = 1000;     //Voltage divider downstream resistors  1K
  float CurrentRF = 0.1;
  PowerDataCallback _callback;
  void processFrame(uint8_t *frame);
};
