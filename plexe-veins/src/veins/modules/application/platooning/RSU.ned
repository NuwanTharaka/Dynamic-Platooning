//
// Copyright (C) 2008 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

//package org.car2x.veins.nodes;
package org.car2x.veins.modules.application.platooning;

import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.application.platooning.*;
import org.car2x.veins.modules.nic.Nic80211p;

//from PlatoonCar.ned

import org.car2x.veins.base.modules.BaseApplLayer;
import org.car2x.veins.base.modules.IBaseApplLayer;
import org.car2x.veins.modules.application.platooning.utilities.BasePositionHelper;
import org.car2x.veins.modules.application.platooning.scenarios.BaseScenario;
import org.car2x.veins.modules.application.platooning.protocols.BaseProtocol;
import org.car2x.veins.modules.application.platooning.apps.BaseApp;
import org.car2x.veins.modules.application.platooning.UnicastProtocol;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;



module RSU
{
    parameters:
        //string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card

        //string scenario_type;
        string helper_type;
        string appl_type;
        string protocol_type;

    gates:
        input veinsradioIn; // gate for sendDirect
    submodules:

        helper: <helper_type> like BasePositionHelper {
            parameters:
                @display("p=60,127");
        }
        //scenario: <scenario_type> like BaseScenario {
        //    parameters:
        //        @display("p=130,88");
        //}

        appl: <appl_type> like BaseApp{
            parameters:
                @display("p=60,50");
        }

        prot: <protocol_type> like BaseProtocol {
            parameters:
                @display("p=60,204");
        }

        unicast: UnicastProtocol {
            parameters:
                @display("p=60,277");
        }

        nic: <nicType> like org.car2x.veins.modules.nic.INic80211p {
            parameters:
                @display("p=60,345");
        }

        mobility: TraCIMobility {
            parameters:
                @display("p=130,172;i=block/cogwheel");
        }

    connections allowunconnected:
        //nic.upperLayerOut --> appl.lowerLayerIn;
        //nic.upperLayerIn <-- appl.lowerLayerOut;
        //nic.upperControlOut --> appl.lowerControlIn;
        //nic.upperControlIn <-- appl.lowerControlOut;

        unicast.upperControlIn <-- prot.lowerControlOut;
        unicast.upperControlOut --> prot.lowerControlIn;
        unicast.upperLayerIn <-- prot.lowerLayerOut;
        unicast.upperLayerOut --> prot.lowerLayerIn;
        nic.upperLayerIn <-- unicast.lowerLayerOut;
        nic.upperLayerOut --> unicast.lowerLayerIn;
        
        veinsradioIn --> nic.radioIn;
}
