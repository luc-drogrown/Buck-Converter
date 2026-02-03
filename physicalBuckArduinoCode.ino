//This is the arduino script meant to run the physical buck converter project for the Power Electronics class
void init_adc()
{
  //function designed to initialize the ADC registers
  cli();

  TCCR0A = 0x00000010;
  TCCR0B = 0x00000010;
  OCR0A = 19;

  ADMUX = 0x01000000;
  ADCSRA = 0x10101100;
  ADCSRB = 0x00000011;

  sei();
}

void init_pwm()
{
  //function designed to initialize TIMER1 for PWM
  TCCR1A = 0x10100011;
  TCCR1B = 0x00010001;
  ICR1 = 1310;
  OCR1A = 0;
  OCR1B = 0;
}

void readADC_it(uint8_t ch){
    ADMUX &= 0b11100000; //Resetează canalul de conversie
    ADMUX |= ch; //Setează canalul conversiei
    ADCSRA |= (1<<6); //Începe conversia
}

ISR(ADC_vect)
{
  uint8_t adc_l = ADCL;
  uint8_t adc_h = ADCH;
  OCR1A = ((adc_h << 8) | adc_l);
}

void setup() {
  // put your setup code here, to run once:
  DDRC &= ~(1 << 0);
  DDRB |= (1 << 1);

  init_adc();
  init_pwm();

  readADC_it(0);
}

void loop() {
  // put your main code here, to run repeatedly:

}