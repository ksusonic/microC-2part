
_uart_init:

;MyProject.c,15 :: 		void uart_init(void)
;MyProject.c,17 :: 		UBRR0H = (unsigned char)(BAUDRATE >> 8);
	LDI        R27, 0
	STS        UBRR0H+0, R27
;MyProject.c,18 :: 		UBRR0L = (unsigned char)BAUDRATE;
	LDI        R27, 31
	OUT        UBRR0L+0, R27
;MyProject.c,19 :: 		UCSR0A = 0b00000000;
	LDI        R27, 0
	OUT        UCSR0A+0, R27
;MyProject.c,20 :: 		UCSR0B = 0b00011000;
	LDI        R27, 24
	OUT        UCSR0B+0, R27
;MyProject.c,21 :: 		UCSR0C = 0b10000110;
	LDI        R27, 134
	STS        UCSR0C+0, R27
;MyProject.c,22 :: 		}
L_end_uart_init:
	RET
; end of _uart_init

_uart_send:

;MyProject.c,24 :: 		void uart_send(unsigned char data_input)
;MyProject.c,26 :: 		while (!UDRE0_bit)
L_uart_send0:
	IN         R27, UDRE0_bit+0
	SBRC       R27, BitPos(UDRE0_bit+0)
	JMP        L_uart_send1
;MyProject.c,27 :: 		;
	JMP        L_uart_send0
L_uart_send1:
;MyProject.c,28 :: 		UDR0 = data_input;
	OUT        UDR0+0, R2
;MyProject.c,29 :: 		}
L_end_uart_send:
	RET
; end of _uart_send

_uart_send_str:

;MyProject.c,31 :: 		void uart_send_str(char *string_input)
;MyProject.c,33 :: 		while (*string_input != '\0')
L_uart_send_str2:
	MOVW       R30, R2
	LD         R16, Z
	CPI        R16, 0
	BRNE       L__uart_send_str18
	JMP        L_uart_send_str3
L__uart_send_str18:
;MyProject.c,35 :: 		uart_send(*string_input);
	MOVW       R30, R2
	LD         R16, Z
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _uart_send+0
	POP        R2
	POP        R3
;MyProject.c,37 :: 		string_input++;
	MOVW       R16, R2
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R2, R16
;MyProject.c,38 :: 		}
	JMP        L_uart_send_str2
L_uart_send_str3:
;MyProject.c,39 :: 		}
L_end_uart_send_str:
	RET
; end of _uart_send_str

_uart_recieve:

;MyProject.c,41 :: 		unsigned char uart_recieve(void) {
;MyProject.c,42 :: 		while(!RXC0_bit)
L_uart_recieve4:
	IN         R27, RXC0_bit+0
	SBRC       R27, BitPos(RXC0_bit+0)
	JMP        L_uart_recieve5
;MyProject.c,43 :: 		;
	JMP        L_uart_recieve4
L_uart_recieve5:
;MyProject.c,44 :: 		return UDR0;
	IN         R16, UDR0+0
;MyProject.c,45 :: 		}
L_end_uart_recieve:
	RET
; end of _uart_recieve

_get_char:

;MyProject.c,48 :: 		char get_char(int number) {
;MyProject.c,49 :: 		return number + '0';
	MOV        R16, R2
	SUBI       R16, 208
;MyProject.c,50 :: 		}
L_end_get_char:
	RET
; end of _get_char

_get_int:

;MyProject.c,52 :: 		int get_int(char number) {
;MyProject.c,53 :: 		int i = 0;
; i start address is: 18 (R18)
	LDI        R18, 0
	LDI        R19, 0
; i end address is: 18 (R18)
;MyProject.c,54 :: 		while (number != 0x00)
L_get_int6:
; i start address is: 18 (R18)
	LDI        R27, 0
	CP         R2, R27
	BRNE       L__get_int22
	JMP        L_get_int7
L__get_int22:
;MyProject.c,56 :: 		number = (number >> 1);
	MOV        R16, R2
	LSR        R16
	MOV        R2, R16
;MyProject.c,57 :: 		i++;
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R18, R16
;MyProject.c,58 :: 		}
	JMP        L_get_int6
L_get_int7:
;MyProject.c,60 :: 		return i - 1;
	MOVW       R16, R18
	SUBI       R16, 1
	SBCI       R17, 0
; i end address is: 18 (R18)
;MyProject.c,61 :: 		}
L_end_get_int:
	RET
; end of _get_int

_display_uart_pressed_button:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;MyProject.c,64 :: 		void display_uart_pressed_button(void)
;MyProject.c,66 :: 		while (1)
	PUSH       R2
	PUSH       R3
L_display_uart_pressed_button8:
;MyProject.c,68 :: 		char current_input = PINA;
	IN         R16, PINA+0
	STD        Y+0, R16
;MyProject.c,69 :: 		if (current_input != 0x00)
	LDD        R16, Y+0
	CPI        R16, 0
	BRNE       L__display_uart_pressed_button24
	JMP        L_display_uart_pressed_button10
L__display_uart_pressed_button24:
;MyProject.c,72 :: 		UART_Write(get_char(get_int(current_input)));
	LDD        R2, Y+0
	CALL       _get_int+0
	MOVW       R2, R16
	CALL       _get_char+0
	MOV        R2, R16
	CALL       _uart_send+0
;MyProject.c,73 :: 		UART_Write('\0');
	CLR        R2
	CALL       _uart_send+0
;MyProject.c,74 :: 		while (PINA != 0x00)
L_display_uart_pressed_button11:
	IN         R16, PINA+0
	CPI        R16, 0
	BRNE       L__display_uart_pressed_button25
	JMP        L_display_uart_pressed_button12
L__display_uart_pressed_button25:
;MyProject.c,75 :: 		;
	JMP        L_display_uart_pressed_button11
L_display_uart_pressed_button12:
;MyProject.c,81 :: 		}
L_display_uart_pressed_button10:
;MyProject.c,82 :: 		}
	JMP        L_display_uart_pressed_button8
;MyProject.c,83 :: 		}
L_end_display_uart_pressed_button:
	POP        R3
	POP        R2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _display_uart_pressed_button

_ogonek:

;MyProject.c,85 :: 		void ogonek() {
;MyProject.c,86 :: 		while(1) {
L_ogonek13:
;MyProject.c,87 :: 		PORTA = uart_recieve();
	CALL       _uart_recieve+0
	OUT        PORTA+0, R16
;MyProject.c,90 :: 		}
	JMP        L_ogonek13
;MyProject.c,91 :: 		}
L_end_ogonek:
	RET
; end of _ogonek

_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27

;MyProject.c,93 :: 		void main() {
;MyProject.c,94 :: 		UART_Init();
	CALL       _uart_init+0
;MyProject.c,99 :: 		DDRA = 0xFF;  // SETTING PORTA AS output   //INPUT
	LDI        R27, 255
	OUT        DDRA+0, R27
;MyProject.c,100 :: 		PORTA = 0x00; // and DEFAULT INPUT 0
	LDI        R27, 0
	OUT        PORTA+0, R27
;MyProject.c,103 :: 		ogonek();
	CALL       _ogonek+0
;MyProject.c,104 :: 		}
L_end_main:
L__main_end_loop:
	JMP        L__main_end_loop
; end of _main
