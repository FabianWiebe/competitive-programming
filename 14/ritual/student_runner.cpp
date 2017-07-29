#include <cstdint>
#include <limits>
#include <stdexcept>
#include <iostream>

namespace ffr_runner_impl {

#if TESTCASE == 1
#include "testcase_sample.cpp"
#elif TESTCASE == 2
#include "testcase_largeSample.cpp"
#else
#error "TESTCASE must be defined as either `1` (sample) or `2` (largeSample)."
#endif

static const uint32_t* ACTIVE_TESTCASE_DATA = nullptr;
static uint32_t ACTIVE_TESTCASE_SIZE = 0;
static uint32_t ACTIVE_TESTCASE_QUERY_CNT = 0;

uint32_t checked_index(uint32_t x, uint32_t y) {
    if (ACTIVE_TESTCASE_SIZE == 0 || ACTIVE_TESTCASE_DATA == nullptr) {
        throw std::logic_error("testcase data was accessed while no testcase was active");
    }

    if (x >= ACTIVE_TESTCASE_SIZE || y >= ACTIVE_TESTCASE_SIZE) {
        throw std::out_of_range("the coordinates given were outside the range of this testcase");
    }

    return y * ACTIVE_TESTCASE_SIZE + x;
}

uint32_t query(uint32_t x, uint32_t y) {
    if (ACTIVE_TESTCASE_QUERY_CNT < std::numeric_limits<uint32_t>::max()) {
        ACTIVE_TESTCASE_QUERY_CNT += 1;
    }

    uint32_t idx = checked_index(x, y);

    return ACTIVE_TESTCASE_DATA[idx];
}

void run(void) {
    for (uint32_t i = 0; i < TESTCASE_CNT; i++) {
        ACTIVE_TESTCASE_DATA = TESTCASE_DATA[i];
        ACTIVE_TESTCASE_SIZE = TESTCASE_SIZE[i];
        ACTIVE_TESTCASE_QUERY_CNT = 0;

        uint64_t res = forest_search(ACTIVE_TESTCASE_SIZE);

        uint32_t xres = (uint32_t)res;
        uint32_t yres = (uint32_t)(res >> 32);

        uint32_t val = ACTIVE_TESTCASE_DATA[checked_index(xres, yres)];

        std::cout << i << ": ";

        if (xres > 0 && ACTIVE_TESTCASE_DATA[checked_index(xres - 1, yres)] < val) {
            std::cout << "error: not a lokal minimum, -x neighbor is smaller" << std::endl;
            continue;
        }

        if (yres > 0 && ACTIVE_TESTCASE_DATA[checked_index(xres, yres - 1)] < val) {
            std::cout << "error: not a lokal minimum, -y neighbor is smaller" << std::endl;
            continue;
        }

        uint32_t s1 = ACTIVE_TESTCASE_SIZE - 1;

        if (xres < s1 && ACTIVE_TESTCASE_DATA[checked_index(xres + 1, yres)] < val) {
            std::cout << "error: not a lokal minimum, +x neighbor is smaller" << std::endl;
            continue;
        }

        if (yres < s1 && ACTIVE_TESTCASE_DATA[checked_index(xres, yres + 1)] < val) {
            std::cout << "error: not a lokal minimum, +y neighbor is smaller" << std::endl;
            continue;
        }

        uint32_t max_queries = 14 * ACTIVE_TESTCASE_SIZE;

        if (ACTIVE_TESTCASE_QUERY_CNT > max_queries) {
            std::cout << "error: too many queries (" << ACTIVE_TESTCASE_QUERY_CNT << "/" << max_queries << ")" << std::endl;
            continue;
        }

        std::cout << "ok" << std::endl;
    }
}

}

uint64_t forest_encode_solution(uint32_t solution_x, uint32_t solution_y) {
    return ((uint64_t)solution_y << 32) | solution_x;
}

uint32_t forest_measure(uint32_t x, uint32_t y) {
    return ffr_runner_impl::query(x, y);
}

int main(void) {
    ffr_runner_impl::run();

    return 0;
}
