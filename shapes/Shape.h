#ifndef SHAPE_H
#define SHAPE_H


#include <iostream>
#include <memory>
#include <cmath>
#include <cstring>
#include <SFML/Graphics.hpp>



class Shape {
    public:
        // A constant used to an error margin to account for floating point errors.
        static constexpr double EPSILON_ERROR = 1e-10;
};










#endif // SHAPE_H