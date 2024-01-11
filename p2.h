/*
 * p2.h
 *
 * Created: 2023-11-08 10:47:32
 * Author: mardea0831
 * Edited: 2023-12-16
 * Editor: Pär Westerlund
 */ 


#ifndef P2_H_
#define P2_H_
#define F_CPU 16000000UL // 16 MHz klockfrekvens.
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>


void setup_p2(void) {

    /*sätter i/o för PORTB
    Bit     Arduino pin     Funktion        i/o 1 = out
    0       pin 8           Summer          1
    1       pin 9           Val res hög     0
    2       pin 10          Val kortslutn   0
    3       pin 11          Val res låg     0
    4       pin 12          Val sp hög      0
    5       pin 13          Val sp låg      0
    6       crystal         Används ej      0
    7       crystal         Används ej      0

    bit      76543210     */
    DDRB = 0b00000001;
    
    /*sätter i/o för PORTC
    Bit     Arduino pin     Funktion        i/o 1 = out
    0       pin A0          Volt hög            0
    1       pin A1          Resistans låg       0
    2       pin A2          Resistans hög       0
    3       pin A3          Volt låg            0
    4       pin A4          Banankontakt LED    1
    5       pin A5          Batterikontroll     0      
    6       reset           Används ej 
    7       ---             Används ej 
    bit      76543210     */
    DDRC = 0b00010000;

    /*sätter i/o för PORTD
    Bit     Arduino pin     Funktion        i/o 1 = out
    0       pin 0           Display 2       1
    1       pin 1           Display 1       1
    2       pin 2           Decimalpunkt    1
    3       pin 3           Display 3       1
    4       pin 4           BCD 1           1
    5       pin 5           BCD 2           1    
    6       pin 6           BCD 3           1
    7       pin 7           BCD 0           1
    bit      76543210       */
    DDRD = 0b11111111;

    /*Initiera analogingångar*/
    ADMUX = (1 << REFS0);
    ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
    while ((ADCSRA & (1 << ADIF)) == 0) ;
    ADCSRA = (1 << ADIF);
    return;
}


/************************************************************************/
/* uint16_t read_analogue_input(uint8_t input_number)                   */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t input_number                                                 */
/* Reprecenterar den ingång (0 - 5) som skall läsas av                  */
/*                                                                      */
/* Return:                                                              */
/* Det returnerande värdet är ett 16-bitars uint-tal mellan 0 - 1023    */
/************************************************************************/
         
uint16_t read_analogue_input(uint8_t input_number) {
    ADMUX = ((1 << REFS0) | input_number);
    ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
    while ((ADCSRA & (1 << ADIF)) == 0) ;
    ADCSRA = (1 << ADIF);
    return ADC;
}

/************************************************************************/
/* bool read_digital_input_portb(uint8_t bit)                           */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t bit                                                          */
/* Reprecenterar den bit på PORTB som skall läsas av                    */
/*                                                                      */
/* Return:                                                              */
/* True eller False beroende på om ingången är hög eller låg            */
/************************************************************************/
bool read_digital_input_portb(uint8_t bit) {
    return PINB & (1 << bit);
}

/************************************************************************/
/* bool read_digital_input_portc(uint8_t bit)                           */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t bit                                                          */
/* Reprecenterar den bit på PORTC som skall läsas av                    */
/*                                                                      */
/* Return:                                                              */
/* True eller False beroende på om ingången är hög eller låg            */
/* OBS! normalt används PORTC för analog läsning                        */
/************************************************************************/
bool read_digital_input_portc(uint8_t bit) {
    return PINC & (1 << bit);
}

/************************************************************************/
/* bool read_digital_input_portd(uint8_t bit)                           */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t bit                                                          */
/* Reprecenterar den bit på PORTD som skall läsas av                    */
/*                                                                      */
/* Return:                                                              */
/* True eller False beroende på om ingången är hög eller låg            */
/************************************************************************/

bool read_digital_input_portd(uint8_t bit) {
    return PIND & (1 << bit);
}

/************************************************************************/
/* bool write_digital_output_portb(uint8_t bit, bool value)             */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t bit                                                          */
/* Reprecenterar den bit på PORTB som skall skrivas till                */
/*                                                                      */
/* bool value                                                           */
/* true eller false beroende på om man vill sätta utgången till hög/låg */
/*                                                                      */
/* Return:                                                              */
/* Void                                                                 */
/************************************************************************/

void write_digital_output_portb(uint8_t bit, bool value) {
    if(value) {
        PORTB |= (1 << bit);
        }else {
        PORTB &= ~(1 << bit);
    }
}

/************************************************************************/
/* bool write_digital_output_portc(uint8_t bit, bool value)             */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t bit                                                          */
/* Representerar den bit på PORTC som skall skrivas till                */
/*                                                                      */
/* bool value                                                           */
/* true eller false beroende på om man vill sätta utgången till hög/låg */
/*                                                                      */
/* Return:                                                              */
/* Void                                                                 */
/* OBS! normalt används PORTC för analog läsning                        */
/************************************************************************/
void write_digital_output_portc(uint8_t bit, bool value) {
    if(value) {
        PORTC |= (1 << bit);
        }else {
        PORTC &= ~(1 << bit);
    }
}

/************************************************************************/
/* bool write_digital_output_portd(uint8_t bit, bool value)             */
/*                                                                      */
/* Argument:                                                            */
/* uint8_t bit                                                          */
/* Representerar den bit på PORTD som skall skrivas till                */
/*                                                                      */
/* bool value                                                           */
/* true eller false beroende på om man vill sätta utgången till hög/låg */
/*                                                                      */
/* Return:                                                              */
/* Void                                                                 */
/************************************************************************/
void write_digital_output_portd(uint8_t bit, bool value) {
    if(value) {
        PORTD |= (1 << bit);
        }else {
        PORTD &= ~(1 << bit);
    }
}

/************************************************************************/
/* Function Name: wait(uint16_t ms)                                     */
/* parameter: int ms, milliseconds to wait                              */
/* Return: void                                                         */
/* Description:                                                         */
/* The program waits a amount of milliseconds                           */
/************************************************************************/
void wait(uint16_t wait_ms) {
	for (uint16_t i = 0;i<wait_ms;i++) {
		_delay_ms(1);
	}
}

/************************************************************************/
/* Function Name: display_digit(uint8_t digit)                          */
/* parameter: uint8_t digit, digit to display                           */
/* Return: void                                                         */
/* Description:                                                         */
/* Encodes decimal digit to BCD and outputs to BCD decoder              */
/************************************************************************/
void display_digit(uint8_t digit) {
    switch(digit) {
        case 0:
            write_digital_output_portd(7, false);
            write_digital_output_portd(4, false);
            write_digital_output_portd(5, false);
            write_digital_output_portd(6, false);
            return;
        case 1:
            write_digital_output_portd(7, true);
            write_digital_output_portd(4, false);
            write_digital_output_portd(5, false);
            write_digital_output_portd(6, false);
            return;
        case 2:
            write_digital_output_portd(7, false);
            write_digital_output_portd(4, true);
            write_digital_output_portd(5, false);
            write_digital_output_portd(6, false);
            return;
        case 3:
            write_digital_output_portd(7, true);
            write_digital_output_portd(4, true);
            write_digital_output_portd(5, false);
            write_digital_output_portd(6, false);
            return;
        case 4:
            write_digital_output_portd(7, false);
            write_digital_output_portd(4, false);
            write_digital_output_portd(5, true);
            write_digital_output_portd(6, false);
            return;
        case 5:
            write_digital_output_portd(7, true);
            write_digital_output_portd(4, false);
            write_digital_output_portd(5, true);
            write_digital_output_portd(6, false);
            return;
        case 6:
            write_digital_output_portd(7, false);
            write_digital_output_portd(4, true);
            write_digital_output_portd(5, true);
            write_digital_output_portd(6, false);
            return;
        case 7:
            write_digital_output_portd(7, true);
            write_digital_output_portd(4, true);
            write_digital_output_portd(5, true);
            write_digital_output_portd(6, false);
            return;
        case 8:
            write_digital_output_portd(7, false);
            write_digital_output_portd(4, false);
            write_digital_output_portd(5, false);
            write_digital_output_portd(6, true);
            return;
        case 9:
            write_digital_output_portd(7, true);
            write_digital_output_portd(4, false);
            write_digital_output_portd(5, false);
            write_digital_output_portd(6, true);
            return;
        default:
            write_digital_output_portd(7, true);
            write_digital_output_portd(4, true);
            write_digital_output_portd(5, true);
            write_digital_output_portd(6, true);            
    }

    return;
}

/************************************************************************/
/* Function Name: turn_off_display(void)                                */
/* parameter: None                                                      */
/* Return: void                                                         */
/* Description:                                                         */
/* Deactivates all digits and DP                                        */
/************************************************************************/
void turn_off_display(void) {
    /* CC1 = D1, CC2 = D0, CC3 = D3, DPX = D2 */
    write_digital_output_portd(1, true);   
    write_digital_output_portd(0, true);  
    write_digital_output_portd(3, true);   
    write_digital_output_portd(2, false);  
}

/************************************************************************/
/* Function Name: turn_on_display(void)                                 */
/* parameter: None                                                      */
/* Return: void                                                         */
/* Description:                                                         */
/* Activates all digits but leaves DP unchanged                         */
/************************************************************************/
void turn_on_display(void) {
    /* CC1 = D1, CC2 = D0, CC3 = D3, DPX = D2 */
    write_digital_output_portd(1, false);   
    write_digital_output_portd(0, false);   
    write_digital_output_portd(3, false);   
}

/************************************************************************/
/* Function Name: get_int_length(uint16_t int_number)                   */
/* parameter: uint16_t int_number, integer number                       */
/* Return: uint8_t, number of digits in int_number                      */
/* Description:                                                         */
/* Calculates number of digits in int_number                            */
/************************************************************************/
uint8_t get_int_length(uint16_t int_number) {

    if (int_number < 10) {
        return 1;
    }
    else if (int_number < 100) {
        return 2;
    }
    else if (int_number < 1000) {
        return 3;
    }
    else if (int_number < 10000) {
        return 4;
    }
    else {
        return 5;
    }

}

/************************************************************************/
/* Function Name: get_digit(uint16_t value, uint8_t digit_number)       */
/* parameter: uint16_t value, int value; uint8_t digit_number, digit no */
/* Return: uint8_t, digit on desired position                           */
/* Description:                                                         */
/* Returns single digit on desired position from int value              */
/************************************************************************/
uint8_t get_digit(uint16_t value, uint8_t digit_number)
{
    uint16_t div_factor;
    uint16_t return_value;

    if (digit_number == 1) {
        div_factor = 1;
    }
    else if (digit_number == 2) {
        div_factor = 10;
    }
    else if (digit_number == 3) {
        div_factor = 100;
    }
    else if (digit_number == 4) {
        div_factor = 1000;
    }
    else if (digit_number == 5) {
        div_factor = 10000;
    }
    else return 10;

    return_value = value/div_factor;
    return_value = return_value % 10;
    return (return_value);
}

/****************************************************************************/
/* Function Name: display_value(float value, uint8_t decimals, bool vin_low)*/
/* parameter: float value, value to display                                 */
/*            uint8_t decimals, number of decimals (0 - 2)                  */
/*            bool vin_low, true if Vin low                                 */
/* Return: void                                                             */
/* Description:                                                             */
/* Converts float value to integer and decimal part with two digits.        */
/* Calculates digits to display.                                            */
/* Displays digits on 7-seg display with display_digit function.            */
/* Lights up DP on digit 3 if Vin is low.                                   */
/****************************************************************************/
void display_value(float value, uint8_t decimals, bool vin_low) {
    uint8_t digit1, digit2, digit3, int_length, int_decimals;
    uint16_t int_value;

    /* Konvertera till heltalsdel och decimaldel */
    int_value = (uint16_t)value;
    int_length = get_int_length(int_value);
    int_decimals = (uint16_t)((value - int_value)*100);

    /* Set digits to display */
    if (int_length == 3) {
        digit1 = get_digit(int_value, 3);
        digit2 = get_digit(int_value, 2);
        digit3 = get_digit(int_value, 1);
    }
    else if (int_length == 2) {
        if (decimals == 1) {
            digit1 = get_digit(int_value, 2);
            digit2 = get_digit(int_value, 1);
            digit3 = get_digit(int_decimals, 2);
        } else {
            digit1 = 0;
            digit2 = get_digit(int_value, 2);
            digit3 = get_digit(int_value, 1);
        }
    }
    else if (int_length == 1) {
        if (decimals == 1) {
            digit1 = 0;
            digit2 = int_value;
            digit3 = get_digit(int_decimals, 2);
        } else if (decimals == 2) {
            digit1 = int_value;
            digit2 = get_digit(int_decimals, 2);
            digit3 = get_digit(int_decimals, 1);
        } else {
            digit1 = 0;
            digit2 = 0;
            digit3 = int_value;
        }
    }

    /* Output to display */
    /* CC1 = D1, CC2 = D0, CC3 = D3, DPX = D2 */
    display_digit(digit1);

    if (decimals == 2) {
        write_digital_output_portd(2, true);
    }

    write_digital_output_portd(1, false);
    wait(5);

    if (decimals == 2) {
        write_digital_output_portd(2, false);
    }

    write_digital_output_portd(1, true);
    display_digit(digit2);
    
    if (decimals == 1) {
        write_digital_output_portd(2, true);
    }

    write_digital_output_portd(0, false);
    wait(5);

    if (decimals == 1) {
        write_digital_output_portd(2, false);
    }

    write_digital_output_portd(0, true);
    display_digit(digit3);

    if (vin_low) {
        write_digital_output_portd(2, true);
    }

    write_digital_output_portd(3, false);
    wait(5);

    if (vin_low) {
        write_digital_output_portd(2, false);
    }

    write_digital_output_portd(3, true);

}  

/************************************************************************/
/* Function Name: volt_low(void)                                        */
/* parameter: none                                                      */
/* Return: float                                                        */
/* Description:                                                         */
/* Measures voltage 0 - 5V and returns float value                      */
/************************************************************************/
float volt_low(void) {
    float volt;

    /* Omvandla analog nivå till max 5V */
    volt = ((float)(read_analogue_input(3)))/204.6;
    return volt;
}

/************************************************************************/
/* Function Name: volt_high(void)                                       */
/* parameter: none                                                      */
/* Return: float                                                        */
/* Description:                                                         */
/* Measures voltage 0 - ~39V and returns float value                    */
/************************************************************************/
float volt_high(void) {
    float volt;

    /* Omvandla analog nivå */
    volt = ((float)(read_analogue_input(0)))/26.06;
    return volt;
}

/************************************************************************/
/* Function Name: res_low(void)                                         */
/* parameter: none                                                      */
/* Return: float                                                        */
/* Description:                                                         */
/* Measures resistance 0 - 1000 ohm and returns float value             */
/************************************************************************/
float res_low(void) {
    float volt, resistance;

    /* Omvandla analog nivå till spänning och räkna ut resistansen */
    volt = ((float)(read_analogue_input(1)))/204.6;
    resistance = (988*volt)/(5 - volt);
    return resistance;
}

/************************************************************************/
/* Function Name: res_beep(void)                                        */
/* parameter: none                                                      */
/* Return: none                                                        */
/* Description:                                                         */
/* Measures resistance and sounds a signal if it is < 10 ohm            */
/************************************************************************/
void res_beep(void) {
   uint16_t counter = 0, j;

    while (res_low() < 10) {
        /* SUMMMERFUNKTION ca 1 s */
        for (uint16_t i = 0; i < 1000; i++) {
            write_digital_output_portb(0, true);    
            for (j = 0; j < 750; j++) {
                counter++;
            }
            write_digital_output_portb(0, false);  
            for (j = 0; j < 750; j++) {
                counter--;
            }
        }
    }
}

/************************************************************************/
/* Function Name: res_high(void)                                        */
/* parameter: none                                                      */
/* Return: float, resistance in kiloohm                                 */
/* Description:                                                         */
/* Measures resistance 1k - 100k ohm and returns kiloohm float value    */
/************************************************************************/
float res_high(void) {
    float volt, resistance;

    // Omvandla analog nivå //
    volt = ((float)(read_analogue_input(2)))/204.6;
    resistance = (9.920*volt)/(5 - volt);
    return resistance;
}

/************************************************************************/
/* Function Name: vin_ok(void)                                          */
/* parameter: none                                                      */
/* Return: bool, true if ok false if not                                */
/* Description:                                                         */
/* Checks if battery or supply voltage is below 6V                      */
/************************************************************************/
bool vin_ok(void) {
    float volt;

    /* Omvandla till matningsspänning */
    volt = ((float)(read_analogue_input(3)))/74.7;

    if (volt < 6) {
        return false;
    } else {
        return true;
    }   
}

#endif /* P2_H_ */