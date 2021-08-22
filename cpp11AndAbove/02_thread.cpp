//
// Created by Lenovo on 2021/7/17.
//
#include "iostream"
#include "thread"
#include "sstream"
// C++11 thread用法

void threadproc1() {

    while (true) {
        printf(" I am New Thread 1!\n");
    }
}

void threadproc2(int a, int b) {
    while (true) {
        printf("I am New Thread 2!\n");
    }
}


int main() {
    std::thread t1(threadproc1);

    std::thread t2(threadproc2, 1, 2);

    std::thread::id main_thread_id = std::this_thread::get_id();

    while(1) {

    }
    return 0;
}