void format_data(void)
{
   restart_wdt();
  
   if(filling_start==1)       // if filling process started 
   {
      kilograms=weight/100.0; // current filled kilograms
      amount=kilograms*rate;  // current filling amount
   
      if(amount>=9999 || kilograms>999)
      {
         disable_interrupts(int_ext);
         output_high(low_sol);   // low solenoid off
         output_high(med_sol);   // medium solenoid off
         output_high(high_sol);  // high solenoid off
         one_time=0; 
      }   

      if(full_filling==0)        // if filling according to rupees entered
      {
         if(amount>=kp_rupees || weight>=kp_iweight)
         {  
            amount=kp_rupees;
            disable_interrupts(int_ext);
            output_high(low_sol);   // low solenoid off
            output_high(med_sol);   // medium solenoid off
            output_high(high_sol);  // high solenoid off
            one_time=0;  
         }
      }
   }

////////////////////////////// Rate Calculation\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
   lcd_data[10]=ad10*16 + rate_hundred;
   lcd_data[11]=ad11*16 + rate_tens;
   lcd_data[2]=ad2*16 + rate_ones;
   lcd_data[0]=ad0*16 + rate_tenth;
   
   if(rate<0.10)
   {
      lcd_data[0]=0x00;lcd_data[2]=0x20;lcd_data[10]=0xA0;lcd_data[11]=0xB0;
   }
   
   else if(rate>=.10 && rate<1)
   {
      lcd_data[2]=0x20;lcd_data[10]=0xAA;lcd_data[11]=0xBA;
   }
   
   else if(rate>=1 && rate<10)
   {
      lcd_data[10]=0xAA;lcd_data[11]=0xBA;
   }
   
   else if(rate>=10 && rate<100)
   {
      lcd_data[10]=0xAA;
   }
   
   
////////////////////////////// kilograms calculation\\\\\\\\\\\\\\\\\\\\\\\\\\\\
   
   temp32=weight;
   hundred=(temp32/10000)%10;
   tens=(temp32/1000)%10;
   ones=(temp32/100)%10;
   tenth=(temp32/10)%10;
   hundredth=(temp32%10);
   
   lcd_data[4]=ad4*16 + hundredth;
   lcd_data[3]=ad3*16 + tenth;
   lcd_data[1]=ad1*16 + ones; 
   lcd_data[8]=ad8*16 + tens;
   lcd_data[9]=ad9*16 + hundred;
   
   if(kilograms<1)
   {
      lcd_data[8]=0x8A;lcd_data[9]=0x9A;lcd_data[1]=0x10;
   }
   else if(kilograms>=1 && kilograms<10)
   {                                                             
      lcd_data[8]=0x8A;lcd_data[9]=0x9A;         
   }                                     
   else if(kilograms>=10 && kilograms<100)
   {
      lcd_data[9]=0x9A;                                             
   }                     
   
////////////////////////////// Rupees Calculation\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
   temp32=100.0*amount;
   thousand=temp32/100000;
   hundred=(temp32/10000)%10;
   tens=(temp32/1000)%10;
   ones=(temp32/100)%10;
   tenth=(temp32/10)%10;
   hundredth=(temp32%10);
   
   lcd_data[13]=ad13*16 + thousand;
   lcd_data[12]=ad12*16 + hundred;
   lcd_data[15]=ad15*16 + tens;
   lcd_data[5] =ad5*16 + ones;
   lcd_data[6] =ad6*16 + tenth;
   lcd_data[7] =ad7*16 + hundredth;
    
   if(amount>=0 && amount<1)
   {                                  
      lcd_data[15]=0xFA;lcd_data[12]=0xCA;lcd_data[13]=0xDA;
      lcd_data[5] =0x50; 
   }                           
   else if(amount>=1 && amount<10)
   {
      lcd_data[15]=0xFA;lcd_data[12]=0xCA;lcd_data[13]=0xDA;
   }                           
   else if(amount>=10 && amount<100)
   {    
      lcd_data[12]=0xCA;lcd_data[13]=0xDA;
   }                   
   else if(amount>=100 && amount<1000)
   {        
      lcd_data[13]=0xDA;
   }
   
   if(input(power_sense))
   {
      lcd_data[14]=0xe2;
   }
   else lcd_data[14]=0xea;
}


