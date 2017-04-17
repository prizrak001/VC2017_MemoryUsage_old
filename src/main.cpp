#include <iostream>
#include <list>

class Aaa {
    public:
        int int1;
        double double1;
};

using AaaList = std::list<Aaa>;

AaaList aaaList;

void fillList(size_t n) {
    for (size_t i = 0; i < n; ++i) {
        aaaList.push_back(Aaa{ 3, 5.7 });
    }
}

void fillList() {
    fillList(300000);
}

void clearList() {
    aaaList.clear();
}

int main() {
    for (size_t i = 0; i < 5; ++i) {
        fillList();
        clearList();
    }

    return EXIT_SUCCESS;
}

