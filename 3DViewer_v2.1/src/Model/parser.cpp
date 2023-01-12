#include "parser.h"

namespace s21 {

Parser::Parser() : countVertexes_(0), countFlats_(0) {}

std::vector<SingleVertex> Parser::getVertexesCoords() {
  return vertexesCoords_;
}

std::vector<SingleNormal> Parser::getNormals() { return normals_; }

std::vector<SingleTexture> Parser::getTextureCoords() { return textureCoords_; }

void Parser::setUpdater(ModelListener *newUpdater) { updater = newUpdater; }

void Parser::fillData(std::string fileName) {
  std::ifstream infile(fileName);
  std::string line;
  while (std::getline(infile, line)) {
    if (line[0] == 'v' && std::isspace(line[1])) {
      vertexesCoords_.push_back(SingleVertex(singleLineProcessing(line)));
      countVertexes_++;
    } else if (line[0] == 'v' && line[1] == 't' && std::isspace(line[2])) {
      textureCoords_.push_back(SingleTexture(singleLineProcessing(line)));
    } else if (line[0] == 'v' && line[1] == 'n' && std::isspace(line[2])) {
      normals_.push_back(SingleNormal(singleLineProcessing(line)));
    } else if (std::isspace(line[1]) && line[0] == 'f') {
      countFlats_++;
      if (checkFlatToQuads(line)) {
        parseF(writeFirstTriangle(line));
        parseF(writeSecondTriangle(line));
      } else {
        parseF(line);
      }
    }
  }
  if (updater != nullptr) {
    updater->updateModel(indexes_, vertexesCoords_, textureCoords_, normals_);
  }
}

bool Parser::checkFlatToQuads(std::string line) {
  int flatCount = 0;
  while (line.find(' ') != std::string::npos) {
    line = line.substr(line.find(" ") + 1);
    flatCount++;
  }
  return (flatCount > 3) ? true : false;
}

std::string Parser::writeFirstTriangle(std::string inputLine) {
  std::string numbers = "1234567890";
  while (numbers.find_last_of(inputLine.back()) == std::string::npos) {
    inputLine.pop_back();
  }
  return inputLine.erase(inputLine.find_last_of(" "));
}

std::string Parser::writeSecondTriangle(std::string inputLine) {
  std::string::size_type firstSpace =
      inputLine.find(" ", inputLine.find(" ") + 1);
  std::string::size_type secondSpace = inputLine.find(" ", firstSpace + 1);
  return inputLine.erase(firstSpace, secondSpace - firstSpace);
}

std::vector<double> Parser::singleLineProcessing(std::string line) {
  int count = 0;
  std::string substr;
  size_t find1 = 0;
  std::vector<double> oneVertex;

  while (line.find(' ') != std::string::npos) {
    try {
      if (!std::isspace(line[line.find(' ') + 1])) {
        substr = line.substr(line.find(' ') + 1);
        if (!substr.empty()) {
          oneVertex.push_back(stod(substr));
          line.clear();
          line.append(substr);
        } else {
          break;
        }
      } else {
        find1 = line.find(' ');
        line.erase(0, find1 + 1);
        count--;
      }
    } catch (std::invalid_argument &e) {
      line.erase(0, 1);
    }
    count++;
    if (count > 2) break;
  }
  return oneVertex;
}

void Parser::parseF(std::string line) {
  std::string substrForAllLine;
  std::string substrForOneToken;
  size_t find1 = 0;

  while (line.find(' ') != std::string::npos) {
    try {
      if (!std::isspace(line[line.find(' ') + 1])) {
        substrForAllLine = line.substr(line.find(' ') + 1);
        indexes_.push_back(stoi(substrForAllLine));

        if (substrForAllLine.find('/') != std::string::npos) {
          if (substrForAllLine[substrForAllLine.find('/') + 1] != '/') {
            substrForOneToken =
                substrForAllLine.substr(substrForAllLine.find('/') + 1);
            indexes_.push_back(stoi(substrForOneToken));
            substrForAllLine.clear();
            substrForAllLine.append(substrForOneToken);
            substrForOneToken =
                substrForAllLine.substr(substrForAllLine.find('/') + 1);
            indexes_.push_back(stoi(substrForOneToken));
          } else {
            substrForOneToken =
                substrForAllLine.substr(substrForAllLine.find('/') + 2);
            indexes_.push_back(stoi(substrForOneToken));
          }
        }
        line.clear();
        line.append(substrForAllLine);
      } else {
        find1 = line.find(' ');
        line.erase(0, find1 + 1);
      }
    } catch (std::invalid_argument &e) {
      line.erase(0, 1);
    }
  }
}

int Parser::numberOfVertexes() { return countVertexes_; }

int Parser::numberOfFlat() { return countFlats_; }

void Parser::clearModel() {
  indexes_.clear();
  vertexesCoords_.clear();
  textureCoords_.clear();
  normals_.clear();
}

}  // namespace s21
