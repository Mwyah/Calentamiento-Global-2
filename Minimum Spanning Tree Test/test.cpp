//
// test.cpp
//

#include <vector>
#include "gtest\gtest.h"

#include "..\Minimum Spanning Tree\MSTFinder.hpp"


TEST(Edge, len) {

	Vertex v1("a", 0, 0), v2("b", 1, 3), v3("c", -2, -2), v4("d", 0.5, 3);

	EXPECT_EQ(Edge(v1, v2, 0, 0).length(), sqrtf(10));
	EXPECT_EQ(Edge(v1, v3, 0, 0).length(), sqrtf(8));
	EXPECT_EQ(Edge(v1, v4, 0, 0).length(), sqrtf(9.25));
	EXPECT_EQ(Edge(v2, v3, 0, 0).length(), sqrtf(34));
	EXPECT_EQ(Edge(v3, v4, 0, 0).length(), sqrtf(31.25));
}

TEST(VertexParser, parsing) {
	std::istringstream iss("1, 1, 1\nallah, 3, 7\na b c, 3, 3.7 3\n2, , , 2, 2,\n , z, 3, 3\na, 3, ");

	Vertex answers[] = {Vertex("1", 1, 1),   Vertex("allah", 3, 7),
		                Vertex("a", 3, 3.7), Vertex("2", 2, 2), 
		                Vertex("z", 3, 3),   Vertex("", 0, 0)};

	size_t i = 0;
	while(!iss.eof()) {
		Vertex v = VertexParser::parse(iss);
		EXPECT_EQ(v.name(), answers[i].name());
		EXPECT_EQ(v.x(), answers[i].x());
		EXPECT_EQ(v.y(), answers[i].y());

		i++;
	}
}

TEST(MSTFinder, adding) {
	MSTFinder mstf;

	EXPECT_EQ(mstf.addVertex(Vertex("", 0, 0)), false);
	EXPECT_EQ(mstf.addVertex(Vertex("a", 2, 2)), true);
	EXPECT_EQ(mstf.addVertex(Vertex("b", 1, 1)), true);
	EXPECT_EQ(mstf.addVertex(Vertex("b", 7, 8)), false);
	EXPECT_EQ(mstf.addVertex(Vertex("c", 1, 1)), false);
}

TEST(MSTFinder, finding) {
	MSTFinder mstf1, mstf2, mstf3, mstf4;
	std::ostringstream oss1, oss2, oss3, oss4;

	mstf1.findMST(oss1);
	EXPECT_EQ(oss1.str(), "");

	mstf2.addVertex({"a", 3, 5});
	mstf2.findMST(oss2);
	EXPECT_EQ(oss2.str(), "");

	mstf3.addVertex({"a", 3, 5});
	mstf3.addVertex({"b", 0, 0});
	mstf3.findMST(oss3);
	EXPECT_EQ(oss3.str(), "a - b");

	mstf4.addVertex({"1", -2, 3});
	mstf4.addVertex({"2", -3, 0});
	mstf4.addVertex({"3", -1, -1});
	mstf4.addVertex({"4", 0, 0});
	mstf4.addVertex({"5", 0, -3});
	mstf4.addVertex({"6", 2, 2});
	mstf4.addVertex({"7", 4, 2});
	mstf4.findMST(oss4);
	EXPECT_TRUE((oss4.str() == "3 - 4\n6 - 7\n2 - 3\n3 - 5\n4 - 6\n1 - 2") ||
				(oss4.str() == "3 - 4\n6 - 7\n3 - 5\n2 - 3\n4 - 6\n1 - 2"));
}