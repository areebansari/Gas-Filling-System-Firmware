int16 s_lookup_table(void)
{
   int16 s_load_r;
   switch (sol_freq)
   {
      case 2:
      s_load_r=601;//freq=416 Hz
      return s_load_r;
      break;
  
      case 3:
      s_load_r=1202;//freq=208 Hz
      return s_load_r;
      break;
  
      case 4:
      s_load_r=1428;//freq=175 Hz
      return s_load_r;
      break;
  
      case 5:
      s_load_r=1773;//freq=141 Hz
      return s_load_r;
      break;
  
      case 6:
      s_load_r=2000;//freq=125 Hz
      return s_load_r;
      break;
  
      case 7:
      s_load_r=2358;//freq=106 Hz
      return s_load_r;
      break;
  
      case 8:
      s_load_r=2604;//freq=96 Hz
      return s_load_r;
      break;
  
      case 9:
      s_load_r=2840;//freq=88 Hz
      return s_load_r;
      break;
  
      case 10:
      s_load_r=3205;//freq=78 Hz
      return s_load_r;
      break;
  
      case 11:
      s_load_r=3571;//freq=70 Hz
      return s_load_r;
      break;
  
      case 12:  
      s_load_r=3846;//freq=65 Hz
      return s_load_r;
      break;
  
      case 13:  
      s_load_r=4166;//freq=60 Hz
      return s_load_r;
      break;
  
      case 14:  
      s_load_r=4545;//freq=55 Hz
      return s_load_r;
      break;
  
      case 15:
      s_load_r=4807;//freq=52 Hz
      return s_load_r;
      break;
  
      case 16:
      s_load_r=5208;//freq=48 Hz
      return s_load_r;
      break;
  
      case 17:
      s_load_r=5555;//freq=45 Hz
      return s_load_r;
      break;
  
      case 18:
      s_load_r=5813;//freq=43 Hz
      return s_load_r;
      break;
  
      case 19:
      s_load_r=6250;//freq=40 Hz
      return s_load_r;
      break;
  
      case 20:
      s_load_r=6756;//freq=37 Hz
      return s_load_r;
      break;
  
      case 21:
      s_load_r=7352;//freq=34 Hz
      return s_load_r;
      break;
  
      case 22:
      s_load_r=8064;//freq=31 Hz
      return s_load_r;
      break;
  
      case 23:
      s_load_r=8928;//freq=28 Hz
      return s_load_r;
      break;
  
      case 24:
      s_load_r=10000;//freq=25 Hz
      return s_load_r;
      break;
  
      case 25:
      s_load_r=11904;//freq=21 Hz
      return s_load_r;
      break;
  
      case 26:
      s_load_r=13888;//freq=18 Hz
      return s_load_r;
      break;
  
      case 27:
      s_load_r=15625;//freq=16 Hz
      return s_load_r;
      break;
  
      case 28:
      s_load_r=17857;//freq=14 Hz
      return s_load_r;
      break;
  
      case 29:
      s_load_r=25000;//freq=10 Hz
      return s_load_r;
      break;
  
      case 30:
      s_load_r=31250;//freq=8 Hz
      return s_load_r;
      break;
   }//switch (sol_freq)
}//long s_lookup_table()

/////////////////////lookup table for excess flow of gas///////////////////////

int16 freq_lookup_table()
{
   long s_load_r;
   switch (sol_freq)
   {
      case 5:
      s_load_r=500;//freq=500 Hz
      return s_load_r;
      break;
  
      case 6:
      s_load_r=416;//freq=600 Hz
      return s_load_r;
      break;
  
      case 7:
      s_load_r=357;//freq=700 Hz
      return s_load_r;
      break;
  
      case 8:
      s_load_r=312;//freq=800 Hz
      return s_load_r;
      break;
  
      case 9:
      s_load_r=277;//freq=900 Hz
      return s_load_r;
      break;
  
      case 10:
      s_load_r=250;//freq=1000 Hz
      return s_load_r;
      break;
  
      case 11:
      s_load_r=227;//freq=1100 Hz
      return s_load_r;
      break;
  
      case 12:
      s_load_r=208;//freq=1200 Hz
      return s_load_r;
      break;
  
      case 13:
      s_load_r=192;//freq=1300 Hz
      return s_load_r;
      break;
  
      case 14:
      s_load_r=178;//freq=1400 Hz
      return s_load_r;
      break;
  
      case 15:
      s_load_r=166;//freq=1500 Hz
      return s_load_r;
      break;
  
      case 16:  
      s_load_r=156;//freq=1600 Hz
      return s_load_r;
      break;
  
      case 17:  
      s_load_r=147;//freq=1700 Hz
      return s_load_r;
      break;
  
      case 18:  
      s_load_r=138;//freq=1800 Hz
      return s_load_r;
      break;
  
      case 19:
      s_load_r=131;//freq=1900 Hz
      return s_load_r;
      break;
  
      case 20:
      s_load_r=125;//freq=2000 Hz
      return s_load_r;
      break;
  
      case 21:
      s_load_r=119;//freq=2100 Hz
      return s_load_r;
      break;
  
      case 22:
      s_load_r=113;//freq=2200 Hz
      return s_load_r;
      break;
  
      case 23:
      s_load_r=108;//freq=2300 Hz
      return s_load_r;
      break;
  
      case 24:
      s_load_r=104;//freq=2400 Hz
      return s_load_r;
      break;
  
      case 25:
      s_load_r=100;//freq=2500 Hz
      return s_load_r;
      break;
 
      case 26:
      s_load_r=96;//freq=2600 Hz
      return s_load_r;
      break;

      case 27:
      s_load_r=92;//freq=2700 Hz
      return s_load_r;
      break;
  
      case 28:
      s_load_r=89;//freq=2800 Hz
      return s_load_r;
      break;
  
      case 29:
      s_load_r=86;//freq=2900 Hz
      return s_load_r;
      break;
  
      case 30:
      s_load_r=83;//freq=3000 Hz
      return s_load_r;
      break;
  
      case 31:
      s_load_r=80;//freq=3100 Hz
      return s_load_r;
      break;
  
      case 32:
      s_load_r=78;//freq=3200 Hz
      return s_load_r;
      break;
  
      case 33:
      s_load_r=75;//freq=3300 Hz
      return s_load_r;
      break;

      case 34:
      s_load_r=79;//freq=3400 Hz
      return s_load_r;
      break;
  
      case 35:
      s_load_r=71;//freq=3500 Hz
      return s_load_r;
      break;
   }//switch (s_value)
}//long freq_lookup_table()

