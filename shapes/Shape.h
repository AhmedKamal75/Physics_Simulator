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

        std::vector<double> static solve_quadratic(double a, double b, double c){
            std::vector<double> roots{};
            double discriminant = b * b - 4 * a * c;
            if (discriminant > 0) {
                double root1 = (-b + sqrt(discriminant)) / (2.0 * a);
                double root2 = (-b - sqrt(discriminant)) / (2.0 * a);
                roots.push_back(root1);
                roots.push_back(root2);
            } else if (discriminant == 0) {
                double root = -b / (2 * a);
                roots.push_back(root);  
            }
            return roots;
        }

};










#endif // SHAPE_H