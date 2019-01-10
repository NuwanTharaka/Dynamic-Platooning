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

void JoinManeuverScenario::setupFormation(int a,int b)
{
    std::vector<int> formation;
    for (int i = a; i < (b+1); i++) formation.push_back(i);
    positionHelper->setPlatoonFormation(formation);



}

void JoinManeuverScenario::prepareManeuverCars(int platoonLane)
{


    switch (positionHelper->getId()) {

    case 15:
    case 10:
    case 0: {
        // this is the leader
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setIsLeader(true);
        //positionHelper->setPlatoonLane(platoonLane);
        positionHelper->setPlatoonSpeed(100 / 3.6);
        positionHelper->setPlatoonId(positionHelper->getId());
        setupFormation(positionHelper->getId(),positionHelper->getId());

        break;
    }

    case 1: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
        traciVehicle->setACCHeadwayTime(0.09);
        singleJoin = new cMessage();
        scheduleAt(simTime() + SimTime(2), singleJoin);
        vehicle_ID = 0;
        flag_shortPath=1;
    //    startManeuver = new cMessage();
    //    scheduleAt(simTime() + SimTime(2), startManeuver);

        break;
    }

    case 16: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
        startManeuver1 = new cMessage();
       // scheduleAt(simTime() + SimTime(3), startManeuver1);

        break;
    }

    case 13: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
        startManeuver2 = new cMessage();
       // scheduleAt(simTime() + SimTime(4), startManeuver2);

        break;
    }

    case 4: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);

        traciVehicle->setACCHeadwayTime(0.09);
        singleJoin = new cMessage();
        scheduleAt(simTime() + SimTime(15), singleJoin);
        vehicle_ID = 1;
        flag_shortPath=1;
     //   startManeuver = new cMessage();
    //    scheduleAt(simTime() + SimTime(60), startManeuver);

        break;
    }

    case 12: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
        startManeuver1 = new cMessage();
      //  scheduleAt(simTime() + SimTime(56), startManeuver1);

        break;
    }

    case 14: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
        startManeuver2 = new cMessage();
      //  scheduleAt(simTime() + SimTime(57), startManeuver2);

        break;
    }

    case 7: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);

        traciVehicle->setACCHeadwayTime(0.09);
        singleJoin = new cMessage();
        scheduleAt(simTime() + SimTime(30), singleJoin);
        vehicle_ID = 4;
        flag_shortPath=1;
    //    startManeuver = new cMessage();
    //    scheduleAt(simTime() + SimTime(120), startManeuver);

        break;
    }

    case 3: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);

        traciVehicle->setACCHeadwayTime(0.09);
        singleJoin = new cMessage();
        scheduleAt(simTime() + SimTime(40), singleJoin);
        vehicle_ID = 7;
        flag_shortPath=1;
       // startManeuver = new cMessage();
       // scheduleAt(simTime() + SimTime(180), startManeuver);
        

        break;
    }

    case 6: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);
       // startManeuver = new cMessage();
       // scheduleAt(simTime() + SimTime(200), startManeuver);

        break;
    }

    default: {
        // these are the followers which are already in the platoon
        traciVehicle->setCruiseControlDesiredSpeed(100.0 / 3.6);
        traciVehicle->setActiveController(Plexe::ACC);
        //traciVehicle->setFixedLane(platoonLane);

        positionHelper->setPlatoonId(-1);
        positionHelper->setIsLeader(false);
        positionHelper->setPlatoonLane(-1);

        break;
    }
    traciVehicle->setFixedLane(traciVehicle->getLaneIndex());
    }
}

JoinManeuverScenario::~JoinManeuverScenario()
{
    cancelAndDelete(startManeuver);
    startManeuver= nullptr;

    cancelAndDelete(startManeuver1);
    startManeuver1= nullptr;

    cancelAndDelete(startManeuver2);
    startManeuver2= nullptr;

    cancelAndDelete(startSendPos);
    startSendPos = nullptr;
}

void JoinManeuverScenario::handleSelfMsg(cMessage* msg)
{

    // this takes car of feeding data into CACC and reschedule the self message
    BaseScenario::handleSelfMsg(msg);

    if (msg == startManeuver){
        EV<<"EasyToFind....goti"<<positionHelper->getId()<< endl;
        //shortPath_fn();
        //scheduleAt(simTime() + SimTime(1), startManeuver_error);
        app->startJoinManeuver(0,0, -1);
    }

    if (msg == startManeuver1){
        EV<<"EasyToFind....goti"<<positionHelper->getId()<< endl;
        //shortPath_fn();
        //scheduleAt(simTime() + SimTime(1), startManeuver_error);

        //traciVehicle->setFixedLane(1);
        app->startJoinManeuver(10, 10, -1);
    }

    if (msg == startManeuver2){
        EV<<"EasyToFind....goti"<<positionHelper->getId()<< endl;
        //shortPath_fn();
        //scheduleAt(simTime() + SimTime(1), startManeuver_error);

        //traciVehicle->setFixedLane(1);
        app->startJoinManeuver(15, 15, -1);
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

        if(app->isShortPath() && (joinReady==1)){
            workShortPath = new cMessage();
            scheduleAt(simTime() + SimTime(10, SIMTIME_MS), workShortPath);
            joinReady = 0;
        }

       
    }

    if (msg == workShortPath) {
        if(app->isShortPath()){
            app->shortPath_function();
            workShortPath = new cMessage();
            scheduleAt(simTime() + SimTime(30, SIMTIME_MS), workShortPath);
        }else{
            joinReady = 1;
            workNearPlatoon = new cMessage();
            scheduleAt(simTime() + SimTime(30, SIMTIME_MS), workNearPlatoon);
        }
        
    }

    if(msg == workNearPlatoon){
        if(app->isNearPlatoon()){
            app->nearPlatoon_function();
            workNearPlatoon = new cMessage();
            scheduleAt(simTime() + SimTime(30, SIMTIME_MS), workNearPlatoon);
        }else{


        }
    }




    if(msg == singleJoin){
      //  traciVehicle->setActiveController(Plexe::FAKED_CACC);
        singleJoin = new cMessage();
        scheduleAt(simTime() + SimTime(30, SIMTIME_MS), singleJoin);
        if(flag_shortPath){
            shortPath_fnc(vehicle_ID);
        }else if(flag_nearPlatoon){
            nearPlatoon_fnc(vehicle_ID);
        }else if(flag_ready){
         //   app->startJoinManeuver(0,0, -1);
        }

    }

}

/*
void JoinManeuverScenario::shortPath_fn(){

    std::vector< std::vector<nodeData> > eachLane;
    for(int x=0;x<6;x=x+1){
        std::vector<nodeData> kill;
        eachLane.push_back(kill);
    }

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
    

    for(nodeData item:eachLane[currentLane]){
        int distance= item.positionX - myVehicle.positionX;
        if(distance>0 && distance < 15){
            traciVehicle->setCruiseControlDesiredSpeed(item.speed);
            

            /////
            int identy = 2 - currentLane;
            int moveLane;
            if(identy>0 || currentLane==0){
                moveLane = currentLane + 1; 
            }else{
                moveLane = currentLane - 1; 
            }
            int flag = 0;
            for(nodeData side:eachLane[moveLane]){
                distance=side.positionX- myVehicle.positionX;
                if(distance>-5 && distance < 5){
                    flag=1;
                    break;
                }

            } 

            if(flag==1){
                moveLane = 2*currentLane - moveLane;
            }

              traciVehicle->setFixedLane(moveLane);
              traciVehicle->setCruiseControlDesiredSpeed((100 / 3.6) + (30 / 3.6));
            ////
            break;
        }

    } 

}

*/




void JoinManeuverScenario::shortPath_fnc(int vehicle_id)
{
    int final_speed=0;
    flag_shortPath =1;
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
 //   int sir=targetPlatoonData->newFormation.at((targetPlatoonData->joinIndex) - 1);
    int sir= vehicle_id;
    int needDistance = vehData[sir].positionX - myVehicle.positionX;


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

    bool p;

    if(needDistance > -5){
        direction = 1;
    }else{
        direction = -1;
    }




    if(currentLane == (vehData[sir].positionY)){
        if((needDistance>0) && (needDistance<5)){
            p= false;
        }else{
            p=true;
        }
    }else{
        if((needDistance> -20) && (needDistance<10) ){
            p= false;
        }else{
            p=true;
        }

    }
    

    if(p){
        int sideGo = 0;

        if(early!= 0){
            sideGo = early;
        }
        early = 0;
        traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed + ((30 / 3.6)*direction));
        int i =-1;
        for(nodeData item:eachLane[currentLane]){
            i=i+1;
            int distance= (item.positionX - myVehicle.positionX)*direction;
            if((distance>(25-5*direction)) && (distance < 40)){
                traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed + ((20 / 3.6)*direction));
            }
            else if(((distance>0 && distance < (25-5*direction)) && (item.id != sir) || (stucked!=0)))  {
                final_speed = 1;
                traciVehicle->setCruiseControlDesiredSpeed(item.speed);
                speed_front= item.speed;
                state=1;
                ///awlak atha front speed item1
                /////
                int identy = vehData[sir].positionY - currentLane;
                int moveLane;
                if(identy>0 || currentLane==0 ){
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
                        traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed - ((30 / 3.6)*direction));
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

                    traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed + ((30 / 3.6)*direction));
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

                    traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed- ((30 / 3.6)*direction));
                    final_speed = 4;
                }         
                ////
                break;
            }

        }
    }else{
        flag_shortPath = 0;
        flag_nearPlatoon = 1;
    }
    EV<<"EasyToFind.....3::::"<<final_speed<< endl;
} 






void JoinManeuverScenario::nearPlatoon_fnc(int vehicle_id){
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
    int sir = vehicle_id;
    int needDistance = vehData[sir].positionX - myVehicle.positionX;
    traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed);
    if(vehData[sir].positionY != currentLane){
        int moveto;
        if(vehData[sir].positionY > currentLane){
            moveto = currentLane + 1;
        }else{
            moveto = currentLane - 1;
        }
        int flag=0;
        int flag2=0;
        int front_speed=0;
        int itemSpeed=0;
        for(nodeData item:eachLane[moveto]){
            int distance= (item.positionX - myVehicle.positionX);
            if((distance>- 8 && distance < 8)){
                itemSpeed = item.speed;
                flag=1;
                break;
            }
        }

        if(flag == 0){
            traciVehicle->setFixedLane(moveto);
            traciVehicle->setCruiseControlDesiredSpeed(vehData[sir].speed);
        }else{
            for(nodeData item:eachLane[currentLane]){
                int distance2= (item.positionX - myVehicle.positionX);
                if((distance2 > 0 && distance2 < 15)){
                    front_speed = item.speed;
                }
                flag2=1;
                break;
            }

            if(flag2 && ((vehData[sir].speed) > front_speed )){

            }else{
                front_speed = (vehData[sir].speed);
            }

            if(itemSpeed == front_speed){
                    traciVehicle->setCruiseControlDesiredSpeed(front_speed - (30 / 3.6));
            }
        }
    }else{
        flag_nearPlatoon=0;
        if((needDistance < 0) || (needDistance > 5.5)){
            flag_shortPath = 1;
            direction=1;
        }else{
            traciVehicle->setCruiseControlDesiredSpeed((vehData[sir].speed)+ (30 / 3.6));
            flag_ready=0;
        }
    }

    EV<<"EasyToFind.....4::::"<< endl;
       
}



