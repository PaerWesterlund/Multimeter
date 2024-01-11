/*
* main.c
*
* Projekt P2
* Created: 11/9/2023 2:43:56 PM
* Author: Pär Westerlund
*/

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "p2.h"

int main(void)
{
    float value = 0;
    uint8_t decimals;
    uint16_t batt_counter = 4000;
    bool vin_low = false;

    setup_p2();

    /* Släck display */
    turn_off_display();

    /* Visa versionsnr */
    for (int i = 0; i < 100; i++) {
        display_value(1.99, 2, false);
    }

    while(1)
    {
        /* Kolla vilket funktionsläge som är valt 
           och hämta uppmätt värde (value).         
           PORTC bit 4 styr LEDar för banankontakter */
        if (read_digital_input_portb(5)) {
            write_digital_output_portc(4, false);
            value = volt_low();
            decimals = 2;
        } else if (read_digital_input_portb(4)) {
            write_digital_output_portc(4, true);            
            value = volt_high();
            decimals = 1;
        } else if (read_digital_input_portb(3)) {
            write_digital_output_portc(4, false);
            value = res_low();
            decimals = 0;
        } else if (read_digital_input_portb(2)) {
            write_digital_output_portc(4, false);
            res_beep();
            value = 0;
            decimals = 0;
        } else if (read_digital_input_portb(1)) {
            write_digital_output_portc(4, false);
            value = res_high();
            decimals = 0;
        }

        /* Kollar Vin ca varje minut
           Om Vin är låg tänds DP på siffra 3 */
        if (batt_counter == 4000) {
            if (!vin_ok()) {
                vin_low = true;
            } else {
                vin_low = false;
            }
            batt_counter = 0;
        }
        
        display_value(value, decimals, vin_low);

        batt_counter++;
    }
}