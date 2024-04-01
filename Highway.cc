#include "headers.h"

Highway::Highway(const int n_s,const int capacity,const int K,const int perc):Nsegs(n_s) {
	cout << "Highway operating" << endl;
	segments = new Segment*[n_s];
	segments[0] = new Segment(0,capacity,K,perc,NULL,segments[1],this);
	for(unsigned int i=1;i<n_s-1;i++) {
		segments[i] = new Segment(i,capacity,K,perc,segments[i-1],segments[i+1],this); 
	} 
	segments[n_s-1] = new Segment(n_s,capacity,K,perc,segments[n_s-1],NULL,this);
	update_num_of_vehicles();
}

int Highway::get_num_of_vehicles() const {
	return num_of_vehicles;
}

int Highway::get_segs() const {
	return Nsegs;
}

void Highway::operate() {
	for(int i = Nsegs-1;i>=0;i--) {
		segments[i]->operate();
	}
	update_num_of_vehicles();
}
void Highway::update_num_of_vehicles() {
	unsigned int sum = 0;
	for(unsigned int i = 0;i<Nsegs;i++)
	{
		sum += segments[i]->get_num_of_vehicles();
	}
	num_of_vehicles = sum;
}

Highway::~Highway() {
	for(unsigned int i =0; i<Nsegs;i++) {
		delete segments[i];
	}
	delete[] segments;
}