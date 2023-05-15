#include "gtest/gtest.h"

#include "../Set/Set.h"


size_t charHash(const void* data) {
	return (size_t) *((char*) data);
}

bool charEquals(const void* a, const void* b) {
	return *((char*) a) == *((char*) b);
}

char dataArr[5] = {'a', 'c', '3', 'b', '#'};

void* set = set_create(0, NULL, NULL);


TEST(SetTest, Creating){

	EXPECT_TRUE(set_create(0, NULL, NULL) == NULL);
	EXPECT_TRUE(set_create(0, charHash, charEquals) == NULL);
	EXPECT_TRUE(set_create(sizeof(char), NULL, charEquals) == NULL);
	EXPECT_TRUE(set_create(sizeof(char), charHash, NULL) == NULL);

	void* set = set_create(sizeof(char), charHash, charEquals);
	ASSERT_TRUE(set != NULL);
	EXPECT_EQ(set_count(set), 0);

	set_destroy(set, NULL);
}


class SetTestClass : public ::testing::Test {
protected:

	void SetUp() override {
		emptySet = set_create(sizeof(char), charHash, charEquals);

		filledSet = set_create(sizeof(char), charHash, charEquals);
		set_insert(filledSet, dataArr);
		set_insert(filledSet, dataArr+1);
		set_insert(filledSet, dataArr+2);
	}

	void TearDown() override {
		set_destroy(emptySet, NULL);
		set_destroy(filledSet, NULL);
	}

	void* notSet = NULL;
	void* emptySet = NULL;
	void* filledSet = NULL;
};


int destroyCallCounter = 0;

void destroy(void* data) {
	destroyCallCounter++;
}

TEST_F(SetTestClass, Destroying) {
	
	set_destroy(NULL, destroy);
	EXPECT_EQ(destroyCallCounter, 0);
	destroyCallCounter = 0;

	set_destroy(emptySet, destroy);
	emptySet = NULL;
	EXPECT_EQ(destroyCallCounter, 0);
	destroyCallCounter = 0;

	set_destroy(filledSet, destroy);
	filledSet = NULL;
	EXPECT_EQ(destroyCallCounter, 3);
	destroyCallCounter = 0;
}

TEST_F(SetTestClass, Init) {

	EXPECT_TRUE(set_init(NULL, 0, NULL, NULL, NULL) == NULL);
	EXPECT_TRUE(set_init(NULL, 5, charHash, charEquals, NULL) == NULL);
	EXPECT_TRUE(set_init(emptySet, 0, charHash, charEquals, NULL) == emptySet);
	EXPECT_TRUE(set_init(emptySet, 0, NULL, charEquals, NULL) == emptySet);
	EXPECT_EQ(set_init(emptySet, 5, charHash, charEquals, NULL), emptySet);

	set_init(filledSet, 5, charHash, charEquals, destroy);
	EXPECT_EQ(destroyCallCounter, 3);
	destroyCallCounter = 0;
}

// set_clear used in set_destroy and set_init and was tested inderectly

TEST_F(SetTestClass, Count) {
	EXPECT_EQ(set_count(NULL), INVALID);
	EXPECT_EQ(set_count(emptySet), 0);
	EXPECT_EQ(set_count(filledSet), 3);
}

TEST_F(SetTestClass, Contains) {
	EXPECT_FALSE(set_contains(NULL, dataArr));

	EXPECT_FALSE(set_contains(emptySet, dataArr));

	EXPECT_TRUE(set_contains(filledSet, dataArr));
	EXPECT_FALSE(set_contains(filledSet, dataArr+3));
}

TEST_F(SetTestClass, Insert) {
	EXPECT_FALSE(set_insert(NULL, dataArr));

	EXPECT_TRUE(set_insert(emptySet, dataArr));
	EXPECT_EQ(set_count(emptySet), 1);
	EXPECT_TRUE(set_contains(emptySet, dataArr));

	EXPECT_FALSE(set_insert(filledSet, dataArr));
	EXPECT_EQ(set_count(filledSet), 3);

	EXPECT_TRUE(set_insert(filledSet, dataArr+3));
	EXPECT_EQ(set_count(filledSet), 4);
	EXPECT_TRUE(set_contains(filledSet, dataArr+3));
}

TEST_F(SetTestClass, Remove) {

	set_remove(emptySet, dataArr, destroy);
	EXPECT_EQ(destroyCallCounter, 0);
	destroyCallCounter = 0;

	set_remove(filledSet, dataArr, destroy);
	EXPECT_FALSE(set_contains(filledSet, dataArr));
	EXPECT_EQ(set_count(filledSet), 2);
	EXPECT_EQ(destroyCallCounter, 1);
	destroyCallCounter = 0;

	set_remove(filledSet, dataArr, destroy);
	EXPECT_EQ(set_count(filledSet), 2);
	EXPECT_EQ(destroyCallCounter, 0);
	destroyCallCounter = 0;
}

TEST_F(SetTestClass, First) {

	EXPECT_EQ(set_first(NULL), INVALID);
	EXPECT_EQ(set_first(emptySet), INVALID);
	EXPECT_EQ(set_first(filledSet), 0);
}

TEST_F(SetTestClass, Last) {

	EXPECT_EQ(set_last(NULL), INVALID);
	EXPECT_EQ(set_last(emptySet), INVALID);
	EXPECT_EQ(set_last(filledSet), 2);
}

TEST_F(SetTestClass, Next) {

	EXPECT_EQ(set_next(NULL, 0), INVALID);
	EXPECT_EQ(set_next(NULL, 1), INVALID);

	EXPECT_EQ(set_next(emptySet, 0), INVALID);
	EXPECT_EQ(set_next(emptySet, 1), INVALID);

	EXPECT_EQ(set_next(filledSet, 0), 1);
	EXPECT_EQ(set_next(filledSet, 1), 2);
	EXPECT_EQ(set_next(filledSet, 2), INVALID);
	EXPECT_EQ(set_next(filledSet, 3), INVALID);
}

TEST_F(SetTestClass, Prev) {

	EXPECT_EQ(set_prev(NULL, 0), INVALID);
	EXPECT_EQ(set_prev(NULL, 1), INVALID);

	EXPECT_EQ(set_prev(emptySet, 0), INVALID);
	EXPECT_EQ(set_prev(emptySet, 1), INVALID);

	EXPECT_EQ(set_prev(filledSet, 0), INVALID);
	EXPECT_EQ(set_prev(filledSet, 1), 0);
	EXPECT_EQ(set_prev(filledSet, 2), 1);
	EXPECT_EQ(set_prev(filledSet, 3), INVALID);
}

TEST_F(SetTestClass, Stop) {

	EXPECT_EQ(set_stop(NULL), INVALID);
	EXPECT_EQ(set_stop(emptySet), INVALID);
	EXPECT_EQ(set_stop(filledSet), INVALID);
}

TEST_F(SetTestClass, Current) {

	EXPECT_TRUE(set_current(NULL, 0) == NULL);

	EXPECT_TRUE(set_current(emptySet, 0) == NULL);

	EXPECT_EQ(set_current(filledSet, 0), dataArr);        //
	EXPECT_EQ(set_current(filledSet, 1), dataArr + 2);    // the element are numbered according to depth-first search
	EXPECT_EQ(set_current(filledSet, 2), dataArr + 1);    //
	EXPECT_TRUE(set_current(filledSet, 3) == NULL);
}

TEST_F(SetTestClass, Erase) {

	set_erase(emptySet, 0, destroy);
	EXPECT_EQ(destroyCallCounter, 0);
	destroyCallCounter = 0;

	set_erase(filledSet, 2, destroy);
	EXPECT_FALSE(set_contains(filledSet, dataArr+1));
	EXPECT_EQ(set_count(filledSet), 2);
	EXPECT_EQ(destroyCallCounter, 1);
	destroyCallCounter = 0;

	set_erase(filledSet, 2, destroy);
	EXPECT_EQ(set_count(filledSet), 2);
	EXPECT_EQ(destroyCallCounter, 0);
	destroyCallCounter = 0;
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}