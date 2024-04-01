#include "prototypes.h"
#define MAX_TOLL 100

class Vehicle {
	bool is_ready;
	int current_junction;
	int destination_junction;
	public:
		Vehicle(const int,const int,const bool);
		void change_status(const bool);
		bool get_status() const;
		int get_dest() const;
};

class Toll {
	protected:
		Segment* segment_of_toll;	
		int waiting_vehicles;
		list<Vehicle*> vehicles;
		int get_destination(Segment*);
	public:
		// Toll(Segment*);
		void add_vehicles(int);
		Vehicle* remove_vehicle();
		list<Vehicle*> get_vehicles(int);
		virtual bool is_electronic();
		virtual ~Toll();
};

class Entrance {
	Segment* current_segment;
	int junction_id;
	int total_tolls;
	Toll** tolls;
	public:
		Entrance(const int,const int,Segment*);
		~Entrance();
		list<Vehicle*> operate(const int,const int);
		void add_random_cars_to_this_entrance();
		// list<Vehicle*> cars_from_entrance(const int,const int);
};

class Segment {
	protected:
		Highway* highway;
		int segment_num;
		int K;
		Entrance entrance;
		int num_of_vehicles;
		const int percent;
		list<Vehicle*> vehicles;
		const int capacity;
		Segment* segment_prev = NULL;
		Segment* segment_next = NULL; 
	public:
		Segment(const int,const int,const int,const int, Segment*,Segment*,Highway*);
		~Segment();
		void enter();
		void exit();
		list<Vehicle*> pass(Segment *);
		int get_num_of_vehicles();
		void operate();
		int get_segment_num();
};


class Electronic_toll : public Toll {
	public:
		Electronic_toll(Segment*);
		bool is_electronic();
		~Electronic_toll();
};

class Employed_toll : public Toll {
	public:
		Employed_toll(Segment*);
		bool is_electronic();
		~Employed_toll();
};

class Highway {
	const int Nsegs;
	int num_of_vehicles;
	Segment** segments;
	void update_num_of_vehicles();
	public:
		Highway(const int,const int,const int,const int);
		~Highway();
		void operate();
		int get_num_of_vehicles() const;
		int get_segs() const;
};