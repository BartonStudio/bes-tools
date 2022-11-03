#include <iostream>
#include <sys/time.h>
#include <functional>
#include <map>
#include <cstring>

#define set_checkpoint(id) set_checkpoint_implement(id, __FILE__, __FUNCTION__, __LINE__) 

class runtime_recorder
{        
    public:
        static runtime_recorder* get_instance();
        static double record_runtime(std::function<void(void)> func);
        double set_checkpoint_implement(int id, std::string file_name, std::string function_name, int line_number);   
        double get_interval(int start_id, int end_id);

    private:
        std::map<int,std::tuple<uint32_t, std::string, std::string, int>> record_map;

    private:
        runtime_recorder() = default;
        ~runtime_recorder() = default;
        runtime_recorder(const runtime_recorder& runtime_recorder) = delete;
        runtime_recorder operator=(runtime_recorder& runtime_recorder) = delete;
};