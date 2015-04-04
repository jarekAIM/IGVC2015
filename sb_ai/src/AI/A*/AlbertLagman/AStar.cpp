#include <iostream>
#include <math.h>
#include "AStar.h"
//test
using namespace std;

// Edited by Albert Lagman:albertlagman@gmail.com

// Initialization function for preparing the variables for A*
bool AStar::Init(int* map, int width, int height)
{
	map_width = width;
	map_height = height;

	int size = map_width * map_height;
	map = new int[size];
	
	frontier_size = 0;
	came_from = new int[size];
	frontier = new int[size];
	cost_from_start = new int[size];
	estimated_cost = new int[size];

	for (int i = 0; i < 100; i++) {
		came_from[i] = -1;
		frontier[i] = -1;
		cost_from_start[i] = INF;
		estimated_cost[i] = INF;
	}
	return true;
}

// Input: 2 location indexes
// This swaps the cost between the two locations in the frontier array
void AStar::Swap(int one, int two) 
{
	int temp;
	temp = frontier[one];
	frontier[one] = frontier[two];
	frontier[two] = temp;
	return;
} 


// This finds the proper position of a location in the frontier
// This assumes that the location was inserted into the end of the frontier tree
void AStar::FrontierPriority(int frontier_position)
{
	// Check that there is a need to find priority
	if (frontier_size == 1) {
		return;
	}
	else {
		
		int parent = (frontier_position - 1) / 2;
		
		while (parent >= 0) {	// check that it's not out of range

			// The frontier prioritizes the locations using their estimated costs
			if (estimated_cost[frontier[parent]] > estimated_cost[frontier[frontier_position]]) {
				Swap(parent, frontier_position); 
			}
			else { break; }

			parent = (parent - 1) / 2;
		}
		
		return;
	}
}


// This inserts a location into the frontier
void AStar::Insert(int location) 
{
	frontier[frontier_size] = location;
	FrontierPriority(frontier_size);
	frontier_size++;
	return;
}



// This prints out the path if a path is found
void AStar::ReconstructPath(int start_location, int goal_location)
{
	int curr = goal_location;
	while (curr != start_location) {
		cout << curr << endl;
		curr = came_from[curr];
	} 
	cout << curr << endl;
	return;
}



// TODO: Convert coordinates (x,y) to an index that would be used to access the map array
int AStar::GetIndex(int x, int y) 
{
	return ((y*map_width)+x); 
}


// TODO: Convert the location index to an X location value
int AStar::GetX(int index)
{
	return (index%map_width);
}


// TODO: Convert the location index to a Y location value
int AStar::GetY(int index) 
{
	return (index/map_width);
}


// This checks whether the cost from start value of the specified location requires overriding
bool AStar::NotAlreadyTravelled(int location, int curr_loc)
{
	if (came_from[location] == -1) { return true; }
	else if (cost_from_start[curr_loc] + 1 < cost_from_start[location]) { return true; }
	else { return false; }
}

// TODO: Heuristic function estimates the cost to travel from start_location to goal_location
// Admissible: Heuristic(start, goal) <= ActualCost(start, goal)
int AStar::Heuristic(int start_location, int goal_location)
{
	int deltax,deltay;
	deltax=GetX(goal_location)-AStar::GetX(start_location);
	deltay=GetY(goal_location)-AStar::GetY(start_location);
	return (sqrt(pow(deltax,2)+pow(deltay,2)));
}


// TODO: a search to check that the location is not found in the frontier array
bool AStar::NotInFrontier(int location)
{
	int counter=0;
	while(counter < frontier_size)
	{
		if (frontier[counter] == location)
		{
			return false;
		}
		counter++;
	}
	return true;
}


// This adds the next locations the robot needs to explore to the frontier array
void AStar::AddNeighborsToFrontier(int current_location, int goal)
{
	int neighbors[4];
	int x = GetX(current_location);
	int y = GetY(current_location);
	
	if (y-1 >= 0) { neighbors[0] = GetIndex(x, y-1); }	// Up
	else { neighbors[0] = -1; }
	
	if (x-1 >= 0) { neighbors[1] = GetIndex(x-1, y); }	// Left
	else { neighbors[1] = -1; }
	
	if (y+1 < 10) { neighbors[2] = GetIndex(x, y+1); }	// Down
	else { neighbors[2] = -1; }
	
	if (x+1 < 10) { neighbors[3] = GetIndex(x+1, y); }	// Right
	else { neighbors[3] = -1; }
	
	for (int i = 0; i < 4; i++) {
		if (neighbors[i] != -1) {
			if (NotAlreadyTravelled(neighbors[i], current_location) && NotInFrontier(neighbors[i])) {
				came_from[neighbors[i]] = current_location;
				cost_from_start[neighbors[i]] = cost_from_start[current_location] + 1;
				estimated_cost[neighbors[i]] = cost_from_start[neighbors[i]] + Heuristic(current_location, goal); 
				Insert(neighbors[i]);
			}
		}
	}
	
	return;
}


// This removes the location with the smallest cost out of the frontier array
void AStar::RemoveRoot()
{		
	int current_pos = 0;
	int smallest, other, smallest_val, other_val;
	frontier_size--;
	frontier[0] = frontier[frontier_size];
	frontier[frontier_size] = -1;		// invalidate position in heap
	
	smallest = (2*current_pos)+1;
	other = smallest+1;
	
	// only loop if left child is valid
	while (smallest < frontier_size) {
	
		smallest_val = frontier[smallest];
		
		// check if right child is invalid
		if (other >= frontier_size) {
			if (estimated_cost[smallest_val] < estimated_cost[frontier[current_pos]]) {
				Swap(current_pos, smallest);
				current_pos = smallest;
			}
			else { break; }
		}
		
		// otherwise compare both children and switch with smallest one
		else {

			other_val = frontier[other];
		
			if (estimated_cost[smallest_val] > estimated_cost[other_val]) {
				smallest = other;
				other = other - 1;
			}
			
			if (estimated_cost[smallest_val] < estimated_cost[frontier[current_pos]]) {
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
	
	return;
}


// This is the A* implementation. It is very similar to the one shown in Wiki.
// http://en.wikipedia.org/wiki/A*_search_algorithm
void AStar::AStarSearch(int start, int goal) 
{
	// TODO: check that the start and goal are valid integers 
	if ((start < 0 || start > 99)||(goal < 0 || goal > 99))
		cout << "Error: Invalid start/end position";	
	cost_from_start[start] = 0;
	estimated_cost[start] = cost_from_start[start] + Heuristic(start,goal);

	Insert(start);
	
	// keep searching for a path while there are still traversable locations
	while (frontier_size != 0) {
		// TODO: int current_location = ?
		int current_location = frontier[0];
		// TODO: if the current_location == goal then ?
		if (current_location == goal)
		{
		ReconstructPath(start, goal);
		return;
		}
		// TODO: What function do you use to remove the current location from the frontier ?
		RemoveRoot();		
		// TODO: There is a function that takes care of choosing the neighbors and adding them to the frontier
		AddNeighborsToFrontier(current_location,goal);
//		frontier_size = 0;	// this is here just to make the initial template runs. Remove this when you no longer need it.
	}
	
	cout << "No path found" << endl;
	return;
}
