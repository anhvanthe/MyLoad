#include "Delay_Timer4_Tick.h"
/*
	
	*****Config Timer4*****
	-F timer4 = 1Mhz
	-Timer4 interrupt enable
	-Count mode : Up
	-Counter Period(AutoRekoad) = 0xFFFF
	
*/
extern TIM_HandleTypeDef htim4;
static volatile uint16_t TickCount=0;
static uint32_t Tick_Per_Us=0;
static uint32_t Tick_Per_Ms=0;
static uint32_t Tick_Per_Sec=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){ // Timer4 interrupt callback 
	
	
	if(htim->Instance == TIM4){
		
		TickCount++;
		if(TickCount>=UINT16_MAX)
			TickCount=0;
	}
		
}

void Tick_Timer_Init(void) // <editor-fold defaultstate="collapsed" desc="Tick initialize">
{
    
  TickCount=0;
	
	Tick_Per_Sec=(uint32_t) 1000000;
	Tick_Per_Ms=(uint32_t) 	Tick_Per_Sec/1000;
	Tick_Per_Us=(uint32_t) 	Tick_Per_Ms/1000;
    
	HAL_TIM_Base_Start_IT(&htim4);
} // </editor-fold>

static uint16_t Get_Timer4(void){
	
	return (TIM4->CNT);
}

static uint32_t Tick_Timer_Get(void) // <editor-fold defaultstate="collapsed" desc="Get tick value">
{
    uint32_t CurTick;
    uint16_t CurCount;

    do
    {
        CurCount=TickCount;
        CurTick=CurCount;
        CurTick<<=16;
        CurTick|=Get_Timer4();
    }
    while(TickCount!=CurCount);

    return CurTick;
} // </editor-fold>

bool Tick_Timer_Is_Over(tick_timer_t *pTick, uint16_t Time, tick_timer_type_t TickType) // <editor-fold defaultstate="collapsed" desc="Check 1 tick">
{
//    uint32_t CurTick=Tick_Timer_Get();

    if(pTick->Timeout)
    {
        pTick->Timeout=0;
				pTick->Start=Tick_Timer_Get();
        if(TickType==US)
            pTick->Duration=((uint32_t) Tick_Per_Us*Time);
        else if(TickType==MS)
            pTick->Duration=((uint32_t) Tick_Per_Ms*Time);
        else
            pTick->Duration=((uint32_t) Tick_Per_Sec*Time);
    }

    if((Tick_Timer_Get()-(pTick->Start)) >= (pTick->Duration)) 
    {
        pTick->Timeout=1;

        return 1;
    }

    return 0;
} // </editor-fold>

void Delay(uint16_t Time, tick_timer_type_t TickType) // <editor-fold defaultstate="collapsed" desc="Delay">
{
    tick_timer_t Tick;

    Tick_Timer_Reset(Tick);
    while(Tick_Timer_Is_Over(&Tick, Time, TickType)==0);
       
} // </editor-fold>

