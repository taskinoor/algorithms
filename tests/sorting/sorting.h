#ifndef ALGTEST_SORTING_H_
#define ALGTEST_SORTING_H_

#include <array>
#include <string>
#include <gtest/gtest.h>

namespace algtest {

class Sorting : public ::testing::Test {
protected:
    std::array<int, 0> empty;
    std::array<std::string, 1> single_element;
    std::array<int, 13> already_sorted;
    std::array<int, 13> reverse_sorted;
    std::array<int, 13> random_ordered;

    std::array<int, 13> expected;
    std::array<std::string, 1> expected_single_element;

    virtual void SetUp() {
        single_element = {"two"};
        already_sorted = {2, 2, 3, 5, 7, 11, 13, 17, 19, 19, 23, 29, 31};
        reverse_sorted = {31, 29, 23, 19, 19, 17, 13, 11, 7, 5, 3, 2, 2};
        random_ordered = {13, 2, 3, 19, 7, 5, 23, 2, 11, 31, 19, 29, 17};

        expected = {2, 2, 3, 5, 7, 11, 13, 17, 19, 19, 23, 29, 31};
        expected_single_element = {"two"};
    }
};

}

#endif