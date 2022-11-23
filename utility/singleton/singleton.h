#ifndef SINGLETON_H_
#define SINGLETON_H_

template <typename T>
class singleton
{
    public:
        static T* get_instance()
        {
            static T instance;
            return &instance;
        };
};


#endif //SINGLETON_H_