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
        scheduleAt(platoonInsertTime + SimTime(4000, SIMTIME_MS), insertJoinerMessage);

        insertJoinerMessage2 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(50, SIMTIME_MS), insertJoinerMessage2);

     /*   insertJoinerMessage2 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2200, SIMTIME_MS), insertJoinerMessage2);

        insertJoinerMessage3 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2400, SIMTIME_MS), insertJoinerMessage3);

        insertJoinerMessage4 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(4000, SIMTIME_MS), insertJoinerMessage4);

        insertJoinerMessage5 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage5);

        insertJoinerMessage6 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage6);

        insertJoinerMessage7 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage7);*/

        

    }
}

void JoinTrafficManager::handleSelfMsg(cMessage* msg)
{

    PlatoonsTrafficManager::handleSelfMsg(msg);

    if (msg == insertJoinerMessage) {
        insertNodes();
    }

    if (msg == insertJoinerMessage2) {
        insertNodes1();
    }



/*    if (msg == insertJoinerMessage2) {
        insertJoiner(0);
    }
    if (msg == insertJoinerMessage3) {
        insertJoiner(0);
    }
    if (msg == insertJoinerMessage4) {
       insertNodes();
    }*/
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

    float ln0 [][3] = {{700, 80, 1}, {800,80,2}, {900, 80, 3}};
    float ln1 [][3] = {{600, 80, 1}, {850, 80, 3}};
    float ln2 [][3] = {{625,80,2}, {790, 80, 3}};
    float ln3 [][3] = {{800, 80, 1}};
    float ln4 [][3] = {{800, 80, 1}, {800,80,2}};
    float ln5 [][3] = {{750, 80, 1}, {850,80,2}, {, 80, 3}};


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



void JoinTrafficManager::insertNodes1()
{

    float ln0 [][3] = {{110, 120, 1}, {55,120,2}, {5, 130, 3}};
    float ln1 [][3] = {{130, 120, 1}, {40,120,2}, {0, 130, 3}};
    float ln2 [][3] = {{120, 120, 1}, {70,120,2}, {10, 130, 3}};
    float ln3 [][3] = {{100, 120, 1}, {50,120,2}, {15, 130, 3}};
    float ln4 [][3] = {{95, 120, 1}, {35,120,2}, {8, 130, 3}};
    float ln5 [][3] = {{75, 120, 1}, {50,120,2}, {3, 130, 3}};

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


