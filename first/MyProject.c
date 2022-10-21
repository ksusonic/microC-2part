#define KEYPAD_PORT PORTB
#define KEYPAD_DDR DDRB
#define KEYPAD_PIN PINB
#define UART_Init uart_init
#define UART_Write uart_send
#define UART_Recieve uart_recieve
#define UART_Write_Text uart_send_str
#define BAUD 19200
#define F_CPU 10000000
#define BAUDRATE ((F_CPU) / (BAUD * 16) - 1)
#define endl "\r\n"
int type;


void uart_init(void)
{
    UBRR0H = (unsigned char)(BAUDRATE >> 8);
    UBRR0L = (unsigned char)BAUDRATE;
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
//        delay_ms(25);
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
//            PORTB = current_input;
            UART_Write(get_char(get_int(current_input)));
            UART_Write('\0');
            while (PINA != 0x00)
            ;

                
//            DDRA = 0xFF;
//            while (1)
//            ;
        }
    }
}

void ogonek() {
 while(1) {
   PORTA = uart_recieve();
//    while (PINA != 0x00)
//            ;
 }
}

void main() {
    UART_Init();

//    DDRB = 0xFF;  // SETTING PORTB AS OUTPUT
//    PORTB = 0x00; // and DEFAULT OUTPUT 0

    DDRA = 0xFF;  // SETTING PORTA AS output   //INPUT
    PORTA = 0x00; // and DEFAULT INPUT 0

//    display_uart_pressed_button();
      ogonek();
}