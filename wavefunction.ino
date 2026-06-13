const int outPin = 9;
const int samples = 100;
uint8_t sineTable[samples];
void setup() {
  // Set pin 9 as an output
  pinMode(outPin, OUTPUT);
  
  // Configure Timer 1 for CTC Mode
  TCCR1A = 0; 
  TCCR1B = 0;
  
  // Set Compare Match value
  OCR1A = 1; // 512 / 256 prescaler - 1
  
  // Turn on CTC mode (WGM12 bit)
  bitSet(TCCR1B, WGM12);
  
  // Set prescaler to 256 and start the timer
  bitSet(TCCR1B, CS12); 
  
  // Enable Timer 1 Output Compare A Match Interrupt
  bitSet(TIMSK1, OCIE1A);
}
void loop() {
  static int i = 0;

  analogWrite(outPin, sineTable[i]);

  i = (i + 1) % samples;
  delayMicroseconds(10);
}

// Interrupt Service Routine that toggles Pin 9
ISR(TIMER1_COMPA_vect) {
  static bool pinState = false;
  pinState = !pinState;
  digitalWrite(9, pinState);
}
