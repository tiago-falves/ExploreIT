//
// Created by tiago on 08/05/2020.
//

#include "Position.h"

#include <cmath>

#include "Position.h"

Position::Position(double x, double y) {
    this->x = x;
    this->y = y;
}

double Position::getX() const {
    return x;
}

double Position::getY() const {
    return y;
}

double Position::calculateRealDistance(const Position &p2){
    return sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
}
