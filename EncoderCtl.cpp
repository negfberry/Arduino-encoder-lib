#include <Arduino.h>
#include "EncoderCtl.h"


EncoderCtl::EncoderCtl(byte pina, byte pinb) {
  _EncoderStr.pinA = pina;
  _EncoderStr.pinB = pinb;
  _EncoderStr.val = 4;
  _EncoderStr.lo = -128 * 4;
  _EncoderStr.hi = 127 * 4;
  _EncoderStr.gray = 0;
  pinMode(pina, INPUT_PULLUP);
  pinMode(pinb, INPUT_PULLUP);
}

void EncoderCtl::update() {
  _EncoderStr.gray <<= 2;
  _EncoderStr.gray |= digitalRead(_EncoderStr.pinA)
                   |  digitalRead(_EncoderStr.pinB) << 1;
  _EncoderStr.gray &= 0x0f;
  switch(_EncoderStr.gray) {
    case 0:
    case 3:
    case 5:
    case 6:
    case 9:
    case 10:
    case 12:
    case 15:
      break;

    case 1:
    case 7:
    case 8:
    case 14:
      _EncoderStr.val++;
      break;

    default:
      _EncoderStr.val--;
      break;
  }

  if(_EncoderStr.roll) {
    if(_EncoderStr.val > _EncoderStr.hi) _EncoderStr.val = _EncoderStr.lo;
    if(_EncoderStr.val < _EncoderStr.lo) _EncoderStr.val = _EncoderStr.hi;
  } else {
    if(_EncoderStr.val > _EncoderStr.hi) _EncoderStr.val = _EncoderStr.hi;
    if(_EncoderStr.val < _EncoderStr.lo) _EncoderStr.val = _EncoderStr.lo;
  }
}
 
void EncoderCtl::set(byte r, int v, int l, int h)
{
  _EncoderStr.val = v * 4;
  _EncoderStr.lo = l * 4;
  _EncoderStr.hi = h * 4 + 3;
  _EncoderStr.roll = r;
}

int EncoderCtl::get() {
  return (_EncoderStr.val / 4);
}

