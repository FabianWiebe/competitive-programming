#include <cstdint>

static const uint32_t TESTCASE_0[9] = {
    2, 3, 4,
    1, 0, 5,
    2, 3, 4,
};

static const uint32_t TESTCASE_1[9] = {
    1, 2, 3,
    0, 5, 4,
    1, 2, 3,
};


static const uint32_t TESTCASE_2[25] = {
    11,  9,  7,  0, 30,
    13, 99,  9, 20, 40,
    15, 11, 10, 30, 50,
    17, 18, 20, 35, 60,
    19, 21, 23, 25, 30,
};

static const uint32_t TESTCASE_CNT = 3;

static const uint32_t TESTCASE_SIZE[3] = { 3, 3, 5 };

static const uint32_t* TESTCASE_DATA[3] = { TESTCASE_0, TESTCASE_1, TESTCASE_2 };
