#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

class customer
{
public:
	int timestamp;
	string name;
	string status;
	int duration;
};

int main()
{
	Dlist<customer> regular, silver, gold, platinum;
	Dlist<customer> all;
	int tick = 0;
	int availableTime = 0;
	int eventCount = 0;
	cin >> eventCount;
	for (int i = 0; i < eventCount; i ++)
	{
		customer* a = new customer;
		cin >> a->timestamp >> a->name >> a->status >> a->duration;
		customer* b = new customer(*a);
		all.insertBack(b);
		if (a->status == "regular")
			regular.insertBack(a);
		else if (a->status == "silver")
			silver.insertBack(a);
		else if (a->status == "gold")
			gold.insertBack(a);
		else if (a->status == "platinum")
			platinum.insertBack(a);
	}
	bool busy = false;
	while (1)
	{
		cout << "Starting tick #" << tick << endl;
		if (regular.isEmpty() and silver.isEmpty() and gold.isEmpty() and platinum.isEmpty())
			break;
		while (!all.isEmpty())
		{
			customer* c = all.removeFront();
			if (c -> timestamp != tick)
			{
				all.insertFront(c);
				break;
			}
			else
			{
				cout << "Call from " << c->name << " a " << c->status << " member" << endl;
			}
			delete c;
		}
		if (tick < availableTime)
			busy = true;
		else
			busy = false;

		while (!busy)
		{
			if (!platinum.isEmpty())
			{
				customer* c = platinum.removeFront();
				if (c -> timestamp <= tick)
				{
					availableTime = tick + c->duration;
					cout << "Answering call from " << c->name << endl;
					delete c;
					break;
				}
				else
					platinum.insertFront(c);
			}
			if (!gold.isEmpty())
			{
				customer* c = gold.removeFront();
				if (c -> timestamp <= tick)
				{
					availableTime = tick + c->duration;
					cout << "Answering call from " << c->name << endl;
					delete c;
					break;
				}
				else
					gold.insertFront(c);
			}
			if (!silver.isEmpty())
			{
				customer* c = silver.removeFront();
				if (c -> timestamp <= tick)
				{
					availableTime = tick + c->duration;
					cout << "Answering call from " << c->name << endl;
					delete c;
					break;
				}
				else
					silver.insertFront(c);
			}
			if (!regular.isEmpty())
			{
				customer* c = regular.removeFront();
				if (c -> timestamp <= tick)
				{
					availableTime = tick + c->duration;
					cout << "Answering call from " << c->name << endl;
					delete c;
					break;
				}
				else
					regular.insertFront(c);
			}
			break;
		}
		tick ++;
	}
}
