#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//////////////////////////////////////////////////////
// listen messages and write to serial port
/////////////////////////////////////////////////////


// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup() {
  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop() {
  
 if ( radio.available()) {   // While there is data ready
        String vastaanotettu;
        String tuloste;
        while (radio.available()) { 
        tuloste == radio.read( &vastaanotettu, sizeof(String) );             // Get the payload
        Serial.print(tuloste);                            // Print revceived
        }      
    }
 else {}
    
}
