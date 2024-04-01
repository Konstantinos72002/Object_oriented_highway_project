#include <vector>
#include <stdlib.h>
#include <iterator>
#include "headers.h"

using namespace std;

int Segment::get_segment_num()
{
	return segment_num;
}

Segment::Segment(const int s_n,const int cap,const int K_, const int perc, Segment* p_s,Segment* n_s,Highway* hw) :
    segment_num(s_n),capacity(cap),K(K_),segment_prev(p_s), segment_next(n_s),highway(hw),entrance(s_n,rand()%10,this), percent(perc){
	num_of_vehicles = rand()%capacity;
	for(int i=0;i<num_of_vehicles;i++)
	{
		Vehicle* to_add = new Vehicle(segment_num,highway->get_segs(),false);
		vehicles.push_back(to_add);
	}
}

void Segment::operate() {
	//First, a number of vehicles leave the current segment.
	exit();
	//Afterwards, vehicles that are ready on the previous segment enter the current segment.
	enter();
	// Update the number of vehicles that arr currently on our segment..
	num_of_vehicles = vehicles.size();
	if(num_of_vehicles < capacity) K--;
	else K++;
	//Now set percent of the cars that entered as "READY" (as cars were entering, they were all set as false..)
	std::list<Vehicle*>:: iterator itr = vehicles.begin();
	for (int i = 0; i<(vehicles.size())*(percent/100); i++)
	{
		Vehicle* current_check = *itr;
		current_check->change_status(true);
		advance(itr, 1);
	}
}

void Segment::enter() {
	// Vehicles that enter the current segment from previous segment.
	if (segment_prev!=NULL)
	{
		vehicles.merge(segment_prev->pass(this)); // Merges the current vehicle list with the list of cars that passed from previous segment.
	}
	//Afterwards, vehicles that enter to current segment from entrance;
	list<Vehicle*> vehicles_from_entrance = entrance.operate(capacity-num_of_vehicles,K);
	if(vehicles_from_entrance.size() != 0) {
		vehicles.merge(vehicles_from_entrance);
	}
}

void Segment::exit() {
	std::list<Vehicle*>:: iterator itr = vehicles.begin();
	int initial_num_of_vehicles = num_of_vehicles;
	for (int i = 0; i<(initial_num_of_vehicles); i++)
	{
		Vehicle* current_check = *itr;
		if (current_check->get_dest() == segment_num && (current_check->get_status()))
		{
			vehicles.erase(itr);
			cout << "A vehicle left the highway at segment " << segment_num << endl;
			num_of_vehicles--;
		}
		advance(itr, 1);
	}
}

list<Vehicle*> Segment::pass(Segment* current_segment) {
	//This function is called from the previous segment to the current one. 
	// It returns a list of the cars that can be passed. That list is appended to the current segment in the *enter* function
	list<Vehicle*> cars_that_pass;
	std::list<Vehicle*>:: iterator itr = vehicles.begin(); // vehicles of the previous segment **
	int initial_prev_vehicles =  get_num_of_vehicles(); // The number of vehicles that we originally had, before vehicles getting out
	for (int i=0; i<initial_prev_vehicles; i++)
	{
		if(capacity == num_of_vehicles)  break;
		Vehicle* current_check = *itr;
		if (current_check->get_status())
		{
			current_check->change_status(false); // Passing cars as false so that the status can be changed later to true for the corresponding percentage
			cars_that_pass.push_back(*itr);
			vehicles.erase(itr);
			cout << "A vehicle moved from segment" << segment_num << " to " << current_segment->get_segment_num() << endl;
			num_of_vehicles--;
		}
		advance(itr, 1);
	}
	// Now fetch cars from tolls on the entrance
	return cars_that_pass;
}

int Segment::get_num_of_vehicles() {
	return num_of_vehicles;
}
Segment::~Segment() {
	for (unsigned int i  = 0 ; i < num_of_vehicles ; i++) {
		std::list<Vehicle*>::iterator it=vehicles.end();
		Vehicle* deleted_vehicle = *it;
		delete deleted_vehicle;
		vehicles.pop_front();
	}
}