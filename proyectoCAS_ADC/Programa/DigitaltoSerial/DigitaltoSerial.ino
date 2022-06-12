byte pinArray[] = {9,8,7,6,5,4,3,2}; // 8 random pins, say MSB is the leftmost, i.e. pin 13
byte newBit;
byte dataByte;
byte x;

void setup(){
  for (x=0; x<8; x=x+1){
  pinMode (pinArray[x], INPUT_PULLUP); // pin  high unless pulled low with a switch or something

  }
Serial.begin(115200);
}
void loop(){
dataByte = 0;
  for (x=0; x<8; x=x+1){
  newBit = digitalRead(pinArray[x]); // read a pin
  dataByte = dataByte | (newBit<<x); //shift the bit into position and put in its place in the data byte
  }
Serial.print(dataByte, DEC);
delay (800); // keep from flooding the PC
}
