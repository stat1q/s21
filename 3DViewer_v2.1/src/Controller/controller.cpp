#include "controller.h"

namespace s21 {

void Controller::callParser(std::string fileName) { model_.fillData(fileName); }

int Controller::getVertexCount() { return model_.numberOfVertexes(); }

int Controller::getFlatCount() { return model_.numberOfFlat(); }

Parser& Controller::getModel() { return model_; }

void Controller::clearModel() { model_.clearModel(); }

}  // namespace s21
