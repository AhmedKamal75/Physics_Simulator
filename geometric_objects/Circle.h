#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include <memory>
#include <cmath>


class Circle {
    private:
        std::shared_ptr<Point> center;
        double radius;

    public:
        Circle(std::shared_ptr<Point> center, double radius) : center(center), radius(radius) {}
        std::shared_ptr<Point> getCenter() const { return center; }
        double getRadius() const { return radius; }
        void setCenter(std::shared_ptr<Point> center) { this->center = center; }
        void setRadius(double radius) { this->radius = radius; }
        double area() const { return M_PI * radius * radius; }
        double circumference() const { return 2 * M_PI * radius; }
        double diameter() const { return 2 * radius; }
        double perimeter() const { return circumference(); }


        /**
         * Checks if a given point is within the bounds of this Circle.
         * 
         * A point is considered to be within the bounds of the circle if its distance from the center of the circle is
         * less than or equal to the radius of the circle.
         * 
         * @param point The point to check.
         * @return True if the point is within the bounds of the circle, false otherwise.
         */
        bool contains(const Point& point) const {
            return center->distanceTo(point) <= radius;
        }

        /**
         * Determines if this Circle intersects with another Circle.
         * 
         * Two circles are considered to intersect if the distance between their 
         * centers is less than or equal to the sum of their radii.
         * 
         * @param other The other Circle to compare with.
         * @return True if the circles intersect, false otherwise.
         */
        bool is_intersecting(const Circle& other) const {
            return center->distanceTo(*other.center) <= radius + other.radius;
        }

        /**
         * Moves the center of this Circle by a given offset in the x and y directions.
         * 
         * @param dx The distance to move the center of this Circle along the x-axis.
         * @param dy The distance to move the center of this Circle along the y-axis.
         */
        void move (const double dx, const double dy) {
            this->center->move(dx, dy);
        }


        /**
         * Scales the radius of this Circle by a given factor.
         * 
         * This method multiplies the current radius of this Circle by the given factor.
         * 
         * @param factor The factor by which to scale the radius of this Circle.
         * A factor > 1 will increase the radius, while a factor < 1 will decrease the radius.
         */
        void scale (const double factor) {
            this->radius *= factor;
        }


        /**
         * Determines if this Circle is tangent to another Circle.
         * 
         * Two circles are tangent if the distance between their centers is 
         * equal to the sum of their radii.
         * 
         * @param other The other Circle to compare with.
         * @return True if the circles are tangent, false otherwise.
         */
        bool is_tangent(const Circle& other) const {
            return center->distanceTo(*other.center) == radius + other.radius;
        }


        /**
         * Determines if this Circle is disjoint with another Circle.
         * 
         * Two circles are disjoint if the distance between their centers is 
         * greater than the sum of their radii.
         * 
         * @param other The other Circle to compare with.
         * @return True if the circles are disjoint, false otherwise.
         */
        bool is_disjoint(const Circle& other) const {
            return center->distanceTo(*other.center) > radius + other.radius;
        }


        /**
         * Checks if this Circle is equal to another Circle.
         * 
         * Two Circles are considered equal if their centers are equal and their radii are equal.
         * 
         * @return True if the two Circles are equal, false otherwise.
         */
        bool is_equal(const Circle& other) const {
            return center->is_equal(*other.center) && radius == other.radius;
        }

        /**
         * Converts this Circle to a shared pointer of an SFML CircleShape.
         * This is useful for drawing Circles with SFML.
         * @param color The color of the shape.
         * @return A shared pointer to an SFML CircleShape.
         */
        std::shared_ptr<sf::CircleShape> to_circle_shape(const sf::Color& color) const {
            std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>(radius);
            std::shared_ptr<Point> bottom_left = std::make_shared<Point>(center->get_x() - radius, center->get_y() - radius);
            circle->setPosition(*bottom_left->to_vector2f());
            circle->setFillColor(color);
            return circle;
        }
};






#endif // CIRCLE_H