void ir_routine(void)
{
   ext_int_edge(2,h_to_l);          // configure ext interrupt pin 2, to capture                                       
   clear_interrupt(int_ext2);       // IR stream
   enable_interrupts(int_ext2);
   
   while(ir==1)                     
   {
      restart_wdt();
      power_check();                // power available
      if(input(sel_switch))         // check if switch is on
      {                             // disable IR interrupt and exit the IR func
         ir=0; disp_pattern=1; ir_key_press2=0;         
         disable_interrupts(INT_EXT2);  
         disable_interrupts(INT_TIMER1);
      }
      
          
      if(ir_key_press2==1 && menu==0) //if key pressed other than menu key then
      {                                // display last filling values 
         format_data();
         show_on_lcd();
      }
      
      if(menu==1)                      // if menu key is pressed
      {
         clear_lcd();                  // blank the lcd
         
         menu_timer++;
         if(menu_timer==400)           // if no key is pressed with in certain 
         {                             // tine, set menu flag to zero.
            menu_timer=0; menu=0; total_1=0; total_2=0;          
         }
         
         if(ir_enter_flag==1 && menu_again==0)          //IF menu key is pressed, this counter 
         {                             // will increment. The value will be  
            ir_enter_count++;          // shown in menu F2 
            ir_enter_flag=0; menu_again=1;
            mwriteword(35,ir_enter_count);  delay_ms(1);
         }
         
         if(ir_key_press==1)
         {
            if(command==0x01)          // If key "1" is pressed
            {                          // solenoid 1 setting menu.
               w1++;
               if(w1>=5)
               {
                  w1=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  solenoid1=parameters_values(solenoid1,1);
                  if(solenoid1>30)
                  {              
                     solenoid1=30;
                  }
                  else if(solenoid1<2) 
                  {                  
                     solenoid1=2;
                  }
                  mWriteByte(1,solenoid1);delay_ms(1);
               }
            }//if(command==0x01)
            
            else if(command==0x02)     // If key "2" is pressed
            {                          // solenoid 2 setting menu.
               w2++;
               if(w2>=5)
               {
                  w2=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  solenoid2=parameters_values(solenoid2,2);
                  if(solenoid2>30)
                  {              
                     solenoid2=30;
                  }
                  else if(solenoid2<2) 
                  {                  
                     solenoid2=2;
                  }
                  mWriteByte(2,solenoid2);delay_ms(1);
               }
            }//else if(command==0x02)
            
            else if(command==0x03)  // If key "3" is pressed
            {                          // solenoid 3 setting menu.
               w3++;
               if(w3>=5)
               {
                  w3=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  solenoid3=parameters_values(solenoid3,3);
                  if(solenoid3>30)
                  {              
                     solenoid3=30;
                  }
                  else if(solenoid3<2) 
                  {                  
                     solenoid3=2;
                  }
                  mWriteByte(3,solenoid3);delay_ms(1);
               }
            }//else if(command==0x03)
            
            else if(command==0x04)  // If key "4" is pressed
            {                       // calibration setting menu
               w4++;
               if(w4>=5)
               {
                  w4=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  calibration=parameters_values(calibration,4);
                  if(calibration>254)
                  {
                     calibration=10;
                  }
                  else if(calibration<10)
                  {
                     calibration=10;
                  }
                  
                  mWriteByte(4,calibration);delay_ms(1);
                  
                  no_of_pulses1=(hundred*10) + tens;
                  no_of_pulses2=no_of_pulses1 + 1;
                  no_of_time1=10-ones;
                  no_of_time2=ones;
      
                  if(no_of_time2==0)
                  {
                     no_perform=1;
                  }
                  else
                  {
                     no_perform=0;
                  }
               }
            }//else if(command==0x04)
            
            else if(command==0x05)  // If key "5" is pressed
            {                       // wait time setting menu, if pulses stops
               w5++;                // during filling, then wait for certain 
               if(w5>=5)            // time, before clocing solenoids.  
               {
                  w5=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  wait_time=parameters_values(wait_time,5);
                  mWriteByte(5,wait_time);delay_ms(1);
               }
            }//else if(command==0x05)
            
            else if(command==0x06)  // If kwy "6" is pressed.
            {                       //resets some parameters to factory setting.
               w6++;
               if(w6>=5)
               {
                  
                  w6=0; menu=0; menu_timer=0; 
                  restart_wdt();
                     
                  solenoid1=7;
                  mWriteByte(1,solenoid1);delay_ms(1);
                     
                  solenoid2=15;
                  mWriteByte(2,solenoid2);delay_ms(1);
                    
                  solenoid3=30;
                  mWriteByte(3,solenoid3);delay_ms(1);
                     
                  calibration=171;
                  mWriteByte(4,calibration);delay_ms(1);
                  temp8=calibration;
                  hundred=temp8/100;
                  temp8=temp8-(hundred*100);
                  tens=temp8/10;
                  ones=temp8-(tens*10);
                  no_of_pulses1=(hundred*10) + tens;
                  no_of_pulses2=no_of_pulses1 + 1;
                  no_of_time1=10-ones;
                  no_of_time2=ones;
      
                  if(no_of_time2==0)
                  {
                     no_perform=1;
                  }
                  else
                  {
                     no_perform=0;
                  }
                     
                  wait_time=5;
                  mWriteByte(5,wait_time);delay_ms(1);
                  
                  cutoff_freq_flag=1;
                  mwritebyte(6,cutoff_freq_flag); delay_ms(1);
                  
                  excess_freq=5;
                  mWriteByte(7,excess_freq);delay_ms(1);   
                  
                  no_flow_time=5;
                  mWriteByte(8,no_flow_time);delay_ms(1);
                  
                  actuator=0;
                  mWriteByte(10,actuator);delay_ms(1);
                        
                  rate_hundred = 4; rate_tens=5; rate_ones=6; rate_tenth=7; 
                  rate_hundredth=8;
                  mWriteByte(11,rate_tens);delay_ms(1);
                  mWriteByte(12,rate_ones);delay_ms(1);
                  mWriteByte(13,rate_tenth);delay_ms(1);
                  mWriteByte(14,rate_hundredth);delay_ms(1); 
                  mWriteByte(15,rate_hundred);delay_ms(1);
                  
                  rate=((rate_hundred*100)+(rate_tens*10) + (rate_ones*1) +
                        (rate_tenth*0.1) + (rate_hundredth*0.01));
               }
            }//else if(command==0x06)
        
            else if(command==0x07)  // If key "7" is pressed
            {                       // excess flow (cutoff) freq, setting menu.
               w7++;
               if(w7>=5)
               {
                  w7=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  excess_freq=parameters_values(excess_freq,7);
                  if(excess_freq==0)
                  {
                     cutoff_freq_flag=0;
                  }                  
                  if(excess_freq>35)
                  {                
                     excess_freq=35; cutoff_freq_flag=1;
                  }
                  else if(excess_freq<5 && excess_freq!=0)
                  {                    
                     excess_freq=5; cutoff_freq_flag=1;
                  }
                  mwritebyte(6,cutoff_freq_flag); delay_ms(1);
                  mWriteByte(7,excess_freq);delay_ms(1);
               }
            }//else if(command==0x07)
            
            else if(command==0x08)  // If key "8" is pressed
            {                       // wait time setting menu, if no filling 
               w8++;                // accurs after switch on, then wait for 
               if(w8>=5)            // certain time, before closing solenoids.
               {
                  w8=0; enter=1; menu=0; menu_timer=0; inc_1=0;
                  no_flow_time=parameters_values(no_flow_time,8);
                  mWriteByte(8,no_flow_time);delay_ms(1);
               }
            }//else if(command==0x08)
            
            else if(command==0x09)  // If key "9" is pressed
            {                       // if no filling accurs, a counter is 
               w9++;                // incremented in the main routine. and is 
               if(w9>=5)            // comapred with the value in menu 9.
               {                    // Number of no flow attempts.         
                  w9=0; enter=1; menu=0; menu_timer=0; inc_1=1;
                  //no_flow_attempts=parameters_values(no_flow_attempts,9);
                  //if(no_flow_attempts>5)
                  //{                
                  //   no_flow_attempts=5;
                  //}
                  //else if(no_flow_attempts<3)
                  //{                    
                  //   no_flow_attempts=3;
                  //}
                  //mWriteByte(9,no_flow_attempts);delay_ms(1);
               }
            }//else if(command==0x09)
            
            else if(command==0xC8 || command==0x82)  // if key is "F2 or Setup"
            {                          // pressed. This menu is used to unlock                         
               w10++;                  // solenoids. 
               if(w10>=5)
               {
                  w10=0; enter=1; menu=0; menu_timer=0; time_remain=0;                                    
                  while(enter==1)
                  {
                     restart_wdt();
                     time_remain++;
                     //no_flow_attempt=0; lock_solenoid=0; switch_counter=0;
                     
                     lcd_data[0]=0x0A;lcd_data[1]=0x1A;lcd_data[2]=0x2A;
                     lcd_data[3]=0x3A;lcd_data[4]=0x4A;lcd_data[5]=0x50;
                     lcd_data[6]=0x60;lcd_data[7]=0x70;lcd_data[8]=0x8A;
                     lcd_data[9]=0x9A;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
                     lcd_data[12]=0xC0;lcd_data[13]=0xD0;lcd_data[14]=0xEA;
                     lcd_data[15]=0xF0;
                  
                     show_on_lcd();
                     
                     if(command==0x5C || time_remain>=500)
                     {                                                
                        enter=0; time_remain=0;
                        //mWriteByte(29,lock_solenoid);delay_ms(1);
                        //mWriteByte(30,no_flow_attempt);delay_ms(1);
                     }           
                  }
               }
            }//else if(command==0xC8 || command==0x82)
            
            else if(command==0x83)  //if key "F3 or Title" is pressed
            {                       // displays the value of IR counter.
               w11++;
               if(w11>=5)
               {
                  w11=0; enter=1; menu=0; menu_timer=0; time_remain=0;
                  while(enter==1)
                  {
                     restart_wdt();
                     time_remain++;
                     
                     temp32=ir_enter_count;
                     hundred=(temp32/10000)%10;
                     tens=(temp32/1000)%10;
                     ones=(temp32/100)%10;
                     tenth=(temp32/10)%10;
                     hundredth=(temp32%10);
                     
                     if(ir_enter_count>=9999)
                     {
                        ir_enter_count=0;
                     }
                     
                     lcd_data[13]=ad13*16 + hundred;
                     lcd_data[12]=ad12*16 + tens;
                     lcd_data[15]=ad15*16 + ones;
                     lcd_data[5]=ad5*16 + tenth;
                     lcd_data[6]=ad6*16 + hundredth;
        
                     if(ir_enter_count==0)
                     {
                       lcd_data[13]=0xD0;lcd_data[12]=0xC0;lcd_data[15]=0xF0;
                       lcd_data[5]=0x50;lcd_data[6]=0x60;
                     }
                     else if(ir_enter_count>=1 && ir_enter_count<10)
                     {                  
                        lcd_data[13]=0xD0;lcd_data[12]=0xC0;lcd_data[15]=0xF0;
                        lcd_data[5]=0x50;
                     }                                                  
                     else if(ir_enter_count>=10 && ir_enter_count<100)   
                     {                                        
                        lcd_data[13]=0xD0;lcd_data[12]=0xC0;lcd_data[15]=0xF0;
                     }
                     else if(ir_enter_count>=100 && ir_enter_count<1000)   
                     {                                        
                        lcd_data[13]=0xD0;lcd_data[12]=0xC0;
                     }
                     else if(ir_enter_count>=1000 && ir_enter_count<10000)   
                     {                                        
                        lcd_data[13]=0xD0;
                     }
                     
                     lcd_data[0]=0x0A;lcd_data[1]=0x1A;lcd_data[2]=0x2A;
                     lcd_data[3]=0x3A;lcd_data[4]=0x4A;lcd_data[8]=0x8A;
                     lcd_data[9]=0x9A;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
                     lcd_data[14]=0xEA;lcd_data[7]=0x7A;
                                            
                     show_on_lcd();
                     
                     if(command==0x5C || time_remain>=2620) //exit the loop
                     {
                        enter=0; time_remain=0;     
                     }
                  }      
               }
            }//else if(command==0x83)
            
            else if(command==0x4B)  // if key "200 or Subtitle" is pressed
            {                       // selects actuator or solenoid process.
               w12++;               // 1 for actuator, 0 for solenoid
               if(w12>=5)
               {
                  w12=0; ;enter=1; menu=0; menu_timer=0; time_remain=0;
                  while(enter==1)
                  {
                     restart_wdt();
                     time_remain++;
                     
                     if(command==0x08)
                     {
                        time_remain=0;
                        command=0x0C;
                        actuator=1;
                     }
                     
                     else if(command==0x09)
                     {
                        time_remain=0;
                        command=0x0C;
                        actuator=0;
                     }
                     
                     lcd_data[5]=ad5*16 + actuator;
                     lcd_data[6]=ad6*16 + (0x01);
                     lcd_data[7]=ad7*16 + (0x00);
                     
                     lcd_data[0]=0x0A;lcd_data[1]=0x1A;lcd_data[2]=0x2A;
                     lcd_data[3]=0x3A;lcd_data[4]=0x4A;lcd_data[8]=0x8A;
                     lcd_data[9]=0x9A;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
                     lcd_data[12]=0xCA;lcd_data[13]=0xDA;lcd_data[14]=0xEA;
                     lcd_data[15]=0xFA;
                     
                     show_on_lcd();
                     
                     if(command==0x5C || time_remain>=2620)
                     {
                        mWriteByte(10,actuator);delay_ms(1);
                        enter=0; time_remain=0; menu_timer=0;
                     }
                  }
               }
            }//else if(command==0x4B)
            
            else if(total_1==1)  //if total key is pressed.
            {                       // Menu is used to set rate
               w13++;
               if(w13>=5)
               {
                  w13=0; enter=1; menu=0; menu_timer=0;
                  
                  ir_rate[0]=rate_hundredth;
                  ir_rate[1]=rate_tenth;
                  ir_rate[2]=rate_ones;
                  ir_rate[3]=rate_tens;
                  ir_rate[4]=rate_hundred;
                  
                  while(enter==1)
                  {
                     restart_wdt();
                  
                     if(numeric==1)
                     {            
                        numeric=0; 
                        ir_rate[4]=ir_rate[3]; ir_rate[3]=ir_rate[2];
                        ir_rate[2]=ir_rate[1]; ir_rate[1]=ir_rate[0]; 
                        ir_rate[0]=command;
                     }
                     
                     lcd_data[1]=ad1*16 + ir_rate[2];      
                     lcd_data[3]=ad3*16 + ir_rate[1];          
                     lcd_data[4]=ad4*16 + ir_rate[0];                  
                     lcd_data[8]=ad8*16 + ir_rate[3];
                     lcd_data[9]=ad9*16 + ir_rate[4];
                     
                     lcd_data[0]=0x0A;lcd_data[2]=0x2A;lcd_data[5]=0x5A;
                     lcd_data[6]=0x6A;lcd_data[7]=0x7A;lcd_data[10]=0xAA;
                     lcd_data[11]=0xBA;lcd_data[12]=0xCA;lcd_data[13]=0xDA;
                     lcd_data[14]=0xEA;lcd_data[15]=0xFA;
        
                     rate=((ir_rate[4]*100)+(ir_rate[3]*10) + (ir_rate[2]*1) + (ir_rate[1]*0.1) + (ir_rate[0]*0.01));                    
                     
                     show_on_lcd();
                                          
                     if(command==0x5C)
                     {                                                 
                        enter=0; 
                        rate_hundredth=ir_rate[0];
                        rate_tenth=ir_rate[1];
                        rate_ones=ir_rate[2];
                        rate_tens=ir_rate[3];
                        rate_hundred=ir_rate[4];
                        
                        mWriteByte(11,rate_tens);delay_ms(1);
                        mWriteByte(12,rate_ones);delay_ms(1);
                        mWriteByte(13,rate_tenth);delay_ms(1);
                        mWriteByte(14,rate_hundredth);delay_ms(1);   
                        mWriteByte(15,rate_hundred);delay_ms(1); 
                     }  
                  }
               }
            }//else if(command==0x0f)     
            else                         
            {
               w1=0;w2=0;w3=0;w5=0;w6=0;w7=0;w8=0;w9=0;w10=0;w11=0;w12=0;w13=0;
            } 
         }//if(ir_key_press==1)
         ir_key_press=0;
      }//if(menu==1)
      
      else if(total_1==1)
      {   
         
         temp32=totalizer1;
         lakh=temp32/10000000;
         tenthousand=(temp32/1000000)%10;
         thousand=(temp32/100000)%10;
         hundred=(temp32/10000)%10;
         tens=(temp32/1000)%10;
         ones=(temp32/100)%10;
         tenth=(temp32/10)%10;
         hundredth=(temp32%10);
         
         
         lcd_data[13]=ad13*16 + lakh*1;
         lcd_data[12]=ad12*16 + tenthousand*1;
         lcd_data[15]=ad15*16 + thousand*1;
         lcd_data[5]=ad5*16 + hundred*1;
         lcd_data[6]=ad6*16 + tens*1;
         lcd_data[7]=ad7*16 + ones*1;
         lcd_data[2]=ad2*16 + tenth*1;
         lcd_data[0]=ad0*16 + hundredth*1;
   
         //if total_kg is 0 then LCD pattern is like that.
         if(totalizer1==0)
         {
            lcd_data[5]=0x5A;lcd_data[6]=0x60;lcd_data[7]=0x70;
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;lcd_data[10]=0xAA;
            lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[2]=0x20;
            lcd_data[0]=0x00;
         }
         //if total_kg is from 1 to 9 then LCD pattern is like that.
         else if(totalizer1>=1 && totalizer1<10)
         {                  
            lcd_data[5]=0x5A;lcd_data[6]=0x6A;lcd_data[7]=0x7A;
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;lcd_data[10]=0xAA;
            lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[2]=0x2A;
         }                                                  
         //if total_kg is from 10 to 99 then LCD pattern is like that.
         else if(totalizer1>=10 && totalizer1<100)   
         {                                        
            lcd_data[5]=0x5A;lcd_data[12]=0xCA;lcd_data[13]=0xDA;
            lcd_data[15]=0xFA;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
            lcd_data[6]=0x6A;lcd_data[7]=0x7A;
         }
         //if total_kg is from 100 to 999 then LCD pattern is like that.
         else if(totalizer1>=100 && totalizer1<1000)   
         {                                        
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;lcd_data[10]=0xAA;
            lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[5]=0x5A;
            lcd_data[6]=0x6A;
         }
         //if total_kg is from 1000 to 9999 then LCD pattern is like that.
         else if(totalizer1>=1000 && totalizer1<10000)   
         {                                        
            lcd_data[12]=0xCA;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
            lcd_data[13]=0xDA;lcd_data[15]=0xFA;lcd_data[5]=0x5A;
         }
         //if total_kg is from 10000 to 99999 then LCD pattern is like that.
         else if(totalizer1>=10000 && totalizer1<100000)   
         {                                         
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;
         }
         //if total_kg is from 100000 to 999999 then LCD pattern is like that.
         else if(totalizer1>=100000 && totalizer1<1000000)   
         {                                        
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;
            lcd_data[12]=0xCA;
         }
         //if total_kg is from 1000000 to 9999999 then LCD pattern is like that.
         else if(totalizer1>=1000000 && totalizer1<10000000)
         {
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;
         }
         //if total_kg is from 10000000 to 99999999 then LCD pattern islike that
         else if(totalizer1>=10000000 && totalizer1<100000000)
         {
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;
         }
         //clear following segments.
         lcd_data[1]=0x1A;lcd_data[3]=0x3A;lcd_data[4]=0x4A;lcd_data[8]=0x8A;
         lcd_data[9]=0x9A;lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[14]=0xEA;
   
         show_on_lcd();
         enter=1;menu=0;total_1=0;//set some variables.
         while(enter==1) 
         {
            restart_wdt();
            delay_ms(2);//some delay is added.
            if(command==0x00)//0 is pressed.
            {               
               w14++;//increament flag.
               time_remain=0;
               command=0x0C;//change the command to 0C so that not enter again 
                            //in the loop.  
               if(w14>=5)//if flag equal to 5
               {
                  w14=0;total_1=0;//set some variables.
                  totalizer1=0;grams_10=0;//reset totalizer
                  mWriteByte(15,grams_10);delay_ms(1);//write in eeprom.
                  mWrite32(16,totalizer1);delay_ms(1);//write in eeprom.
                  //show total_kg 0000 when reset for some time
                  lcd_data[0]=0x00;lcd_data[1]=0x1A;lcd_data[2]=0x20;
                  lcd_data[3]=0x3A;lcd_data[4]=0x4A;lcd_data[5]=0x5A;
                  lcd_data[6]=0x60;lcd_data[7]=0x70;lcd_data[8]=0x8A;
                  lcd_data[9]=0x9A;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
                  lcd_data[12]=0xCA;lcd_data[13]=0xDA;lcd_data[14]=0xEA;
                  lcd_data[15]=0xFA;
                  
                  show_on_lcd();
                  
               }                                
            }
            if(command==0x5C || time_remain>=2000)//ok pressed or time out 
            { 
               enter=0; w14=0; menu_timer=0; time_remain=0;      
            }
            time_remain++;
         }
         
      }//else if(total==1 && check==1)
      
      else if(total_2==1)//if total key is pressed 
      {   
         //Breaking the total_kg values into seperate intergers for dispalying.
         temp32=totalizer2;
         lakh=temp32/10000000;
         tenthousand=(temp32/1000000)%10;
         thousand=(temp32/100000)%10;
         hundred=(temp32/10000)%10;
         tens=(temp32/1000)%10;
         ones=(temp32/100)%10;
         tenth=(temp32/10)%10;
         hundredth=(temp32%10);
         
         //saving values into lcd_data for displaying on LCD. 
         lcd_data[13]=ad13*16 + lakh*1;
         lcd_data[12]=ad12*16 + tenthousand*1;
         lcd_data[15]=ad15*16 + thousand*1;
         lcd_data[5]=ad5*16 + hundred*1;
         lcd_data[6]=ad6*16 + tens*1;
         lcd_data[7]=ad7*16 + ones*1;
         lcd_data[2]=ad2*16 + tenth*1;
         lcd_data[0]=ad0*16 + hundredth*1;
   
         //if total_kg is 0 then LCD pattern is like that.
         if(totalizer2==0)
         {
            lcd_data[5]=0x5A;lcd_data[6]=0x60;lcd_data[7]=0x70;
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;lcd_data[10]=0xAA;
            lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[2]=0x20;
            lcd_data[0]=0x00;
         }
         //if total_kg is from 1 to 9 then LCD pattern is like that.
         else if(totalizer2>=1 && totalizer2<10)
         {                  
            lcd_data[5]=0x5A;lcd_data[6]=0x6A;lcd_data[7]=0x7A;
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;lcd_data[10]=0xAA;
            lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[2]=0x2A;
         }                                                  
         //if total_kg is from 10 to 99 then LCD pattern is like that.
         else if(totalizer2>=10 && totalizer2<100)   
         {                                        
            lcd_data[5]=0x5A;lcd_data[12]=0xCA;lcd_data[13]=0xDA;
            lcd_data[15]=0xFA;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
            lcd_data[6]=0x6A;lcd_data[7]=0x7A;
         }
         //if total_kg is from 100 to 999 then LCD pattern is like that.
         else if(totalizer2>=100 && totalizer2<1000)   
         {                                        
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;lcd_data[10]=0xAA;
            lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[5]=0x5A;
            lcd_data[6]=0x6A;
         }
         //if total_kg is from 1000 to 9999 then LCD pattern is like that.
         else if(totalizer2>=1000 && totalizer2<10000)   
         {                                        
            lcd_data[12]=0xCA;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
            lcd_data[13]=0xDA;lcd_data[15]=0xFA;lcd_data[5]=0x5A;
         }
         //if total_kg is from 10000 to 99999 then LCD pattern is like that.
         else if(totalizer2>=10000 && totalizer2<100000)   
         {                                         
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;
            lcd_data[12]=0xCA;lcd_data[15]=0xFA;
         }
         //if total_kg is from 100000 to 999999 then LCD pattern is like that.
         else if(totalizer2>=100000 && totalizer2<1000000)   
         {                                        
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;
            lcd_data[12]=0xCA;
         }
         //if total_kg is from 1000000 to 9999999 then LCD pattern is like that.
         else if(totalizer2>=1000000 && totalizer2<10000000)
         {
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;
         }
         //if total_kg is from 10000000 to 99999999 then LCD pattern islike that
         else if(totalizer2>=10000000 && totalizer2<100000000)
         {
            lcd_data[10]=0xAA;lcd_data[11]=0xBA;
         }
         //clear following segments.
         lcd_data[1]=0x1A;lcd_data[3]=0x3A;lcd_data[4]=0x4A;lcd_data[8]=0x8A;
         lcd_data[9]=0x9A;lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[14]=0xEA;
   
         show_on_lcd();
         enter=1;menu=0;total_2=0;//set some variables.
         while(enter==1) 
         {
            restart_wdt();
            delay_ms(2);//some delay is added.
            
            if(command==0x5C || time_remain>=2000)//ok pressed or time out 
            {              
               enter=0; menu_timer=0; time_remain=0; 
            }
            time_remain++;
         }
         
      }//else if(total==1 && check==1)
   
      
   }//while(ir==1)
}//void ir_routine(void)




////////////////////////////////////////////////////////////////////////////////

int parameters_values(int value,int menu_no)
{
   int1 time_remain2_flag=0;
   unsigned int8 parameters=0,time_remain2=0;
   
   parameters=value;
   time_remain=0;
   
   while(enter==1)
   {
      restart_wdt();
      
      time_remain2++;
      if(time_remain2>=150)
      {
         time_remain2=0; time_remain2_flag=1;
      }
      
      if(command==0x08 && time_remain2_flag==1)
      {                                    
         time_remain=0;
         command=0x0C; 
         parameters=parameters+1;
      }
      else if(command==0x09 && time_remain2_flag==1)
      {                                         
         time_remain=0;
         command=0x0C;
         parameters=parameters-1;           
      }
      else if(command==0x05 && time_remain2_flag==1 && inc_1==0)
      {
         time_remain=0;
         command=0x0C; 
         parameters=parameters+10;
      }
      else if (command==0x06 && time_remain2_flag==1 && inc_1==0)
      {
         time_remain=0;
         command=0x0C; 
         parameters=parameters-10;
      }
      
      temp8=(int8)(parameters);
      hundred=temp8/100;
      temp8=temp8-(hundred*100);
      tens=temp8/10;
      ones=temp8-(tens*10);
      
       
      lcd_data[12]=ad12*16 + hundred;
      lcd_data[15]=ad15*16 + tens;
      lcd_data[5]=ad5*16 + ones;
     
      if(parameters<10)
      {
         lcd_data[15]=0xFA;lcd_data[12]=0xCA;            
      }
      else if(parameters>=10 && parameters<100)
      {
         lcd_data[12]=0xCA;
      }
      
      clear_segments();
      
      lcd_data[7]=ad7*16 + menu_no;
                                            
      show_on_lcd();
      
      if(command==0x5C || time_remain>=2620)
      {
         enter=0; time_remain=0; menu_timer=0; time_remain2_flag=0; 
         time_remain2=0;
      }
      time_remain++;
   }
   
   return parameters;
}

////////////////////////////////////////////////////////////////////////////////
void clear_segments()
{ 
   lcd_data[0]=0x0A;lcd_data[1]=0x1A;lcd_data[2]=0x2A;lcd_data[3]=0x3A;
   lcd_data[4]=0x4A;lcd_data[6]=0x6A;;lcd_data[8]=0x8A;lcd_data[9]=0x9A;
   lcd_data[10]=0xAA;lcd_data[11]=0xBA;lcd_data[13]=0xDA;lcd_data[14]=0xEA;
}
