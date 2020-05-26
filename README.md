# Light-and-Temperature-Analog-Digital-Converter
Utilize PIC18F4620 ADC and incorporate light and temperature senors. The following are set conditions project must follow.
```
Read the voltage from the LM34 using the PIC18F4620’s
ADC Channel 0 
2) Convert that voltage into the equivalent temperature (in degree F)
3) Convert the temperature into BCD 
4) Output the range of result onto to two 7-segment displays.
5) Output the same result to the TeraTerm terminal so that we can see the data on the computer screen
6) In addition, the circuit does include two common anode RGB LEDs called D1 and D2. Get the program to do the following:
           a) D1 will show different colors based on the following conditions:
Temperature Range D1’s color Below 65F
65F – 72F 73F – 76F 77F – 83F Above 83F
Off Red
Green Blue
White Felix Pinaib) D2 will show the range of the temperature as follows:
Temperature Range D2’s color Below 10
Off
10-19 20-29 30-39 40-49 50-59 60-69
Above 70 Red Green
Yellow Blue
Purple Cyan
White
7) Measure the voltage at the pin AN1 coming from the photo resistor PR1. Change the color of the Common-Cathode D3 based on the following voltage reading:
AN1 voltage < 2.5V
D3’s color RED
>=2.5V && < 3.5V GREEN >= 3.5V
```
