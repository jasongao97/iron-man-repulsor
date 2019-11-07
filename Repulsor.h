#include <Arduino.h>

class Repulsor {
  private:
    byte indicatorLED;
    byte flashLED;
    byte speaker;

    double energy = 0; // 0 ~ 100
    double flashValue = 0; // 0 ~ 255

    void init();
    void refresh();

  public:
    Repulsor(byte indicatorLED, byte flashLED, byte speaker);
    
    void charge();
    void discharge();
    void repulse();
};
