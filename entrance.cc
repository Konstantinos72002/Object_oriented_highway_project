#include "headers.h"

Entrance::Entrance(const int j_id, const int toll_count,Segment* s) : junction_id(j_id), total_tolls(toll_count) {
	tolls = new Toll*[total_tolls];
	for (unsigned int i=0; i<total_tolls; i++)
	{
		const int mode = rand()%2;
		if (mode)
		{
			tolls[i] = new Employed_toll(s);
		}
		else
		{
			tolls[i] = new Electronic_toll(s);
		}
	}
	//Entrance created
}

list<Vehicle*> Entrance::operate(const int max_limit,const int K) {
	unsigned int have_passed_by_empoloied=0,have_passed_by_electronic=0;
	list<Vehicle*> return_list;
	if(max_limit == 0) {
		for(unsigned int i = 0;i<total_tolls;i++) {
			tolls[i]->add_vehicles(rand()%20);
		}
		return return_list;
	}
	while (true) {
		bool car_has_entered = false;
		for(unsigned int i=0;i<total_tolls;i++) {
			if(have_passed_by_electronic+have_passed_by_empoloied == max_limit) {
				for(unsigned int i = 0;i<total_tolls;i++) {
					tolls[i]->add_vehicles(rand()%20);
				}
				return return_list;
			}
			if(tolls[i]->is_electronic() && have_passed_by_electronic < 2*K) {
				// Move the first vehicle of list at return list

				Vehicle* push_vehicle = tolls[i]->remove_vehicle();
				return_list.push_back(push_vehicle);
				push_vehicle->change_status(false); 
				have_passed_by_electronic++;
				car_has_entered = true;
			}
			else if (!(tolls[i]->is_electronic()) && have_passed_by_empoloied < K){
				// Move the first vehicle of list at return list

				Vehicle* push_vehicle = tolls[i]->remove_vehicle();
				return_list.push_back(push_vehicle);
				push_vehicle->change_status(false); 
				have_passed_by_electronic++;
				car_has_entered = true;
			}
		}	
		if(!car_has_entered) {
			for(unsigned int i = 0;i<total_tolls;i++) {
				tolls[i]->add_vehicles(rand()%20);
			}
			return return_list;
		}
	}
	for(unsigned int i = 0;i<total_tolls;i++) {
			tolls[i]->add_vehicles(rand()%20);
	}
			return return_list;
}

Entrance::~Entrance() {
	for (unsigned int i=0; i<total_tolls; i++)
	{
		delete tolls[i];
	}
	delete[] tolls;
}