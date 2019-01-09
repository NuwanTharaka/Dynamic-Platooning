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
/*
    std::vector<int> v;
    std::vector<int> node;
    node.push_back(0);
    node.push_back(0);
    node.push_back(0);


    std::vector<int> ln0;
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
    v.push_back(ln5); */

    float ln0 [][3] = {{110, 120, 1}, {95,120,2}, {50, 130, 3}};
    float ln1 [][3] = {{120, 120, 1}, {110,120,2}, {40, 130, 3}};
    float ln2 [][3] = {{80, 120, 1}, {70,120,2}, {35, 130, 3}};
    float ln3 [][3] = {{100, 120, 1}, {80,120,2}, {40, 130, 3}};
    float ln4 [][3] = {{130, 120, 1}, {100,120,2}, {30, 130, 3}};
    float ln5 [][3] = {{90, 120, 1}, {75,120,2}, {55, 130, 3}};

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
    for (int l = 0; l < sizeof(ln0) / sizeof(*ln0); l++) {
        automated.position = ln0[l][0];
        automated.lane = 0;
        automated.destination = ln0[l][2];
        automated.maxSpeed = ln0[l][1];
        addVehicleToQueue(0, automated);
    }

    for (int l = 0; l < sizeof(ln1) / sizeof(*ln1); l++) {
        automated.position = ln1[l][0];
        automated.lane = 1;
        automated.destination = ln1[l][2];
        automated.maxSpeed = ln1[l][1];
        addVehicleToQueue(0, automated);
    }

    for (int l = 0; l < sizeof(ln2) / sizeof(*ln2); l++) {
        automated.position = ln2[l][0];
        automated.lane = 2;
        automated.destination = ln2[l][2];
        automated.maxSpeed = ln2[l][1];
        addVehicleToQueue(0, automated);
    }

    for (int l = 0; l < sizeof(ln3) / sizeof(*ln3); l++) {
        automated.position = ln3[l][0];
        automated.lane = 3;
        automated.destination = ln3[l][2];
        automated.maxSpeed = ln3[l][1];
        addVehicleToQueue(0, automated);
    }

    currentPos = totalLength;
    for (int l = 0; l < sizeof(ln4) / sizeof(*ln4); l++) {
        automated.position = ln4[l][0];
        automated.lane = 4;
        automated.destination = ln4[l][2];
        automated.maxSpeed = ln4[l][1];
        addVehicleToQueue(0, automated);
    }

    for (int l = 0; l < sizeof(ln5) / sizeof(*ln5); l++) {
        automated.position = ln5[l][0];
        automated.lane = 5;
        automated.destination = ln5[l][2];
        automated.maxSpeed = ln5[l][1];
        addVehicleToQueue(0, automated);
    }

    delete[] laneOffset;
}