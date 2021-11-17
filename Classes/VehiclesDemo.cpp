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


#include <vector>
#import <OpenGLES/ES1/gl.h>
#include "b2dJson/b2dJson.h"
#include "VehiclesDemo.h"

//A collection of different vehicles to play around with.
//Yes, I know the walker don't walk so good and the tank
//tracks fall off almost immediately... but it's still fun
//even without tracks :p
//
//This demo shows how to load a Box2D world from a JSON file
//and access named joints in the file to manipulate later.
//See the class constructor for details.


VehiclesDemo::VehiclesDemo()
{		
	m_pCurrentJoints = NULL;
	
	//load world from JSON file
	b2dJson json;
	m_world = json.readFromFile("vehicles");
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);
	m_world->SetDebugDraw( &m_debugDraw );
	
	//get named drive joints from the JSON info
	json.getJointsByName("bike", m_bikeJoints);
	json.getJointsByName("car", m_carJoints);
	json.getJointsByName("truck", m_truckJoints);
	json.getJointsByName("tank", m_tankJoints);
	json.getJointsByName("walker", m_walkerJoints);	
	
	//set up initial state
	m_vehicle = e_bike;
	m_buttonState = 0;
	m_pCurrentJoints = &m_bikeJoints;
	m_currentViewCenter = b2Vec2(0,0);//GetCurrentVehicleLocation();
}

void VehiclesDemo::ButtonDown(_buttonId buttonId)
{
	switch (buttonId)
	{
		case b_left: m_buttonState |= b_left; break;
		case b_right: m_buttonState |= b_right; break;
		case b_change:
			m_vehicle = (vehicleType)(m_vehicle+1);
			if ( m_vehicle == e_vehicleMax )
				m_vehicle = e_bike;
			switch ( m_vehicle )
		{
			case e_bike: m_pCurrentJoints = &m_bikeJoints; break;
			case e_car: m_pCurrentJoints = &m_carJoints; break;
			case e_truck: m_pCurrentJoints = &m_truckJoints; break;
			case e_tank: m_pCurrentJoints = &m_tankJoints; break;
			case e_walker: m_pCurrentJoints = &m_walkerJoints; break;
		}
			
			break;
	}
}

void VehiclesDemo::ButtonUp(_buttonId buttonId)
{
	switch (buttonId)
	{
		case b_left: m_buttonState -= b_left; break;
		case b_right: m_buttonState -= b_right; break;
	}
}

void VehiclesDemo::Step()
{
	m_world->Step(1/60.0f, 8, 3);
	
	//set motor speeds for current vehicle
	float32 motorSpeed = m_buttonState == b_left ? 1 : m_buttonState == b_right ? -1 : 0;
	switch ( m_vehicle )
	{
		case e_bike : motorSpeed *= 30; break;
		case e_car : motorSpeed *= 30; break;
		case e_truck : motorSpeed *= 15; break;
		case e_tank : motorSpeed *= 10; break;
		case e_walker : motorSpeed *= -3; break;
	}
	for (int i = 0; i < m_pCurrentJoints->size(); i++) {
		switch ( m_vehicle )
		{
			case e_bike :
			case e_walker :
				((b2RevoluteJoint*)m_pCurrentJoints->at(i))->SetMotorSpeed(motorSpeed);
				break;
			default:
				((b2WheelJoint*)m_pCurrentJoints->at(i))->SetMotorSpeed(motorSpeed);
		}
	}
}

void VehiclesDemo::Render(float zoom)
{
	glViewport(0, 0, 480, 320);
	
	m_currentViewCenter = 0.75f * m_currentViewCenter + 0.25f * GetCurrentVehicleLocation();
	glOrthof(m_currentViewCenter.x-1.5f*zoom, m_currentViewCenter.x+1.5f*zoom,
			 m_currentViewCenter.y-zoom, m_currentViewCenter.y+zoom,
			 -1, 1);
	
	m_world->DrawDebugData();
}

b2Vec2 VehiclesDemo::GetCurrentVehicleLocation()
{
	//position of current vehicle
	if ( !m_pCurrentJoints->empty() ) 
		return m_pCurrentJoints->at(0)->GetBodyA()->GetWorldCenter();
	else 
		return b2Vec2(0,0);
}








