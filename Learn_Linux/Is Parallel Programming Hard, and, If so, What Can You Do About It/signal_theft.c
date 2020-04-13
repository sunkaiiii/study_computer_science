#include <api.h>

#define THEFT_IDLE 0
#define THEFT_REQ 1
#define THEFT_ACK 2
#define THEFT_READY 3

int __thread theft = THEFT_IDLE;
int __thread counting =0;
unsigned long __thread counter=0;
unsigned long __thread countermax=0;
unsigned long globalcountermax=1000;
unsigned long globalcount=0;
unsigned long globalreserve=0;
unsigned long *counterp[NR_THREADS] = {NULL};
unsigned long *countermaxp[NR_THREADS]={NULL};
int *theftp[NR_THREADS]={NULL};
DEFINE_SPINLOCK(gblcnt_mutex);
#define MAX_COUNTERMAX 100