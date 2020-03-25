#include "new pcard.h"
#include "lcd_func.c"
#include "functions.c"
#include "format_data.c"
#include "IR routine.c"
#include "IR interrupt.c"
#include "pulses interrupt.c"
#include "solenoid look up table.c"
#include "keypad routine.c"

void main()
{
   /////////////////////////////////////////////////////////////////////////////
   //At very first start delay of 2 sec is included which is used to avoid 
   //malfunctioning in reading EEPROM.
   //This loop also monitor the input voltage range.if voltage is less than 185v
   //the processor stop working and the delay of 2 sec restart.
   
   output_low(strobe_l);      // make the strobe low (deactivate LCD strobe)
   output_high(strobe_k);     // make the strobe high (deactivate keypad strobe)
   output_high(clock_pin);    // make the clock pin high (deactivate clock output)
   
   output_drive(data_pin);    // clear bit 3 of TrisA register. (make this pin as output)
   
//!   output_drive(PIN_A0);   //clear bit 0 of TrisA register. (for debugging purpose only)
//!   output_drive(PIN_B6);   //clear bit 0 of TrisA register. (for debugging purpose only)
//!   output_drive(PIN_B7);   //clear bit 0 of TrisA register. (for debugging purpose only)
   
   delay_ms(1000);
   do
   {
      power_check();
      if(p_occured == TRUE)   // Power is OFF, restart power_loop_counter.
      {
         power_loop_counter=0;
         p_occured = FALSE;
      }
      delay_ms(10);
      power_loop_counter++;
   }
   while(power_loop_counter<200);
   two_sec_passed = TRUE;     // to indicate that two seconds have passed.
   /////////////////////////////////////////////////////////////////////////////
   
   setup_wdt(wdt_off);
   
   setup_adc_ports(no_analogs); setup_adc(adc_off);
   setup_timer_0(rtcc_internal | rtcc_div_4);   // Used to measure frequency
   setup_timer_1(t1_internal | t1_div_by_8);    // Used with IR routine
   enable_interrupts(global);
   
   setup_wdt(wdt_on);               // turn on WDT
   
   strb_sel();                      // AEI or ARL Compatibility function.
   
   if(first_start==1)               // Very first time power on OR after power 
   {                                // restore, reload all the parameters stroed
      restart_wdt();                // in EEPROm
      
      ee_flag=mreadbyte(51); delay_ms(1);
      if(ee_flag==255)              // after programming, first time store all 
      {                             // zeros in first 50 locations
         for(loop=0;loop<=50;loop++)
         {
            mwritebyte(loop,0);
         }
         ee_flag=0;   
         mwritebyte(51,ee_flag);
      }
      
      ir_enter_count=mreadword(35); delay_ms(1);// How many times enter in IR.
      solenoid1=mreadbyte(1); delay_ms(1);      // solenoid 1 freq value
      solenoid2=mreadbyte(2); delay_ms(1);      // solenoid 2 freq value
      solenoid3=mreadbyte(3); delay_ms(1);      // solenoid 3 freq value
            
      calibration=mreadbyte(4); delay_ms(1);    // calibration value
      
      temp8=calibration;
      hundred=temp8/100;
      temp8=temp8-(hundred*100);
      tens=temp8/10;
      ones=temp8-(tens*10);
      no_of_pulses1=(hundred*10) + tens;
      no_of_pulses2=no_of_pulses1 + 1;
      no_of_time1=10-ones;
      no_of_time2=ones;
      
      if(no_of_time2==0) no_perform=1;
      else no_perform=0;
            
      wait_time=mreadbyte(5); delay_ms(1);         // wait time value
      
      cutoff_freq_flag=mreadbyte(6); delay_ms(1);  // excess frequecy flag
      
      excess_freq=mreadbyte(7); delay_ms(1);       // excess frequecy value
      
      no_flow_time=mreadbyte(8); delay_ms(1);      // no flow time value
      //no_flow_attempts=mreadbyte(9); delay_ms(1);  // no flow attepmts value
      actuator=mreadbyte(10); delay_ms(1);         // actuator/solenoid process
      
      rate_tens=mreadbyte(11); delay_ms(1);        // rate tens value
      rate_ones=mreadbyte(12); delay_ms(1);        // rate ones value
      rate_tenth=mreadbyte(13); delay_ms(1);       // rate tenth value
      rate_hundredth=mreadbyte(14); delay_ms(1);   // rate hundredth value
      rate_hundred=mreadbyte(15); delay_ms(1);     // rate hundred value
      
      rate=((rate_hundred*100)+(rate_tens*10) + (rate_ones*1) + // converting 
            (rate_tenth*0.1) + (rate_hundredth*0.01));   // rate values to float
      
      totalizer1=mread32(16); delay_ms(1);         // totalizer 1 value
      totalizer2=mread32(20); delay_ms(1);         // totalizer 2 value
      grams_10=mreadbyte(24); delay_ms(1);         // mech counter kg
      
      weight=mread32(25); delay_ms(1);             // filling weight value
      ram_weight[0]=weight;
      
      int_amount = mread32(31); delay_ms(1);       // last filling amount
      amount=int_amount*0.01;      
      ram_rupees[0]=amount;
      kilograms = weight/100;
            
      format_data();
      show_on_lcd();
      
      first_start=0;  loop=0;      // enter once only after power UP
      load_ram=1;
   }
   
   while(true)
   {
      
      restart_wdt();      
      power_check();

      //////////////////////////////// Switch ON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
      if(input(sel_switch))      // if switch is on
      {
         restart_wdt();
         if(disp_pattern==1)
         {
            disp_pattern=0;
            disp_888();          // show 888 pattern
            delay_250();   delay_250(); 
            
            if(!input(sel_switch))  //If switch is off, then go to IR routine
            {
               ir=1; menu_again=0;
               ir_routine();
            }
            else 
            {
               clear_888();      // Clear 888 pattern
               delay_250();   delay_250();                
               filling=1; 
            }
            
            if(filling==1)
            {
               ram_weight[2]=ram_weight[1];
               ram_weight[1]=ram_weight[0];
               ram_weight[0]=weight;
               
               ram_rupees[2]=ram_rupees[1];
               ram_rupees[1]=ram_rupees[0];
               ram_rupees[0]=amount;
            
               start=1; filling_state=1; one_time=0;
               calib_check=0; pulse_counter=0; calib_cntr=0; vol=0;
               weight=0; filling=0; no_flow=1; no_flow_timer=0; 
               no_flow_timer1=0; wait_timer1_1=0; wait_timer1_2=0;
               settling_timer=0; settling_flag=0; filling_state_timer=0;
               wait_timer2_1=0; wait_timer2_2=0; cut_off_timer=0;
               filling_start=1; filling_performed=0; filling_ended=0;
               load_ram=0; 
                              
               if(kp_rupees==0)
               {
                  full_filling=1;
                  kp_weight=0; kp_iweight=0; kp_rupees=0;
               }
               else 
               {
                  full_filling=0;
                  kp_weight = kp_rupees/rate;
                  kp_iweight = kp_weight*100;
               }
               
               kp_n=9;                                               
               value_from_kp();
               
               sol_freq=solenoid1;     // load Solenoid 1 value
               solenoid1_freq=s_lookup_table();
                              
               sol_freq=solenoid2;     // load Solenoid 2 value
               solenoid2_freq=s_lookup_table();
                                 
               sol_freq=solenoid3;     // load Solenoid 3 value
               solenoid3_freq=s_lookup_table();
               
               if(cutoff_freq_flag==1) // If excess flow control enabled
               {
                  sol_freq=excess_freq;   // load Excess frequency value
                  cut_off_freq=freq_lookup_table();
               }
               
               if(actuator==0)         // if solenoid process all solenoids on
               {
                  output_low(low_sol);    
                  output_low(med_sol); 
                  output_low(high_sol);
               }
               else if(actuator==1)    // if actuator process high actuator on
               {
                  output_high(low_sol);
                  output_high(med_sol); 
                  output_low(high_sol);
               }
               
               clear_interrupt(int_ext);
               ext_int_edge(0,l_to_h); enable_interrupts(int_ext);
               
            }//if(filling==1)
            
            else filling=0;
            
         }//if(disp_pattern==1)
         
         format_data();                // format data according to lcd segments
         show_on_lcd();                // show on LCD
         
         if(one_time==1)               // if 200gm gas has been filled 
         {
            //<!---------------------Filling State ONE----------------------!>//
            if(filling_state==1)
            {
               if(actuator==1)         // if actuator process
               {
                  if(settling_flag == 0)  // 2 sec delay for actuator settling
                  {
                     settling_timer++;
                     
                     output_low(low_sol);    // low actuator ON
                     output_high(high_sol);  // high actuator OFF
                                          
                     if(settling_timer>=80)  // 2 sec delay approx
                     {
                        settling_timer=0;
                        settling_flag=1;
                     }
                  }
                  
                  // if frequency greater than menu 1 frequency
                  if(filling_freq <= solenoid1_freq && settling_flag==1)
                  {
                     output_low(low_sol);    // low actuator ON
                     filling_state_timer=0;
                  }
                  
                  // if frequency less than menu 1 frequency
                  else if (filling_freq > solenoid1_freq && settling_flag==1)
                  {
                     filling_state_timer++;
                     if(filling_state_timer>=10)   // 250ms delay
                     {
                        filling_state=2; settling_timer=0; settling_flag=0;
                        filling_state_timer=0;                         
                     }
                  }                  
               }//if(actuator==1)
               
               else if(actuator==0)    // if solenoid process
               {     
                  //frequency greater than menu 1
                  if(filling_freq <= solenoid1_freq) 
                  {
                     output_low(low_sol);    // low solenoid on
                     output_high(med_sol);   // medium solenoid off
                     output_high(high_sol);  // high solenoid off                   
                     filling_state_timer=0;
                  }
                  
                  //frequency less than menu 1
                  else if (filling_freq > solenoid1_freq)
                  {
                     filling_state_timer++;
                     if(filling_state_timer>=20) // 500ms delay approx 
                     {
                        filling_state=2; 
                        filling_state_timer=0;                         
                     }
                  }                  
               }//else if(actuator==0)
            }//if(filling_state==1)
            //<!-------------------Filling State ONE END--------------------!>//
            
            //<!---------------------Filling State TWO----------------------!>//            
            else if(filling_state==2)
            {
               if(actuator==1)   // if actuator process
               {
                  if(settling_flag == 0) // 2 sec delay for actuator settling
                  {
                     settling_timer++;
                     
                     output_low(med_sol);    // Medium actuator on
                     output_high(low_sol);   // Low actuator off
                     
                     if(settling_timer>=80)  // 2 sec delay approx
                     {
                        settling_timer=0;
                        settling_flag=1;
                     }
                  }
                  
                  // if frequency greater than menu 2 frequency                  
                  if(filling_freq <= solenoid2_freq && settling_flag==1)
                  {
                     output_low(med_sol);    // medium actuator on                    
                     filling_state_timer=0;
                  }
                  
                  // if frequency less than menu 2 frequency
                  else if (filling_freq > solenoid2_freq && settling_flag==1)
                  {
                     filling_state_timer++;
                     if(filling_state_timer>=10)   // 250ms delay
                     {
                        filling_state=3; settling_timer=0; settling_flag=0;
                        filling_state_timer=0; 
                     }
                  }
               }//if(actuator==1)
               
               else if(actuator==0) // if solenoid process
               {
                  //frequency greater than menu 2
                  if(filling_freq <= solenoid2_freq)
                  {
                     output_low(low_sol);    // low solenoid on 
                     output_low(med_sol);    // medium solenoid on
                     output_high(high_sol);  // high solenoid off
                     filling_state_timer=0;
                  }
                  
                  //frequency less than menu 2
                  else if (filling_freq > solenoid2_freq)
                  {
                     filling_state_timer++;
                     if(filling_state_timer>=20) // 500ms delay approx 
                     {
                        filling_state=3; 
                        filling_state_timer=0;                       
                     }
                  }   
               }//else if(actuator==0)
            }//else if(filling_state==2)
            //<!-------------------Filling State TWO END--------------------!>//
            
            //<!--------------------Filling State THREE---------------------!>//           
            else if (filling_state==3)
            {
               if(actuator==1)   // if actuator process
               {
                  if(settling_flag == 0)  // 2 sec delay for actuator settling
                  {
                     settling_timer++;
                     output_low(high_sol);   // high actuator on
                     output_high(med_sol);   // medium actuator off
                     
                     if(settling_timer>=80)  // 2 sec delay approx
                     {
                        settling_timer=0;
                        settling_flag=1;                        
                     }
                  }
                  
                  // if frequency greater than menu 1 frequency
                  if(filling_freq <= solenoid3_freq && settling_flag==1)
                  {
                     output_low(high_sol);   // high actuator on
                     filling_state_timer=0;
                     wait_timer2_1=0;
                  }
                  
                  // if frequency less than menu 1 frequency     
                  else if (filling_freq > solenoid3_freq && settling_flag==1)
                  {
                     wait_timer2_1++;     // increment wait timer                   
                  }
               }//if(actuator==1)
               
               else if(actuator==0)    // if siolenoid process
               {
                  if(filling_freq <= solenoid3_freq)
                  {
                     output_low(low_sol);    // low solenoid on
                     output_low(med_sol);    // medium solenoid on
                     output_low(high_sol);   // high solenoid on
                     
                     filling_state_timer=0;
                     wait_timer2_1=0;
                  }
                  
                  else if (filling_freq > solenoid3_freq)
                  {
                     wait_timer2_1++;     // increment wait timer
                  }
               }//else if(actuator==0)
            }//else if (filling_state==3)
            //<!------------------Filling State THREE END-------------------!>//
            
            //<!--------------------EXCESS FLOW CONTROL---------------------!>//
            if(cutoff_freq_flag==1)       // if excess flow control enabled
            {
               // if frequency greater than excess frequency
               if(filling_freq<cut_off_freq) 
               {
                  cut_off_timer++;
                  if(cut_off_timer>=40)   // 1 sec delay approx
                  {
                     disable_interrupts(int_ext);
                     output_high(low_sol);   // low solenoid off
                     output_high(med_sol);   // medium solenoid off
                     output_high(high_sol);  // high solenoid off
                     filling_ended=1;
                     filling_start=0;
                     cut_off_timer=0;
                     one_time=0; filling_state=0;
                  }
               }
            }//if(cutoff_freq_flag==1)
            //<!------------------EXCESS FLOW CONTROL END-------------------!>//
            
            wait_timer1_1++;
            if(wait_timer1_1>=40 || wait_timer2_1>=40)
            {
               wait_timer1_2++; wait_timer2_2++;               
               wait_timer1_1=0; wait_timer2_1=0;
               if(wait_timer1_2 >= wait_time || wait_timer2_2 >= wait_time)
               {
                  disable_interrupts(int_ext);
                  output_high(low_sol);   // low solenoid off
                  output_high(med_sol);   // medium solenoid off
                  output_high(high_sol);  // high solenoid off
                  filling_ended=1;
                  filling_start=0;
                  wait_timer1_2=0; wait_timer2_2=0;
                  one_time=0; filling_state=0;
               }
            }
         }//if(one_time==1)
         
         if(mech_led==1)            // Increemnts Kg on Mechanical counter
         {
            output_low(mech_counter);
            loop++;
            if(loop>=25)            // 500ms delay approx
            {
               output_high(mech_counter);
               mech_led=0; loop=0;
            }
         }//if(mech_led==1)
         
         if(no_flow==1)    //if gas does not flow, then increment the timer and 
         {                 // close solenoids after time over
            no_flow_timer++;
            if(no_flow_timer==40)
            {
               no_flow_timer=0; 
               no_flow_timer1++;
               if(no_flow_timer1>=no_flow_time)
               {
                  disable_interrupts(int_ext);      
                  no_flow=0;
                  filling_ended=1;
                  filling_start=0;
                  output_high(low_sol);   // low solenoid off
                  output_high(med_sol);   // medium solenoid off
                  output_high(high_sol);  // high solenoid off
               }
            }
         }//if(no_flow==1)
      }//if(input(sel_switch))
      ////////////////////////////// Switch ON END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
      
      /////////////////////////////// Switch OFF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
      else if(!input(sel_switch))      // if switch is OFF
      {
         restart_wdt();
         disp_pattern=1;
         
         if(filling_ended==0)
         {
            disable_interrupts(int_ext);  
            output_high(low_sol);      // low solenoid off
            output_high(med_sol);      // medium solenoid off
            output_high(high_sol);     // high solenoid off
            delay_ms(1);
            format_data();
            filling_start=0; filling_ended=1; one_time=0;
         }
         
         if(mech_led==1)   //if mech totalizer is not incremented in filling 
         {                 // state, then increment the counter.
            output_low(mech_counter);
            loop++;
            if(loop>=25)
            {
               output_high(mech_counter);
               mech_led=0; loop=0;
            }
         }//if(mech_led==1)
         
         if(filling_performed==0 && load_ram==0 ) // if filling not performed
         {                 // then load previous filled KG and amount from RAM.  
            weight=ram_weight[0];    
            ram_weight[0]=ram_weight[1]; 
            ram_weight[1]=ram_weight[2];
    
            amount=ram_rupees[0];   
            ram_rupees[0]=ram_rupees[1];
            ram_rupees[1]=ram_rupees[2];            
         
            kilograms = weight*0.01;
            load_ram=1;
            kp_rupees=0;
         }
         
         if(filling_performed==1 && load_ram==0)   //if new filling is performed
         {                       // then store new filling KG and amount in RAM.
            ram_weight[2]=ram_weight[1];
            ram_weight[1]=ram_weight[0]; 
            ram_weight[0]=weight;   
    
            ram_rupees[2]=ram_rupees[1];
            ram_rupees[1]=ram_rupees[0];
            ram_rupees[0]=amount;   
            
            kp_rupees=0;
            load_ram=1;
         }
                
         read_keypad();    // read and scans keypad
         
         if(kp_pressed==1) // if any key pressed ?
         {
            value_from_kp();
            kp_rupees=kp_value;
            
            lcd_data[0]=0x0A; lcd_data[1]=0x1A; lcd_data[2]=0x2A;
            lcd_data[3]=0x3A; lcd_data[4]=0x4A; lcd_data[8]=0x8A; 
            lcd_data[9]=0x9A; lcd_data[10]=0xAA; lcd_data[11]=0xBA;
            lcd_data[14]=0xEA;
         }
         else
         {
            format_data();             // format data according to lcd segments
         }
         show_on_lcd();                // show on LCD
         
         if(remaining_cntr==1)   //if filling is not started with in time, after
         {              //entering values from KP, then set KP rupeesto "0".                                              
            remaining_time--;                                                       
            if(remaining_time<=1)
            {                       
               kp_n=9;
               value_from_kp();        
               kp_rupees=kp_value;
               remaining_time=1250; remaining_cntr=0; keypad_time=0;
            }
         }
         
      }//else if(!input(sel_switch))
      ///////////////////////////// Switch OFF END \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
   
   }//while(true)

}//void main()
