#include <iostream>
#include "PriorityQueue.h"

using namespace std;

MinHeap::MinHeap()
{
  size = 0;
  // assign empty values in frontier?
}





/** PRIVATE */

// TODO
void MinHeap::SortPriority(int loc)
{
	if (size == 1) {
		return;
	}
	
	else {
		
		int parent;
		parent = (loc - 1) / 2;
		
		while (parent >= 0) {	// check that it's not out of range

			if (keys[parent].cost > keys[loc].cost) {
				Swap(parent, loc); // if it doesn't swap, break the loop
			}
			else { break; }

			parent = (parent - 1) / 2;
		}
		
		return;
	}
}


void MinHeap::Swap(int one, int two)
{
	int temp_loc;
	Key temp_key;
	
	temp_loc = locations[one];
	locations[one] = locations[two];
	locations[two] = temp_loc;
	
	temp_key = keys[one];
	keys[one] = keys[two];
	keys[two] = temp_key;
	
	return;
}
 
 
// Basically it's bfs
int MinHeap::Find(int location)
{
	for (int i = 0; i < size; i++) {
		if (locations[i] == location) { return i; }
	}
	// if not found, return -1
  return -1;
}




/** PUBLIC */


void MinHeap::IncreaseSize()
{
  size += 1;
  return;
}

// TODO
void MinHeap::Remove(int location)
{
  return;
}


void MinHeap::Insert(Key key, int location)
{
  int index = size;
  locations[index] = location;
  keys[index] = key;
  SortPriority(index);
  IncreaseSize();
  return;
}


void MinHeap::Update(int location, Key key)
{
  int index = Find(location);
  if (index != -1) {
		locations[index] = location;
		keys[index] = key;
	}
  return;
}




// need to change to take parameters for storing TODO
int MinHeap::Pop()
{
	if (size == 0) { return -1; }

  int current_pos = 0;
	int smallest, other;
	int ret_val = locations[0];
	size--;
	locations[0] = locations[size];
	keys[0] = keys[size];
	
	locations[size] = -1;		// invalidate position in heap
	// TODO invalidate keys location (if necessary)
	
	smallest = (2*current_pos)+1;
	other = smallest+1;
	
	// only loop if left child is valid
	while (smallest < size) {
	
		//smallest_val = frontier[smallest];
		
		// check if right child is invalid
		if (other >= size) {
			if (keys[smallest].cost < keys[current_pos].cost) {
				Swap(current_pos, smallest);
				current_pos = smallest;
			}
			else { break; }
		}
		
		// otherwise compare both children and switch with smallest one
		else {

			//other_val = frontier[other];
		
			if (keys[smallest].cost > keys[other].cost) {
				smallest = other;
				other = other - 1;
			}
			
			if (keys[smallest].cost < keys[current_pos].cost) {
				Swap(current_pos, smallest);
				current_pos = smallest;
			}
		
			else {
				break;
			}	
		}	

		smallest = (2*current_pos)+1;
		other = smallest+1;
	} 
	
	return ret_val;
}





// gets the min location
int MinHeap::Top()
{
  return locations[0];
}
	  

// Gets the min key
Key MinHeap::TopKey()
{
  return keys[0];
} 






int main() 
{
  Key test_key;
  test_key.value = 0;
  test_key.cost = 10;
  MinHeap test;
  test.Insert(test_key, 9);
  test_key = test.TopKey();
  cout << "Key value: " << test_key.value << endl;
  cout << "Key cost: " << test_key.cost << endl; 
  cout << "Location: " << test.Pop() << endl;
  return 0;
}