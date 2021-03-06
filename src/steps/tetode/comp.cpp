/*
 #################################################################################
#
#    STEPS - STochastic Engine for Pathway Simulation
#    Copyright (C) 2007-2018 Okinawa Institute of Science and Technology, Japan.
#    Copyright (C) 2003-2006 University of Antwerp, Belgium.
#    
#    See the file AUTHORS for details.
#    This file is part of STEPS.
#    
#    STEPS is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License version 2,
#    as published by the Free Software Foundation.
#    
#    STEPS is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#    
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#################################################################################   

 */


// Standard library & STL headers.
#include <map>
#include <vector>

// STEPS headers.
#include "steps/common.h"
#include "steps/error.hpp"
#include "steps/solver/compdef.hpp"
#include "steps/tetode/comp.hpp"
#include "steps/tetode/tet.hpp"
// logging
#include "easylogging++.h"
////////////////////////////////////////////////////////////////////////////////

namespace stode = steps::tetode;
namespace ssolver = steps::solver;

////////////////////////////////////////////////////////////////////////////////

stode::Comp::Comp(steps::solver::Compdef * compdef)
: pCompdef(compdef)
, pTets()
, pVol(0.0)
, pTets_GtoL()
{
    AssertLog(pCompdef != 0);
}

////////////////////////////////////////////////////////////////////////////////

stode::Comp::~Comp()
= default;

////////////////////////////////////////////////////////////////////////////////

void stode::Comp::checkpoint(std::fstream & cp_file)
{
    cp_file.write((char*)&pVol, sizeof(double));
}

////////////////////////////////////////////////////////////////////////////////

void stode::Comp::restore(std::fstream & cp_file)
{
    cp_file.read((char*)&pVol, sizeof(double));
}

////////////////////////////////////////////////////////////////////////////////

void stode::Comp::addTet(stode::Tet * tet)
{
    AssertLog(tet->compdef() == def());
    uint lidx = pTets.size();
    pTets.push_back(tet);
    pTets_GtoL.insert(std::pair<uint, uint>(tet->idx(), lidx));

    pVol+=tet->vol();
}

////////////////////////////////////////////////////////////////////////////////

stode::Tet * stode::Comp::getTet(uint lidx)
{
    AssertLog(lidx < pTets.size());
    return pTets[lidx];
}


////////////////////////////////////////////////////////////////////////////////

uint stode::Comp::getTet_GtoL(uint gidx)
{
    std::map<uint, uint>::const_iterator lidx_it = pTets_GtoL.find(gidx);
    AssertLog(lidx_it != pTets_GtoL.end());
    return lidx_it->second;
}

////////////////////////////////////////////////////////////////////////////////

// END
