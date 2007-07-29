////////////////////////////////////////////////////////////////////////////////
// STEPS - STochastic Engine for Pathway Simulation
// Copyright (C) 2005-2007 Stefan Wils. All rights reserved.
//
// $Id$
////////////////////////////////////////////////////////////////////////////////

// STL headers.
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// STEPS headers.
#include <steps/common.h>
#include <steps/math/constants.hpp>
#include <steps/rng/rng.hpp>
#include <steps/sim/shared/compdef.hpp>
#include <steps/sim/shared/reacdef.hpp>
#include <steps/sim/shared/specdef.hpp>
#include <steps/sim/shared/statedef.hpp>
#include <steps/sim/swiginf/func_core.hpp>
#include <steps/sim/wmdirect/state.hpp>

////////////////////////////////////////////////////////////////////////////////

// STEPS library.
NAMESPACE_ALIAS(steps::math, smath);

////////////////////////////////////////////////////////////////////////////////

char * siGetSolverName(void)
{
    return "tetexact";
}

////////////////////////////////////////////////////////////////////////////////

char * siGetSolverDesc(void)
{
    return "Exact SSA in tetrahedral mesh";
}

////////////////////////////////////////////////////////////////////////////////

char * siGetSolverAuthors(void)
{
    return "Stefan Wils";
}

////////////////////////////////////////////////////////////////////////////////

char * siGetSolverEmail(void)
{
    return "wils@oist.jp";
}

////////////////////////////////////////////////////////////////////////////////

State * siNewState(void)
{
}

////////////////////////////////////////////////////////////////////////////////

void siDelState(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siBeginStateDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siEndStateDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siBeginVarDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siEndVarDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

uint siNewSpec(State * s, char * name)
{
}

////////////////////////////////////////////////////////////////////////////////

void siBeginReacDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siEndReacDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

uint siNewReac(State * s, char * name, double kcst)
{
}

////////////////////////////////////////////////////////////////////////////////

void siAddReacLHS(State * s, uint ridx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siAddReacRHS(State * s, uint ridx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siBeginCompDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siEndCompDef(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

uint siNewComp(State * s, char * name, double vol)
{
}

////////////////////////////////////////////////////////////////////////////////

void siAddCompSpec(State * s, uint cidx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siAddCompReac(State * s, uint cidx, uint ridx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetRNG(State * s, steps::rng::RNG * rng)
{
}

////////////////////////////////////////////////////////////////////////////////

void siReset(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

void siRun(State * s, double endtime)
{
}

////////////////////////////////////////////////////////////////////////////////

double siGetTime(State * s)
{
}

////////////////////////////////////////////////////////////////////////////////

double siGetCompVol(State * s, uint cidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompVol(State * s, uint cidx, double vol)
{
}

////////////////////////////////////////////////////////////////////////////////

uint siGetCompCount(State * s, uint cidx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompCount(State * s, uint cidx, uint sidx, uint n)
{
}

////////////////////////////////////////////////////////////////////////////////

double siGetCompMass(State * s, uint cidx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompMass(State * s, uint cidx, uint sidx, double m)
{
}

////////////////////////////////////////////////////////////////////////////////

double siGetCompConc(State * s, uint cidx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompConc(State * s, uint cidx, uint sidx, double c)
{
}

////////////////////////////////////////////////////////////////////////////////

bool siGetCompClamped(State * s, uint cidx, uint sidx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompClamped(State * s, uint cidx, uint sidx, bool buf)
{
}

////////////////////////////////////////////////////////////////////////////////

double siGetCompReacK(State * s, uint cidx, uint ridx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompReacK(State * s, uint cidx, uint ridx, double kf)
{
}

////////////////////////////////////////////////////////////////////////////////

bool siGetCompReacActive(State * s, uint cidx, uint ridx)
{
}

////////////////////////////////////////////////////////////////////////////////

void siSetCompReacActive(State * s, uint cidx, uint ridx, bool act)
{
}

////////////////////////////////////////////////////////////////////////////////

// END
