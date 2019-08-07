#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <epicsTypes.h>
#include <string.h>

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

static long units_number_to_string(aSubRecord *prec)
{
    int i;
    epicsOldString result;
    
    i = *(int*) prec->a;
    
    if (0 <= i && i < UNITS_ARRAY_SIZE)
    {
        strcpy_s(result, MAX_STRING_SIZE, UNITS_ARRAY[i]);
    }
    else
    {
        strcpy_s(result, MAX_STRING_SIZE, "Unknown");
    }
    
    prec->vala = result;
    
    return 0;
}

static long units_string_to_number(aSubRecord *prec)
{
    int i;
    epicsOldString* input;
    
    input = (epicsOldString*) prec->a;
    
    for (i=0; i<UNITS_ARRAY_SIZE; ++i) 
    {
        if (_stricmp(input, UNITS_ARRAY[i]) == 0)
        {
            *(long*) prec->vala = i;
            return 0;
        }
    }
    return 1;
}

epicsRegisterFunction(units_number_to_string);
epicsRegisterFunction(units_string_to_number);
