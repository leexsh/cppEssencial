#include <iostream>
#include <memory>
using namespace std;

int main() {
    std::unique_ptr<int> sp1(std::make_unique<int>(12));
    std::unique_ptr<int> sp2 = std::move(sp1);
    std::unique_ptr<int> sp3 = std::make_unique<int>(1);
    std::cout<<*sp3<<std::endl;
    std::cout<<sp3.get()<<std::endl;

    std::shared_ptr<int> sp4 = std::make_shared<int>(123);
    cout<<*sp4<<endl;
    sp4 = move(sp2);
    cout<<*sp4<<endl;
    sp4.reset();
    if (!sp4) {
        cout << "sp4 is nullptr" << endl;
    }
    else {
        cout << "sp4 is not nullpty" << endl;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
