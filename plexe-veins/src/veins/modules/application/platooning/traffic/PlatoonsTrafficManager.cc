//
// Copyright (C) 2014-2018 Michele Segata <segata@ccs-labs.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "PlatoonsTrafficManager.h"

Define_Module(PlatoonsTrafficManager);

void PlatoonsTrafficManager::initialize(int stage)
{

    TraCIBaseTrafficManager::initialize(stage);

    if (stage == 0) {

        nCars = par("nCars").longValue();
        platoonSize = par("platoonSize").longValue();
        nLanes = par("nLanes").longValue();
        platoonInsertTime = SimTime(par("platoonInsertTime").doubleValue());
        platoonInsertSpeed = par("platoonInsertSpeed").doubleValue();
        platoonInsertDistance = par("platoonInsertDistance").doubleValue();
        platoonInsertHeadway = par("platoonInsertHeadway").doubleValue();
        platoonLeaderHeadway = par("platoonLeaderHeadway").doubleValue();
        platooningVType = par("platooningVType").stdstringValue();
        insertPlatoonMessage = new cMessage("");
        scheduleAt(platoonInsertTime+ SimTime(1), insertPlatoonMessage);
        insertPlatoonMessage1 = new cMessage("");
    //    scheduleAt(platoonInsertTime+ SimTime(2), insertPlatoonMessage1);
        scheduleAt(simTime() + SimTime(3100, SIMTIME_MS), insertPlatoonMessage1); 

       // insertPlatoonMessage1 = new cMessage("");
       // scheduleAt(platoonInsertTime+ SimTime(3), insertPlatoonMessage1);
        insertPlatoonMessage2 = new cMessage("");
        scheduleAt(simTime() + SimTime(4400, SIMTIME_MS), insertPlatoonMessage2); 
    }
}

void PlatoonsTrafficManager::scenarioLoaded()
{
    automated.id = findVehicleTypeIndex(platooningVType);
    automated.lane = -1;
    automated.position = 0;
    automated.speed = platoonInsertSpeed / 3.6;
}

void PlatoonsTrafficManager::handleSelfMsg(cMessage* msg)
{

    TraCIBaseTrafficManager::handleSelfMsg(msg);

    if (msg == insertPlatoonMessage) {
        insertPlatoon(4,50,3);

    }

    if (msg == insertPlatoonMessage1) {
        insertPlatoon(4,50,3);

    }

    if (msg == insertPlatoonMessage2) {
        insertPlatoon(4,50,3);

    }
/*
    if (msg == insertPlatoonMessage1) {
        insertPlatoons();

    }

*/

}

void PlatoonsTrafficManager::insertPlatoons(int size)
{
    platoonSize = size;
    nCars = nCars +size - 4;
    // compute intervehicle distance
    double distance = platoonInsertSpeed / 3.6 * platoonInsertHeadway + platoonInsertDistance;
    // total number of platoons per lane
    int nPlatoons = nCars / platoonSize / nLanes;
    // length of 1 platoon
    double platoonLength = platoonSize * 4 + (platoonSize - 1) * distance;
    // inter-platoon distance
    double platoonDistance = platoonInsertSpeed / 3.6 * platoonLeaderHeadway;
    // total length for one lane
    double totalLength = nPlatoons * platoonLength + (nPlatoons - 1) * platoonDistance;

    // for each lane, we create an offset to have misaligned platoons
    double* laneOffset = new double[nLanes];
    for (int l = 0; l < nLanes; l++) laneOffset[l] = uniform(0, 20);

    double currentPos = totalLength;
    int currentCar = 0;
    for (int i = 0; i < nCars / nLanes; i++) {
        for (int l = 0; l < nLanes; l++) {
            automated.position = currentPos + laneOffset[l];
            automated.lane = l;
            addVehicleToQueue(0, automated);
        }
        currentCar++;
        if (currentCar == platoonSize) {
            currentCar = 0;
            // add inter platoon gap
            currentPos -= (platoonDistance + 4);
        }
        else {
            // add intra platoon gap
            currentPos -= (4 + distance);
        }
    }

    delete[] laneOffset;
}

void PlatoonsTrafficManager::insertPlatoon (int a, double b , int lane){


    double laneOffset = 0;
    for (int i = 0; i < a; i++){

        automated.position = b - laneOffset;
        automated.lane = lane;
        addVehicleToQueue(0,automated);
        laneOffset = laneOffset + 10;
    }
}

PlatoonsTrafficManager::~PlatoonsTrafficManager()
{
    cancelAndDelete(insertPlatoonMessage);
    insertPlatoonMessage = nullptr;
}
