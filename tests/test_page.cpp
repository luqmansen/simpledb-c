//
// Created by Luqman Setyo Nugroho on 08/12/24.
//
#include <iostream>
#include "gtest/gtest.h"

extern "C" {
#include "page.h"
}


TEST(Page, transfer_page_content) {
    size_t page_size = 100; // 100 bytes
    Page *page1 = Page_create_with_size(page_size);

    Page_set_int(page1, 0, 420);
    Page_set_string(page1, 80, "Valkomen");

    EXPECT_EQ(
        Page_get_int(page1, 0),
        420
    );
    EXPECT_STREQ(
        Page_get_string(page1, 80),
        "Valkomen"
    );

    char* page1_content = Page_contents(page1);
    Page* page2 = Page_create_from_bytes(page1_content, page_size);

    EXPECT_EQ(
        Page_get_int(page2, 0),
        420
    );
    EXPECT_STREQ(
        Page_get_string(page2, 80),
        "Valkomen"
    );

    Page_destroy(page1);
    Page_destroy(page2);
    free(page1_content);
}

TEST(Page, set_and_get_int) {
    size_t page_size = 100; // 100 bytes
    Page *page1 = Page_create_with_size(page_size);

    int lastOffset = 0;
    for (int i= 0; i<=20; i++) {
        Page_set_int(page1, lastOffset, i);
        lastOffset += sizeof(i);
    }
    lastOffset = 0;
    for (int i= 0; i<=20; i++) {
        EXPECT_EQ(
            Page_get_int(page1, lastOffset),
            i
        );
        lastOffset += sizeof(i);
    }

    Page_destroy(page1);

}

TEST(Page, set_and_get_str) {
    size_t page_size = 4000;
    Page *page1 = Page_create_with_size(page_size);

    int lastOffset = 0;
    for (int i= 0; i<=20; i++) {
        char buffer[32];
        snprintf(buffer, sizeof buffer, "%d", i);
        Page_set_string(page1, lastOffset, buffer);
        lastOffset += sizeof buffer;
    }
    lastOffset = 0;
    for (int i= 0; i<=20; i++) {
        char buffer[32];
        snprintf(buffer, sizeof buffer, "%d", i);
        EXPECT_STREQ(
            Page_get_string(page1, lastOffset),
            buffer
        );
        lastOffset += sizeof(buffer);
    }

    Page_destroy(page1);

}



