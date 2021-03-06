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


#ifndef STEPS_TETEXACT_GHKCURR_HPP
#define STEPS_TETEXACT_GHKCURR_HPP 1

////////////////////////////////////////////////////////////////////////////////

// Standard library & STL headers.
#include <string>
#include <vector>

// STEPS headers.
#include "steps/common.h"
#include "steps/math/constants.hpp"
#include "steps/solver/ghkcurrdef.hpp"
#include "steps/tetexact/kproc.hpp"
//#include "tetexact.hpp"


////////////////////////////////////////////////////////////////////////////////

namespace steps{
namespace tetexact{

////////////////////////////////////////////////////////////////////////////////

// Forward declarations.
class Tri;
class Tetexact;

////////////////////////////////////////////////////////////////////////////////

class GHKcurr
: public steps::tetexact::KProc
{

public:

    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    GHKcurr(steps::solver::GHKcurrdef * ghkdef, steps::tetexact::Tri * tri);
    ~GHKcurr();

    ////////////////////////////////////////////////////////////////////////
    // CHECKPOINTING
    ////////////////////////////////////////////////////////////////////////
    /// checkpoint data
    void checkpoint(std::fstream & cp_file);

    /// restore data
    void restore(std::fstream & cp_file);

    ////////////////////////////////////////////////////////////////////////
    // VIRTUAL INTERFACE METHODS
    ////////////////////////////////////////////////////////////////////////

    void setupDeps();
    bool depSpecTet(uint gidx, steps::tetexact::WmVol * tet);
    bool depSpecTri(uint gidx, steps::tetexact::Tri * tri);
    void reset();


    double rate(steps::tetexact::Tetexact * solver);

    // double rate(double v, double T);
    std::vector<KProc*> const & apply(steps::rng::RNG * rng, double dt, double simtime);

    inline bool efflux() const
    { return pEffFlux; }

    void setEffFlux(bool efx)
    { pEffFlux = efx; }

    uint updVecSize() const
    { return pUpdVec.size(); }

    ////////////////////////////////////////////////////////////////////////

private:

    ////////////////////////////////////////////////////////////////////////

    steps::solver::GHKcurrdef         * pGHKcurrdef;
    steps::tetexact::Tri              * pTri;
    std::vector<KProc*>                 pUpdVec;

    // Flag if flux is outward, positive flux (true) or inward, negative flux (false)
    bool                                pEffFlux;

    ////////////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////

#endif

// STEPS_TETEXACT_GHKCURR_HPP
