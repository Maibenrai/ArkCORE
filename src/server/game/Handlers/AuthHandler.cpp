/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gamePCH.h"
#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"

void WorldSession::SendAuthResponse(uint8 code, bool shortForm,
        uint32 queuePos) {
    WorldPacket packet(SMSG_AUTH_RESPONSE,
            1 + 4 + 1 + 4 + 2 + 1 + (shortForm ? 0 : (4 + 1)));
    packet << uint8(code);
    packet << uint32(0); // BillingTimeRemaining
    packet << uint8(0); // BillingPlanFlags
    packet << uint32(0); // BillingTimeRested
    packet << uint8(Expansion()); // payed expansion
    packet << uint8(Expansion()); // server expansion

    if (!shortForm) {
        packet << uint32(queuePos); // Queue position
        packet << uint8(0); // Unk 3.3.0
    }

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version) {
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}