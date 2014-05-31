#include <18F8722.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //Low power osc < 200 khz
#FUSES NOPROTECT                //Code not protected from reading
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES MCU                      //Microcontroller Mode
#FUSES NOWAIT                   //Wait selections unavailable for Table Reads or Table Writes

#use delay(clock=10000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,stream=PIC)
#use rs232(baud=57600,parity=N,xmit=PIN_G1,rcv=PIN_G2,bits=8,stop=1,stream=servo)
void init()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1 (T1_INTERNAL|T1_DIV_BY_4);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_4(T4_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RDA2);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);



//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!

}
