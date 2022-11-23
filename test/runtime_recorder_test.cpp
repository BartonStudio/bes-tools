#include "runtime_recorder/runtime_recorder.h"
#include <unistd.h>

void sleep_for_seconds(int time)
{
    std::cout<<"Start sleeping!"<<std::endl;
    sleep(time);
    std::cout<<"Finish sleeping!"<<std::endl;
}


int main(void)
{
    //example 1
    runtime_recorder::record_runtime(std::bind(sleep_for_seconds,2));

    //example 2
    runtime_recorder *test = runtime_recorder::get_instance();
    test->set_checkpoint(1);
    uint32_t a = 1000000000;
    while(a--);
    test->set_checkpoint(3);

    return 0;
}