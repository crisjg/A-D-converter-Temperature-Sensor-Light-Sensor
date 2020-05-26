#include <p18f4620.h> 
#include <stdio.h> 
#include <math.h> 
#include <usart.h>
#pragma config OSC = INTIO67 
#pragma config WDT=OFF 
#pragma config LVP=OFF 
#pragma config BOREN =OFF
#define D1_RED      PORTBbits.RB0//ports for D1's Color
#define D1_GREEN    PORTBbits.RB1//ports for D1's Color
#define D1_BLUE     PORTBbits.RB2//ports for D1's Color

#define D2_RED      PORTBbits.RB3//ports for D2's Color
#define D2_GREEN    PORTBbits.RB4//ports for D2's Color
#define D2_BLUE     PORTBbits.RB5//ports for D2's Color

#define D3_RED      PORTEbits.RE0//ports for Light Sensor Color
#define D3_GREEN    PORTEbits.RE1//port for Light Sensor Color
#define D3_BLUE     PORTEbits.RE2//port for Light Sensor Color
int ADC_Result;

//initalize methods Prototype Area
void do_init();
void init_UART();
void Init_ADC(void);

unsigned int Get_Full_ADC(void);
void SET_D1_RED();//sets D1's Red
void SET_D1_GREEN();//sets D1's Green
void SET_D1_YELLOW();//sets D1's Yellow
void SET_D1_BLUE();//sets D1's Blue
void SET_D1_PURPLE();//sets D1's Purple
void SET_D1_CYAN();//sets D1's Cyan
void SET_D1_WHITE();//sets D1's White
void SET_D1_OFF(); //sets D1's Off
void SET_D2_RED();//sets D2's Red
void SET_D2_GREEN();//sets D2's Green
void SET_D2_YELLOW();//sets D2's Yellow
void SET_D2_BLUE();//sets D2's Blue
void SET_D2_PURPLE();//sets D2's Purple
void SET_D2_CYAN();//sets D2's Cyan
void SET_D2_WHITE();//sets D2's White
void SET_D2_OFF();//sets D2's Off
void DO_RGB3(float f);// displays colors for photo resistor
void DO_RGB2(int t2);//displays color for D2's Colors
void DO_RGB1(int t1);//displays color for D1's Colors

void init_UART()
{
 OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF &
USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX &
USART_BRGH_HIGH, 25);
 OSCCON = 0x60;
}

void putch (char c)
{
    while (!TRMT);
    TXREG = c;
}


void init_ADC(void) {
    ADCON0=0x01; // select channel AN0, and turn on the ADDC subsystem
    ADCON1=0x1B;
    ADCON2=0xA9;// Set the bit conversion time (TAD) and acquisition time
}


//Measure Analog Voltage
unsigned int Get_Full_ADC(void) 
{
    int result;
        ADCON0bits.GO=1; 
        while(ADCON0bits.DONE==1);
        result = (ADRESH * 0x100) + ADRESL;
        return result;
}

void main(void)
{
    
    do_init();
    PORTB = 0xFF;//00
    PORTC = 0xFF; // OUTPUT PORT 7-SEGMENT LED U
    PORTD = 0xFF; // OUTPUT PORT 7-SEGMENT LED L
    PORTE = 0x00; // Common Cathode LED OFF
    
      int ISTEP;
      int IVOLT;
      int ITEMP;
      int ISTEP1;
      int IVOLT1;
      int ITEMP1;
      float LIGHT;
      int L; //right digit on 7 segment display
      int U; //left digit on 7 segment display
      char SEVEN_SEG[10] = {0x01,0x4F,0x12,0x06,0x4C,0x24,0x60,0x0F,0x00,0x0C};// sets up numerical values for 7 segment display
    while(1)
    {   
        ADCON0 = 0x01; // Analog to Digital Conversion set to LM34 Temperature Sensor
        ISTEP = Get_Full_ADC();   
        IVOLT = ISTEP * 4; //(volt rec/ max # steps) (4mv/step)
        ITEMP = IVOLT / 10; // divide by 10 for 10mV
        U = ITEMP % 10;//ones place % by 10
        L = ITEMP / 10;//tenths place divide by 10
        PORTC = SEVEN_SEG[U];
        PORTD = SEVEN_SEG[L];
        
        printf ("TEMP = %d\r\n", ITEMP); //outputs to TeraTerm the temp
        ADCON0 =0x09;
        ISTEP1 = Get_Full_ADC();   
        IVOLT1 = ISTEP1 * 4;//(volt rec/ max # steps) (4mv/step)
        ITEMP1 = IVOLT1 / 10;// divide by 10 for 10mV
        LIGHT = IVOLT1/1000.0;
        printf ("LIGHT = %f\r\n", LIGHT);
        DO_RGB3(LIGHT); // Displays colors for photo resistor
        DO_RGB2(ITEMP1);//Displays color for D2's Colors
        DO_RGB1(ITEMP);// Displays color for D1's Colors
    }
}

void do_init()
{
    init_UART();
    TRISA = 0xFF;//initialize TRISA Input
    TRISB = 0x00;//initialize TRISB Output
    TRISC = 0x00;//initialize TRISC Output
    TRISD = 0x00;//initialize TRISD Output
    TRISE = 0x00;//initialize TRISE Output
    init_ADC();
} 

void SET_D1_RED() 
{
    D1_RED = 0;
    D1_GREEN = 1; 
    D1_BLUE = 1;
}
void SET_D1_GREEN()
{
    D1_RED = 1;
    D1_GREEN = 0; 
    D1_BLUE = 1;
}
void SET_D1_YELLOW()
{
    D1_RED = 0;
    D1_GREEN = 0; 
    D1_BLUE = 1;
}
void SET_D1_BLUE()
{
    D1_RED = 1;
    D1_GREEN = 1; 
    D1_BLUE = 0;
}
void SET_D1_PURPLE()
{
    D1_RED = 0;
    D1_GREEN = 1; 
    D1_BLUE = 0;
}
void SET_D1_CYAN()
{
    D1_RED = 1;
    D1_GREEN = 0; 
    D1_BLUE = 0;
}
void SET_D1_WHITE()
{
    D1_RED = 0;
    D1_GREEN = 0; 
    D1_BLUE = 0;
}

void SET_D1_OFF() 
{
    D1_RED = 1;
    D1_GREEN = 1; 
    D1_BLUE = 1;
}

void SET_D2_RED() 
{
    D2_RED = 0;
    D2_GREEN = 1; 
    D2_BLUE = 1;
}
void SET_D2_GREEN()
{
    D2_RED = 1;
    D2_GREEN = 0; 
    D2_BLUE = 1;
}
void SET_D2_YELLOW()
{
    D2_RED = 0;
    D2_GREEN = 0; 
    D2_BLUE = 1;
}
void SET_D2_BLUE()
{
    D2_RED = 1;
    D2_GREEN = 1; 
    D2_BLUE = 0;
}
void SET_D2_PURPLE()
{
    D2_RED = 0;
    D2_GREEN = 1; 
    D2_BLUE = 0;
}
void SET_D2_CYAN()
{
    D2_RED = 1;
    D2_GREEN = 0; 
    D2_BLUE = 0;
}
void SET_D2_WHITE()
{
    D2_RED = 0;
    D2_GREEN = 0; 
    D2_BLUE = 0;
}

void SET_D2_OFF() 
{
    D2_RED = 1;
    D2_GREEN = 1; 
    D2_BLUE = 1;
}

void DO_RGB3(float f)
{
    if (f < 2.5)
    { 
        //red
       D3_RED = 1;
       D3_GREEN = 0; 
       D3_BLUE = 0;
    }
    else if(f >= 2.5 && f < 3.5) 
    {
        //green
        D3_RED = 0;
        D3_GREEN = 1; 
        D3_BLUE = 0;
    }
    else if(f >= 3.5)
    {
        //yellow
        D3_RED = 1;
        D3_GREEN = 1; 
        D3_BLUE = 0;
    }
}

void DO_RGB2(int t2)
{
    if (t2 < 10) // Temperature Range below 10
    {
        SET_D2_OFF();// D2's Color Off
    }
    else if (t2 >= 10 && t2 <= 19) // Temperature Range Between 10 - 19
    {
        SET_D2_RED(); // Turn D2 Red
    }
    else if (t2 >= 20 && t2 <= 29)// Temperature Range Between 20 - 29
    {
        SET_D2_GREEN(); // Turn D2 Green
    }
    else if (t2 >= 30 && t2 <= 39)// Temperature Range Between 30 - 39
    {
        SET_D2_YELLOW(); // Turn D2 Yellow
    }
    else if (t2 >= 40 && t2 <= 49)// Temperature Range Between 40 - 49
    {
        SET_D2_BLUE();// Turn D2 Blue
    }
    else if (t2 >= 50 && t2 <= 59)// Temperature Range Between 50 - 59
    {
        SET_D2_PURPLE();//Turn D2 Purple
    }
    else if (t2 >= 60 && t2 <= 69)// Temperature Range Between 60 - 69
    {
        SET_D2_CYAN();//Turn D2 Cyan
    }
    else if (t2 >= 70)//Temperature Range above 70
    {
        SET_D2_WHITE();//Turn D2 White
    }
}

void DO_RGB1(int t1)//Displays D1's Colors
{
    if(t1 < 65)//Temperature Range below 65
    {
        SET_D1_OFF();
    }
    else if (t1 <= 72 && t1 >= 65)
    {
        SET_D1_RED();
    }
    else if(t1 <= 76 && t1 >= 73)
    {
        SET_D1_GREEN();
    }
    else if (t1 <= 83 && t1 >= 77)
    {
        SET_D1_BLUE();
    }
    else if (t1 > 83)
    {
        SET_D1_WHITE();
    }
}