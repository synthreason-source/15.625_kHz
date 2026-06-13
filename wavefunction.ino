const int outPin = 9;
const int samples = 100;
uint8_t sineTable[samples];
void setup() {
  cli(); // Disable global interrupts
  
  TCCR1A = 0; // Reset Timer1 control registers
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter
  
  // Set the compare match register for 1 Hz (16MHz / 1024 / 1Hz - 1)
  OCR1A = 15624; 
  
  TCCR1B |= (1 << WGM12); // Turn on CTC (Clear Timer on Compare) mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set the 1024 prescaler
  
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare match interrupt
  
  sei(); // Enable global interrupts
}

ISR(TIMER1_COMPA_vect) {
  // This code executes exactly once every second
}


void loop() {
  static int i = 0;

  analogWrite(outPin, sineTable[i]);

  i = (i + 1) % samples;
  delayMicroseconds(10);
}
