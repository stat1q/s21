#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "modellistener.h"
#include "normal.h"
#include "texture.h"
#include "vertex.h"

namespace s21 {
class Parser {
 private:
  std::vector<int> indexes_;
  std::vector<SingleVertex> vertexesCoords_;
  std::vector<SingleTexture> textureCoords_;
  std::vector<SingleNormal> normals_;

  ModelListener *updater = nullptr;

  unsigned int countVertexes_;
  unsigned int countFlats_;

 private:
  std::vector<double> singleLineProcessing(std::string line);
  void parseF(std::string line);
  bool checkFlatToQuads(std::string line);
  std::string writeFirstTriangle(std::string inputLine);
  std::string writeSecondTriangle(std::string inputLine);

 public:
  Parser();
  ~Parser(){};

 public:
  void fillData(std::string fileName);
  int numberOfVertexes();
  int numberOfFlat();
  void clearModel();

  std::vector<SingleVertex> getVertexesCoords();
  std::vector<SingleTexture> getTextureCoords();
  std::vector<SingleNormal> getNormals();
  std::vector<int> getIndexes() { return indexes_; }
  void setUpdater(ModelListener *newUpdater);
};
}  // namespace s21
#endif  // PARSER_H
