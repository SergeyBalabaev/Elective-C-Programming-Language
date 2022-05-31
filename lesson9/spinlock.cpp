// g++ spinlock.cpp -o spinlock -lpthread -fsanitize=thread
#include <atomic>
#include <thread>
#include <iostream>

int globalvar = 10;

class Spinlock
{
private:
   std::atomic<bool> locked_{false} ;

public:
    void lock()
    {
       while (locked_.exchange(true)){};
    }
    void unlock()
    {
        locked_.store(false);
    }
};

Spinlock SL;
int flag = 0;
int main()
{  
    std::thread thr_1([](){
            SL.lock();
            globalvar = 15;
            SL.unlock();
        });
    std::thread thr_2([](){
            SL.lock();
            globalvar = 25;
            SL.unlock();
        });
    thr_1.join();
    thr_2.join();
}
