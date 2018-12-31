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

#include "veins/modules/application/platooning/maneuver/JoinAtBack.h"
#include "veins/modules/application/platooning/apps/GeneralPlatooningApp.h"
#include <veins/modules/mobility/traci/TraCIBaseTrafficManager.h>


#ifndef coreEV
#define coreEV_clear EV
#define coreEV EV << logName() << "::" << getClassName() << ": "
#endif

JoinAtBack::JoinAtBack(GeneralPlatooningApp* app)
    : JoinManeuver(app)
    , joinManeuverState(JoinManeuverState::IDLE)
{
}

void JoinAtBack::startManeuver(const void* parameters)
{
    JoinManeuverParameters* pars = (JoinManeuverParameters*) parameters;
    if (joinManeuverState == JoinManeuverState::IDLE) {
        ASSERT(app->getPlatoonRole() == PlatoonRole::NONE);
        ASSERT(!app->isInManeuver());

        app->setInManeuver(true);
        app->setPlatoonRole(PlatoonRole::JOINER);

        // collect information about target Platoon
        targetPlatoonData.reset(new TargetPlatoonData());
        targetPlatoonData->platoonId = pars->platoonId;
        targetPlatoonData->platoonLeader = pars->leaderId;

        // send join request to leader
        JoinPlatoonRequest* req = createJoinPlatoonRequest(positionHelper->getId(), positionHelper->getExternalId(), targetPlatoonData->platoonId, targetPlatoonData->platoonLeader, traciVehicle->getLaneIndex(), mobility->getCurrentPosition().x, mobility->getCurrentPosition().y);
        app->sendUnicast(req, targetPlatoonData->platoonLeader);
        joinManeuverState = JoinManeuverState::J_WAIT_REPLY;
        EV<<"EasyToFind.....1"<<positionHelper->getId()<< endl;
    }
}

void JoinAtBack::abortManeuver()
{
}

void JoinAtBack::onPlatoonBeacon(const PlatooningBeacon* pb)
{
    if (joinManeuverState == JoinManeuverState::J_MOVE_IN_POSITION) {
        // check correct role
        ASSERT(app->getPlatoonRole() == PlatoonRole::JOINER);

        // if the message comes from the leader
        if (pb->getVehicleId() == targetPlatoonData->newFormation.at(0)) {
            traciVehicle->setLeaderVehicleFakeData(pb->getControllerAcceleration(), pb->getAcceleration(), pb->getSpeed());
        }
        // if the message comes from the front vehicle
        int frontPosition = targetPlatoonData->joinIndex - 1;
        int frontId = targetPlatoonData->newFormation.at(frontPosition);
        if (pb->getVehicleId() == frontId) {
            // get front vehicle position
            Coord frontPosition(pb->getPositionX(), pb->getPositionY(), 0);
            // get my position
            Veins::TraCICoord traciPosition = mobility->getManager()->omnet2traci(mobility->getCurrentPosition());
            Coord position(traciPosition.x, traciPosition.y);
            // compute distance
            double distance = position.distance(frontPosition) - pb->getLength();
            traciVehicle->setFrontVehicleFakeData(pb->getControllerAcceleration(), pb->getAcceleration(), pb->getSpeed(), distance);
            // if we are in position, tell the leader about that
            if ((distance < 16) && (flag_shortPath==0) && (flag_nearPlatoon==0)) { // TODO fixed value? make dependent on ..................................................................metthana < daanna
                // controller and headway time
                // send move to position response to confirm the parameters
                traciVehicle->setFixedLane(targetPlatoonData->platoonLane);
                MoveToPositionAck* ack = createMoveToPositionAck(positionHelper->getId(), positionHelper->getExternalId(), targetPlatoonData->platoonId, targetPlatoonData->platoonLeader, targetPlatoonData->platoonSpeed, targetPlatoonData->platoonLane, targetPlatoonData->newFormation);
                app->sendUnicast(ack, targetPlatoonData->newFormation.at(0));
                joinManeuverState = JoinManeuverState::J_WAIT_JOIN;
            }
            else{
                
            }
        }
    }
}


void JoinAtBack::shortPath_fn()
{
    int final_speed=0;
    flag_shortPath =1;
    std::vector< std::vector<nodeData> > eachLane;
    for(int x=0;x<6;x=x+1){
        std::vector<nodeData> kill;
        eachLane.push_back(kill);
    }
    int nLanes = 4;
    int state = 0;

    int myVehicleId = positionHelper->getId();

    std::vector<nodeData> vehData = getData();
    nodeData myVehicle = vehData[myVehicleId];
    int needDistance = vehData[(targetPlatoonData->platoonLeader)+3].positionX - myVehicle.positionX;


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
    if(currentLane == (targetPlatoonData->platoonLane)){
        if((needDistance>0) && (needDistance<20)){
            p= false;
        }else{
            p=true;
        }
    }else{
        if((needDistance>-20) && (needDistance<20) ){
            p= false;
        }else{
            p=true;
        }

    }
    

    if(p){
        traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed + ((30 / 3.6)*direction));
        for(nodeData item:eachLane[currentLane]){
            int distance= (item.positionX - myVehicle.positionX)*direction;
            if((distance>0 && distance < 20) || (stucked!=0)){
                final_speed = 1;
                traciVehicle->setCruiseControlDesiredSpeed(item.speed);
                speed_front= item.speed;
                state=1;
                /////
                int identy = targetPlatoonData->platoonLane - currentLane;
                int moveLane;
                if(identy>0 || currentLane==0){
                    moveLane = currentLane + 1; 
                }else{
                    moveLane = currentLane - 1; 
                }

                if(stucked>0){
                    moveLane = currentLane + 1; 
                }else if(stucked<0){
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
                    if((speed_front == speed_side1) && (stucked==0)){
                        gotoback=1;
                    }else if(stucked!=0){
                        traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed - ((30 / 3.6)*direction));
                        final_speed = 2;
                    }else{

                    }
                }else if(noption2){
                    if(((speed_front == speed_side1) && (speed_front == speed_side2))){
                        gotoback=1;
                    }else{
                        
                    }

                }else{
                    traciVehicle->setFixedLane(moveLane);
                    traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed + ((30 / 3.6)*direction));
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

                    traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed - ((30 / 3.6)*direction));
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






void JoinAtBack::nearPlatoon_fn(){
    std::vector< std::vector<nodeData> > eachLane;
    for(int x=0;x<6;x=x+1){
        std::vector<nodeData> kill;
        eachLane.push_back(kill);
    }
    int nLanes = 4;
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

    int needDistance = vehData[targetPlatoonData->platoonLeader+3].positionX - myVehicle.positionX;
    traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed);
    if(targetPlatoonData->platoonLane != currentLane){
        int moveto;
        if(targetPlatoonData->platoonLane > currentLane){
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
            traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed);
        }else{
            for(nodeData item:eachLane[currentLane]){
                int distance2= (item.positionX - myVehicle.positionX);
                if((distance2 > 0 && distance2 < 15)){
                    front_speed = item.speed;
                }
                flag2=1;
                break;
            }

            if(flag2 && ((targetPlatoonData->platoonSpeed) > front_speed )){

            }else{
                front_speed = (targetPlatoonData->platoonSpeed);
            }

            if(itemSpeed == front_speed){
                    traciVehicle->setCruiseControlDesiredSpeed(front_speed - (30 / 3.6));
            }
        }
    }else{
        flag_nearPlatoon=0;
        if((needDistance < 0) || (needDistance > 20)){
            flag_shortPath = 1;
        }
    }

    EV<<"EasyToFind.....4::::"<< endl;
       
}

void JoinAtBack::handleJoinPlatoonRequest(const JoinPlatoonRequest* msg)
{

    if (msg->getPlatoonId() != positionHelper->getPlatoonId()) return;

    if (app->getPlatoonRole() != PlatoonRole::LEADER && app->getPlatoonRole() != PlatoonRole::NONE) return;

    bool permission = app->isJoinAllowed();

    // send response to the joiner
    JoinPlatoonResponse* response = createJoinPlatoonResponse(positionHelper->getId(), positionHelper->getExternalId(), msg->getPlatoonId(), msg->getVehicleId(), permission);
    app->sendUnicast(response, msg->getVehicleId());

    if (!permission) return;

    app->setInManeuver(true);
    app->setPlatoonRole(PlatoonRole::LEADER);

    // disable lane changing during maneuver
    traciVehicle->setFixedLane(traciVehicle->getLaneIndex());
    positionHelper->setPlatoonLane(traciVehicle->getLaneIndex());

    // save some data. who is joining?
    joinerData.reset(new JoinerData());
    joinerData->from(msg);

    // this was only to grant the request
    // now send the data about the platoon to the joiner
    // add the joiner to the end of the platoon
    joinerData->newFormation = positionHelper->getPlatoonFormation();
    joinerData->newFormation.push_back(joinerData->joinerId);

    MoveToPosition* mtp = createMoveToPosition(positionHelper->getId(), positionHelper->getExternalId(), positionHelper->getPlatoonId(), joinerData->joinerId, positionHelper->getPlatoonSpeed(), positionHelper->getPlatoonLane(), joinerData->newFormation);
    app->sendUnicast(mtp, joinerData->joinerId);

    EV<<"EasyToFind.....2"<<positionHelper->getId()<< endl;

    joinManeuverState = JoinManeuverState::L_WAIT_JOINER_IN_POSITION;
}

void JoinAtBack::handleJoinPlatoonResponse(const JoinPlatoonResponse* msg)
{
    if (app->getPlatoonRole() != PlatoonRole::JOINER) return;
    if (joinManeuverState != JoinManeuverState::J_WAIT_REPLY) return;
    if (msg->getPlatoonId() != targetPlatoonData->platoonId) return;
    if (msg->getVehicleId() != targetPlatoonData->platoonLeader) return;

    // evaluate permission
    if (msg->getPermitted()) {
        // wait for information about the join maneuver
        joinManeuverState = JoinManeuverState::J_WAIT_INFORMATION;
        // disable lane changing during maneuver
        traciVehicle->setFixedLane(traciVehicle->getLaneIndex());
        EV<<"EasyToFind.....3"<<positionHelper->getId()<< endl;
    }
    else {
        // abort maneuver
        joinManeuverState = JoinManeuverState::IDLE;
        app->setPlatoonRole(PlatoonRole::NONE);
        app->setInManeuver(false);
    }
}

void JoinAtBack::handleMoveToPosition(const MoveToPosition* msg)
{
    if (app->getPlatoonRole() != PlatoonRole::JOINER) return;
    if (joinManeuverState != JoinManeuverState::J_WAIT_INFORMATION) return;
    if (msg->getPlatoonId() != targetPlatoonData->platoonId) return;
    if (msg->getVehicleId() != targetPlatoonData->platoonLeader) return;

    // the leader told us to move in position, we can start
    // save some data about the platoon
    targetPlatoonData->from(msg);

    // check for correct lane. if not in correct lane, change it
    // if this already is the platoon lane, join at the back (or v.v.)
    // if this is not the plaoon lane, we have to move into longitudinal
    // position
    int currentLane = traciVehicle->getLaneIndex();
    if (currentLane != targetPlatoonData->platoonLane) {
      //  traciVehicle->setFixedLane(targetPlatoonData->platoonLane);
    }

    // approaching the platoon

    // activate faked CACC. this way we can approach the front car
    // using data obtained through GPS
    traciVehicle->setCACCConstantSpacing(5);
    // we have no data so far, so for the moment just initialize
    // with some fake data
    traciVehicle->setLeaderVehicleFakeData(0, 0, targetPlatoonData->platoonSpeed);
    traciVehicle->setFrontVehicleFakeData(0, 0, targetPlatoonData->platoonSpeed, 15);
    // set a CC speed higher than the platoon speed to approach it


   

    
    traciVehicle->setActiveController(Plexe::FAKED_CACC);

    joinManeuverState = JoinManeuverState::J_MOVE_IN_POSITION;

    flag_shortPath =1;
    direction= 1;
    traciVehicle->setCruiseControlDesiredSpeed(targetPlatoonData->platoonSpeed + ((20 / 3.6)*direction));
    EV<<"EasyToFind.....4"<<positionHelper->getId()<< endl;
}



void JoinAtBack::handleMoveToPositionAck(const MoveToPositionAck* msg)
{
    if (app->getPlatoonRole() != PlatoonRole::LEADER) return;
    if (joinManeuverState != JoinManeuverState::L_WAIT_JOINER_IN_POSITION) return;
    if (msg->getPlatoonId() != positionHelper->getPlatoonId()) return;
    if (msg->getVehicleId() != joinerData->joinerId) return;

    for (unsigned i = 0; i < msg->getNewPlatoonFormationArraySize(); i++) ASSERT(msg->getNewPlatoonFormation(i) == joinerData->newFormation.at(i));

    // the joiner is now in position and is ready to join

    // tell the joiner to join the platoon
    JoinFormation* jf = createJoinFormation(positionHelper->getId(), positionHelper->getExternalId(), positionHelper->getPlatoonId(), joinerData->joinerId, positionHelper->getPlatoonSpeed(), traciVehicle->getLaneIndex(), joinerData->newFormation);
    app->sendUnicast(jf, joinerData->joinerId);
    joinManeuverState = JoinManeuverState::L_WAIT_JOINER_TO_JOIN;
}

void JoinAtBack::handleJoinFormation(const JoinFormation* msg)
{
    if (app->getPlatoonRole() != PlatoonRole::JOINER) return;
    if (joinManeuverState != JoinManeuverState::J_WAIT_JOIN) return;
    if (msg->getPlatoonId() != targetPlatoonData->platoonId) return;
    if (msg->getVehicleId() != targetPlatoonData->platoonLeader) return;

    for (unsigned i = 0; i < msg->getNewPlatoonFormationArraySize(); i++) ASSERT(msg->getNewPlatoonFormation(i) == targetPlatoonData->newFormation[i]);

    // we got confirmation from the leader
    // switch from faked CACC to real CACC
    traciVehicle->setActiveController(Plexe::CACC);
    // set spacing to 5 meters to get close to the platoon
    traciVehicle->setCACCConstantSpacing(5);

    // update platoon information
    positionHelper->setPlatoonId(msg->getPlatoonId());
    positionHelper->setPlatoonLane(targetPlatoonData->platoonLane);
    positionHelper->setPlatoonSpeed(targetPlatoonData->platoonSpeed);
    std::vector<int> formation;
    for (unsigned i = 0; i < msg->getNewPlatoonFormationArraySize(); i++) formation.push_back(msg->getNewPlatoonFormation(i));
    positionHelper->setPlatoonFormation(formation);

    // tell the leader that we're now in the platoon
    JoinFormationAck* jfa = createJoinFormationAck(positionHelper->getId(), positionHelper->getExternalId(), positionHelper->getPlatoonId(), targetPlatoonData->platoonLeader, positionHelper->getPlatoonSpeed(), traciVehicle->getLaneIndex(), formation);
    app->sendUnicast(jfa, positionHelper->getLeaderId());

    app->setPlatoonRole(PlatoonRole::FOLLOWER);
    joinManeuverState = JoinManeuverState::IDLE;

    app->setInManeuver(false);
}

// final state for leader
// request update of formation information
void JoinAtBack::handleJoinFormationAck(const JoinFormationAck* msg)
{
    if (app->getPlatoonRole() != PlatoonRole::LEADER) return;
    if (joinManeuverState != JoinManeuverState::L_WAIT_JOINER_TO_JOIN) return;
    if (msg->getPlatoonId() != positionHelper->getPlatoonId()) return;
    if (msg->getVehicleId() != joinerData->joinerId) return;
    for (unsigned i = 0; i < msg->getNewPlatoonFormationArraySize(); i++) ASSERT(msg->getNewPlatoonFormation(i) == joinerData->newFormation.at(i));

    // the joiner has joined the platoon
    // add the joiner to the list of vehicles in the platoon
    positionHelper->setPlatoonFormation(joinerData->newFormation);

    // send to all vehicles in Platoon
    for (unsigned int i = 1; i < positionHelper->getPlatoonSize(); i++) {
        UpdatePlatoonFormation* dup = app->createUpdatePlatoonFormation(positionHelper->getId(), positionHelper->getExternalId(), positionHelper->getPlatoonId(), -1, positionHelper->getPlatoonSpeed(), traciVehicle->getLaneIndex(), joinerData->newFormation);
        int dest = positionHelper->getMemberId(i);
        dup->setDestinationId(dest);
        app->sendUnicast(dup, dest);
    }

    joinManeuverState = JoinManeuverState::IDLE;
    app->setInManeuver(false);
}
