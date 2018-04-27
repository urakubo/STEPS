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


#ifndef STEPS_WMRSSA_PATCH_HPP
#define STEPS_WMRSSA_PATCH_HPP 1


// STL headers.
#include <cassert>
#include <vector>
#include <fstream>

// STEPS headers.
#include "steps/common.h"
#include "steps/solver/patchdef.hpp"
#include "steps/wmrssa/kproc.hpp"
#include "steps/wmrssa/comp.hpp"
#include "steps/wmrssa/sreac.hpp"
#include "steps/solver/types.hpp"

////////////////////////////////////////////////////////////////////////////////

 namespace steps {
 namespace wmrssa {

////////////////////////////////////////////////////////////////////////////////

namespace swmrssa = steps::wmrssa;

////////////////////////////////////////////////////////////////////////////////

// Forward declarations.
class Patch;
class Wmrssa;

// Auxiliary declarations.
typedef Patch *                         PatchP;
typedef std::vector<PatchP>             PatchPVec;
typedef PatchPVec::iterator             PatchPVecI;
typedef PatchPVec::const_iterator       PatchPVecCI;

////////////////////////////////////////////////////////////////////////////////

class Patch
{
public:

    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    Patch(steps::solver::Patchdef * patchdef, swmrssa::Comp * icomp, swmrssa::Comp * ocomp);
    ~Patch(void);

    ////////////////////////////////////////////////////////////////////////
    // CHECKPOINTING
    ////////////////////////////////////////////////////////////////////////
    /// checkpoint data
    void checkpoint(std::fstream & cp_file);

    /// restore data
    void restore(std::fstream & cp_file);

    ////////////////////////////////////////////////////////////////////////

    void setupKProcs(Wmrssa * wmd);
    void setupDeps(void);

    void reset(void);

    ////////////////////////////////////////////////////////////////////////
    // DATA ACCESS
    ////////////////////////////////////////////////////////////////////////

    inline steps::solver::Patchdef * def(void) const
    { return pPatchdef; }

    ////////////////////////////////////////////////////////////////////////

    inline std::vector<steps::wmrssa::KProc *>::const_iterator kprocBegin(void) const
    { return pKProcs.begin(); }
    inline std::vector<steps::wmrssa::KProc *>::const_iterator kprocEnd(void) const
    { return pKProcs.end(); }
    inline uint countKProcs(void) const
    { return pKProcs.size(); }

    steps::wmrssa::KProc * sreac(uint lsridx) const;

    ////////////////////////////////////////////////////////////////////////

    inline swmrssa::Comp * iComp(void) const
    { return pIComp; }

    inline swmrssa::Comp * oComp(void) const
    { return pOComp; }

    ////////////////////////////////////////////////////////////////////////

    void setBounds(uint i, int nc);
    bool isOutOfBound(uint i, int nc);
    double* pools(steps::wmrssa::PropensityRSSA prssa) const;
    void setupSpecDeps(void);
    std::vector<steps::wmrssa::KProc*> const & getSpecUpdKProcs(uint slidx);

private:

    ////////////////////////////////////////////////////////////////////////

    steps::solver::Patchdef             * pPatchdef;

    /// The kinetic processes.
    std::vector<steps::wmrssa::KProc *> pKProcs;

    swmrssa::Comp                          * pIComp;
    swmrssa::Comp                          * pOComp;
    // Table of the lower bounds on populations of the species in this compartment.
    double                              * pPoolLB;
    // Table of the upper bounds on populations of the species in this compartment.
    double                              * pPoolUB;
    std::vector<std::vector<steps::wmrssa::KProc *>> localSpecUpdKProcs;

    ////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}
}

#endif
// STEPS_WMRSSA_PATCH_HPP

// END
