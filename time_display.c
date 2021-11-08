

//012345678901234567890
// yyyy-mm-dd hh:mm:ss
void time_display (void)
{
	unsigned char dh,dl;
	if ((old_sec != sec) || (time_update)) {
	   old_sec = sec;
	   dh = (old_sec / 10) + 0x30;
	   dl = (old_sec % 10) + 0x30;
	   if (time_update) put_engxy(17,0,':');
	   put_engxy(18,0,dh);
	   put_engxy(19,0,dl);
	   if ((old_min != min) || (time_update)) {
	   	  old_min = min;
	      dh = (old_min / 10) + 0x30;
	      dl = (old_min % 10) + 0x30;
	      if (time_update) put_engxy(14,0,':');
	      put_engxy(15,0,dh);
	      put_engxy(16,0,dl);
	      if ((old_hour != hour) || (time_update)) {
	         old_hour = hour;
	         dh = (old_hour / 10) + 0x30;
	         dl = (old_hour % 10) + 0x30;
	         put_engxy(12,0,dh);
	         put_engxy(13,0,dl);
		  	 if ((old_hour == 0) || (time_update)) {
		  	 	lcd_printf(0,0," %4d-%.2d-%.2d ",year,month,day);
		     }
	      }				
       }
	}
    time_update = false;	
}

// userdefs.h 에 구조체 선언추가 

typedef struct
{
      short year;
      char month;
      char day;
      char hour;
      char min;
      char sec;
      char wday;
} time_rtc;
// 함수원형 추가 
// time.c
extern void time_from_seconds (time_rtc *ptime, unsigned int ul_seconds);
extern void time_to_seconds (time_rtc *ptime, unsigned int *pul_seconds);
extern void set_time (time_rtc *p_time);
extern void init_rtc (void);

// time.c init_rtc 추가 
void init_rtc (void)
{
      NVIC_InitTypeDef NVIC_InitStructure;
      /* Configure and enable RTC interrupt */
      NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
      // 아래내용 추 가 
      /* Enable PWR and BKP clocks */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

