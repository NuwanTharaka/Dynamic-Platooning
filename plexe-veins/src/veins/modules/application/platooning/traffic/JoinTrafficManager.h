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

#ifndef JOINTRAFFICMANAGER_H_
#define JOINTRAFFICMANAGER_H_

#include <veins/modules/application/platooning/traffic/PlatoonsTrafficManager.h>

class JoinTrafficManager : public PlatoonsTrafficManager {

public:
    virtual void initialize(int stage);

    JoinTrafficManager()
        : PlatoonsTrafficManager()
    {
        insertJoinerMessage = 0;
        insertJoinerMessage2 = 0;
        insertJoinerMessage3 = 0;
        insertJoinerMessage4 = 0;
        insertJoinerMessage5 = 0;
        insertJoinerMessage6 = 0;
        insertJoinerMessage7 = 0;

    }
    virtual ~JoinTrafficManager();

protected:
    cMessage* insertJoinerMessage;
    cMessage* insertJoinerMessage2;
    cMessage* insertJoinerMessage3;
    cMessage* insertJoinerMessage4;
    cMessage* insertJoinerMessage5;
    cMessage* insertJoinerMessage6;
    cMessage* insertJoinerMessage7;


    void insertJoiner(int lane);

    void insertNodes();
    void insertNodes1();


    virtual void handleSelfMsg(cMessage* msg);
};

#endif
