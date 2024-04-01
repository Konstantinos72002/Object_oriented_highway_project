#include "headers.h"

void Vehicle::change_status(const bool new_status)
{
    is_ready = new_status;
}

bool Vehicle::get_status() const
{
    return is_ready;
}

int Vehicle::get_dest() const
{
    return destination_junction;
}

Vehicle::Vehicle(const int cur,const int dest,const bool ready) : is_ready(ready),current_junction(cur),destination_junction(dest) {}