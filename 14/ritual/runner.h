#pragma once

#ifndef __cplusplus
#error "This header is written for C++."
#endif

#ifndef _MSC_VER
#if __cplusplus < 201103L
#warning "This header requries C++11."
#endif
#endif

#include <cstdint>

extern "C" {

/// This function must be implemented by you. It is called once per test case
/// and receives one argument, the length of one side of the forest. It must
/// return the coordinates of the dark tree, encoded by `forest_encode_solution`.
///
/// This function will not be called concurrently. It will only be called again,
/// after the previous call has returned.
uint64_t forest_search(uint32_t n);

/// This function is provided. It encodes two 32bit coordinates `x` and `y` into
/// one 64bit value, as `(y << 32) | x`;
uint64_t forest_encode_solution(uint32_t solution_x, uint32_t solution_y);

/// This function is provided. It must only be called from inside
/// `forest_search`. Given some coordinates, `x` and `y`, the height of the tree
/// at that point will be returned.
uint32_t forest_measure(uint32_t x, uint32_t y);

}

#ifndef DOMJUDGE
#include "student_runner.cpp"
#endif
