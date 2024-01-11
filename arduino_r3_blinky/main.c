#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 0;

int main()
{
  DDRB |= (1 << DDB5);     // 13.4.3 Port B data direction register. Set port B5 to high according to Arduino board datasheet
  TCCR0A |= (1 << WGM02);  // 14.7.2 Set the Timer Mode to CTC. In clear timer on compare or CTC mode (WGM02:0 = 2), 
                           // the OCR0A register is used to manipulate the counter resolution
  OCR0A = 249;             // 14.9.4 Set the value that we want TC0 to count to (249). The output compare register A contains an 8-bit value that is continuously compared with the counter value (TCNT0). A 
                           // match can be used to generate an output compare interrupt, or to generate a waveform output on the OC0A pin.
  TIMSK0 |= (1 << OCIE0A); // 14.9.6 When the OCIE0A bit is written to one, and the I-bit in the status register is set, the Timer/Counter0 compare match A 
                           // interrupt is enabled.
  sei();                   // enable global interrupts
  TCCR0B |= (1 << CS02);   //14.9.2 CS (Clock Select) clk_IO / 256 (from prescaler). 

  while (1)
  {
    if (counter >= 249)
    {
      PORTB ^= (1 << PB5); // Toggle LED
      counter = 0;
    }
  }
}

ISR (TIMER0_COMPA_vect)
{
  counter++;
}