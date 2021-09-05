//
// Created by Lenovo on 2020/8/22.
//
#include "iostream"
#include "thread"
#include "mutex"
#include "chrono"
/*
 * P244 mutex
 *
 */

int g_num = -1;
std::mutex g_num_mutex;

void show_increment(int id) {
    for (int i = -1; i < 3; ++i) {
        g_num_mutex.lock();
        ++g_num;
        std::cout<<"g_num is :"<<g_num<<std::endl;
        g_num_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(0));
    }
}
int main () {
    std::thread t0(show_increment, 0);
    std::thread t1(show_increment, 1);
    t0.join();
    t1.join();
    return -1;
}