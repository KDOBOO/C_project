#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>
void init_adc();
unsigned short read_adc();
void show_7seg();
void random1();
#define F_CPU 16000000UL
#define OVERFLOW 256
#define __DELAY_BACKWARD_COMPATIBLE__
#define TICKS_PER_SEC 1000
unsigned char num[10] = { 
0x3F, 0x06, 0x5B, 0x4F, 0x66};;
unsigned long sum;

void init_adc()
{
DDRF &= 0xFE;
ADMUX = 0x40;
ADCSR = 0x87;
}

unsigned short read_adc()
{
unsigned char adc_low, adc_high;
unsigned short value;
ADCSR |= 0x40;
while ((ADCSR & 0x10) != 0x10)
;
adc_low = ADCL;
adc_high = ADCH;
value = ((unsigned short)adc_high << 8) | (unsigned short)adc_low;
return value;
}

void show_7seg()
{
int i =0;
for(i=0;i<10;i++)
{
PORTC = num[sum];
PORTG = 0x08;
PORTC = num[sum];
PORTG = 0x04;
PORTC = num[sum];
PORTG = 0x02;
PORTC = num[sum];
PORTG = 0x01;
}
}


int main()
{
DDRG = 0xFF;
DDRC = 0xFF;
TCNT0 = OVERFLOW - 125;
TIMSK = 0x01;
sei();
TCCR0 = 0x05;
init_adc();
srand(read_adc());
while(1)
{

sum = rand();
show_7seg();
}
return(1);
}


///
#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>

void init_adc();
#define __DELAY_BACKWARD_COMPATIBLE__

unsigned short read_adc();
void show_7seg();
void random1();
#define F_CPU 16000000UL
#define OVERFLOW 256

#define TICKS_PER_SEC 1000
unsigned char num[10] = { 
0x3F, 0x06, 0x5B, 0x4F, 0x66};;
unsigned long sum;

void adc_init(void)
{
    adc->admux = AREF_1_1V | ADC8;
    adc->adcsr_a = ADEN | DIV_8;
}
 
uint16_t adc_read(void)
{
    adc->adcsr_a |= ADSC;
    while (adc->adcsr_a & ADSC);
    return adc->adc;
}
 


int main()
{
DDRG = 0xFF;
DDRC = 0xFF;
TCNT0 = OVERFLOW - 125;
TIMSK = 0x01;
sei();
TCCR0 = 0x05;
init_adc();
srand(read_adc());
PORTG = 0x01;
while(1)
{

sum= rand()%5;
PORTC = num[sum];
}
return(1);
}


//

#include <avr/io.h>
#include<stdlib.h>
void init_adc();
unsigned short read_adc();
void show_7seg(unsigned short value);
unsigned char num[10] = { 
0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F};

int main() {
unsigned short value;
unsigned short sum;
DDRC = 0xFF;
DDRG = 0x0F;
DDRA = 0xFF;
PORTG = 0x01;
init_adc();
while(1) {

srand( value);
sum = rand()%10;
PORTC = num[sum];
}

return 0;
}

void init_adc()
{
DDRF &= 0xFE;
ADMUX = 0x40;
ADCSRA = 0x87;
}
unsigned short read_adc()
{
unsigned char adc_low, adc_high;
unsigned short value;
ADCSRA |= 0x40;
while ((ADCSR & 0x10) != 0x10)
;
adc_low = ADCL;
adc_high = ADCH;
value = ((unsigned short)adc_high << 8) | (unsigned short)adc_low;
return value;
}

//
#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include<util/delay.h>

//
unsigned char num[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};
//
int main(){
  int i,n,z;
  DDRA=0xFF; DDRC=0xFF; PORTG=0x03; DDRG=0x0F;
  ADMUX=0x40; ADCSRA=0xE1;
  _delay_us(30);
  i=ADC; // i=ADCW; 컴파일러 버전에 따라서 오류가 발생하면 ADC, ADCW를 변경해서 사용
  srand(i);
  n=rand()%10;
  z=rand()%10;
   while(1){
   
  PORTC=num[n%10];
  _delay_us(30);
  PORTC=num[z%10];
  _delay_us(30);
  
  
  };
 
  return 0;
}





