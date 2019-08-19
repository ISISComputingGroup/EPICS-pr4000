#include <stdlib.h>
#include <string.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <menuFtype.h>
#include <errlog.h>
#include <epicsTypes.h>
#include <epicsString.h>
#include <units.h>

#include <epicsExport.h>

static const char* UNITS_ARRAY[] = {
    "uBar",  // 0
    "mBar",  // 1
    "Bar",   // 2
    "mTor",  // 3
    "Torr",  // 4
    "kTor",  // 5
    "Pa",    // 6
    "kPa",   // 7
    "mH2O",  // 8
    "cH2O",  // 9
    "PSI",   // 10
    "N/qm",  // 11
    "SCCM",  // 12
    "SLM",   // 13
    "SCM",   // 14
    "SCFH",  // 15
    "SCFM",  // 16
    "mA",    // 17
    "V",     // 18
    "%",     // 19
    "C",     // 20
};

#define UNITS_ARRAY_SIZE (sizeof(UNITS_ARRAY) / sizeof(const char*))

long units_number_to_string(aSubRecord *prec)
{
    epicsInt32 i;
    epicsOldString* result = (epicsOldString*)prec->vala;
    i = *(epicsInt32*)prec->a;
    if (prec->fta != menuFtypeLONG || prec->ftva != menuFtypeSTRING)
    {
         errlogPrintf("%s incorrect input type. Should be A (LONG), VALA (STRING)", prec->name);
         return -1;
    }

    if (0 <= i && i < UNITS_ARRAY_SIZE)
    {
        strcpy_s(*result, MAX_STRING_SIZE, UNITS_ARRAY[i]);
    }
    else
    {
        strcpy_s(*result, MAX_STRING_SIZE, "Unknown");
    }
    return 0;
}

long units_string_to_number(aSubRecord *prec)
{
    epicsInt32 i;
    epicsOldString* input = (epicsOldString*) prec->a;
    if (prec->fta != menuFtypeSTRING || prec->ftva != menuFtypeLONG)
    {
         errlogPrintf("%s incorrect input type. Should be A (STRING), VALA (LONG)", prec->name);
         return -1;
    }

    for (i=0; i<UNITS_ARRAY_SIZE; ++i) 
    {
        // use case sensitive comparison as e.g. "mBar" and "MBar" are not the same
        if (strcmp(*input, UNITS_ARRAY[i]) == 0)
        {
            *(epicsInt32*)prec->vala = i;
            return 0;
        }
    }
    return 1;
}

epicsRegisterFunction(units_number_to_string);
epicsRegisterFunction(units_string_to_number);
