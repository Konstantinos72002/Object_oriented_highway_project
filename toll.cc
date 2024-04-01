#include "headers.h"

int Toll::get_destination(Segment* p)
{
    const int minimum = p->get_segment_num();
    const int random = rand()%(MAX_TOLL-minimum +1);
    return random+minimum;
}

// Toll::Toll(Segment *p) {;}

Toll::~Toll() {
    /* Virtual function */ ;
}

Electronic_toll::Electronic_toll(Segment* p) {
    Toll::segment_of_toll = p;
    Toll::waiting_vehicles = rand()%MAX_TOLL;
	for(int i=0;i<Toll::waiting_vehicles;i++)
	{
		Vehicle* to_add = new Vehicle(p->get_segment_num(),get_destination(p),false);
		vehicles.push_back(to_add);
	}
}

Employed_toll::Employed_toll(Segment* p) {
    Toll::segment_of_toll = p;
    Toll::waiting_vehicles = rand()%MAX_TOLL;
	for(int i=0;i<Toll::waiting_vehicles;i++)
	{
		Vehicle* to_add = new Vehicle(p->get_segment_num(),get_destination(p),false);
		vehicles.push_back(to_add);
	}
}

void Toll::add_vehicles(int new_veh)
{
    waiting_vehicles+=new_veh;
    for (int i  = 0 ; i < new_veh; i++)
    {
        Vehicle* p = new Vehicle(segment_of_toll->get_segment_num(),get_destination(segment_of_toll),false);
        vehicles.push_back(p);
    }
}

Vehicle* Toll::remove_vehicle() {
    std::list<Vehicle*>::iterator it = vehicles.begin();
    vehicles.pop_front();
    return *it;
}

list<Vehicle*> Toll::get_vehicles(int N) {
    if (N>waiting_vehicles)
    {
        N = waiting_vehicles;
        // Return all the vehicles if asked for more and print corresponding message..
        cout << "Tried to get more vehicles from a toll than that toll has. Will return ALL the vehicles of the toll" << endl;
    }
    list<Vehicle*> to_return;
    std::list<Vehicle*>::iterator it=vehicles.begin();
    for(int i =0;i<N;i++) {
        to_return.push_back(*it);
        advance(it, 1);
    }
    for (int i  = 0 ; i < N ; i++)
    {
        vehicles.pop_front();
        // Vehicle not destroyed because it is contained on the other list. It is responsibility
        // of the other function to free it..
    }
    return to_return;
}
bool Toll::is_electronic() {return false;}; 
bool Electronic_toll::is_electronic() {return true;}
bool Employed_toll::is_electronic() {return false;}


Electronic_toll::~Electronic_toll() {
    for (unsigned int i  = 0 ; i < Toll::waiting_vehicles ; i++) {
        std::list<Vehicle*>::iterator it=vehicles.end();
        Vehicle* deleted_vehicle = *it;
        delete deleted_vehicle;
        vehicles.pop_front();
    }
}
Employed_toll::~Employed_toll() {
    for (unsigned int i  = 0 ; i < Toll::waiting_vehicles ; i++) {
        std::list<Vehicle*>::iterator it=vehicles.end();
        Vehicle* deleted_vehicle = *it;
        delete deleted_vehicle;
        vehicles.pop_front();
    }
}