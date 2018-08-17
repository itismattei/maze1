
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

#include "interval.h"


/*
 * delay:
 *      Wait for some number of milliseconds
 *********************************************************************************
 */

void delay (unsigned int howLong)
{
  struct timespec sleeper, dummy ;

  sleeper.tv_sec  = (time_t)(howLong / 1000) ;
  sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

  nanosleep (&sleeper, &dummy) ;
}



/*
 * millis:
 *      Return a number of milliseconds as an unsigned int.
 *********************************************************************************
 */

unsigned int millis (void)
{
  struct timeval tv ;
  uint64_t now ;

  gettimeofday (&tv, NULL) ;
  now  = (uint64_t)tv.tv_sec * (uint64_t)1000 + (uint64_t)(tv.tv_usec / 1000) ;

  return (uint32_t)(now - epochMilli) ;
}


/*
    inizializza la variabile epochMilli e cosi' e' possibile misurare i millisecondi
    dall'inizializzazione della variabile
*/
void millisInit(void){
  struct timeval tv ;
  uint64_t now ;

  gettimeofday (&tv, NULL) ;
  epochMilli  = (uint64_t)tv.tv_sec * (uint64_t)1000 + (uint64_t)(tv.tv_usec / 1000) ;
}


/*
    Effettua uno sleep di millis millisecondi
*/
void sleepMs(uint32_t millis){
  usleep(millis * 1000);
}
