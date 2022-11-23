#include "runtime_recorder/runtime_recorder.h"

runtime_recorder* runtime_recorder::get_instance()
{
    static runtime_recorder instance;
    return &instance;
}

double runtime_recorder::record_runtime(std::function<void(void)> func)
{
    struct timeval time_start{0,0},time_end{0,0};
    gettimeofday(&time_start,NULL);
    func();
    gettimeofday(&time_end,NULL);
    double time_interval =   (double)(time_end.tv_sec - time_start.tv_sec)*1000 + (double)(time_end.tv_usec - time_start.tv_usec)/1000;
    std::cout<<"Funtion runtime:  "<<time_interval<<" ms"<<std::endl;
    return time_interval;
}

double runtime_recorder::set_checkpoint_implement(int id, std::string file_name, std::string function_name, int line_number)
{
    struct timeval time_checkpoint{0,0};
    gettimeofday(&time_checkpoint,NULL);
    auto [iter, success_flag] = record_map.try_emplace(id,std::tuple((double)time_checkpoint.tv_sec*1000 + (double)time_checkpoint.tv_usec/1000, file_name, function_name, line_number));
    if(success_flag)
    {
        std::cout<<"Checkpoint["<<id<<"]        "<<file_name<<" -> "<<function_name<<" -> line "<<line_number<<std::endl;

        if(iter == record_map.begin())
        {
            return 0;
        }

        int current_id =  iter->first;
        double current_timestamp = std::get<0>(iter->second);
        auto previous_iter = --iter;
        int previous_id =  previous_iter->first;
        double previous_timestamp = std::get<0>(previous_iter->second);
        double time_interval = current_timestamp-previous_timestamp;
        std::cout<<"Previous checkpoint["<<previous_id<<"] -> Current checkpoint["<<current_id<<"]: "<<time_interval<<" ms"<<std::endl;
        return time_interval;
    }
    else
    {
        std::cout<<"This id has already been registered, record failed!"<<std::endl;
        this->record_map.erase(iter);
        exit(1);
    }
}

double runtime_recorder::get_interval(int start_id, int end_id)
{
    auto iter_begin = this->record_map.find(start_id);
    auto iter_end = this->record_map.find(end_id);
    if(iter_begin == this->record_map.end())
    {
        std::cout<<"Id "<<start_id<< " doesn't exist!"<<std::endl;
        return -1;
    }
    if(iter_end == this->record_map.end())
    {
        std::cout<<"Id "<<end_id<< " doesn't exist!"<<std::endl;
        return -1;
    }

    double time_interval = std::get<0>(iter_end->second) - std::get<0>(iter_begin->second);
    std::cout<<std::endl;
    std::cout<<"    Previous checkpoint[" <<iter_begin->first<<"]     "<<std::get<1>(iter_begin->second)<<" -> "<<std::get<2>(iter_begin->second)<<" -> line "<<std::get<3>(iter_begin->second)<<std::endl;
    std::cout<<"    Current  checkpoint[" <<iter_end->first<<"]     "<<std::get<1>(iter_end->second)<<" -> "<<std::get<2>(iter_end->second)<<" -> line "<<std::get<3>(iter_end->second)<<std::endl;
    std::cout<<"    Runtime  interval:         "<<time_interval<<" ms"<<std::endl;
    return time_interval;
}