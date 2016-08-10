#ifndef EncoderCtl_h
#define EncoderCtl_h
 
#include <Arduino.h>

class EncoderCtl{
  public:
        EncoderCtl(byte, byte);
        void update(void);
        void set(byte, int, int, int);
        int get(void);
  private:
        struct {
          volatile int val;
          volatile int lo;
          volatile int hi;
          volatile byte roll;
          byte gray;
          byte pinA;
          byte pinB;
        } _EncoderStr;
};
 
#endif
