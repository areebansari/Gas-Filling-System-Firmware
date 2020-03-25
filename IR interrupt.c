#int_TIMER1
void timer1_interrupt(void)                       
{  
   restart_wdt();
   set_timer1(65486);                             
 
   if(!input(ir_pin))      // If IR pin low
   {                                                    
      irs[state]=0;                
      state++;                             
   }
   else if(input(ir_pin))  // If IR pin high                    
   {                                                         
      irs[state]=1;                  
      state++;                            
   }   
   
   if(state>=58)  // complete data stream captured ?
   {                                                    
      disable_interrupts(INT_TIMER1);
      state=0;
  
      leader=(irs[0]*128 + irs[1]*64 + irs[2]*32 + irs[3]*16 + irs[4]*8 + 
              irs[5]*4 + irs[6]*2 +irs[7]*1);
     
      if(leader==valid_leader)                                                                   
      {
         startbit=(irs[8]*2 + irs[9]*1);
         if(startbit==valid_start)
         {                                       
            mode=(irs[10]*32 + irs[11]*16 + irs[12]*8 + irs[13]*4 + irs[14]*2 
                 + irs[15]*1);
            
            if(mode==valid_mode)                                                  
            {
               togle=(irs[16]*8 + irs[17]*4 + irs[18]*2 + irs[19]*1);
               if(togle==valid_togle1 || togle==valid_togle2)
               {                                        
                  address=(irs[21]*128 + irs[23]*64 + irs[25]*32 + irs[27]*16
                          + irs[29]*8 + irs[31]*4 +irs[33]*2 + irs[35]*1);
                 
                  if(address==valid_address)
                  {  
                     if(togle!=prv_togle)
                     {
                        prv_togle=togle;        
                        command=(irs[37]*128)+(irs[39]*64)+(irs[41]*32)+
                                (irs[43]*16)+(irs[45]*8)+(irs[47]*4)+(irs[49]*2)
                                +(irs[51]*1);
                        ir_key_press=1; ir_key_press2=1;
                        if(command>0x09)
                        {
                           if(command==0x0f)
                           {
                              total_1=1; total_2=0; numeric=0;  
                           }
                           
                           else if(command==0x4e)
                           {
                              total_2=1; total_1=0; numeric=0; 
                           }
                           
                           else if(command==0xD1)
                           { 
                              menu=1; ir_enter_flag=1; numeric=0; 
                           }
                           
                           else if(command==0x5C)
                           { 
                              total_1=0; total_2=0; 
                           }
                           
                        }
                                             
                        
                        else if(command>=0x00 && command<=0x09)//numeric key                        
                        {                           
                           numeric=1; 
                        }
                     
                     }
                  }                                       
               }                                                               
            }                                
         }                                         
      }             
   }               
}

////////////////////////////////////////////////////////////////////////////////
#int_EXT2                                             
void isr_ext2(void)       
{                                                       
   clear_interrupt(INT_TIMER1);                                 
   enable_interrupts(INT_TIMER1);                                     
   set_timer1(65514);               
}   
