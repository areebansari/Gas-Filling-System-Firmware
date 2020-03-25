#include <18F252.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOOSCSEN                 //Oscillator switching is disabled, main oscillator is source
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES PROTECT                  //Code protected from reads
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads

#use delay(clock=4000000,RESTART_WDT)
//#use rs232(baud=19200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)


////////////////////////LCD Compatibility function\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#define strb_low  output_bit(pin_a1,bit_to_output)    // Done to make code ARL                                                   
#define strb_high output_bit(pin_a1,bit_to_output^1)  // lcd compatible


///////////////////////////// LCD Variables\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
unsigned int8  lcd_data[16] ={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90
                             ,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0};//lcd data

unsigned int8  lcd_clear[16]={0x0a,0x1a,0x2a,0x3a,0x4a,0x5a,0x6a,0x7a,0x8a,0x9a
                             ,0xaa,0xba,0xca,0xda,0xea,0xfa};//clear lcd data
unsigned int8  ad0=0x00,ad1=0x01,ad2=0x02,ad3=0x03,ad4=0x04,ad5=0x05,ad6=0x06,
               ad7=0x07,ad8=0x08,ad9=0x09,ad10=0x0A,ad11=0x0B,ad12=0x0C,
               ad13=0x0D,ad15=0x0F;
               
unsigned int8 value1=0,value2=0,value3=0;
int1 bit_to_output=1;

///////////////////////////////IR variables\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
int1 irs[58]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
              ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int8 state=0,leader=0,startbit=0,togle=0,address=0,mode=0,prv_togle=0,
              command=0,enter=0,w1=0,w2=0,w3=0,w4=0,w5=0,w6=0,
              w7=0,w8=0,w9=0,w10=0,w11=0,w12=0,w13=0,w14=0;
              
unsigned int16 menu_timer=0,time_remain=0,ir_enter_count=0; 
int1 ir=0,numeric=0,menu=0,menu_again=0,total_1=0,total_2=0,ir_key_press=0,
     ir_enter_flag=0,ir_key_press2=0,any_key_press=0,key_press_check=0;


/////////////////////////////Keypad Variables\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
unsigned int16 kp_value=0,kp_rupees=0;
int1 clock_status=0,kp_pressed=0;
unsigned int8 col=0,col_loop=0,kp_n=0,key=0;
unsigned col_data[4]={0x7F,0xbF,0xdF,0xEF};   
unsigned int16 kp_data[5]={0,0,0,0,0};
unsigned int8 kp_value1=0,kp_value2=0,kp_value3=0;
unsigned int8 kp_d0=0,kp_d1=0,kp_d2=0,kp_d3=0;
unsigned int16 remaining_time=1250;        
unsigned int8 remaining_cntr=0,keypad_time=0;
unsigned int32 kp_iweight=0;

/////////////////////////////mix variables\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
int1 disp_pattern=0,inc_1=0,actuator=0,first_start=1,filling=0,
     start=0,calib_check=0,one_time=0,no_perform=0,mech_led=0,settling_flag=0,
     no_flow=0,cutoff_freq_flag=0,full_filling=0,filling_start=0,load_ram=1,
     filling_performed=0;
     
unsigned int8 temp8=0,ones=0,tens=0,hundred=0,tenth=0,hundredth=0,thousand=0,
              lakh=0,tenthousand=0,solenoid1=0,solenoid2=0,solenoid3=0,
              calibration=0,no_of_pulses1=0,no_of_pulses2=0,no_of_time1=0,
              no_of_time2=0,excess_freq=0,no_flow_time=0,no_flow_timer1=0,
              rate_ones=0,rate_tens=0,grams_10=0,vol=0,
              rate_hundredth=0,rate_tenth=0,calib_cntr=0,pulse_counter=0,
              loop=0,ee_flag=0,no_flow_timer=0,filling_state=0,sol_freq=0,
              wait_timer1_1=0,wait_time=0,
              wait_timer1_2=0,settling_timer=0,filling_state_timer=0,
              wait_timer2_1=0,wait_timer2_2=0,cut_off_timer=0,filling_ended=2;
              
unsigned int16 filling_freq=0,solenoid1_freq=0,solenoid2_freq=0,
               solenoid3_freq=0,cut_off_freq=0,rate_hundred=0;
unsigned int32 temp32=0,weight=0,totalizer1=0,totalizer2=0,int_amount=0;
unsigned int32 ram_weight[3]={0,0,0};
float ram_rupees[3]={0,0,0};
float rate=0,kilograms=0,amount=0,kp_weight=0;
unsigned int16 ir_rate[5]={0,0,0,0,0};

int1 p_occured=FALSE,new_filling=FALSE,two_sec_passed=FALSE;
int power_loop_counter=0,blink=0;
int32 total1=0,total2=0,total3=0,total4=0;

///////////////////////////////////////////////////////////////////////////////

#define     low_sol        pin_c0      // low solenoid pin
#define     med_sol        pin_c1      // medium solenoid pin
#define     high_sol       pin_c2      // high solenoid pin
#define     power_sense    pin_a5      // power sense pin
#define     data_pin       pin_a3      // data pin for lcd and keypad
#define     clock_pin      pin_a2      // clock pin for lcd and keypad
#define     strobe_l       pin_a1      // strobe pin for lcd
#define     strobe_k       pin_a4      // strobe pin for keypad
#define     sel_switch     pin_b1      // on off switch for filling/non filling
#define     mech_counter   pin_b4      // Mechanical counter pin
#define     key_pressed    pin_b3      // keypad "key pressed" pin
#define     ir_pin         pin_b2      // IR sensor data capture pin

/////////////////////////////IR defines\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#define     valid_leader   0x03
#define     valid_start    0x01                                              
#define     valid_mode     0x2A                                 
#define     valid_togle1   0x03                                               
#define     valid_togle2   0x0C              
#define     valid_address  0x04                                               

///////////////////////////EEPROM R/W functions\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
                            
#define mReadByte(addr)  read_eeprom(addr)
#define mWriteByte(addr,data) write_eeprom(addr,data)

#define mReadWord(addr) make16(read_eeprom(addr+1),read_eeprom(addr))
#define mWriteWord(addr,data) {write_eeprom(addr,make8(data,0));write_eeprom((addr+1),make8(data,1));}

#define mRead32(addr)  make32(read_eeprom(addr+3),read_eeprom(addr+2),read_eeprom(addr+1),read_eeprom(addr))
#define mWrite32(addr,data) {write_eeprom(addr,make8(data,0));write_eeprom((addr+1),make8(data,1));write_eeprom((addr+2),make8(data,2));write_eeprom((addr+3),make8(data,3));}

void data_save(void);      //function to save data in eeprom
void power_check(void);    //check whether power is avaiable or not

void show_on_lcd(void);    //function to send filling/nonfilling data to lcd
void clear_lcd(void);      //function to blank the lcd
void format_data(void);    //function to format the data, to show on lcd
int8 swap_bits(int data);  //used with lcd func, used to swap bits
void dataout_lcd(void);    //used to send data to lcd
void disp_888(void);       //displays 888 pattern on lcd
void clear_888(void);      //clear 888 pattern from lcd

void delay_50(void);       //50ms delay approx
void delay_250(void);      //250ms delay approx

void ir_routine(void);     //routine to capture and decode IR data stream
int parameters_values(int value,int menu_no);   //IR parameter setting function
void clear_segments(void); //used in ir routine, used to clear some segments


void read_keypad(void);
void dataout_kp(void);
void scan_keypad(void);
void value_from_kp(void);



