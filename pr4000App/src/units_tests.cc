#include <gtest/gtest.h>

#include <epicsString.h>
#include <aSubRecord.h>
#include <menuFtype.h>

#include "units.h"

// in an asub function you should not reassign members of asubRecord,
// however we are setting up an asubRecord here and so need to do so

namespace {
    TEST(Units, test_GIVEN_index_THEN_check_unit_returned){
        // GIVEN
        aSubRecord rec;

        rec.fta = menuFtypeLONG;
        rec.noa = 1;
        rec.a = new epicsInt32[rec.noa];

        rec.ftva = menuFtypeSTRING;
        rec.nova = 1;
        rec.vala = new epicsOldString[rec.nova];

        // WHEN
        *(epicsInt32*)rec.a = 1;
        int ret = units_number_to_string(&rec);

        // THEN
        EXPECT_EQ(ret, 0);
        EXPECT_STREQ(*(epicsOldString*)rec.vala, "mBar"); // or could make UNITS_ARRAY accessible and lookup directly

        delete[] rec.a;
        delete[] rec.vala;
    }

    TEST(Units, test_GIVEN_unit_THEN_check_index_returned){
        // GIVEN
        aSubRecord rec;

        rec.fta = menuFtypeSTRING;
        rec.noa = 1;
        rec.a = new epicsOldString[rec.noa];

        rec.ftva = menuFtypeLONG;
        rec.nova = 1;
        rec.vala = new epicsInt32[rec.nova];

        // WHEN
        strncpy(*(epicsOldString*)rec.a, "Torr", sizeof(epicsOldString));
        int ret = units_string_to_number(&rec);

        // THEN
        EXPECT_EQ(ret, 0);
        EXPECT_EQ(*(epicsInt32*)rec.vala, 4); // or could make UNITS_ARRAY accessible and lookup

        delete[] rec.a;
        delete[] rec.vala;
    }
} // namespace
