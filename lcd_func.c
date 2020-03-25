// The strobe signal for LCD has been changed from active low to active high in
// software and a nand gate form CD4093 has been used form LCD hardware to 
// invert the logic. This has been done to prevent garbage values from showing
// on LCD.

///////////////////////////////////////////////////////////////////////////////
void clear_lcd(void)       //to clear the lcd
{
   unsigned int8 x=0;
   restart_wdt();
   for(x=0;x<16;x++)
   {
      value1=swap_bits(lcd_clear[x]);                  
      dataout_lcd();                             
      strb_high;           // Activate strobe (LCD strobe is active HIGH)
      delay_us(2);
      strb_low;            // Deactivate strobe
   }
}

///////////////////////////////////////////////////////////////////////////////
void show_on_lcd(void)     //to show filling/non filling data to lcd
{
   unsigned int8 x=0;
   restart_wdt();
   for(x=0;x<16;x++)
   {            
      value1=swap_bits(lcd_data[x]);           
      dataout_lcd();
      strb_high;           // Activate strobe (LCD strobe is active HIGH)                   
      delay_us(2);
      strb_low;            // Deactivate strobe  
   }
}

///////////////////////////////////////////////////////////////////////////////
void dataout_lcd(void)     //output data to LCD
{
   unsigned int y=0;
   restart_wdt();   
   value2=0b00000001;
   for(y=0;y<8;y++)                     
   {
      value3=value1 & value2;
      output_bit(data_pin,value3);
      output_low(clock_pin);
      output_high(clock_pin);
      rotate_left(&value2,1);
   }
}

///////////////////////////////////////////////////////////////////////////////
int8 swap_bits(int8 data)  //swap bits, before sending data to lcd
{
   unsigned int result=0;
   restart_wdt();
   if(bit_test(data,0)) bit_set(result,7);
   if(bit_test(data,1)) bit_set(result,6);
   if(bit_test(data,2)) bit_set(result,5);
   if(bit_test(data,3)) bit_set(result,4);
   if(bit_test(data,4)) bit_set(result,3);
   if(bit_test(data,5)) bit_set(result,2);          
   if(bit_test(data,6)) bit_set(result,1);
   if(bit_test(data,7)) bit_set(result,0);
   return result;                                          
} 

///////////////////////////////////////////////////////////////////////////////
void strb_sel(void)        // for AEI & ARL LCD compatibilty
{
   restart_wdt();
   if(input(pin_c6))       // Jumper setting
   {  
      bit_to_output = 0;   // ARL compatible
   } 
   else 
   {
      bit_to_output = 1;   // AEI compatible
   } 
}


///////////////////////////////////////////////////////////////////////////////
void disp_888(void)        //for displaying 888 on lcd    
{                                
   restart_wdt();
   
   value1=swap_bits(0x78);
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   value1=swap_bits(0x48);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   value1=swap_bits(0x08);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0x68);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   value1=swap_bits(0x38);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;

   value1=swap_bits(0x28);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0x58);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   value1=swap_bits(0x18);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;

   value1=swap_bits(0xb8);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0xf8);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;

   value1=swap_bits(0x88);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;

   value1=swap_bits(0xa8);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0xc8);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;

   value1=swap_bits(0x98);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0xd8);
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   value1=swap_bits(0xe8);                  
   dataout_lcd();                                                            
   strb_high; 
   delay_us(2);                                    
   strb_low;
   
   delay_50();
}


///////////////////////////////////////////////////////////////////////////////
void clear_888(void)       //for clear 888 pattern after dispaly 888 pattern
{                                
   restart_wdt();
   
   value1=swap_bits(0xea);
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0xda);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0x9a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0xca);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0xaa);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0x8a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0xfa);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0xba);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0x1a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0x5a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0x2a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0x3a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0x6a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   value1=swap_bits(0x0a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   delay_50();
   
   value1=swap_bits(0x4a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
 
   value1=swap_bits(0x7a);                  
   dataout_lcd();                  
   strb_high;  
   delay_us(2); 
   strb_low;
   
   delay_50();   
}
