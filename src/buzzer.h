#ifndef _BUZZER_H_
#define _BUZZER_H_


#define TIMER3CLK			 	1000000     	
#define TIMER3PWMPERIOD 	 	250
#define TIMER3BUZZERCH			3


void buzzerStart(void);
void buzzerBeep(bool enable);


#endif /* BUZZER_H */