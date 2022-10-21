#line 1 "C:/BIV194/MT/first/MyProject.c"
#line 12 "C:/BIV194/MT/first/MyProject.c"
int type;


void uart_init(void)
{
 UBRR0H = (unsigned char)( (( 10000000 ) / ( 19200  * 16) - 1)  >> 8);
 UBRR0L = (unsigned char) (( 10000000 ) / ( 19200  * 16) - 1) ;
 UCSR0A = 0b00000000;
 UCSR0B = 0b00011000;
 UCSR0C = 0b10000110;
}

void uart_send(unsigned char data_input)
{
 while (!UDRE0_bit)
 ;
 UDR0 = data_input;
}

void uart_send_str(char *string_input)
{
 while (*string_input != '\0')
 {
 uart_send(*string_input);

 string_input++;
 }
}

unsigned char uart_recieve(void) {
 while(!RXC0_bit)
 ;
 return UDR0;
}


char get_char(int number) {
 return number + '0';
}

int get_int(char number) {
 int i = 0;
 while (number != 0x00)
 {
 number = (number >> 1);
 i++;
 }

 return i - 1;
}


void display_uart_pressed_button(void)
{
 while (1)
 {
 char current_input = PINA;
 if (current_input != 0x00)
 {

  uart_send (get_char(get_int(current_input)));
  uart_send ('\0');
 while (PINA != 0x00)
 ;





 }
 }
}

void ogonek() {
 while(1) {
 PORTA = uart_recieve();


 }
}

void main() {
  uart_init ();




 DDRA = 0xFF;
 PORTA = 0x00;


 ogonek();
}
