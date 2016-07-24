#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "string.h"

//////////////////////////////////////////////////////
// listen messages and write to serial port
/////////////////////////////////////////////////////


// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node" ,"3Node"};

void setup() {
  Serial.begin(57600);
  printf_begin();
  printf("nfr24l01_to_serial");
  
  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
 // radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.openReadingPipe(2,addresses[1]);
  radio.startListening();                 // Start listening
//  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop() {
  if(radio.available()){
       char tmpArray[32];                       // This generally should be the same size as the sending array
       radio.read(&tmpArray,sizeof(tmpArray));  // Read payload + NULL character)
       char *s;
       s = strstr(tmpArray, ";");               // search for string ";" in tmpArray so we know the valid message received
        if (s != NULL) {                    // if successful then s now points at "hassasin"
          //printf("Found string at index = %d\n", s - tmpArray); // index of ";" in buff can be found by pointer subtraction
          Serial.println(tmpArray);             // found so print to serial
          }                                  
        else  {
          // dont print anything
          //printf("String not found\n");  // `strstr` returns NULL if search string not found
          //Serial.println(tmpArray);
        }
  }      
}
