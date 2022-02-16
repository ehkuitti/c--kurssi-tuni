#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
    : cycle_(cycle)
{
}

Queue::~Queue()
{

}

void Queue::enqueue(const string& reg)
{
    if(is_green_ == true)
    {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        return;
    }

    Vehicle* new_vehicle = new Vehicle({reg, nullptr});
    if (last_ != nullptr)
    {
        last_->next = new_vehicle;
    }
    else
    {
        first_ = new_vehicle;
    }
    last_ = new_vehicle;
}

void Queue::switch_light()
{
    //looppi tähän

    is_green_ = not is_green_;
//    std::cout << is_green_;

    if (is_green_ == false and first_ == nullptr)
    {
        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == true and first_ == nullptr){
        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == true and first_ != nullptr)
    {
        std::cout << "GREEN: Vehicle(s) ";
        //Vehicle* vehicle_pointer = first_;
        unsigned int i = 0;
        while (first_ != nullptr and i < cycle_)
        {
            std::cout << first_->reg_num << " ";
            remove_vehicle();
            i++;
        }
        std::cout << "can go on" << std::endl;
        is_green_ = false;

    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;

    if (cycle < 1)
    {
        cycle_ = 1;
    }
}

void Queue::print()
{

    if (is_green_ == false and first_ == nullptr)
    {
        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == true and first_ == nullptr){
        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == false) //Jos valo on punainen
    {
       std::cout << "RED: Vehicle(s) ";
//        Vehicle* next_of_first = first_->next;
//        std::cout << (*next_of_first).reg_num;
//        unsigned int i = 0;

//       Vehicle* old_first = first_;
//       std::cout << old_first->reg_num << " ";
//       first_ = first_->next;

       Vehicle* tulostettava = first_;

        while (tulostettava != nullptr)
        {
            std::cout << tulostettava->reg_num << " ";

            tulostettava = tulostettava->next;
        }

        std::cout << "waiting in traffic lights" << std::endl;
    }
    else {
        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
    }

}

bool Queue::remove_vehicle()
{
    if (first_ == nullptr)
    {
        return false;
    }

    else if (first_ == last_)
    {
        last_ = nullptr;
    }

    Vehicle* old_first = first_;
    first_ = first_->next;
    delete old_first;
    old_first = nullptr;

    return true;
}
