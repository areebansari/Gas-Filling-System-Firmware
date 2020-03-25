#int_EXT
void  EXT_isr(void) 
{
   restart_wdt();
   if(start==1)
   {                         
      clear_interrupt(INT_TIMER0);     // clear timer 0 interrupt flag
      filling_freq=get_timer0();       // get pulses frequency
      set_timer0(0);                   // reset timer
      
      no_flow=0;no_flow_timer=0; no_flow_timer1=0;
      wait_timer1_1=0; wait_timer1_2=0; 
      filling_performed=1;new_filling=TRUE;
      
      if(calib_check==0)
      {
         calib_cntr++;                 // count incoming pulses
         if(calib_cntr==no_of_pulses1) // pulses equl to calibration factor, or 
         {                             // equal to no of pulses1
            calib_cntr=0;              
            pulse_counter++;           
            grams_10++;          // used with mech counter   
            vol++;               // used in start of filling
            totalizer1++;        // totalizer 1 increment
            totalizer2++;        // totalizer 2 increment
            weight++;            // incr. in weight, 1 incr = 10 grams, iwt
            
            if(pulse_counter==no_of_time1 && no_perform==0)
            {
               calib_check=1;
               pulse_counter=0;
            }
         }
      }//if(calib_check==0)
      
      else if(calib_check==1)
      {
         calib_cntr++;                 // count incoming pulses
         if(calib_cntr==no_of_pulses2) // pulses equl to calibration factor, or 
         {                             // equal to no of pulses1
            calib_cntr=0;
            pulse_counter++;
            grams_10++;          // used with mech counter   
            vol++;               // used in start of filling
            totalizer1++;        // totalizer 1 increment
            totalizer2++;        // totalizer 2 increment
            weight++;            // incr. in weight, 1 incr = 10 grams, iwt
            
            if(pulse_counter==no_of_time2)
            {
               calib_check=0;
               pulse_counter=0;
            }
         }
      }//else if(calib_check==1)
      
      if(vol>20)  // if 200 gms gas filled
      {        
         one_time=1;
         vol=0;
      }
      
      if(grams_10==100) // if 1kg gas filled, increment mechanical totalizer
      {        
         mech_led=1; 
         grams_10=0;
      }
            
   }
}                                                        

