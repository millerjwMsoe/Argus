#include <IRremote.h>

#define PIN_IR 3

IRsend irsend;
void setup()
{
  irsend.enableIROut(38);
  irsend.mark(0);
}

void loop() {

}
