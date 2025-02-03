#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Utilities.h"


class Point : public std::enable_shared_from_this<Point> {
    private:
        double x;
        double y;
        double epsilon_error = 1e-20; // Small value to handle floating-point errors, infinitely close to 0.

    public:
        Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

        double get_x() const {return x;}
        double get_y() const {return y;}

        void set_x(double x) {this->x = x;}
        void set_y(double y) {this->y = y;}


        /**
         * Calculates the Euclidean distance from this Point to another Point.
         *
         * @param other The other Point to which the distance is calculated.
         * @return The distance between this Point and the specified Point.
         */
        double distanceTo(const Point& other) const {
            double dx = x - other.x;
            double dy = y - other.y;
            return std::sqrt(dx*dx + dy*dy);
        }


        /**
         * Prints the Point to the console in the format (x, y).
         */
        void print() const {
            std::cout << "(" << x << ", " << y << ")";
        }

        /**
         * Clones this Point and returns a shared pointer to the clone.
         * 
         * @return A shared pointer to a clone of this Point.
         */
        std::shared_ptr<Point> clone() const {
            return std::make_shared<Point>(x, y);
        }

        /**
         * Sets the coordinates of this Point to the specified x and y values.
         *
         * @param x The new x-coordinate for this Point.
         * @param y The new y-coordinate for this Point.
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> set(const double x, const double y) {
            this->x = x;
            this->y = y;
            return shared_from_this();
        }

        /**
         * Sets the coordinates of this Point to be equal to the coordinates of another Point.
         *
         * @param other The Point whose coordinates are to be copied.
         * 
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> set(const Point& other) {
            x = other.x;
            y = other.y;
            return shared_from_this();
        }


        /**
         * Moves the point by the specified offset in the x and y directions.
         *
         * @param dx The distance to move the point along the x-axis.
         * @param dy The distance to move the point along the y-axis.
         * 
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> move(const double dx, const double dy) {
            x += dx;
            y += dy;
            return shared_from_this();
        }

        /**
         * Adds the given Point to this Point.
         * This is equivalent to adding the x-coordinates and adding the y-coordinates.
         *
         * @param other The Point to add to this Point.
         * 
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> add(const Point& other) {
            x += other.x;
            y += other.y;
            return shared_from_this();
        }

        /**
         * Subtracts the given Point from this Point.
         * This is equivalent to adding the negative of the given point to this point.
         * 
         * @param other The Point to subtract from this Point.
         * 
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> subtract(const Point& other) {
            x -= other.x;
            y -= other.y;
            return shared_from_this();
        }

        double dot(const Point& other) const {
            return x * other.x + y * other.y;
        }
        
        /**
         * Scales the point by a given factor.
         * This is useful for multiplying a point by a scalar, or scaling a point to a given size.
         * @param factor The factor to scale the point by.
         * 
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> scale(const double factor) {
            x *= factor;
            y *= factor;
            return shared_from_this();
        }

        /**
         * Normalizes this Point, so that it has magnitude 1.
         * This is useful for getting a unit vector in the direction of the point.
         * @return A shared pointer to this Point.
         */
        std::shared_ptr<Point> normalize() {
            double magnitude = std::sqrt(x*x + y*y);
            
            // Handle the case where the magnitude is 0
            if (magnitude == 0) return shared_from_this();
            
            // Normalize the point
            x /= magnitude;
            y /= magnitude;
            return shared_from_this();
        }

        /**
         * Rotates this Point around the origin by a given angle.
         * The rotation is performed in the 2D plane using the standard rotation matrix.
         *
         * @param angle The angle in radians by which to rotate the point.
         * 
         * @return A shared pointer to this Point after rotation.
         */
        std::shared_ptr<Point> rotate(const double angle) { 
            double new_x = x * std::cos(angle) - y * std::sin(angle);
            double new_y = x * std::sin(angle) + y * std::cos(angle);
            x = new_x;
            y = new_y;
            return shared_from_this();
        }


        /**
         * Rotates this Point around the given center point by a given angle.
         * The rotation is performed in the 2D plane using the standard rotation matrix.
         *
         * @param center The point around which to rotate the point.
         * @param angle The angle in radians by which to rotate the point.
         * 
         * @return A shared pointer to this Point after rotation.
         */
        std::shared_ptr<Point> rotate(const Point& center, const double angle) { // angle in radians
            // Translate point to origin
            double translated_x = x - center.get_x() + this->epsilon_error;
            double translated_y = y - center.get_y() + this->epsilon_error;

            // Apply rotation
            double new_x = translated_x * std::cos(angle) - translated_y * std::sin(angle);
            double new_y = translated_x * std::sin(angle) + translated_y * std::cos(angle);

            // Translate back to the original position
            x = new_x + center.get_x();
            y = new_y + center.get_y();

            return shared_from_this();
        }

        /**
         * Computes the midpoint between this Point and another Point.
         * @param other The reference to the other Point to compute the midpoint with.
         * @return A shared pointer to a new Point that is the midpoint of the two points.
         */
        std::shared_ptr<Point> in_between(const Point& other) const {
            return std::make_shared<Point>((x + other.x) / 2, (y + other.y) / 2);
        }


        /**
         * Checks if this Point is equal to another Point.
         * @param other The reference to the other Point to compare with.
         * @return True if the two points are equal, false otherwise.
         */
        bool is_equal(const Point& other) const {
            return (this->x - other.x < epsilon_error) && (this->y - other.y < epsilon_error);
        }

        /**
         * Converts this Point to a shared pointer of an SFML Vector2f.
         * This is useful for passing Points to SFML functions.
         *
         * @return A shared pointer to an SFML Vector2f.
         */
        std::shared_ptr<sf::Vector2f> to_vector2f() const {
            return std::make_shared<sf::Vector2f>(static_cast<float>(x), static_cast<float>(y));
        }

        /**
         * Converts this Point to a shared pointer of an SFML CircleShape.
         * The CircleShape is positioned at the coordinates of this Point and
         * has a radius of 5.0f by default. The fill color of the circle is red.
         * This is useful for drawing the Point as a small red circle.
         * @param radius The radius of the CircleShape to create. Defaults to 5.0f.
         * @return A shared pointer to an SFML CircleShape.
         */
        std::shared_ptr<sf::CircleShape> point_to_circle_shape(const sf::Color& color, const double radius = 5.0f) const {
            std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>(radius);
            circle->setPosition(*this->to_vector2f());
            circle->setFillColor(color);
            return circle;
        }
};


#endif // POINT_H