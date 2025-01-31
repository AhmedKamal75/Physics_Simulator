#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include <memory.h>

/*
* A class representing a line in 2D space
* the line equation is y = mx + c
* m = (y2 - y1) / (x2 - x1)
* c = y1 - m * x1
* The line is defined by two points
* The line has a length, and can be moved, scaled, rotated, cloned, set and checked for equality
* A point can be checked if it is on the line
*/

class Line {
    private:
        std::shared_ptr<Point> start;
        std::shared_ptr<Point> end;
        double m;
        double c;


    public:
        /**
         * Creates a line from two points
         * @param start The start point of the line
         * @param end The end point of the line
         */
        Line(std::shared_ptr<Point> start, std::shared_ptr<Point> end) : start(start), end(end) {
            calculate_slope_intercept();
        }

        std::shared_ptr<Point> get_start() const {return start;}
        std::shared_ptr<Point> get_end() const {return end;}
        double get_slope() const {return m;}
        double get_intercept() const {return c;}
        
        /**
         * Sets the start point of this line to be equal to the specified start point.
         * 
         * After setting the start point, the slope (m) and intercept (c) of the line are recalculated.
         * @param start The new start point of this Line.
         */
        void set_start(std::shared_ptr<Point> start) {
            this->start = start;
            this->calculate_slope_intercept();
        }
        /**
         * Sets the end point of this line to be equal to the specified end point.
         * 
         * After setting the end point, the slope (m) and intercept (c) of the line are recalculated.
         * @param end The new end point of this Line.
         */
        void set_end(std::shared_ptr<Point> end) {
            this->end = end;
            this->calculate_slope_intercept();
        }

        /**
         * Calculates the length of this line.
         *
         * The length of a line is calculated as the Euclidean distance between its start and end points.
         * @return The length of this line.
         */
        double length() const {
            return start->distanceTo(*end);
        }

        /**
         * Prints the line to the console in the format (start.x, start.y) -> (end.x, end.y).
         */
        void print() const {
            start->print();
            std::cout << " -> ";
            end->print();
        }

        /**
         * Creates a clone of this Line object.
         * 
         * @return A shared pointer to a new Line object with the same start and end points.
         */
        std::shared_ptr<Line> clone() const {
            return std::make_shared<Line>(start->clone(), end->clone());
        }

        /**
         * Sets the start and end points of this line.
         * 
         * @param start The new start point for this line.
         * @param end The new end point for this line.
         */
        void set(const std::shared_ptr<Point> start, const std::shared_ptr<Point> end) {
            this->start = start;
            this->end = end;
        }

        /**
         * Sets the start and end points of this line to the same as another line.
         *
         * This method is a convenience method for setting the start and end points
         * of this line to the same as another line. It is equivalent to calling
         * set(other.start, other.end).
         *
         * @param other The other line whose start and end points are to be copied.
         */
        void set(const Line& other) {
            start = other.start;
            end = other.end;
        }

        /**
         * Moves the line by a given offset.
         * 
         * This method translates the line by the given offset, moving both the start and end points.
         * @param offset The offset by which to move the line.
         */
        void move(const std::shared_ptr<Point> offset) {
            start->add(*offset);
            end->add(*offset);
        }

        /**
         * Scales the line by a given factor.
         * 
         * This method scales both the start and end points of the line by the given factor.
         * @param factor The factor by which to scale the line.
         * A factor > 1 will increase the length of the line, while a factor < 1 will decrease the length.
         */
        void scale(const double factor) {
            start->scale(factor);
            end->scale(factor);
        }

        /**
         * Rotates the line around a specified center point by a specified angle.
         * 
         * This method updates the positions of the start and end points of the line
         * by rotating them around the given center point by the specified angle.
         * After rotation, the slope and intercept of the line are recalculated to
         * reflect the updated line orientation.
         *
         * @param center The point around which to rotate the line.
         * @param angle The angle in radians to rotate the line.
         */
        void rotate_around(const Point& center, const double angle) {
            start->rotate(center, angle);
            end->rotate(center, angle);
            calculate_slope_intercept();
        }

        /**
         * Rotates the line around the origin by a specified angle.
         * 
         * This is a convenience method for rotating the line around the origin.
         * It is equivalent to calling rotate_around(Point(0,0), angle).
         * After rotation, the slope and intercept of the line are recalculated to
         * reflect the updated line orientation.
         * @param angle The angle in radians to rotate the line.
         */
        void rotate_origin(const double angle) {
            std::shared_ptr<Point> center = std::make_shared<Point>();
            this->rotate_around(*center, angle);
        }

        /**
         * Rotates the line around its center point by a specified angle.
         * 
         * This method calculates the midpoint of the line as the center of rotation.
         * It then rotates the line around this center point by the specified angle.
         * After rotation, the slope and intercept of the line are recalculated to
         * reflect the updated line orientation.
         * @param angle The angle in radians to rotate the line.
         */
        void rotate_center(const double angle) {
            std::shared_ptr<Point> center = start->in_between(*end);
            this->rotate_around(*center, angle);

        }


        /**
         * Calculates and sets the slope (m) and intercept (c) of the line.
         *
         * The slope is calculated as the change in y divided by the change in x
         * between the start and end points of the line. If the change in x (dx) is zero,
         * the slope is set to 0, and the intercept is set to the x-coordinate of the start point.
         * This effectively treats the line as vertical.
         */
        void calculate_slope_intercept() {
            double dx = end->get_x() - start->get_x();
            if (dx == 0) {
                // m = std::numeric_limits<double>::infinity();
                // c = std::numeric_limits<double>::quiet_NaN();
                m = 0;
                c = start->get_x();
            } else {
                m = (end->get_y() - start->get_y()) / dx;
                c = start->get_y() - m * start->get_x();
            }
        }

        /**
         * Checks if a given point is on this line.
         * 
         * The point is considered to be on the line if the y-coordinate of the point
         * is equal to the y-coordinate calculated from the equation of the line
         * in the slope-intercept form (y = mx + c).
         * 
         * @param point The point to check.
         * @return True if the point is on the line, false otherwise.
         */
        bool on_line(const Point& point) const {
            return point.get_y() == m * point.get_x() + c;
        }

        /**
         * Checks if this line is parallel to another line.
         * 
         * Two lines are considered parallel if they have the same slope (m).
         * 
         * @param other The other line to check for parallelism with.
         * @return True if the two lines are parallel, false otherwise.
         */
        bool is_parallel(const Line& other) const {
            return this->m == other.m;
            
        }

        /**
         * Checks if this line is perpendicular to another line.
         * 
         * Two lines are considered perpendicular if the product of their slopes (m) is -1.
         * 
         * @param other The other line to check for perpendicularity with.
         * @return True if the two lines are perpendicular, false otherwise.
         */
        bool is_perpendicular(const Line& other) const {
            return this->m * other.m == -1;     
        }


        /**
         * Checks if this line is intersecting with another line.
         * 
         * Two lines are considered intersecting if they share a common point.
         * 
         * @param other The other line to check for intersection with.
         * @return True if the two lines intersect, false otherwise.
         */
        bool is_intersecting(const Line& other) const {
        }

        /**
         * Checks if a given point is within the bounds of this line.
         * 
         * The point is considered to be within the bounds of the line if its x-coordinate
         * is within the range of the x-coordinates of the start and end points of the line,
         * and its y-coordinate is within the range of the y-coordinates of the start and end points of the line.
         * 
         * @param point The point to check.
         * @return True if the point is within the bounds of the line, false otherwise.
         */
        bool between_bounds(const Point& point) const {
            return ((point.get_x() >= start->get_x() && point.get_x() <= end->get_x()) &&
                    (point.get_y() >= start->get_y() && point.get_y() <= end->get_y())) ||
                    ((point.get_x() >= end->get_x() && point.get_x() <= start->get_x()) &&
                    (point.get_y() >= end->get_y() && point.get_y() <= start->get_y()));
        }

        /**
         * Computes the intersection point between this line and another line.
         * 
         * @param other The other line to compute the intersection point with.
         * @return A shared pointer to a new Point that is the intersection of the two lines, or nullptr if the lines do not intersect.
         */
        std::shared_ptr<Point> intersection(const Line& other) const {
            if (!this->is_intersecting(other)) {
                return nullptr;
            }
            double x = (other.c - this->c) / (this->m - other.m);
            double y = this->m * x + this->c;
            return std::make_shared<Point>(x, y);
        }

        /**
         * Checks if this line is equal to another line.
         * 
         * A line is considered equal to another line if the two lines have the same start and end points.
         * 
         * @param other The other line to compare with.
         * @return True if the two lines are equal, false otherwise.
         */
        bool is_equal(const Line& other) const {
            return this->start->is_equal(*other.start) && 
                    this->end->is_equal(*other.end);
        }


        /**
         * Converts the line to an SFML VertexArray, so that it can be drawn to an SFML window.
         * 
         * @return An SFML VertexArray object representing the line.
         */
        std::shared_ptr<sf::VertexArray> to_vertex_array() const {
            std::shared_ptr<sf::VertexArray> line = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
            line->operator[](0).position = sf::Vector2f(static_cast<float>(start->get_x()), static_cast<float>(start->get_y()));
            line->operator[](1).position = sf::Vector2f(static_cast<float>(end->get_x()), static_cast<float>(end->get_y()));
            return line;
        }

};

#endif // LINE_H