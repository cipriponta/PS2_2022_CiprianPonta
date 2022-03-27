#include "TimerPWMModule.h"

void timer_pwm_v_init()
{
    DDRB |= (1 << PB7);                                 // Builtin LED
    
    DDRB |= (1 << PB6);                                 // Red   Component (Pin 12, OCR1B)
    DDRB |= (1 << PB5);                                 // Green Component (Pin 11, OCR1A)
    DDRB |= (1 << PB4);                                 // Blue  Component (Pin 10, OCR2A)  
    
    // Timer1, OCR1A(Pin 11), OCR1B(Pin 12) -> Fast PWM
    TCCR1A |= (1 << WGM10);                             // Fast PWM, 8-bit
    TCCR1B |= (1 << WGM12);                             // Fast PWM, 8-bit
    TCCR1A |= (1 << COM1A1);                            // OCR1A non inverting mode
    TCCR1A |= (1 << COM1B1);                            // OCR1B non inverting mode
    TCCR1B |= (1 << CS12) | (1 << CS10);                // Prescaler = 1024
    
    // Timer2, OCR2A(Pin 10) -> Fast PWM
    TCCR2A |= (1 << WGM21) | (1 << WGM20);              // Fast PWM, 8-bit
    TCCR2A |= (1 << COM2A1);                            // OCR2A non inverting mode
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  // Prescaler = 1024
    
    // Timer5 -> CTC, 1 second interrupt
    TCCR5B |= (1 << WGM52);                             // CTC
    TCCR5B |= (1 << CS51) | (1 << CS50);                // Prescaler = 64
    TIMSK5 |= (1 << OCIE5A);                            // Interrupt enable
    OCR5A = (int)((F_CPU / PRESC) / 10);                // Interrupt period
    
    // RGB led initial values
    OCR1B = 0;
    OCR1A = 0;
    OCR2A = 0;  
}