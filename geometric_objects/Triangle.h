#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Line.h"
#include <memory>


class Triangle {
    private:
        std::shared_ptr<Point> p1;
        std::shared_ptr<Point> p2;
        std::shared_ptr<Point> p3;
        double epsilon_error = 1e-20; // Small value to handle floating-point errors

    public:
        Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3) : p1(p1), p2(p2), p3(p3) {}

        std::shared_ptr<Point> get_p1() const {return p1;}
        std::shared_ptr<Point> get_p2() const {return p2;}
        std::shared_ptr<Point> get_p3() const {return p3;}
        void set_p1(std::shared_ptr<Point> p1) {this->p1 = p1;}
        void set_p2(std::shared_ptr<Point> p2) {this->p2 = p2;}
        void set_p3(std::shared_ptr<Point> p3) {this->p3 = p3;}

        /**
         * Calculates the perimeter of the triangle.
         * 
         * The perimeter is calculated as the sum of the lengths of the three sides of the triangle.
         * 
         * @return The perimeter of the triangle.
         */
        double calculate_perimeter() const {
            double side1 = p1->distanceTo(*p2);
            double side2 = p2->distanceTo(*p3);
            double side3 = p3->distanceTo(*p1);
            return side1 + side2 + side3;
        }

        /**
         * Calculates the area of the triangle using the determinant method.
         * 
         * The area is calculated using the coordinates of the triangle's vertices
         * based on the formula: 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|, 
         * where (x1, y1), (x2, y2), and (x3, y3) are the coordinates of the triangle's vertices.
         * 
         * @return The area of the triangle.
         */
        double calculate_area() const {
            return this->calculate_area(p1, p2, p3);
        }


        /**
         * Calculates the area of the triangle using the determinant method.
         * 
         * The area is calculated using the coordinates of the triangle's vertices
         * based on the formula: 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|, 
         * where (x1, y1), (x2, y2), and (x3, y3) are the coordinates of the triangle's vertices.
         * 
         * @param a_ The first vertex of the triangle.
         * @param b_ The second vertex of the triangle.
         * @param c_ The third vertex of the triangle.
         * @return The area of the triangle.
         */
        double calculate_area(std::shared_ptr<Point> a_, std::shared_ptr<Point> b_, std::shared_ptr<Point> c_) const {
            return abs(a_->get_x() * (b_->get_y() - c_->get_y()) + 
                       b_->get_x() * (c_->get_y() - a_->get_y()) + 
                       c_->get_x() * (a_->get_y() - b_->get_y())) / 2.0;
        }

        double calculate_angle(const std::shared_ptr<Point>& a_, const std::shared_ptr<Point>& b_, const std::shared_ptr<Point>& c_) const {
            double length_ab = a_->distanceTo(*b_);
            double length_bc = b_->distanceTo(*c_);
            double length_ac = a_->distanceTo(*c_);

            // Calculate the cosine of the angle at a_
            double numerator = length_ab * length_ab + length_ac * length_ac - length_bc * length_bc;
            double denominator = 2 * length_ab * length_ac;
            
            double cos_angle_a = numerator / (denominator + epsilon_error);

            // Ensure the value is within the valid range for acos
            if (cos_angle_a < -1.0) cos_angle_a = -1.0;
            if (cos_angle_a > 1.0) cos_angle_a = 1.0;

            // angle at a_ in radians
            double angle_a = acos(cos_angle_a);

            return angle_a;
        }


        std::vector<double> angles() const {
            std::vector<double> angles{};
            angles.push_back(this->calculate_angle(p1, p2, p3));
            angles.push_back(this->calculate_angle(p2, p3, p1));
            angles.push_back(this->calculate_angle(p3, p1, p2));
            return angles;
        }

        /**
         * Converts the triangle to an SFML ConvexShape, allowing it to be drawn in an SFML window.
         *
         * @param color_fill The color to fill the triangle with.
         * @param color_outline The color to use for the outline of the triangle.
         * @param outline_thickness The thickness of the triangle's outline.
         * @return A shared pointer to an SFML ConvexShape object representing the triangle.
         */
        std::shared_ptr<sf::ConvexShape> to_convex_shape(const sf::Color& color_fill, const sf::Color& color_outline, const double outline_thichness) const {
            std::shared_ptr<sf::ConvexShape> triangle = std::make_shared<sf::ConvexShape>(3);
            
            triangle->setPoint(0, *p1->to_vector2f());
            triangle->setPoint(1, *p2->to_vector2f());
            triangle->setPoint(2, *p3->to_vector2f());
            triangle->setFillColor(color_fill);
            triangle->setOutlineColor(color_outline);
            triangle->setOutlineThickness(outline_thichness);
            return triangle;
        }
};


#endif // TRIANGLE_H