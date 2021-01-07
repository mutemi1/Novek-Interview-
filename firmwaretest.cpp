#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <string>

#define uart_buffer_size 1024

char uart_0_buffer[uart_buffer_size];
int buffer_position=0;
char resp[20];
int send_value=0;
int main(void )
{
  sei();
  USART_Init(103);
  

  while(1){

     if(send_value==0){
      uart_0_clear_buffer();
      strcpy (resp,"0");
      uart_0_write("00000101\r\n"); ///turn pin 2 on 
        _delay_ms(1000);
      }
     else if(send_value==1){
      uart_0_clear_buffer();
      strcpy (resp,"0");
      uart_0_write("00001001\r\n"); ///turn pin 4 on
        _delay_ms(1000);
      }
     else if(send_value==2){
      uart_0_clear_buffer();
      strcpy (resp,"0");
      uart_0_write("00001011\r\n"); ///turn pin 5 on
        _delay_ms(1000);
      }
     else if(send_value==3){
      uart_0_clear_buffer();
      strcpy (resp,"0");
      uart_0_write("00000100\r\n"); ///turn pin 2 off
        _delay_ms(1000);
      }
     else if(send_value==4){
      uart_0_clear_buffer();
      strcpy (resp,"0");
      uart_0_write("00001000\r\n"); ///turn pin 2 off
        _delay_ms(1000);
      }
     else if(send_value==5){
       uart_0_clear_buffer();
       strcpy (resp,"0");
      uart_0_write("00001010\r\n"); ///turn pin 2 off
        _delay_ms(1000);
      }
      
      if(send_value>5)
      {
        send_value=0;
        }
      if(strstr(uart_0_buffer,resp)){
      send_value++;
      
      }

     
 }
 
}

void USART_Init( unsigned int ubrr)
{
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /*Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
  /* Set frame format: 8data */
  UCSR0C |=(1<<UCSZ00)|(1<<UCSZ01);


}

void uart_0_print_char(char ch){
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = ch;
}

void uart_0_write(char * byte){
  for (;*byte;++byte)
  {
    uart_0_print_char(*byte);
  }
}

char uart_0_read_char(){
  char chr;
  chr=UDR0;
  return chr;
}

void uart_0_read(){
  uart_0_buffer[buffer_position]= uart_0_read_char();
  buffer_position++;
  if(buffer_position==500)buffer_position=0;
  
}




void uart_0_clear_buffer(void){
  int x;
  for(x=0; x<uart_buffer_size; x++)
  
  {uart_0_buffer[x]=0x00; //initializing the data array to null

  }
  buffer_position=0;
}








