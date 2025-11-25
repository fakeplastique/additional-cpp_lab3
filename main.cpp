// Ihor Bondar K-25, gcc

#include <iostream>
#include <thread>
#include <barrier>
#include <format>
#include <syncstream>
#include <vector>

using namespace std;

const int nt = 5;
barrier sync_point(nt);

void synchronizedOut(const string &s) {
    osyncstream(cout) << s;
}

void f(char actionSet, int actionIdx) {
    synchronizedOut(format("З набору {} виконано дію {}.\n", actionSet, actionIdx));
}

void thread1() {
    for (int i = 1; i <= 9; i++)
        f('a', i);
    sync_point.arrive_and_wait();

    for (int i = 1; i <= 4; i++)
        f('g', i);
    sync_point.arrive_and_wait();

    f('j', 1);
}

void thread2() {
    for (int i = 1; i <= 9; i++)
        f('e', i);
    sync_point.arrive_and_wait();

    f('g', 5);
    for (int i = 1; i <= 3; i++)
        f('h', i);
    sync_point.arrive_and_wait();

    f('j', 2);
}

void thread3() {
    for (int i = 1; i <= 5; i++)
        f('b', i);
    for (int i = 1; i <= 3; i++)
        f('d', i);
    sync_point.arrive_and_wait();

    for (int i = 4; i <= 7; i++)
        f('h',i);
    sync_point.arrive_and_wait();

    f('j', 3);
}

void thread4() {
    for (int i = 1; i <= 7; i++)
        f('c', i);
    f('d', 4);
    f('d', 5);
    sync_point.arrive_and_wait();

    f('h', 8);
    f('h', 9);
    f('i', 1);
    f('i', 2);
    sync_point.arrive_and_wait();

    f('j', 4);
    f('j', 5);
}

void thread5() {
    for (int i = 6; i <= 8; i++)
        f('d', i);

    for (int i = 1; i <= 5; i++)
        f('f', i);
    sync_point.arrive_and_wait();

    for (int i = 3; i <= 6; i++)
        f('i', i);

    sync_point.arrive_and_wait();
    f('j', 6);
    f('j', 7);
}

using MAIN = void();

MAIN *functions[] = {thread1, thread2, thread3, thread4, thread5};

int main()
{

    synchronizedOut("Обчислення розпочато.\n");

    {
        std::vector<jthread> threads;
        for (int i = 0; i < 5; i++)
            threads.emplace_back(functions[i]);
    }

    synchronizedOut("Обчислення завершено.\n");



}