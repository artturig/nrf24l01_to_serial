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
  printf("nfr24l01_to_serial");
  
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
if(radio.available()){
       char tmpArray[32];                                               // This generally should be the same size as the sending array
       radio.read(&tmpArray,sizeof(tmpArray));  // Reading 19 bytes of payload (18 characters + NULL character)
       Serial.println(tmpArray);                                   // Prints only the received characters because the array is NULL terminated
}
}
/*
 if ( radio.available()) {   // While there is data ready
        String received;
        String output;
        while (radio.available()) { 
        output == radio.read( &received, sizeof(String) );             // Get the payload
        Serial.print(output);                                          // Print output to output
        }      
    }
 else {}
    
}
*/
