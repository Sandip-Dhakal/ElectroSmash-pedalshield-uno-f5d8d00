// CC-by-www.Electrosmash.com
// Based on OpenMusicLabs previous works.
// pedalshield_uno_tremolo.ino creates a tremolo effect, modulating the volume with a sinewave.
// pressing the pushbutton_1 or 2 makes the modulation faster or slower.

//this waveform is used to modulate the volume of the output signal.
const byte waveform[]=
{
0x0,0x1,0x1,0x2,0x2,0x2,0x3,0x3,0x4,0x4,0x4,0x5,0x5,0x5,0x6,0x6,0x7,0x7,0x7,0x8,
0x8,0x9,0x9,0x9,0xa,0xa,0xb,0xb,0xb,0xc,0xc,0xd,0xd,0xd,0xe,0xe,0xe,0xf,0xf,0x10,
0x10,0x10,0x11,0x11,0x12,0x12,0x12,0x13,0x13,0x14,0x14,0x14,0x15,0x15,0x16,0x16,0x16,0x17,0x17,0x17,
0x18,0x18,0x19,0x19,0x19,0x1a,0x1a,0x1b,0x1b,0x1b,0x1c,0x1c,0x1d,0x1d,0x1d,0x1e,0x1e,0x1e,0x1f,0x1f,
0x20,0x20,0x20,0x21,0x21,0x22,0x22,0x22,0x23,0x23,0x24,0x24,0x24,0x25,0x25,0x26,0x26,0x26,0x27,0x27,
0x27,0x28,0x28,0x29,0x29,0x29,0x2a,0x2a,0x2b,0x2b,0x2b,0x2c,0x2c,0x2d,0x2d,0x2d,0x2e,0x2e,0x2f,0x2f,
0x2f,0x30,0x30,0x30,0x31,0x31,0x32,0x32,0x32,0x33,0x33,0x34,0x34,0x34,0x35,0x35,0x36,0x36,0x36,0x37,
0x37,0x38,0x38,0x38,0x39,0x39,0x39,0x3a,0x3a,0x3b,0x3b,0x3b,0x3c,0x3c,0x3d,0x3d,0x3d,0x3e,0x3e,0x3f,
0x3f,0x3f,0x40,0x40,0x41,0x41,0x41,0x42,0x42,0x42,0x43,0x43,0x44,0x44,0x44,0x45,0x45,0x46,0x46,0x46,
0x47,0x47,0x48,0x48,0x48,0x49,0x49,0x4a,0x4a,0x4a,0x4b,0x4b,0x4b,0x4c,0x4c,0x4d,0x4d,0x4d,0x4e,0x4e,
0x4f,0x4f,0x4f,0x50,0x50,0x51,0x51,0x51,0x52,0x52,0x53,0x53,0x53,0x54,0x54,0x54,0x55,0x55,0x56,0x56,
0x56,0x57,0x57,0x58,0x58,0x58,0x59,0x59,0x5a,0x5a,0x5a,0x5b,0x5b,0x5b,0x5c,0x5c,0x5d,0x5d,0x5d,0x5e,
0x5e,0x5f,0x5f,0x5f,0x60,0x60,0x61,0x61,0x61,0x62,0x62,0x63,0x63,0x63,0x64,0x64,0x64,0x65,0x65,0x66,
0x66,0x66,0x67,0x67,0x68,0x68,0x68,0x69,0x69,0x6a,0x6a,0x6a,0x6b,0x6b,0x6c,0x6c,0x6c,0x6d,0x6d,0x6d,
0x6e,0x6e,0x6f,0x6f,0x6f,0x70,0x70,0x71,0x71,0x71,0x72,0x72,0x73,0x73,0x73,0x74,0x74,0x75,0x75,0x75,
0x76,0x76,0x76,0x77,0x77,0x78,0x78,0x78,0x79,0x79,0x7a,0x7a,0x7a,0x7b,0x7b,0x7c,0x7c,0x7c,0x7d,0x7d,
0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x80,0x80,0x81,0x81,0x81,0x82,0x82,0x83,0x83,0x83,0x84,0x84,0x85,0x85,
0x85,0x86,0x86,0x87,0x87,0x87,0x88,0x88,0x88,0x89,0x89,0x8a,0x8a,0x8a,0x8b,0x8b,0x8c,0x8c,0x8c,0x8d,
0x8d,0x8e,0x8e,0x8e,0x8f,0x8f,0x8f,0x90,0x90,0x91,0x91,0x91,0x92,0x92,0x93,0x93,0x93,0x94,0x94,0x95,
0x95,0x95,0x96,0x96,0x97,0x97,0x97,0x98,0x98,0x98,0x99,0x99,0x9a,0x9a,0x9a,0x9b,0x9b,0x9c,0x9c,0x9c,
0x9d,0x9d,0x9e,0x9e,0x9e,0x9f,0x9f,0xa0,0xa0,0xa0,0xa1,0xa1,0xa1,0xa2,0xa2,0xa3,0xa3,0xa3,0xa4,0xa4,
0xa5,0xa5,0xa5,0xa6,0xa6,0xa7,0xa7,0xa7,0xa8,0xa8,0xa9,0xa9,0xa9,0xaa,0xaa,0xaa,0xab,0xab,0xac,0xac,
0xac,0xad,0xad,0xae,0xae,0xae,0xaf,0xaf,0xb0,0xb0,0xb0,0xb1,0xb1,0xb2,0xb2,0xb2,0xb3,0xb3,0xb3,0xb4,
0xb4,0xb5,0xb5,0xb5,0xb6,0xb6,0xb7,0xb7,0xb7,0xb8,0xb8,0xb9,0xb9,0xb9,0xba,0xba,0xbb,0xbb,0xbb,0xbc,
0xbc,0xbc,0xbd,0xbd,0xbe,0xbe,0xbe,0xbf,0xbf,0xc0,0xc0,0xc0,0xc1,0xc1,0xc2,0xc2,0xc2,0xc3,0xc3,0xc4,
0xc4,0xc4,0xc5,0xc5,0xc5,0xc6,0xc6,0xc7,0xc7,0xc7,0xc8,0xc8,0xc8,0xc7,0xc7,0xc7,0xc6,0xc6,0xc5,0xc5,
0xc5,0xc4,0xc4,0xc4,0xc3,0xc3,0xc2,0xc2,0xc2,0xc1,0xc1,0xc0,0xc0,0xc0,0xbf,0xbf,0xbe,0xbe,0xbe,0xbd,
0xbd,0xbc,0xbc,0xbc,0xbb,0xbb,0xbb,0xba,0xba,0xb9,0xb9,0xb9,0xb8,0xb8,0xb7,0xb7,0xb7,0xb6,0xb6,0xb5,
0xb5,0xb5,0xb4,0xb4,0xb3,0xb3,0xb3,0xb2,0xb2,0xb2,0xb1,0xb1,0xb0,0xb0,0xb0,0xaf,0xaf,0xae,0xae,0xae,
0xad,0xad,0xac,0xac,0xac,0xab,0xab,0xaa,0xaa,0xaa,0xa9,0xa9,0xa9,0xa8,0xa8,0xa7,0xa7,0xa7,0xa6,0xa6,
0xa5,0xa5,0xa5,0xa4,0xa4,0xa3,0xa3,0xa3,0xa2,0xa2,0xa1,0xa1,0xa1,0xa0,0xa0,0xa0,0x9f,0x9f,0x9e,0x9e,
0x9e,0x9d,0x9d,0x9c,0x9c,0x9c,0x9b,0x9b,0x9a,0x9a,0x9a,0x99,0x99,0x98,0x98,0x98,0x97,0x97,0x97,0x96,
0x96,0x95,0x95,0x95,0x94,0x94,0x93,0x93,0x93,0x92,0x92,0x91,0x91,0x91,0x90,0x90,0x8f,0x8f,0x8f,0x8e,
0x8e,0x8e,0x8d,0x8d,0x8c,0x8c,0x8c,0x8b,0x8b,0x8a,0x8a,0x8a,0x89,0x89,0x88,0x88,0x88,0x87,0x87,0x87,
0x86,0x86,0x85,0x85,0x85,0x84,0x84,0x83,0x83,0x83,0x82,0x82,0x81,0x81,0x81,0x80,0x80,0x7f,0x7f,0x7f,
0x7e,0x7e,0x7e,0x7d,0x7d,0x7c,0x7c,0x7c,0x7b,0x7b,0x7a,0x7a,0x7a,0x79,0x79,0x78,0x78,0x78,0x77,0x77,
0x76,0x76,0x76,0x75,0x75,0x75,0x74,0x74,0x73,0x73,0x73,0x72,0x72,0x71,0x71,0x71,0x70,0x70,0x6f,0x6f,
0x6f,0x6e,0x6e,0x6d,0x6d,0x6d,0x6c,0x6c,0x6c,0x6b,0x6b,0x6a,0x6a,0x6a,0x69,0x69,0x68,0x68,0x68,0x67,
0x67,0x66,0x66,0x66,0x65,0x65,0x64,0x64,0x64,0x63,0x63,0x63,0x62,0x62,0x61,0x61,0x61,0x60,0x60,0x5f,
0x5f,0x5f,0x5e,0x5e,0x5d,0x5d,0x5d,0x5c,0x5c,0x5b,0x5b,0x5b,0x5a,0x5a,0x5a,0x59,0x59,0x58,0x58,0x58,
0x57,0x57,0x56,0x56,0x56,0x55,0x55,0x54,0x54,0x54,0x53,0x53,0x53,0x52,0x52,0x51,0x51,0x51,0x50,0x50,
0x4f,0x4f,0x4f,0x4e,0x4e,0x4d,0x4d,0x4d,0x4c,0x4c,0x4b,0x4b,0x4b,0x4a,0x4a,0x4a,0x49,0x49,0x48,0x48,
0x48,0x47,0x47,0x46,0x46,0x46,0x45,0x45,0x44,0x44,0x44,0x43,0x43,0x42,0x42,0x42,0x41,0x41,0x41,0x40,
0x40,0x3f,0x3f,0x3f,0x3e,0x3e,0x3d,0x3d,0x3d,0x3c,0x3c,0x3b,0x3b,0x3b,0x3a,0x3a,0x39,0x39,0x39,0x38,
0x38,0x38,0x37,0x37,0x36,0x36,0x36,0x35,0x35,0x34,0x34,0x34,0x33,0x33,0x32,0x32,0x32,0x31,0x31,0x30,
0x30,0x30,0x2f,0x2f,0x2f,0x2e,0x2e,0x2d,0x2d,0x2d,0x2c,0x2c,0x2b,0x2b,0x2b,0x2a,0x2a,0x29,0x29,0x29,
0x28,0x28,0x27,0x27,0x27,0x26,0x26,0x26,0x25,0x25,0x24,0x24,0x24,0x23,0x23,0x22,0x22,0x22,0x21,0x21,
0x20,0x20,0x20,0x1f,0x1f,0x1e,0x1e,0x1e,0x1d,0x1d,0x1d,0x1c,0x1c,0x1b,0x1b,0x1b,0x1a,0x1a,0x19,0x19,
0x19,0x18,0x18,0x17,0x17,0x17,0x16,0x16,0x16,0x15,0x15,0x14,0x14,0x14,0x13,0x13,0x12,0x12,0x12,0x11,
0x11,0x10,0x10,0x10,0xf,0xf,0xe,0xe,0xe,0xd,0xd,0xd,0xc,0xc,0xb,0xb,0xb,0xa,0xa,0x9,
0x9,0x9,0x8,0x8,0x7,0x7,0x7,0x6,0x6,0x5,0x5,0x5,0x4,0x4,0x4,0x3,0x3,0x2,0x2,0x2,
0x1,0x1,0x0,0x0,
};

//defining harware resources.
#define LED 13
#define FOOTSWITCH 12
#define TOGGLE 2
#define PUSHBUTTON_1 A5
#define PUSHBUTTON_2 A4

//defining the output PWM parameters
#define PWM_FREQ 0x00FF // pwm frequency - 31.3KHz
#define PWM_MODE 0 // Fast (1) or Phase Correct (0)
#define PWM_QTY 2 // 2 PWMs in parallel

//other variables
int input, speed=1;
int counter=0;
unsigned int ADC_low, ADC_high;
int sample=0;
int divider=0;

void setup() {
  //setup IO
  pinMode(TOGGLE, INPUT_PULLUP);
  pinMode(FOOTSWITCH, INPUT_PULLUP);
  pinMode(PUSHBUTTON_1, INPUT_PULLUP);
  pinMode(PUSHBUTTON_2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  // setup ADC
  ADMUX = 0x60; // left adjust, adc0, internal vcc
  ADCSRA = 0xe5; // turn on adc, ck/32, auto trigger
  ADCSRB = 0x07; // t1 capture for trigger
  DIDR0 = 0x01; // turn off digital inputs for adc0

  // setup PWM
  TCCR1A = (((PWM_QTY - 1) << 5) | 0x80 | (PWM_MODE << 1)); //
  TCCR1B = ((PWM_MODE << 3) | 0x11); // ck/1
  TIMSK1 = 0x20; // interrupt on capture interrupt
  ICR1H = (PWM_FREQ >> 8);
  ICR1L = (PWM_FREQ & 0xff);
  DDRB |= ((PWM_QTY << 1) | 0x02); // turn on outputs
  sei(); // turn on interrupts - not really necessary with arduino
  }

void loop() 
{
  //Turn on the LED if the effect is ON.
  if (digitalRead(FOOTSWITCH)) digitalWrite(LED, HIGH); 
    else  digitalWrite(LED, LOW);
  
  //nothing else here, all happens in the Timer 1 interruption.
}

ISR(TIMER1_CAPT_vect) 
{
  // get ADC data
  ADC_low = ADCL; // you need to fetch the low byte first
  ADC_high = ADCH;

  // the input signal is modulated here using a sinewave
  ADC_low = map(ADC_low, 0,255, 0, waveform[sample]);
  ADC_high = map(ADC_high, 0,255, 0, waveform[sample]);
  
  //construct the input sumple summing the ADC low and high byte.
  input = ((ADC_high << 8) | ADC_low) + 0x8000; // make a signed 16b value
  
  counter++; //to save resources, the pushbuttons are checked every 1000 times.
  if(counter==1000)
{ 

counter=0;
if (!digitalRead(PUSHBUTTON_2)) {
  if (speed<1024)speed=speed+1; //increase the vol
    digitalWrite(LED, LOW); //blinks the led
    }

    if (!digitalRead(PUSHBUTTON_1)) {
  if (speed>0)speed=speed-1; //decrease vol
  digitalWrite(LED, LOW); //blinks the led
    }
}

  // there is a divider to slow the waveform (otherwise is too fast)
  divider++;
  if (divider==4){ divider=0; sample=sample+speed;}
 
 if(sample>1023)sample=0;

  //write the PWM signal
  OCR1AL = ((input + 0x8000) >> 8); // convert to unsigned, send out high byte
  OCR1BL = input; // send out low byte
}
