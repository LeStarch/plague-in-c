#include <stdlib.h>
#include <stdio.h>
//local headers
#include <constants.h>
#include <dumby.h>

double randomD();
unsigned long randomL(unsigned long bound);


extern unsigned char __executable_start,_edata;

/**
 * Wraps the fork call
 * @return - pid
 */
pid_t __wrap_fork()
{
    int ret = __real_fork();
    if (ret == 0)
    {
    	//Corrupt the children
    	double d = randomD();
        printf("Child being granted life: %f\n",d);
    	if (d <= CORRUPTION_RATIO)
        {
            printf("Mutation in child occurring\n");
            unsigned char* addr = randomL(&_edata - &__executable_start) + &__executable_start;
            *addr = randomL(256);
        }

        main(0,NULL);
    } else if (ret > 0) {
    	printf("Child spawned with id:%d\n",ret);
    } else if (ret == -1) {
    	fprintf(stderr,"Error occurred spawning child\n");
    }
    return ret;
}
/**
 * Gets a random double.
 * @return a random double [0.0 , 1.0)
 */
double randomD()
{
    return ((double)rand()/(double)RAND_MAX);
}
/**
 * Gets a random bounded integer.
 * @param bound - bound for inetegr
 * @return a random inetegr [0 , bound)
 */
unsigned long randomL(unsigned long bound)
{
    // Uniform distribution is produced from:
    //   unsigned long r = rand() % bound;
    // only when (bound * I = RAND_MAX) where I is some Integer
    // thus use a better approach for any bound.
    return (unsigned long)(randomD()*(double)bound);
}
