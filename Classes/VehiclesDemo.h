/*
 * Author: Chris Campbell - www.iforce2d.net
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef VEHICLES_DEMO_H
#define VEHICLES_DEMO_H

//A collection of different vehicles to play around with.
//Yes, I know the walker don't walk so good and the tank
//tracks fall off almost immediately... but it's still fun
//even without tracks :p
//
//This demo shows how to load a Box2D world from a JSON file
//and access named joints in the file to manipulate later.
//See the class constructor for details.

#include <vector>
#include <Box2D/Box2D.h>
#include "GLES1DebugDraw.h"

using namespace std;

class VehiclesDemo
{
public:
	enum vehicleType {
		e_bike,
		e_car,
		e_truck,
		e_tank,
		e_walker,
		e_vehicleMax,
	};
	
	enum _buttonId {
		b_left = 	0x01,
		b_right = 	0x02,
		b_change =	0x04,
	};
	
	VehiclesDemo();	
	void ButtonDown(_buttonId buttonId);	
	void ButtonUp(_buttonId buttonId);
	void Step();
	void Render(float zoom);
	b2Vec2 GetCurrentVehicleLocation();
	
protected:	
	//main stuff
	b2World* m_world;
	GLES1DebugDraw m_debugDraw;
	
	//control state
	vehicleType m_vehicle;
	int m_buttonState;

	//drive joints for available vehicles
	vector<b2Joint*> m_bikeJoints;
	vector<b2Joint*> m_carJoints;
	vector<b2Joint*> m_truckJoints;
	vector<b2Joint*> m_tankJoints;
	vector<b2Joint*> m_walkerJoints;

	//reference to drive joints of currently controlled vehicle
	vector<b2Joint*>* m_pCurrentJoints;
	
	//current location, used to move the view smoothly instead of
	//rigidly sticking to the current vehicles location
	b2Vec2 m_currentViewCenter;
};

#endif
