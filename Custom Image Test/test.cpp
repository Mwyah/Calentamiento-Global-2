#include "pch.h"

unsigned char data[] = {1,  2,  3,  4,  5, 
                        6,  7,  8,  9,  10,
                        11, 12, 13, 14, 15, 
                        16, 17, 18, 19, 20};


TEST(Image, Constructors) {
	Image img1 = Image();
    EXPECT_TRUE(img1.data() == nullptr);
    EXPECT_EQ(img1.cols(), 0);
    EXPECT_EQ(img1.rows(), 0);
    EXPECT_EQ(img1.channels(), 0);
    EXPECT_EQ(img1.total(), 0);
    EXPECT_TRUE(img1.empty());
    EXPECT_EQ(img1.countRef(), 1);

    Image img2 = Image(10, 0, 3);
    EXPECT_TRUE(img2.data() == nullptr);
    EXPECT_EQ(img2.cols(), 0);
    EXPECT_EQ(img2.rows(), 10);
    EXPECT_EQ(img2.channels(), 3);
    EXPECT_EQ(img2.total(), 0);
    EXPECT_TRUE(img2.empty());
    EXPECT_EQ(img2.countRef(), 1);

    Image img3 = Image(10, 10, 3);
    EXPECT_TRUE(img3.data() == nullptr);
    EXPECT_EQ(img3.cols(), 10);
    EXPECT_EQ(img3.rows(), 10);
    EXPECT_EQ(img3.channels(), 3);
    EXPECT_EQ(img3.total(), 100);
    EXPECT_TRUE(img3.empty());
    EXPECT_EQ(img3.countRef(), 1);

    Image img4 = Image(3, 3, 2, data);
    EXPECT_FALSE(img4.data() == nullptr);
    EXPECT_EQ(img4.cols(), 3);
    EXPECT_EQ(img4.rows(), 3);
    EXPECT_EQ(img4.channels(), 2);
    EXPECT_EQ(img4.total(), 9);
    EXPECT_FALSE(img4.empty());
    EXPECT_EQ(img4.countRef(), 1);
}

TEST(Image, at) {
    Image img = Image(3, 3, 2, data);
    EXPECT_EQ(img.at(0), 1);
    EXPECT_EQ(img.at(2), 5);
    EXPECT_EQ(img.at(8), 17);
}

TEST(Image, CopyingAndDestructing) {
    Image* img1 = new Image(3, 3, 2, data);
    EXPECT_EQ(img1->countRef(), 1);

    Image img2 = Image(*img1);
    EXPECT_EQ(img1->countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);

    Image img3 = Image(img2, Range(0, 2), Range(1, 3));
    EXPECT_EQ(img1->countRef(), 3);
    EXPECT_EQ(img2.countRef(), 3);
    EXPECT_EQ(img3.countRef(), 3);

    EXPECT_EQ(img3.cols(), 2);
    EXPECT_EQ(img3.rows(), 2);
    EXPECT_EQ(img3.channels(), 2);
    EXPECT_EQ(img3.total(), 4);
    EXPECT_FALSE(img3.empty());
    EXPECT_EQ(img3.at(0), 3);
    EXPECT_EQ(img3.at(3), 11);

    delete img1;

    EXPECT_EQ(img2.countRef(), 2);
    EXPECT_EQ(img3.countRef(), 2);
}

TEST(Image, Operators) {
    Image img1 = Image(3, 3, 2, data);
    EXPECT_EQ(img1.countRef(), 1);

    Image img2 = img1;
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);

    Image img3 = img1(Range(0, 2), Range(1, 3));
    EXPECT_EQ(img1.countRef(), 3);
    EXPECT_EQ(img2.countRef(), 3);
    EXPECT_EQ(img3.countRef(), 3);

    EXPECT_EQ(img3.cols(), 2);
    EXPECT_EQ(img3.rows(), 2);
    EXPECT_EQ(img3.channels(), 2);
    EXPECT_EQ(img3.total(), 4);
    EXPECT_FALSE(img3.empty());
    EXPECT_EQ(img3.at(0), 3);
    EXPECT_EQ(img3.at(3), 11);
}

TEST(Image, Clone) {
    Image img1 = Image(3, 3, 2, data);
    EXPECT_EQ(img1.countRef(), 1);

    Image img2 = img1;
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);

    Image img3 = img1.clone();
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);
    EXPECT_EQ(img3.countRef(), 1);

    EXPECT_EQ(img2.cols(), 3);
    EXPECT_EQ(img2.rows(), 3);
    EXPECT_EQ(img2.channels(), 2);
    EXPECT_EQ(img2.total(), 9);
    EXPECT_FALSE(img2.empty());
    EXPECT_EQ(img2.at(0), 1);
    EXPECT_EQ(img2.at(7), 15);

    img1.cloneTo(img2);
    EXPECT_EQ(img1.countRef(), 1);
    EXPECT_EQ(img2.countRef(), 1);
    EXPECT_EQ(img3.countRef(), 1);

    EXPECT_EQ(img3.cols(), 3);
    EXPECT_EQ(img3.rows(), 3);
    EXPECT_EQ(img3.channels(), 2);
    EXPECT_EQ(img3.total(), 9);
    EXPECT_FALSE(img3.empty());
    EXPECT_EQ(img3.at(0), 1);
    EXPECT_EQ(img3.at(7), 15);
}

TEST(Image, Create) {
    Image img1 = Image(3, 3, 2, data);

    Image img2 = img1;
    img2.create(2, 2, 3);
    EXPECT_EQ(img1.countRef(), 1);
    EXPECT_EQ(img2.countRef(), 1);
    EXPECT_EQ(img2.at(1), 4);
    EXPECT_EQ(img2.at(3), 10);
}

TEST(Image, Col) {
    Image img1 = Image(3, 3, 2, data);

    Image img2 = img1.col(2);
    EXPECT_EQ(img2.cols(), 1);
    EXPECT_EQ(img2.rows(), 3);
    EXPECT_EQ(img2.countRef(), 2);
    EXPECT_EQ(img2.at(0), 5);
    EXPECT_EQ(img2.at(1), 11);

    Image img3 = img1.row(2);
    EXPECT_EQ(img3.cols(), 3);
    EXPECT_EQ(img3.rows(), 1);
    EXPECT_EQ(img3.countRef(), 3);
    EXPECT_EQ(img3.at(0), 13);
    EXPECT_EQ(img3.at(1), 15);

    Image img4 = img1.col(3);
    EXPECT_TRUE(img4.empty());

    Image img5 = img1.row(3);
    EXPECT_TRUE(img5.empty());
}

TEST(Image, ColRange) {
    Image img1 = Image(3, 3, 2, data);

    Image img2 = img1.colRange(Range(1, 2));
    EXPECT_EQ(img2.cols(), 1);
    EXPECT_EQ(img2.rows(), 3);
    EXPECT_EQ(img2.countRef(), 2);
    EXPECT_EQ(img2.at(0), 3);
    EXPECT_EQ(img2.at(1), 9);

    Image img3 = img1.rowRange(Range(1, 2));
    EXPECT_EQ(img3.cols(), 3);
    EXPECT_EQ(img3.rows(), 1);
    EXPECT_EQ(img3.countRef(), 3);
    EXPECT_EQ(img3.at(0), 7);
    EXPECT_EQ(img3.at(1), 9);
}

TEST(Image, ZerosAndValues) {
    Image img1 = Image::zeros(3, 3, 3);
    EXPECT_EQ(img1.cols(), 3);
    EXPECT_EQ(img1.rows(), 3);
    EXPECT_EQ(img1.channels(), 3);
    EXPECT_EQ(img1.total(), 9);
    EXPECT_FALSE(img1.empty());
    EXPECT_EQ(img1.countRef(), 1);
    EXPECT_EQ(img1.at(0), 0);
    EXPECT_EQ(img1.at(7), 0);

    Image img2 = Image::values(3, 3, 3, 10);
    EXPECT_EQ(img2.cols(), 3);
    EXPECT_EQ(img2.rows(), 3);
    EXPECT_EQ(img2.channels(), 3);
    EXPECT_EQ(img2.total(), 9);
    EXPECT_FALSE(img2.empty());
    EXPECT_EQ(img2.countRef(), 1);
    EXPECT_EQ(img2.at(0), 10);
    EXPECT_EQ(img2.at(7), 10);
}

