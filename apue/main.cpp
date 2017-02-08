
#include <unistd.h>
#include "iotest.h"
#include "processtest.h"
#include "signaltest.h"

int main(void) 
{
    // file_io_test();
    
    // test_system();

    test_signal();
    return 0;
}