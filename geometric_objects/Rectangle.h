#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"

class Rectangle {
    private:
        std::shared_ptr<Point> upper_left;
        std::shared_ptr<Point> lower_right;
        std::shared_ptr<Point> upper_right;
        std::shared_ptr<Point> lower_left;

    public:
        /**
         * Constructs a Rectangle with specified upper-left and lower-right corners.
         * Initializes the other two corners (upper-right and lower-left) based on the given points.
         * 
         * @param upper_left A shared pointer to a Point representing the upper-left corner.
         * @param lower_right A shared pointer to a Point representing the lower-right corner.
         */
        Rectangle(std::shared_ptr<Point> upper_left, std::shared_ptr<Point> lower_right) : upper_left(upper_left), lower_right(lower_right) {
            upper_right = std::make_shared<Point>(lower_right->get_x(), upper_left->get_y());
            lower_left = std::make_shared<Point>(upper_left->get_x(), lower_right->get_y());
        }

        /**
         * Calculates the area of this Rectangle.
         * 
         * The area is calculated by multiplying the width (distance between the upper-left and upper-right points) by the height (distance between the upper-left and lower-left points).
         * 
         * @return The area of this Rectangle.
         */
        double area() const {
            return upper_left->distanceTo(*upper_right) * upper_left->distanceTo(*lower_left);
        }


        /**
         * Gets the upper left point of the rectangle.
         * @return The upper left point of the rectangle.
         */
        std::shared_ptr<Point> get_upper_left() const {
            return upper_left;
        }

        /**
         * Gets the lower right point of the rectangle.
         * @return The lower right point of the rectangle.
         */
        std::shared_ptr<Point> get_lower_right() const {
            return lower_right;
        }


        /**
         * Gets the upper right point of the rectangle.
         * @return The upper right point of the rectangle.
         */
        std::shared_ptr<Point> get_upper_right() const {
            return upper_right;
        }
        
        /**
         * Gets the lower left point of the rectangle.
         * @return The lower left point of the rectangle.
         */
        std::shared_ptr<Point> get_lower_left() const {
            return lower_left;
        }

        /**
         * Rotate the rectangle around a specified center by a specified angle.
         * This method updates the positions of all four corners of the rectangle.
         * @param center The point to rotate the rectangle around.
         * @param angle The angle in radians to rotate the rectangle.
         */
        void rotate_around(const Point& center, const double angle) {
            upper_left->rotate(center, angle);
            upper_right->rotate(center, angle);
            lower_right->rotate(center, angle);
            lower_left->rotate(center, angle);
        }


        /**
         * Rotates the rectangle around the origin by a specified angle.
         * @param angle The angle in radians to rotate the rectangle.
         */
        void rotate_origin(const double angle) {
            std::shared_ptr<Point> center = std::make_shared<Point>();
            this->rotate_around(*center, angle);
        }

        /** * Rotates the rectangle around its center by a specified angle.
         * @param angle The angle in radians to rotate the rectangle.
         */
        void rotate_center(const double angle) {
            std::shared_ptr<Point> center = upper_left->in_between(*lower_right);
            this->rotate_around(*center, angle);
        }

        /**
         * Scales the rectangle by a specified factor from its origin.
         * @param factor The factor by which to scale the rectangle.
         * A factor > 1 enlarges the rectangle, while a factor < 1 shrinks it.
         */
        void scale(const double factor) {
            upper_left->scale(factor);
            upper_right->scale(factor);
            lower_right->scale(factor);
            lower_left->scale(factor);
        }

        /**
         * Moves the rectangle by a specified offset in the x and y directions.
         * @param dx The distance to move the rectangle along the x-axis.
         * @param dy The distance to move the rectangle along the y-axis.
         */
        void move(const double dx, const double dy) {
            upper_left->move(dx, dy);
            upper_right->move(dx, dy);
            lower_right->move(dx, dy);
            lower_left->move(dx, dy);
        }

        /**
         * Prints the coordinates of the rectangle in the order: upper_left -> upper_right -> lower_right -> lower_left
         */
        void print() const {
            upper_left->print();
            std::cout << " -> ";
            upper_right->print();
            std::cout << " -> ";
            lower_right->print();
            std::cout << " -> ";
            lower_left->print();
            std::cout << std::endl;
        }



        /**
         * Checks if this rectangle is equal to another rectangle.
         * @param other The rectangle to compare with.
         * @return True if the two rectangles are equal, false otherwise.
         */
        bool is_equal(const Rectangle& other) const {
            return upper_left->is_equal(*other.upper_left) &&
                    upper_right->is_equal(*other.upper_right) &&
                    lower_right->is_equal(*other.lower_right) &&
                    lower_left->is_equal(*other.lower_left);
        }

        /**
         * Checks if a given point is within the bounds of this rectangle.
         * @param point The point to check.
         * @return True if the point is within the bounds of the rectangle, false otherwise.
         */
        bool contains(const Point& point) const {
            return (point.get_x() >= upper_left->get_x() && point.get_x() <= lower_right->get_x() &&
                    point.get_y() <= upper_left->get_y() && point.get_y() >= lower_right->get_y());


        }

        /**
         * Checks if a given point is within the bounds of this rectangle.
         * @param point The point to check.
         * @return True if the point is within the bounds of the rectangle, false otherwise.
         */
       bool between_bounds(const Point& point) const {
            return ((point.get_x() >= upper_left->get_x() && point.get_x() <= lower_right->get_x()) &&
                    (point.get_y() >= upper_left->get_y() && point.get_y() <= lower_right->get_y())) ||
                    ((point.get_x() >= lower_right->get_x() && point.get_x() <= upper_left->get_x()) &&
                    (point.get_y() >= lower_right->get_y() && point.get_y() <= upper_left->get_y()));
        }


        /**
         * Gets the center point of the rectangle.
         *
         * @return A shared pointer to the center point of the rectangle.
         */
        std::shared_ptr<Point> get_center() const {
            return upper_left->in_between(*lower_right);
        }

        /**
         * Converts the rectangle to an SFML ConvexShape, so that it can be drawn to an SFML window.
         *
         * @param color_fill The color to fill the rectangle with.
         * @param color_outline The color to use for the outline of the rectangle.
         * @param outline_thickness The thickness of the outline of the rectangle.
         * @return An SFML ConvexShape object representing the rectangle.
         */
        std::shared_ptr<sf::ConvexShape> to_vertex_array(const sf::Color& color_fill, const sf::Color& color_outline, const double outline_thickness) const {
            std::shared_ptr<sf::ConvexShape> rectangle = std::make_shared<sf::ConvexShape>(4);
            rectangle->setPoint(0, *this->get_upper_left()->to_vector2f());
            rectangle->setPoint(1, *this->get_upper_right()->to_vector2f());
            rectangle->setPoint(2, *this->get_lower_right()->to_vector2f());
            rectangle->setPoint(3, *this->get_lower_left()->to_vector2f());
            rectangle->setFillColor(color_fill);
            rectangle->setOutlineColor(color_outline);
            rectangle->setOutlineThickness(outline_thickness);
            return rectangle;
        }
};

#endif // RECTANGLE_H