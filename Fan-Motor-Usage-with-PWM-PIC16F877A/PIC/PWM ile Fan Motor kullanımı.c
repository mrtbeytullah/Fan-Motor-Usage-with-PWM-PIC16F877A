/*                                                                            /
/  Bu projemizde mikrodenetleyicimiz olan PIC16F877A ile LM35 S�cakl�k        /
/ sens�r�nden okudu�umuz s�cakl�k de�eri ile birlikde DC-FAN Motorumuzu       /
/ PWM kullanarak s�rece�iz.                                                   /
/                                                                             /
/  A0 Pinine Ba�l� LM35 s�cakl�k sens�r�nden s�cakl�k de�erini okuyaca��z     /
/ s�cakl�k de�erimiz e�er 20 Derece alt�nda ise fan�m�z �al��mayacak          /
/ 20 ile 30 Derece aras�nda C2 Pinine ba�l� Transist�r ile Fan h�z�m�z        /                                                                       
/ S�cakl�k Sens�r�nden gelen de�ere g�re linner bir �ekilde artacak.          /                                                                     
/ s�cakl�k de�erimiz 30 Derece oldu�unda ise fan h�z�m�z tam kapasite         /                                                                     
/ olarak �al��acak                                                            /
*/  
// Linkedin:mrtbeytullah 

#include <PWM ile Fan Motor kullan�m�.h>

#define LCD_ENABLE_PIN PIN_E2
#define LCD_RS_PIN PIN_E0
#define LCD_RW_PIN PIN_E1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>  

int16 Duty,ADC_Deger;  
float Vadc,Duty_Yuzde,Sicaklik;

void main()
{                                                                                                                                            
   setup_adc_ports(AN0); //ADC ayarlamas� yap�yoruz
   setup_adc(ADC_CLOCK_DIV_16);
   set_adc_channel(0);      
   delay_us(20);  
     
   setup_timer_2(T2_DIV_BY_16,255,1);      //Timer ayarlamalar�m�z� yap�yoruz
   setup_ccp2(CCP_PWM);                   //CCP2'yi PWM olarak kullanaca��z
              
   lcd_init();         

   while(TRUE)  
   { 
      ADC_Deger=read_adc();               
      Vadc=ADC_Deger*0.0048875855;       
      Sicaklik=(Vadc*100); /*LM35 S�cakl�k Sens�r�nde her 10mV 'luk her art��ta/ 
                          /1 Derece artmaktad�r dolay�s�yla gerilim de�erini/   
                         /100 ile �arparak s�cakl��� �l�ebiliyoruz */
      
     if(sicaklik<20)
      { 
       Duty=0;  
       Duty_Yuzde=Duty/10.24; 
       set_pwm2_duty(Duty);                                                                  
       printf(lcd_putc,"\fDuty_Yuzde=%f\nSicaklik=%2.1f",Duty_Yuzde,Sicaklik);
       Delay_ms(100);  
      }  
      
     else if(Sicaklik>=20 && Sicaklik<=30)
      { 
        Duty=(Sicaklik*(512/5))-((512/5)*20);/*Duty hesab� yapar iken 20-30 Derece aras� fan h�z�m�z 
                linner olarak artaca��ndan hesap yapar iken e�im denklemi kullanarak hesap yap�yoruz*/  
        Duty_Yuzde=Duty/10.24;  
        set_pwm2_duty(Duty);                                                                      
        printf(lcd_putc,"\fDuty_Yuzde=%f\nSicaklik=%2.1f",Duty_Yuzde,Sicaklik);
        Delay_ms(100);  
      }  
      
     else if(Sicaklik>30)
      {   
         Duty=1023;  
         Duty_Yuzde=Duty/10.24; 
         set_pwm2_duty(Duty);   
         printf(lcd_putc,"\fDuty_Yuzde=%f\nSicaklik=%2.1f",Duty_Yuzde,Sicaklik);
         Delay_ms(100);  
      }
     
   }             
                  
}
