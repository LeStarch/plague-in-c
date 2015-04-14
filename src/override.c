#include <stdlib.h>
//local headers
#include <constants.h>
#include <dumby.h>

double randomD();
unsigned long randomL(unsigned long bound);


extern unsigned char stext,etext;

/**
 * Wraps the fork call
 * @return - pid
 */
pid_t __wrap_fork()
{
    int ret = __real_fork();
    //Corrupt the children
    double d = randomD();
    if (ret == 0 && d <= CORRUPTION_RATIO)
    {
        unsigned char* addr = randomL(&etext - &stext) + &stext;
        *addr = randomL(256);
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
