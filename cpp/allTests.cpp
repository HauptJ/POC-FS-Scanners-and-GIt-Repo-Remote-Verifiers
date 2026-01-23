//
// Created by josh on 1/22/26.
//

#include "gtest/gtest.h"
#include "gitRepoUtil_unittests.cpp"
#include "rootDirScanner_unittests.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}