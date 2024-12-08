//
// Created by Luqman Setyo Nugroho on 08/12/24.
//
#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "file/block.h"
}


TEST(Block, all) {
    Block *block1 = Block_create("file1.txt", 1);
    EXPECT_STREQ(
        Block_filename(block1),
        "file1.txt"
    );
    EXPECT_EQ(
        Block_number(block1),
        1
    );

    Block *block2 = Block_create("file1.txt", 1);

    EXPECT_TRUE(Block_equals(block1, block2));

    Block_destroy(block1);
    Block_destroy(block2);
}