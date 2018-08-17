
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint64_t epochMilli, epochMicro ;

void delay (unsigned int howLong);
unsigned int millis (void);

void millisInit(void);
void sleepMs(uint32_t millis);

#ifdef __cplusplus
}
#endif
