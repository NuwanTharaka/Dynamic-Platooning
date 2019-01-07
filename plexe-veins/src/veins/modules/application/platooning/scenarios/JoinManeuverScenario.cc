//
// Copyright (c) 2012-2018 Michele Segata <segata@ccs-labs.org>
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

#include "veins/modules/application/platooning/scenarios/JoinManeuverScenario.h"
#include <veins/modules/mobility/traci/TraCIBaseTrafficManager.h>


Define_Module(JoinManeuverScenario);

#ifndef coreEV
#define coreEV_clear EV
#define coreEV EV << logName() << "::" << getClassName() << ": "
#endif

Veins::TraCIMobility *mobility;
Veins::TraCICommandInterface::Vehicle *traciVehicle;

void JoinManeuverScenario::initialize(int stage)
{

    BaseScenario::initialize(stage);

    if (stage == 1) {
        app = FindModule<GeneralPlatooningApp*>::findSubModule(getParentModule());
        prepareManeuverCars(0);
    }

    startSendPos = new cMessage();
    scheduleAt(simTime(), startSendPos);

}

void JoinManeuverScenario::setupFormation()
{
    std::vector<int> formation;
    for (int i = 0; i < 4; i++) formation.push_back(i);
    positionHelper->setPlatoonFormation(formation);
}

void JoinManeuverScenario::prepareManeuverCars(int platoonLane)
{
    int ID = positionHelper->getId();

    if(ID == 18){
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        traciVehicle->setFixedLane(platoonLane);

        positionHelper->setIsLeader(true);
        positionHelper->setPlatoonLane(platoonLane);
        positionHelper->setPlatoonSpeed(100 / 3.6);
        positionHelper->setPlatoonId(positionHelper->getId());
        setupFormation();
        startManeuver = new cMessage();
        scheduleAt(simTime() + SimTime(20), startManeuver);

    }else if(ID>18 && ID<22){
        traciVehicle->setCruiseControlDesiredSpeed(130.0 / 3.6);
        traciVehicle->setActiveController(Plexe::CACC);
        traciVehicle->setFixedLane(platoonLane);

        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(platoonLane);
        positionHelper->setPlatoonSpeed(100 / 3.6);
        positionHelper->setPlatoonId(positionHelper->getLeaderId());
        setupFormation();

    }else{
        traciVehicle->setCruiseControlDesiredSpeed(100 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
         
    }
/*
    switch (positionHelper->getId()) {

    case 0: {
        // this is the leader
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        traciVehicle->setFixedLane(platoonLane);

        positionHelper->setIsLeader(true);
        positionHelper->setPlatoonLane(platoonLane);
        positionHelper->setPlatoonSpeed(100 / 3.6);
        positionHelper->setPlatoonId(positionHelper->getId());
        setupFormation();

        break;
    }

    case 1:
    case 2:
    case 3: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(130.0 / 3.6);
        traciVehicle->setActiveController(Plexe::CACC);
        traciVehicle->setFixedLane(platoonLane);

        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(platoonLane);
        positionHelper->setPlatoonSpeed(100 / 3.6);
        positionHelper->setPlatoonId(positionHelper->getLeaderId());
        setupFormation();
        
        break;
    }

    case 4: {
        // this is the car which will join
        traciVehicle->setCruiseControlDesiredSpeed(100 / 3.6);
        traciVehicle->setFixedLane(2);
        traciVehicle->setActiveController(Plexe::ACC);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);

        // after 30 seconds of simulation, start the maneuver
        startManeuver = new cMessage();
        scheduleAt(simTime() + SimTime(10), startManeuver);
        break;
    }
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12: {
        traciVehicle->setCruiseControlDesiredSpeed(100 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
         
        break;

    }
    } */
}

JoinManeuverScenario::~JoinManeuverScenario()
{
    cancelAndDelete(startManeuver);
    startManeuver = nullptr;

    cancelAndDelete(startSendPos);
    startSendPos = nullptr;
}

void JoinManeuverScenario::handleSelfMsg(cMessage* msg)
{

    // this takes car of feeding data into CACC and reschedule the self message
    BaseScenario::handleSelfMsg(msg);

    if (msg == startManeuver){
      //app->startJoinManeuver(0, 0, -1); 
        startManeuver = new cMessage();
        scheduleAt(simTime() + SimTime(25, SIMTIME_MS), startManeuver); 
        platoonPath();

    } 

    if (msg == startSendPos) {
        mobility = Veins::TraCIMobilityAccess().get(getParentModule());
        traciVehicle = mobility->getVehicleCommandInterface();
        Plexe::VEHICLE_DATA data;
        traciVehicle->getVehicleData(&data);
        int indexLane = traciVehicle->getLaneIndex();
        double position = traciVehicle->getLanePosition();

        sendData(positionHelper->getId(), data.speed, data.acceleration, position, indexLane);

        startSendPos = new cMessage();
        scheduleAt(simTime() + SimTime(1, SIMTIME_MS), startSendPos);
    }
}


void JoinManeuverScenario::platoonPath()
{
    int final_speed=0;
   // flag_shortPath =1;
    std::vector< std::vector<nodeData> > eachLane;
    for(int x=0;x<6;x=x+1){
        std::vector<nodeData> kill;
        eachLane.push_back(kill);
    }
    int nLanes = 6;
    int state = 0;

    int myVehicleId = positionHelper->getId();

    std::vector<nodeData> vehData = getData();
    nodeData myVehicle = vehData[myVehicleId];

    int currentLane =  myVehicle.positionY;

    int i=0;
    for(nodeData vehicle:vehData){

        if(myVehicleId == i){ 

        }else {
            int a = vehicle.positionY; 
            eachLane[a].push_back(vehicle);
            
        }
        i=i+1;

    }
    int speed_front;
    int speed_side1;
    int speed_side2;

    int sideGo = 0;

    if(early!= 0){
        sideGo = early;
    }
    early = 0;
    traciVehicle->setCruiseControlDesiredSpeed(130 / 3.6);
    for(nodeData item:eachLane[currentLane]){
        int distance= (item.positionX - myVehicle.positionX);
        if((distance>(40)) && (distance < 90)){
            traciVehicle->setCruiseControlDesiredSpeed( 110 / 3.6);
        }
        else if((distance>0 && distance < (40)) || (stucked!=0)){
            final_speed = 1;
            traciVehicle->setCruiseControlDesiredSpeed(item.speed);
            speed_front= item.speed;
            state=1;
            ///awlak atha front speed item1
            /////
            
            int moveLane;
            if(currentLane==0 ){
                moveLane = currentLane + 1; 
            }else{
                moveLane = currentLane - 1; 
            }

            if(sideGo != 0){
                stucked= sideGo;
            }




            if((stucked>0) && (currentLane!=(nLanes-1))){
                moveLane = currentLane + 1; 
            }else if((stucked<0) && (currentLane!=0)){
                moveLane = currentLane - 1; 
            }
            



            int flag = 0;
            for(nodeData side:eachLane[moveLane]){
                distance=side.positionX- myVehicle.positionX;
                if(distance>-8 && distance < 8){
                    flag=1;
                    speed_side1 = side.speed;
                    break;
                }
            }

            int noption1 = 0;
            int noption2 = 0;

            if(flag==1){
                state=2;
                moveLane = 2*currentLane - moveLane;
                if(((moveLane==-1) || (moveLane==nLanes))  || (stucked!=0)){
                    noption1 = 1;
                    state=3;
                }else{
                    for(nodeData side:eachLane[moveLane]){
                        distance=side.positionX- myVehicle.positionX;
                        if(distance>-8 && distance < 8){
                            noption2=1;
                            state=4;
                            speed_side2 = side.speed;
                            break;
                        }
                    }
                } 

            }
            int gotoback=0;
            if (noption1){
                if((speed_front == speed_side1)){
                    gotoback=1;
                }else if(stucked!=0){
                    traciVehicle->setCruiseControlDesiredSpeed(80 / 3.6);
                    final_speed = 2;
                }else{

                }
            }else if(noption2){
                if(((speed_front == speed_side1) && (speed_front == speed_side2))){
                    gotoback=1;
                }else{
                    
                }

            }else{

                early = moveLane - currentLane;
                traciVehicle->setFixedLane(moveLane);

                traciVehicle->setCruiseControlDesiredSpeed(130 / 3.6);
                final_speed = 3;
                int val= stucked*stucked; 
                if( val == 4){
                    stucked = stucked/2;
                }else if(val == 1){
                    stucked = 0;
                }
                gotoback=0;
            }

            if(gotoback){
                if(currentLane<2){
                    stucked= 2;
                }else{
                    stucked= -2;
                }

                traciVehicle->setCruiseControlDesiredSpeed(80 / 3.6);
                final_speed = 4;
            }       
            ////
            break;
        }
    }
    



}
