#include <iostream>
#include <string>
#include <thread>
#include <omp.h>

using namespace std;

class Truck
{

private:
    int id;

public:
    Truck(int); // constructor
    int getID();
    void assingLeadership();
    bool steering();
    bool brake();
    bool accelerate();
    bool connect(Truck t);
    static bool isConnected(Truck, Truck);
};

int Truck::getID()
{
    return id;
}

void Truck::assingLeadership()
{

    cout << "Truck " << id << " Is Leader" << endl;
}

bool Truck::steering()
{

    cout << "drive ahead" << endl;
    return 1;
}

bool Truck::brake()
{

    cout << "Truck " << id << "Is Breaking";
    return 1;
}

bool Truck::accelerate()
{

    cout << "Truck " << id << "Is Accelerating";
    return 1;
}

bool Truck::connect(Truck t)
{

    cout << "Connected " << endl;
    return 1;
}

bool Truck::isConnected(Truck t1, Truck t2)
{

    if (t1.connect(t2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Truck truck0(0);
Truck truck1(1);
Truck truck2(2);
Truck truck3(3);

void thread_steering()
{

    while (true)
    {

#pragma omp parallel num_threads(3)
        {

#pragma omp task
            {
                truck1.steering();
                this_thread::sleep_for(100ms);
            }

#pragma omp task
            {
                truck2.steering();
                this_thread::sleep_for(100ms);
            }

#pragma omp task
            {
                truck3.steering();
                this_thread::sleep_for(100ms);
            }
        }
    }
}

void thread_brake()
{

    while (true)
    {

#pragma omp parallel num_threads(3)
        {

#pragma omp task
            {
                if (truck0.steering())
                {
                    truck1.steering();
                    this_thread::sleep_for(100ms);
                }
            }

#pragma omp task
            {
                if (truck0.steering())
                {
                    truck2.steering();
                    this_thread::sleep_for(100ms);
                }
            }

#pragma omp task
            {
                if (truck0.steering())
                {
                    truck3.steering();
                    this_thread::sleep_for(100ms);
                }
            }
        }
    }
}

void thread_accelerate()
{

    while (true)
    {

#pragma omp parallel num_threads(3)
        {

#pragma omp task
            {
                truck1.accelerate();
                this_thread::sleep_for(100ms);
            }

#pragma omp task
            {
                truck2.accelerate();
                this_thread::sleep_for(100ms);
            }

#pragma omp task
            {
                truck3.accelerate();
                this_thread::sleep_for(100ms);
            }
        }
    }
}

void thread_connect()
{

    while (true)
    {

#pragma omp parallel num_threads(3)
        {

#pragma omp task
            {
                if (!Truck::isConnected(truck0, truck1))
                {
                    truck0.connect(truck1);
                    this_thread::sleep_for(100ms);
                }
            }

#pragma omp task
            {
                if (!Truck::isConnected(truck0, truck2))
                {
                    truck0.connect(truck2);
                    this_thread::sleep_for(100ms);
                }
            }

#pragma omp task
            {
                if (!Truck::isConnected(truck0, truck3))
                {
                    truck0.connect(truck3);
                    this_thread::sleep_for(100ms);
                }
            }
        }
    }
}

int main()
{

    truck0.assingLeadership();

#pragma omp parallel num_threads(3)
{
#pragma omp task
    truck0.connect(truck1);
#pragma omp task
    truck0.connect(truck2);
#pragma omp task
    truck0.connect(truck3);
}

thread t1(thread_steering);
thread t2(thread_brake);
thread t3(thread_accelerate);
thread t4(thread_connect, t1, t2);

t1.join();
t2.join();
t3.join();
t4.join();

}