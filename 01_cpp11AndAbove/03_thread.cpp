//
// Created by Lenovo on 2021/7/19.
//
#include "iostream"
#include "thread"
#include "memory"
using  namespace std;

class Thread{
public:
    Thread(){}
    ~Thread(){}
    void Start() {
        m_stopped = false;
        m_spThread.reset(new std::thread(&Thread::threadFunc, this, 1000, 2000));
    }

    void Stop() {
        m_stopped = true;
        if (m_spThread) {
            if (m_spThread->joinable()) {
                m_spThread->join();
            }
        }
    }
private:
    void threadFunc(int arg1, int arg2) {
        while (!m_stopped) {
            cout<<"Thread function use instance method"<<endl;
        }
    }

    shared_ptr<thread> m_spThread;
    bool m_stopped;
};
int main() {
    Thread td;
    td.Start();
    while (1) {

    }
    return 0;
}

