void data_save(void)    //Used to save data in EEPROM
{
   output_high(mech_counter);    //Deactivate mechanical counter for saving power
   mech_led=0;loop=0;            //Flags for deactivating mech counter.
//!   output_low(PIN_B6);
//!   output_low(PIN_B7);
//!   output_low(PIN_A0);
   
   restart_wdt(); 
   mwrite32(16,totalizer1); delay_ms(1);  // totalizer 1 
   
   mwrite32(20,totalizer2); delay_ms(1);  // totalizer 2 
   
   mwritebyte(24,grams_10); delay_ms(1);    // mech counter kg 
   
   mwrite32(25,weight); delay_ms(1);      // filling weight
   
   int_amount=amount*100;
   mwrite32(31,int_amount); delay_ms(1);    // int32 amount
   
//!   total1=mread32(16);delay_ms(1);
//!   total2=mread32(25);delay_ms(1);
//!   total3=mread32(31);delay_ms(1);
//!   total4=mread32(20);delay_ms(1);
//!   
//!   if(total1 == totalizer1 && total4 == totalizer2) output_high(PIN_B6);
//!   if(total_2 == weight) output_high(PIN_B7);
//!   if(total3 == int_amount) output_high(PIN_A0);

   new_filling = FALSE;
}


///////////////////////////////////////////////////////////////////////////////
void delay_50(void)     //50ms delay approx
{
   unsigned int8 delay=0;
   
   restart_wdt();
   
   while(delay<=5)
   {
      delay++;
      delay_ms(10);
      power_check();
   }
   
   if(delay>=5) delay=0;
}


///////////////////////////////////////////////////////////////////////////////
void delay_250(void)    //250ms delay approx
{
   unsigned int8 delay=0;
   
   restart_wdt();
   
   while(delay<=25)
   {
      delay++;
      delay_ms(10);
      power_check();
   }
   
   if(delay>=25) delay=0;
}


///////////////////////////////////////////////////////////////////////////////
void power_check(void)                 //check power state
{
   restart_wdt();
   if(input(power_sense))
   {
      disable_interrupts(INT_EXT);     // disable pulses interrupt 
      disable_interrupts(INT_EXT2);    // disable IR interrupt  
      disable_interrupts(INT_TIMER1);  // disable timer 1 used with IR
      
      one_time=0; filling_state=0; disp_pattern=0;
      output_high(low_sol); output_high(med_sol); output_high(high_sol);
      
      //////////////////////////////////////////////////////////////////////////
      //This check if new filling occured then save the data on power down.
      //If no new filling occured and power goes then no data will be stored in
      //EEPROM.
      if(new_filling == TRUE)
      {
         data_save();
      }
      //////////////////////////////////////////////////////////////////////////
      
      if(two_sec_passed == TRUE)
      {
         lcd_data[14]=0xe2;      //indication of P on power loss
         format_data();
         show_on_lcd();   
      }
      
      while(input(power_sense))  // Stay here untill power Restores
      {
         restart_wdt();
      }
      p_occured = TRUE;          // Indicate Power is OFF
   }
}
