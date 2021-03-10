#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

int sw = 14;

template <class MyType>

void MySwap (MyType &v1, MyType &v2) {
	MyType v3 = v1;
	v1 = v2;
	v2 = v3;
}

template <class ArrayType, class LessFunctionType>
int FindMinimumIndex (ArrayType &data_array, int beginIndex, int endIndex, LessFunctionType LessFunction){
	int minimumIndex = beginIndex;
	for (int element_number = beginIndex + 1; element_number <= endIndex; ++element_number) {
		if (LessFunction (data_array[element_number], data_array[minimumIndex])) {
		minimumIndex = element_number;
		}
	}
return minimumIndex;
}

template <class ArrayType, class LessFunctionType>
void SelectionSort (ArrayType &data_array, int beginIndex, int endIndex, LessFunctionType LessFunction) {
	for (int element_number = beginIndex; element_number < endIndex; ++element_number) {
		int minimumIndex = FindMinimumIndex (data_array, element_number, endIndex, LessFunction);
		MySwap (data_array[minimumIndex], data_array[element_number]);
	}
}

class Vehicle {
protected:
	double distance;
	double time;

private:
	void set_name(string s){
		name = s;
	}
	double baseSpeed;

public:
	string name;
	double speed;
	Vehicle (string _name = "Untyped vehicle", double _speed = -1) {
		name = _name;
		speed = _speed;
		distance = 0;
		time = 0;
	}
	virtual ~Vehicle () {
	}
	virtual bool MakeTrip(double distanceOfTrip) = 0;
	string get_name(){ return name; };
	double get_speed(){ return speed; };
	double get_distance(){ return distance; };
	double get_time(){ return time; };

	bool operator< (Vehicle &rhs) {
		if (get_speed () < rhs.get_speed()) {
			return true;
		}
		return false;
	}
};

bool CompareDefault (Vehicle *lhs, Vehicle *rhs) {
	return *lhs < *rhs;
}
bool CompareTime (Vehicle *lhs, Vehicle *rhs) {
	return lhs->get_time() < rhs->get_time();
}

const double DefaultMaxDistance = 1000;

class Coach : public Vehicle {
protected:
	double MAX_DISTANCE;
public:
	Coach (string _name = "Default Coach", double _speed = 10) {
		name = _name;
		speed = _speed;
		distance = 0;
		time = 0;
		MAX_DISTANCE = DefaultMaxDistance;
	}
	void set_max_dist(double d){
		MAX_DISTANCE = d;
	}
	virtual bool MakeTrip(double distanceOfTrip) override{
		if(speed != 0) {
			distance += distanceOfTrip;
			time += distanceOfTrip / speed;
			speed *= exp(-time/500.);
			return 1;
		}
		else {
			return 0;
		}
	}
};

class Automobile : public Vehicle {
public:
	Automobile (string _name = "Default Automobile", double _speed = 100) {
		name = _name;
		speed = _speed;
		distance = 0;
		time = 0;
	}
	virtual bool MakeTrip(double distanceOfTrip) {
		if(speed != 0) {
			distance += distanceOfTrip;
			time += distanceOfTrip / speed;
			speed *= exp(-distance/500.);
			return 1;
		}
		else {
			return 0;
		}
	}
};

const double DefaultTimeToBoot = 0.01;

class Computer {
public:
	Computer () : base_time_to_boot (DefaultTimeToBoot) {}
	double get_time_to_boot () { 
		return base_time_to_boot;
	}
	void ComputerUpdate(double newTimeToBoot) {
		base_time_to_boot = newTimeToBoot;
	}
protected:
	double base_time_to_boot;
};

const double DefaultMaxFlyTime = 10000;

class Aeroplane : public Vehicle {
private:
	double MAX_FLY_TIME;
	double time_since_last_repair;
	Computer c;
protected:
	double base_time_to_boot;
public:
	void repair(){
		time_since_last_repair = 0;
	}
	void set_max_fly_time(double t){
		MAX_FLY_TIME = t;
	}
	double get_time_to_boot() { return c.get_time_to_boot(); }
	double get_time_since_last_repair() { return time_since_last_repair; }
	Aeroplane (string _name = "Default Aeroplane", double _speed = 500) {
		name = _name;
		speed = _speed;
		distance = 0;
		time = 0;
		time_since_last_repair = 0;
		MAX_FLY_TIME = DefaultMaxFlyTime;
	}
	virtual bool MakeTrip (double distanceOfTrip) {
		double timeOfTrip = distanceOfTrip / get_speed () + c.get_time_to_boot();
		if (time_since_last_repair + timeOfTrip > MAX_FLY_TIME) {
			return false;
		}
		time_since_last_repair += timeOfTrip;
		distance += distanceOfTrip;
		time += timeOfTrip;
		return true;
	}
	bool operator< (Aeroplane &rhs) {
		if (get_time_since_last_repair () < rhs.get_time_since_last_repair()) {
			return true;
		}
		return false;
	}
	void boot_time_update (double newTimeToBoot) {
		c.ComputerUpdate(newTimeToBoot);
	}
};

bool CompareTimeSinceLastRepair (Aeroplane *lhs, Aeroplane *rhs) {
	return *lhs < *rhs;
}


void CommitRandomTrips(vector <Vehicle *> &vehicles) {
	for(int i = 0; i < vehicles.size(); ++i) {
		double randomDistance = double(rand() % 20001) / 10.;
		vehicles[i]->MakeTrip(randomDistance);
	}
}


void DisplayVehicles (vector <Vehicle *> &vehicles) {
	cout << setw(sw) << "name" << setw(sw) << "speed" << setw(sw)  << "distance" << setw(sw) << "time" << endl;
	for (int i = 0; i < vehicles.size(); ++i) {
		cout << setw(sw) << vehicles[i]->get_name() << setw(sw) << vehicles[i]->get_speed() << setw(sw) << vehicles[i]->get_distance() << setw(sw) << vehicles[i]->get_time() << endl;
	}
	cout << endl << endl;
}

void DisplayAeroplanes (vector <Aeroplane *> &vehicles) {
	cout << setw(sw) << "name" << setw(sw) << "speed" << setw(sw)  << "distance" << setw(sw) << "time" << setw(sw) << "timesincerep" << endl;
	for (int i = 0; i < vehicles.size(); ++i) {
		cout << setw(sw) << vehicles[i]->get_name() << setw(sw) << vehicles[i]->get_speed() << setw(sw) << vehicles[i]->get_distance() << setw(sw) << vehicles[i]->get_time() << setw(sw) << vehicles[i]->get_time_since_last_repair() << endl;
	}
	cout << endl << endl;
}


void test1() {

	srand(0);

	vector <Coach> coaches;
	vector <Automobile> automobiles;
	vector <Aeroplane> aeroplanes;

	coaches.push_back(Coach("Coach 1", 9.));
	coaches.push_back(Coach("Coach 2", 11.));
	coaches.push_back(Coach("Coach 3", 10.));
	coaches.push_back(Coach("Coach 4", 9.5));
	coaches.push_back(Coach("Coach 5"));

	automobiles.push_back(Automobile("Automobile 1"));
	automobiles.push_back(Automobile("Automobile 2", 90.));
	automobiles.push_back(Automobile("Automobile 3", 120.));
	automobiles.push_back(Automobile("Automobile 4", 150.));

	aeroplanes.push_back(Aeroplane("Aeroplane 1", 1030.));
	aeroplanes.push_back(Aeroplane("Aeroplane 2", 560.));
	aeroplanes.push_back(Aeroplane("Aeroplane 3", 2200.));

	vector<Vehicle *> coachPointers;
	vector<Vehicle *> automobilePointers;
	vector<Vehicle *> aeroplanePointers;
	vector<Aeroplane *> aeroplanePointers1;
	vector <Vehicle *> vehiclePointers;

	for (int i = 0; i < coaches.size(); ++i) {
		coachPointers.push_back(&coaches[i]);
		vehiclePointers.push_back(&coaches[i]);
	}
	
	for (int i = 0; i < automobiles.size(); ++i) {
		automobilePointers.push_back(&automobiles[i]);
		vehiclePointers.push_back(&automobiles[i]);
	}
	
	for (int i = 0; i < aeroplanes.size(); ++i) {
		aeroplanePointers.push_back(&aeroplanes[i]);
		aeroplanePointers1.push_back(&aeroplanes[i]);
		vehiclePointers.push_back(&aeroplanes[i]);
	}

	DisplayVehicles(vehiclePointers);

	CommitRandomTrips(vehiclePointers);

	DisplayVehicles(vehiclePointers);

	CommitRandomTrips(aeroplanePointers);
	DisplayAeroplanes(aeroplanePointers1);
	SelectionSort(aeroplanePointers1, 0, aeroplanePointers1.size() - 1, CompareTimeSinceLastRepair);
	DisplayAeroplanes(aeroplanePointers1);
	aeroplanePointers1[aeroplanePointers1.size() - 1]->repair();
	DisplayAeroplanes(aeroplanePointers1);	

}

int main() {
	test1();
}