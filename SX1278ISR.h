#ifndef SX1278_ISR_H
#define SX1278_ISR_H

#ifndef HeltecLoRaV2
  #define DIO0 25
  #define DIO1 26
  #define DIO2 27
  #define DIO3 32
#else
  #define DIO0 26
  #define DIO1 35
  #define DIO2 34
  #define DIO3 32
#endif

volatile bool detectDIO0Flag=false;
volatile bool detectDIO3Flag=false;
volatile uint8_t ringBuffer[128];
volatile uint8_t bufferMask=128;
volatile uint8_t writePtr=0;
volatile uint8_t readPtr=0;

void IRAM_ATTR dio0ISR() { detectDIO0Flag=true; }

void IRAM_ATTR dio1ISR() {
  if (digitalRead(DIO2)==LOW) { ringBuffer[writePtr]|=bufferMask; }
  bufferMask>>=1; if (bufferMask==0) {
    bufferMask=128; writePtr++; writePtr%=128; ringBuffer[writePtr]=0; } }

void IRAM_ATTR dio3ISR() { detectDIO3Flag=true; }

#endif
