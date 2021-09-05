//
// Created by Lenovo on 2021/9/5.
//
// P256 利用线程同步来通知创建者线程是否创建成功

#include <thread>
#include "mutex"
#include "condition_variable"
#include "iostream"
using namespace std;

mutex mymutex;
condition_variable mycv;
bool success = false;
void thread_func() {
    {
        std::unique_lock<mutex> lock(mymutex);
        success = true;
        mycv.notify_one();
    }

    while (true) {

    }
}

int main() {
    thread t1(thread_func);
    {
        unique_lock<mutex> lock(mymutex);
        while(!success) {
            mycv.wait(lock);
        }
    }
    cout<< "start thread success" <<endl;
    t1.join();
    return 0;
}
