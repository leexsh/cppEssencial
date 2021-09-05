#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <iostream>


class Task {
public:
	Task(int taskID) {
		this->taskID = taskID;
	}

	~Task() {
	}

	void doTask() {
		std::cout << "handle a task taskID is : " << taskID << " , threadID is :" << std::this_thread::get_id() << std::endl;
	}
private:
	int taskID;
};


std::mutex mymutex;
std::list<Task*> tasks;
std::condition_variable mycv;

void* consumer_thread() {
	Task* pTask = nullptr;
	while (true) {
		std::unique_lock<std::mutex> guard(mymutex);
		while (tasks.empty()) {
			mycv.wait(guard);
		}
		pTask = tasks.front();
		tasks.pop_front();

		if (pTask == nullptr) {
			continue;
		}
		pTask->doTask();
		delete pTask;
		pTask = nullptr;
	}
	return nullptr;
}

void* product_thread() {
    int taskID = 0;
    Task* pTask = nullptr;

    while (true) {
        pTask = new Task(taskID);
        {
            std::lock_guard<std::mutex> guard(mymutex);
            tasks.emplace_back(pTask);
            std::cout << "produce a task id is" << taskID << " , threadId is: "<< std::this_thread::get_id() << std::endl;
        }
        mycv.notify_one();
        taskID++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return nullptr;
}

int main() {
    std::thread consumer1(consumer_thread);
    std::thread consumer2(consumer_thread);
    std::thread consumer3(consumer_thread);
    std::thread consumer4(consumer_thread);
    std::thread consumer5(consumer_thread);

    std::thread producer(product_thread);
    producer.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    consumer5.join();
    return 0;
}
