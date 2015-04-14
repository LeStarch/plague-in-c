#include <time.h>
#include <stdlib.h>
//system headers
#include <unistd.h>

/**
 * Main program.
 */
int main(int argc, char** argv)
{
    srand(time(NULL));
    __wrap_fork();
}
