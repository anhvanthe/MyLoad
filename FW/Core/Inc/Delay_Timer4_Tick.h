#ifndef DELAY_TIMER4_TICK_H_
#define DELAY_TIMER4_TICK_H_

#include "main.h"
#include "stdbool.h"

typedef enum {
    US = 0,
    MS,
    SEC
} tick_timer_type_t;

typedef struct
{
		bool  Timeout;
    uint32_t  Start;
    uint32_t  Duration;
} tick_timer_t;


void Tick_Timer_Init(void);
bool Tick_Timer_Is_Over(tick_timer_t *pTick, uint16_t Time, tick_timer_type_t TickType);
void Delay(uint16_t Time, tick_timer_type_t TickType);

#define __delay_us(t)                       Delay(t, US)
#define __delay_ms(t)                       Delay(t, MS)
#define Tick_Timer_Reset(Tick)  						Tick.Timeout=1
#define Tick_Counter_Reset(x)               x=0
#define Tick_Timer_Is_Over_Us(pTick, Time)  Tick_Timer_Is_Over(&pTick, Time, US)
#define Tick_Timer_Is_Over_Ms(pTick, Time)  Tick_Timer_Is_Over(&pTick, Time, MS)
#define Tick_Timer_Is_Over_Sec(pTick, Time) Tick_Timer_Is_Over(&pTick, Time, SEC)

#endif
