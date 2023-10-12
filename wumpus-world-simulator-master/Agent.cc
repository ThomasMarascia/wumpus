// Agent.cc

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Agent.h"

#include "Action.h"
#include "Location.h"
#include "Orientation.h"


using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{
	
}

void Agent::Initialize ()
{
	// initialize the worldstate:
	worldState.worldSize = 4;
	worldState.pitLocations; //no pits
	worldState.wumpusLocation = Location(4,4);
	worldState.agentLocation = Location(1,1);
	worldState.agentOrientation = RIGHT;
	worldState.agentHasGold = false;
	worldState.agentHasArrow = true;
	worldState.agentAlive = true;
	worldState.wumpusAlive = true;
	worldState.goldLocation; //unknown
	worldState.agentInCave = true; //in cave

}
// whenever an action is taken, update the worldstate so the agent knows it's next gamestate:
Action Agent::Process (Percept& percept)
{
	Action action;
	// if on the gold, grab it
	if (percept.Glitter == true){
		action = GRAB;
		worldState.agentHasGold = true;
	}
	// if agent has the gold and is on the home square, climb and win the game
	else if(worldState.agentLocation.X == 1 && worldState.agentLocation.Y == 1 && worldState.agentHasGold){
		action = CLIMB;
	}
	// if agent can shoot the wumpus, shoot it
	else if(worldState.agentHasArrow && worldState.agentLocation.Y == 4 && worldState.agentOrientation == RIGHT){
		action = SHOOT;
		worldState.agentHasArrow = false;
	}
	else if(worldState.agentHasArrow && worldState.agentLocation.X == 4 && worldState.agentOrientation == UP){
		action = SHOOT;
		worldState.agentHasArrow = false;
	}
	// if none of the above conditions are true, randomly select the next move. Move foward, turn left, or turn right.
	else{
		
		int ranVal = ((rand()%3) + 1);
		if (ranVal == 1){
			action = GOFORWARD;
			if(worldState.agentOrientation == RIGHT){
				if(worldState.agentLocation.X < worldState.worldSize){
					worldState.agentLocation.X++;
				}
			}
			else if(worldState.agentOrientation == LEFT){
				if(worldState.agentLocation.X > 1){
					worldState.agentLocation.X--;
				}
			}
			else if(worldState.agentOrientation == UP){
				if(worldState.agentLocation.Y < worldState.worldSize){
					worldState.agentLocation.Y++;
				}
			}
			else if(worldState.agentOrientation == DOWN){
				if(worldState.agentLocation.Y > 1){
					worldState.agentLocation.Y--;
				}
			}
		}

		else if(ranVal == 2){
			action = TURNLEFT;
			if(worldState.agentOrientation == RIGHT){
				worldState.agentOrientation = UP;
			}
			else if(worldState.agentOrientation == UP){
				worldState.agentOrientation = LEFT;
			}
			else if(worldState.agentOrientation == LEFT){
				worldState.agentOrientation = DOWN;
			}
			else if(worldState.agentOrientation == DOWN){
				worldState.agentOrientation = RIGHT;
			}
		}
		else if(ranVal == 3){
			action = TURNRIGHT;
			if(worldState.agentOrientation == RIGHT){
				worldState.agentOrientation = DOWN;
			}
			else if(worldState.agentOrientation == DOWN){
				worldState.agentOrientation = LEFT;
			}
			else if(worldState.agentOrientation == LEFT){
				worldState.agentOrientation = UP;
			}
			else if(worldState.agentOrientation == UP){
				worldState.agentOrientation = RIGHT;
			}
		}
	}
	return action;
	/*
	Manual game playing (used for testing):
	char c;
	Action action;
	bool validAction = false;

	while (! validAction)
	{
		validAction = true;
		cout << "Action? ";
		cin >> c;
		if (c == 'f') {
			action = GOFORWARD;
		} else if (c == 'l') {
			action = TURNLEFT;
		} else if (c == 'r') {
			action = TURNRIGHT;
		} else if (c == 'g') {
			action = GRAB;
		} else if (c == 's') {
			action = SHOOT;
		} else if (c == 'c') {
			action = CLIMB;
		} else {
			cout << "Huh? What you say?" << endl;
			validAction = false;
		}
	}
	return action;
	*/
}

void Agent::GameOver (int score)
{

}

