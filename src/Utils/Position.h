//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_POSITION_H
#define CAL1920_POSITION_H


class Position {
private:
    double x, y;
public:
    Position(double x, double y);
    double getX() const;
    double getY() const;
    double calculateRealDistance(const Position & p2);
};



#endif //CAL1920_POSITION_H
