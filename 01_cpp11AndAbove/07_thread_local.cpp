//
// Created by Lenovo on 2021/9/5.
// P268 thread_local
// 线程局部变量

#include "thread"
#include "chrono"
#include "iostream"

thread_local int g_data = 1;
void thread_fun1() {
    while (true) {
        ++g_data;
    }
}

void thread_fun2() {
    while(true) {
        std::cout<<"g_data = " << g_data <<", thread_id is: "<<std::this_thread::get_id() <<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
int main () {
    std::thread t1(thread_fun1);
    std::thread t2(thread_fun2);

    t1.join();
    t2.join();
    return 0;
}

