#include <ti/sysbios/knl/Task.h>

/***** Prototypes *****/
void alarmTask_init( void );
void alarmTaskFunction(UArg arg0, UArg arg1);

#define ALARM_H 0x8
#define ALARM_M 0x4
#define ALARM_L 0x2
#define ALARM_0 0x1
