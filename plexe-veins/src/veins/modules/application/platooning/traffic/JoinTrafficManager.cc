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

#include "JoinTrafficManager.h"

Define_Module(JoinTrafficManager);

void JoinTrafficManager::initialize(int stage)
{

    PlatoonsTrafficManager::initialize(stage);

    if (stage == 0) {

        insertJoinerMessage = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage);

    }
}

void JoinTrafficManager::handleSelfMsg(cMessage* msg)
{

    PlatoonsTrafficManager::handleSelfMsg(msg);

    if (msg == insertJoinerMessage) {
        insertNodes();
    }
}

void JoinTrafficManager::insertJoiner(int lane)
{
    automated.position = 0;
    automated.lane = lane;
    addVehicleToQueue(0, automated);
}

JoinTrafficManager::~JoinTrafficManager()
{
    cancelAndDelete(insertJoinerMessage);
    insertJoinerMessage = nullptr;

    cancelAndDelete(insertJoinerMessage2);
    insertJoinerMessage2 = nullptr;

    cancelAndDelete(insertJoinerMessage3);
    insertJoinerMessage3 = nullptr;
}

void JoinTrafficManager::insertNodes()
{

    std::vector< std::vector<int> > v;
    std::vector<int> ln0 = {150,75,30};
    std::vector<int> ln1 = {110,95,50};
    std::vector<int> ln2 = {120,110,40};
    std::vector<int> ln3 = {80,70,35};
    std::vector<int> ln4 = {100,80,40};
    std::vector<int> ln5 = {130,100,30};
    v.push_back(ln0);
    v.push_back(ln1);
    v.push_back(ln2);
    v.push_back(ln3);
    v.push_back(ln4);
    v.push_back(ln5);

    int automatedCars = 18;
    int automatedLanes = 6;
    // keep 50 m between human vehicles (random number)
    double distance = 50;
    // total number of cars per lane
    int carsPerLane = automatedCars / automatedLanes;
    // total length for one lane
    double totalLength = carsPerLane * (4 + distance);

    // for each lane, we create an offset to have misaligned platoons
    double* laneOffset = new double[automatedLanes];
    for (int l = 0; l < automatedLanes; l++) laneOffset[l] = uniform(0, 20);

    double currentPos = totalLength;
    for (int i = 0; i < 6; i++) {
        for (int l = 0; l < v[i].size(); l++) {
            automated.position = v[i][l];
            automated.lane = i;
            addVehicleToQueue(0, automated);
        }
        currentPos -= (4 + distance);
    }

    delete[] laneOffset;
}