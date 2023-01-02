//
// Created by sondahi on 30.12.22.
//

#include "gtest/gtest.h"

extern "C" {
#include "x.h"
}

TEST(Test,test1){
    int a = add (1,1);
    EXPECT_EQ(a,2);
}