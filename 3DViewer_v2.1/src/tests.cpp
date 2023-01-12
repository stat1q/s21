#include <gtest/gtest.h>

#include "Model/parser.h"

TEST(model, test_1) {
  s21::Parser test;
  std::string filename = "obj_files/Logo_S21.obj";
  test.fillData(filename);

  EXPECT_EQ(test.numberOfFlat(), 84);
  EXPECT_EQ(test.numberOfVertexes(), 46);
}

TEST(texture_parse, test_1) {
  s21::Parser test;
  std::string filename = "obj_files/Backpack.obj";
  test.fillData(filename);
  EXPECT_EQ(test.numberOfFlat(), 24176);
  EXPECT_EQ(test.numberOfVertexes(), 24184);
  std::vector<s21::SingleNormal> normal = test.getNormals();
  std::vector<s21::SingleVertex> vertex = test.getVertexesCoords();
  std::vector<s21::SingleTexture> texture = test.getTextureCoords();
  test.clearModel();
  EXPECT_GE(normal.size(), 0);
  EXPECT_GE(vertex.size(), 0);
  EXPECT_GE(texture.size(), 0);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
