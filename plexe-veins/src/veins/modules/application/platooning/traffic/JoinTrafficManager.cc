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
        scheduleAt(platoonInsertTime + SimTime(1), insertJoinerMessage);
    }
}

void JoinTrafficManager::handleSelfMsg(cMessage* msg)
{

    PlatoonsTrafficManager::handleSelfMsg(msg);

    if (msg == insertJoinerMessage) {
        insertNodes();
    }
}

void JoinTrafficManager::insertJoiner()
{
    automated.position = 0;
    automated.lane = 2;
    addVehicleToQueue(0, automated);
}
JoinTrafficManager::~JoinTrafficManager()
{
    cancelAndDelete(insertJoinerMessage);
    insertJoinerMessage = nullptr;
}

/*void JoinTrafficManager::insertNodes()
{
    struct vehicle
    {
        double distance;
        int lane;
    };

    std::vector<vehicle> v;
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());
    v.push_back(vehicle());

    v[0].distance = 5;
    v[0].lane = 4;

    v[1].distance = 35;
    v[1].lane = 4;

    v[2].distance = 55;
    v[2].lane = 3;

    v[3].distance = 85;
    v[3].lane = 3;

    v[4].distance = 100;
    v[4].lane = 3;

    v[5].distance = 35;
    v[5].lane = 2;

    v[6].distance = 120;
    v[6].lane = 2;

    v[7].distance = 55;
    v[7].lane = 1;

    v[8].distance = 95;
    v[8].lane = 1;

    for (int i = 0; i < v.size(); ++i)
    {
        automated.position = v[i].distance;
        automated.lane = v[i].lane;
        addVehicleToQueue(0, automated);
    }
}*/

void JoinTrafficManager::insertNodes()
{
    int g = 200;
    int s = 25;

    std::vector< std::vector<int> > v;
    std::vector<int> ln0 = {g,g-2*s,g-4*s};
    std::vector<int> ln1 = {g-s,g-3*s,g-5*s};
    std::vector<int> ln2 = {g,g-2*s,g-4*s};
    std::vector<int> ln3 = {g-s,g-3*s,g-5*s};
    std::vector<int> ln4 = {g,g-2*s,g-4*s};
    std::vector<int> ln5 = {g-s,g-3*s,g-5*s};


/*
    std::vector< std::vector<int> > v;
    std::vector<int> ln0 = {150,100,50};
    std::vector<int> ln1 = {150,100,50};
    std::vector<int> ln2 = {150,100,50};
    std::vector<int> ln3 = {150,100,50};
    std::vector<int> ln4 = {150,100,50};
    std::vector<int> ln5 = {150,100,50};
*/
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
