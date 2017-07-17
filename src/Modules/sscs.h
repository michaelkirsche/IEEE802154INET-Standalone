//
// Copyright (C) 2013 Matti Schnurbusch (original code)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
// 
#pragma once

#ifndef SSCS_H_
#define SSCS_H_

#include "mcpsData_m.h"

#define sscsEV (ev.isDisabled()||!sscsDebug) ? EV : EV << "[802154_SSCS]: " // switchable debug output

class sscs : public cSimpleModule
{
    public:
        sscs(){};  // std Ctor
        virtual ~sscs(){}; // std Dtor;

    protected:
        virtual void initialize(int stage);
        virtual int numInitStages() const { return 1; }

        virtual void handleMessage(cMessage* msg);

    protected:
        /** @brief Debug output switch for the SSCS module */
        bool sscsDebug = false;
};

#endif /* SSCS_H_ */
