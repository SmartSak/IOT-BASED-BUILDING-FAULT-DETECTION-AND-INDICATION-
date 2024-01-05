#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define ADC_Pin PA0 //Defining the analogue input port
#define B5 PB5 //relay driver input
#define B6 PB6
#define B7 PB7

#define LCD_PORT PORTC
#define LCD_DDR  DDRC
#define LCD_PIN  PINC
#define RS       PC2
#define EN       PC3

uint8_t customChar[] = { //Enumerated character
	0x00,
	0x1B,
	0x15,
	0x11,
	0x0A,
	0x04,
	0x00,
	0x00
};

void LCD_cmd(unsigned char cmd){
	LCD_PORT=(LCD_PORT & 0x0F)|(cmd & 0xF0);
	LCD_PORT &=~(1<<RS);
	LCD_PORT |=(1<<EN);
	_delay_us(100);
	LCD_PORT &=~(1<<EN);
	_delay_us(100);
	LCD_PORT=(LCD_PORT & 0x0F)|(cmd<<4);
	LCD_PORT |=(1<<EN);
	_delay_us(100);
	LCD_PORT &=~(1<<EN);
}
void LCD_data(unsigned char data){
	LCD_PORT=(LCD_PORT & 0x0F)|(data & 0xF0);
	LCD_PORT |=(1<<RS);
	LCD_PORT |=(1<<EN);
	_delay_us(100);
	LCD_PORT &=~(1<<EN);
	_delay_us(100);
	LCD_PORT=(LCD_PORT & 0x0F)|(data<<4);
	LCD_PORT |=(1<<EN);
	_delay_us(100);
	LCD_PORT &=~(1<<EN);
}
void LCD_init(){
	LCD_DDR=0xFC;
	LCD_PORT &=~(1<<EN);
	_delay_ms(2);
	LCD_cmd(0x33);
	_delay_us(100);
	LCD_cmd(0x32);
	_delay_us(100);
	LCD_cmd(0x28);
	_delay_us(100);
	LCD_cmd(0x0C);
	_delay_us(100);
	LCD_cmd(0x01);
	_delay_ms(2);
	LCD_cmd(0x06);
	_delay_us(100);
	
}
void LCD_gotoXY(unsigned char x, unsigned char y){
	unsigned char firstCharAdr[]={0x80,0xC0,0x94,0xD4};
	LCD_cmd(firstCharAdr[y-1]+x-1);
	_delay_us(100);
}
void LCD_string(char *str){
	unsigned char i=0;
	while(str[i]!=0){
		LCD_data(str[i]);
		i++;
	}
}
void LCD_customChar (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		LCD_cmd(0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)
		{	/* Write 8 byte for generation of 1 character */
			LCD_data(msg[i]);
		}
	}
}


void ADC_init()
{
	ADCSRA |=((1<<ADEN)|(ADPS2)|(1<<ADPS1)); /* ADC Prescaling =64 */ //free running mode
	//ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // Enable ADC also set Prescaler as 128
	ADMUX |=(1<<REFS0); /* Reference voltage on VCC */
}
uint16_t ADC_read(uint8_t channel)
{
	ADMUX=((0xF0 & ADMUX) | channel);//enabling 8bit channel
	ADCSRA |=(1<<ADSC);//start conversion
	while(!(ADCSRA&(1<<ADIF)));//wait for adif conversion complete return
	//ADCSRA|=(1<<ADIF);//clear adif when conversion is complete
	return(ADC);
}


int main(void)//main entry to the program
{	
	DDRA &=~(1<<ADC_Pin);//set PORTA0 as input
	ADC_init();
	int ADC_Value=0 ; // define an integer to save adc read value
	LCD_init();
	LCD_customChar(0,customChar);
	while(1)
	{
		LCD_gotoXY(1,1);
		LCD_string("IOT system");
		_delay_ms(10);
		LCD_gotoXY(1,2);
		LCD_string("Fault Detection");
		_delay_ms(100);
		LCD_cmd(0X01);
		LCD_gotoXY(1,1);LCD_string("RED");
		LCD_gotoXY(6,1);LCD_string("YELLOW");
		LCD_gotoXY(13,1);LCD_string("BLUE");
		_delay_ms(10);
		//LCD_data(0);

		PORTB|=(1<<B7);//Output
		PORTB&=~(1<<B6);
		PORTB&=~(1<<B5);
		_delay_ms(100);

		ADC_Value = ADC_read(ADC_Pin); //save adc read value in integer
		//RED PHASE
		if(ADC_Value>=1000)
		{
			LCD_gotoXY(1,2);
			LCD_string("N0FT");
		}
		else if ((ADC_Value>=890)&&(ADC_Value<=920))
		{
			LCD_gotoXY(1,2);
			LCD_string("2FL");
		}
		else if ((ADC_Value>=870)&&(ADC_Value<=880))
		{
			LCD_gotoXY(1,2);
			LCD_string("4FL");
		}
		else if ((ADC_Value>=800)&&(ADC_Value<=825))
		{
			LCD_gotoXY(1,2);
			LCD_string("6FL");
		}
		else if ((ADC_Value>=670)&&(ADC_Value<=688))
		{
			LCD_gotoXY(1,2);
			LCD_string("8FL");
		}
		_delay_ms(100);
		PORTB&=~(1<<B7);
		PORTB|=(1<<B6);//Output
		PORTB&=~(1<<B5);
		_delay_ms(100);
		
		ADC_Value = ADC_read(ADC_Pin); //save adc read value in integer
		//YELLOW PHASE
		if(ADC_Value>=1000)
		{
			LCD_gotoXY(7,2);
			LCD_string("NOFT");
		}
		else if ((ADC_Value>=890)&&(ADC_Value<=920))
		{
			LCD_gotoXY(7,2);
			LCD_string("2FL");
		}
		else if ((ADC_Value>=870)&&(ADC_Value<=880))
		{
			LCD_gotoXY(7,2);
			LCD_string("4FL");
		}
		else if ((ADC_Value>=800)&&(ADC_Value<=825))
		{
			LCD_gotoXY(7,2);
			LCD_string("6FL");
		}
		else if ((ADC_Value>=670)&&(ADC_Value<=688))
		{
			LCD_gotoXY(7,2);
			LCD_string("6FL");
		}
		_delay_ms(100);
		PORTB&=~(1<<B7);
		PORTB&=~(1<<B6);
		PORTB|=(1<<B5);//Output
		_delay_ms(100);
		
		ADC_Value = ADC_read(ADC_Pin); //save adc read value in integer
		//BLUE PHASE
		if(ADC_Value>=1000)
		{
			LCD_gotoXY(13,2);
			LCD_string("NOFT");
		}
		else if ((ADC_Value>=890)&&(ADC_Value<=920))
		{
			LCD_gotoXY(13,2);
			LCD_string("2FL");
		}
		else if ((ADC_Value>=870)&&(ADC_Value<=880))
		{
			LCD_gotoXY(13,2);
			LCD_string("4FL");
		}
		else if ((ADC_Value>=800)&&(ADC_Value<=825))
		{
			LCD_gotoXY(13,2);
			LCD_string("6FL");
		}
		else if ((ADC_Value>=670)&&(ADC_Value<=688))
		{
			LCD_gotoXY(13,2);
			LCD_string("8FL");
		}
		_delay_ms(100);
		LCD_cmd(0X01);
		_delay_ms(100);

		
	}
	return 0;
}
