void read_keypad(void)
{
   for(col_loop=0; col_loop<4; col_loop++)
   {
      kp_value1 = col_data[col_loop];
      dataout_kp();
      output_high(strobe_k);
      delay_us(10);
      output_low(strobe_k);      
   }
}

void dataout_kp(void)
{
   unsigned int8 z=0;
   kp_value2=0b00000001;
   for(z=0; z<8; z++)
   {
      kp_value3 = kp_value1 & kp_value2;   
      output_bit(data_pin,kp_value3);
      
      output_low(clock_pin); clock_status=0;
      delay_us(10);
      if(!input(key_pressed))
      {
         keypad_time++;
         if(keypad_time==1)
         {                                  
            remaining_cntr=1;
         }
         if(keypad_time>=2)
         {
            keypad_time=2;  
            remaining_time=1250;
         }                   
         
         kp_pressed=1;
         col=col_loop;
         scan_keypad();
         while(!input(key_pressed))
         {  
            restart_wdt();
         }
      }
      
      output_high(clock_pin); clock_status=1;
      delay_us(10);
      if(!input(key_pressed))
      {
         keypad_time++;
         if(keypad_time==1)
         {
            remaining_cntr=1;
         }
         if(keypad_time>=2)
         {
            keypad_time=2;
            remaining_time=1250;
         }
         
         kp_pressed=1;
         col=col_loop;
         scan_keypad();
         while(!input(key_pressed))
         {  
            restart_wdt();
         }
      }
      rotate_left(&kp_value2,1);
   }   
}


void scan_keypad(void)
{
   switch(col)
   {
      case 0:               
         if(kp_value3==0 && clock_status==0)    //key "50" is pressed
         {
            kp_n=5;
            kp_data[2]=0;
            kp_data[1]=5;
         }
         else if(kp_value3==1 && clock_status==0)  //key "100" is pressed
         {
            kp_n=6;
            kp_data[3]=0;
            kp_data[2]=0;
            kp_data[1]=1;
         }
         else if(kp_value3==0 && clock_status==1)  //key "150" is pressed
         {
            kp_n=7;                                         
            kp_data[3]=0;
            kp_data[2]=5;
            kp_data[1]=1;
         }
         else if(kp_value3==1 && clock_status==1)  //key "200" is pressed
         {
            kp_n=8;
            kp_data[3]=0;
            kp_data[2]=0;
            kp_data[1]=2;
         }
      break;
   
      case 1:               
         if(kp_value3==0 && clock_status==0)    //key "1" is pressed
         {
            key=1;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;            
         }
         else if(kp_value3==1 && clock_status==0)  //key "4" is pressed
         {
            key=4;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==0 && clock_status==1)  //key "7" is pressed
         {
            key=7;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==1 && clock_status==1)  //key "F1" is pressed
         {
            remaining_time=100;
            while(remaining_time>1)
            {
               restart_wdt();
       
               remaining_time--;
               weight=ram_weight[2];
               kilograms=weight;
               kilograms=kilograms*0.01;
               amount=ram_rupees[2];
               format_data();
               show_on_lcd();
            }
            
            weight=ram_weight[0];
            kilograms=weight;
            kilograms=kilograms*0.01;
            amount=ram_rupees[0];
            format_data();
            show_on_lcd();
            kp_n=9;
         }
      break;
   
      case 2:              
         if(kp_value3==0 && clock_status==0)    //key "2" is pressed
         {
            key=2;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==1 && clock_status==0)  //key "5" is pressed
         {
            key=5;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==0 && clock_status==1)  //key "8" is pressed
         {
            key=8;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==1 && clock_status==1)  //key "0" is pressed
         {
            key=0;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         } 
      break;
   
      case 3:              
         if(kp_value3==0 && clock_status==0)    //key "3" is pressed
         {
            key=3;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==1 && clock_status==0)  //key "6" is pressed
         {
            key=6;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         } 
         else if(kp_value3==0 && clock_status==1)  //key "9" is pressed
         {
            key=9;
            kp_n++;
            if(kp_n>4)
            { kp_n=1; }
            kp_data[kp_n]=key;
         }
         else if(kp_value3==1 && clock_status==1)  //key "F2" is pressed
         {
            kp_n=9;
         }
      break;
   }
}


void value_from_kp(void)
{
   switch(kp_n)
   {
      case 1:  //Format data when one key is entered from KP e.g. "9"
      {
         kp_data[4]=0;kp_data[3]=0;kp_data[2]=0;
         lcd_data[15]=0xFA;lcd_data[12]=0xCA;lcd_data[13]=0xDA; 
         kp_d0=ad5*16 + kp_data[1]*1;
         lcd_data[5]=kp_d0;lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_value=(kp_data[1]*1);
      }
      break;                            
      
      case 2:  //Format data when two keys are entered from KP e.g. "99"
      {
         kp_data[4]=0;kp_data[3]=0;
         lcd_data[12]=0xCA;lcd_data[13]=0xDA;
         kp_d1=ad5*16 + kp_data[2]*1;                       
         lcd_data[5]=kp_d1;lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_d0=ad15*16 + kp_data[1]*1;
         lcd_data[15]=kp_d0;
         kp_value=(kp_data[1]*10)+(kp_data[2]*1);
      }
      break;
      
      case 3:  //Format data when three keys are entered from KP e.g. "999"
      {      
         kp_data[4]=0;lcd_data[13]=0xDA;
         kp_d2=ad5*16 + kp_data[3]*1;
         lcd_data[5]=kp_d2;lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_d1=ad15*16 + kp_data[2]*1;
         lcd_data[15]=kp_d1;
         kp_d0=ad12*16 + kp_data[1]*1;
         lcd_data[12]=kp_d0;
         kp_value=(kp_data[1]*100)+(kp_data[2]*10)+(kp_data[3]*1);
         //printf("\r\n %lu %lu %lu,kp_data[1],kp_data[2],kp_data[3]);
         //printf("\r\n kp_vla %ld",kp_value);
      }
      break;
      
      case 4:  //Format data when four keys are entered from KP e.g. "9999"
      {      
         kp_d3=ad5*16 + kp_data[4];   
         lcd_data[5]=kp_d3;
         kp_d2=ad15*16 + kp_data[3]*1;
         lcd_data[15]=kp_d2;
         kp_d1=ad12*16 + kp_data[2]*1;
         lcd_data[12]=kp_d1;
         kp_d0=ad13*16 + kp_data[1]*1;
         lcd_data[13]=kp_d0;lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_value=(kp_data[1]*1000)+(kp_data[2]*100)+(kp_data[3]*10)+(kp_data[4]*1);
      }
      break;
      
      case 5:  //when preset value "50" is entered
      {
         kp_data[4]=0;kp_data[3]=0;
         lcd_data[12]=0xCA;lcd_data[13]=0xDA;
         kp_d3=ad5*16 + kp_data[2];
         lcd_data[5]=kp_d3;
         kp_d2=ad15*16 + kp_data[1]*1;
         lcd_data[15]=kp_d2;
         lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_value=(kp_data[1]*10)+(kp_data[2]*1);
      }
      break;
      
      case 6:  //when preset value "100" is entered
      {                                            
         kp_data[4]=0;lcd_data[13]=0xDA;
         kp_d3=ad5*16 + kp_data[3]*1;
         lcd_data[5]=kp_d3;
         kp_d2=ad15*16 + kp_data[2]*1;
         lcd_data[15]=kp_d2;
         kp_d1=ad12*16 + kp_data[1]*1;
         lcd_data[12]=kp_d1;
         lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_value=(kp_data[1]*100)+(kp_data[2]*10)+(kp_data[3]*1);
      }
      break;
      
      case 7:  //when preset value "150" is entered
      {
         kp_data[4]=0;lcd_data[13]=0xDA;
         kp_d3=ad5*16 + kp_data[3]*1;
         lcd_data[5]=kp_d3;
         kp_d2=ad15*16 + kp_data[2]*1;
         lcd_data[15]=kp_d2;
         kp_d1=ad12*16 + kp_data[1]*1;
         lcd_data[12]=kp_d1;
         lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_value=(kp_data[1]*100)+(kp_data[2]*10)+(kp_data[3]*1);
      }
      break;
      
      case 8:  //when preset value "200" is entered
      {
         kp_data[4]=0;lcd_data[13]=0xDA;
         kp_d3=ad5*16 + kp_data[3]*1;
         lcd_data[5]=kp_d3;
         kp_d2=ad15*16 + kp_data[2]*1;
         lcd_data[15]=kp_d2;
         kp_d1=ad12*16 + kp_data[1]*1;
         lcd_data[12]=kp_d1;
         lcd_data[6]=0x60;lcd_data[7]=0x70;
         kp_value=(kp_data[1]*100)+(kp_data[2]*10)+(kp_data[3]*1);
      }
      break;
      
      case 9:  //this will clear the screen and kp_value becomes zero "0"
      {
         kp_value=0;
         lcd_data[5]=0x5A;lcd_data[6]=0x6A;lcd_data[7]=0x7A;lcd_data[15]=0xFA;
         lcd_data[12]=0xCA;lcd_data[13]=0xDA;
         kp_pressed=0;remaining_cntr=0;remaining_time=1250;keypad_time=0; 
      }
      break;
   
      case 10:
      {
         kp_value=0;
         kp_pressed=0;remaining_cntr=0;remaining_time=1250;keypad_time=0; 
      }
      break;
   }
}

