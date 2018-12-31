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
        scheduleAt(platoonInsertTime + SimTime(200, SIMTIME_MS), insertJoinerMessage);

        insertJoinerMessage2 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage2);

        insertJoinerMessage3 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(4000, SIMTIME_MS), insertJoinerMessage3);

        insertJoinerMessage4 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(6000, SIMTIME_MS), insertJoinerMessage4);

        insertJoinerMessage5 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage5);

        insertJoinerMessage6 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage6);

        insertJoinerMessage7 = new cMessage("");
        scheduleAt(platoonInsertTime + SimTime(2000, SIMTIME_MS), insertJoinerMessage7);

        

    }
}

void JoinTrafficManager::handleSelfMsg(cMessage* msg)
{

    PlatoonsTrafficManager::handleSelfMsg(msg);

    if (msg == insertJoinerMessage) {
        insertJoiner(0);
    }
    if (msg == insertJoinerMessage2) {
        insertJoiner(0);
    }
    if (msg == insertJoinerMessage3) {
        insertJoiner(0);
    }
    if (msg == insertJoinerMessage4) {
        insertJoiner(0);
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

