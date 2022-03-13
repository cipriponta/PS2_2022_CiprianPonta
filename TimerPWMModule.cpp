#include "TimerPWMModule.h"

void TimerPWMModule::init()
{
    DDRB |= (1 << PB5);     // Builtin LED
    
    DDRB |= (1 << PB3);     // Red   Component (Pin 13, OCR2A)
    DDRD |= (1 << PD6);     // Green Component (Pin  6, OCR0A)
    DDRD |= (1 << PD5);     // Blue  Component (Pin  5, OCR0B)  
    
    // Timer2 Setup - OCR2A(Pin 13) -> PWM
    TCCR2A |= (1 << WGM21) | (1 << WGM20);              // Fast PWM Mode
    TCCR2A |= (1 << COM2A1);                            // Non inverting mode, OCR2A
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  // 1024 prescaler
    
    // Timer0 Setup - OCR0A(Pin 6) -> PWM, OCR0B(Pin 5) -> PWM
    TCCR0A |= (1 << WGM01) | (1 << WGM00);              // Fast PWM Mode
    TCCR0A |= (1 << COM0A1);                            // Non inverting mode, OCR0A
    TCCR0A |= (1 << COM0B1);                            // Non inverting mode, OCR0B
    TCCR0B |= (1 << CS02) | (1 << CS00);                // 1024 prescaler
    
    // Timer1 Setup -> Timer with 0.05 period
    TCCR1B |= (1 << WGM12);                             // CTC
    TCCR1B |= (1 << CS11) | (1 << CS10);                // 64 prescaler
    TIMSK1 |= (1 << OCIE1A);                            // Interrupt enable
    OCR1A = (int)((F_CPU / PRESC) / 10LL);              // Interrupt period
    
    OCR2A = 255;
    OCR0A = 255;
    OCR0B = 255;
}

