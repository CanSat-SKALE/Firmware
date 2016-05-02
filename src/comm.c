#include <ch.h>
#include <hal.h>
#include "thread_prio.h"

#include "comm.h"


static THD_WORKING_AREA(comm_wa, 256);
static THD_FUNCTION(comm, arg)
{
    BaseSequentialStream *comm_port = (BaseSequentialStream*)arg;
    chRegSetThreadName("comm");
    while (true) {
        // loopback
        chSequentialStreamPut(comm_port, chSequentialStreamGet(comm_port));
    }
}


void comm_start(void)
{
    chThdCreateStatic(comm_wa, sizeof(comm_wa), THD_PRIO_COMM, comm, &SD2);
}
