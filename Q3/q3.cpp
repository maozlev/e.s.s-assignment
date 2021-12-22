//Question 3 - pointers

// There is a memory leak in the code below, where is it?,
// what class/solution can you use to fix it while ensuring that the object will be deleted only once
// and only when it's not used by any consumer
// Task: Modify the code to address the issues above.
// Please explain the changes you made and how they solve the memory allocation/deletion issue

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature

/// Q3:

// When we called new operator there is an allocation of memory on the heap.
// On this program there is use with 2 threads on 1 object- "Payload" both of them activate by one thread t.
// write new operator for this program to control the leaks. now I can see all allocations.
// write delete operator for this program to control the frees. now I can see all frees.
// with these operators find leaks can be very easy to debug.
// write a struct to check the allocation vs freed memory.
// write function that print the memory usage.
// print the allocation usage after the 2 threads are finish.

// *** another option is to use valgrind when compile the program.

/// Modify:

// with Smart pointer we don't need to worry about delete / free memory that's why im using shared pointer.
// change signature of the operation function to be able to receive smart pointer


#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <memory>

struct AllocationMetrics{
    uint32_t TotalAllocated=0;
    uint32_t TotalFreed=0;
    uint32_t CurrentUsage(){return TotalAllocated-TotalFreed; }
};static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size){
    s_AllocationMetrics.TotalAllocated+=size;
    return malloc(size);
}

void operator delete(void* memory, size_t size){
    free(memory);
    s_AllocationMetrics.TotalFreed+=size;
}
static void PrintMemoryUsage(){
    std::cout<< "Memory usage: "<<s_AllocationMetrics.CurrentUsage()<<"bytes"<<std::endl;
}

struct Payload {
    Payload(uint64_t id_) : id(id_), veryLargeVector(1000 * 1000)
    {}
    uint64_t id;
    std::vector<int> veryLargeVector;
};

void operation1(std::shared_ptr<Payload> p) {
    std::cout << "Performing operation1 on payload " << p->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
    std::cout << "Operation1 Performed" << std::endl;
}

void operation2(std::shared_ptr<Payload> p) {
    std::cout << "Performing operation2 on payload "  << p->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
    std::cout << "Operation2 Performed" << std::endl;
}

void dispacher_thread() {
//    Payload* payload = new Payload(1);
    std::shared_ptr<Payload> p= std::make_shared<Payload>(1);
    std::shared_ptr<Payload> p1=p;
    std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
    std::thread wt1(&operation1,p);
    std::thread wt2(&operation2, p1);
    //Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
    wt1.detach();
    wt2.detach();
}

int main(int argc, char** argv)
{
    std::cout << "Calling dispatcher thread" << std::endl;
    std::thread t(&dispacher_thread);
    t.join();
    std::cout << "Press enter to exit" << std::endl;
    getchar();
    // here's the checking of leaking memory. when operations are finish just press enter and see that there are no memory lacks.
    PrintMemoryUsage();
    return 0;
}