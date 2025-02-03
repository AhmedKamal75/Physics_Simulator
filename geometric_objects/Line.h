#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Circle.h"
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

class Line : public std::enable_shared_from_this<Line> {
    private:
        std::shared_ptr<Point> start;
        std::shared_ptr<Point> end;
        double m;
        double c;
        double epsilon_error = 1e-20; // Small value to handle floating-point errors, infinitly close to 0.



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
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> set_start(std::shared_ptr<Point> start) {
            this->start = start;
            this->calculate_slope_intercept();
            return this->shared_from_this();
        }
        /**
         * Sets the end point of this line to be equal to the specified end point.
         * 
         * After setting the end point, the slope (m) and intercept (c) of the line are recalculated.
         * @param end The new end point of this Line.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> set_end(std::shared_ptr<Point> end) {
            this->end = end;
            this->calculate_slope_intercept();
            return this->shared_from_this();
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
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> set(const std::shared_ptr<Point> start, const std::shared_ptr<Point> end) {
            this->start = start;
            this->end = end;
            return this->shared_from_this();
        }

        /**
         * Sets the start and end points of this line to the same as another line.
         *
         * This method is a convenience method for setting the start and end points
         * of this line to the same as another line. It is equivalent to calling
         * set(other.start, other.end).
         *
         * @param other The other line whose start and end points are to be copied.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> set(const Line& other) {
            start = other.start;
            end = other.end;
            return this->shared_from_this();
        }

        /**
         * Moves the line by a given offset.
         * 
         * This method translates the line by the given offset, moving both the start and end points.
         * @param offset The offset by which to move the line.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> move(const Point& offset) {
            start->add(offset);
            end->add(offset);
            return shared_from_this();
        }

        /**
         * Scales the line by a given factor.
         * 
         * This method scales both the start and end points of the line by the given factor.
         * @param factor The factor by which to scale the line.
         * A factor > 1 will increase the length of the line, while a factor < 1 will decrease the length.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> scale(const double factor) {
            start->scale(factor);
            end->scale(factor);
            return shared_from_this();
        }


        /**
         * Extends the line by a given factor from its midpoint.
         * 
         * This method lengthens the line by the specified factor, keeping the midpoint unchanged,
         * and scaling equally in both directions along the line's direction.
         * 
         * @param factor The factor by which to extend the line. A factor > 1 will increase the 
         * length of the line, while a factor < 1 will decrease the length.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> extend(const double factor) {
            std::shared_ptr<Point> mid_point = start->in_between(*end);
            double current_length = start->distanceTo(*end);
            double new_length = current_length * factor;
            this->set(*std::make_shared<Circle>(mid_point, new_length / 2.0)->solve_with(*this));
            this->calculate_slope_intercept();
            return shared_from_this();
            // std::shared_ptr<Point> vector = start->clone()->subtract(*end->clone()); // normalized unit vector from start to end
            // this->start->set(*mid_point->subtract(*vector->clone()->scale(factor / 2.0)));
            // this->end->set(*mid_point->add(*vector->clone()->scale(factor / 2.0)));
            // return shared_from_this();
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
         * 
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> rotate_around(const Point& center, const double angle) {
            start->rotate(center, angle);
            end->rotate(center, angle);
            calculate_slope_intercept();
            return shared_from_this();
        }

        /**
         * Rotates the line around the origin by a specified angle.
         * 
         * This is a convenience method for rotating the line around the origin.
         * It is equivalent to calling rotate_around(Point(0,0), angle).
         * After rotation, the slope and intercept of the line are recalculated to
         * reflect the updated line orientation.
         * @param angle The angle in radians to rotate the line.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> rotate_origin(const double angle) {
            std::shared_ptr<Point> center = std::make_shared<Point>();
            return this->rotate_around(*center, angle);
        }

        /**
         * Rotates the line around its center point by a specified angle.
         * 
         * This method calculates the midpoint of the line as the center of rotation.
         * It then rotates the line around this center point by the specified angle.
         * After rotation, the slope and intercept of the line are recalculated to
         * reflect the updated line orientation.
         * @param angle The angle in radians to rotate the line.
         * @return A shared pointer to this Line object.
         */
        std::shared_ptr<Line> rotate_center(const double angle) {
            std::shared_ptr<Point> center = start->in_between(*end);
            return this->rotate_around(*center, angle);
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
         * the error epsilon_error is used to account for floating-point errors.
         * 
         * @param point The point to check.
         * @return True if the point is on the line, false otherwise.
         */
        bool on_line(const Point& point) const {
            return abs(m * point.get_x() + c - point.get_y()) < epsilon_error;
        }

        /**
         * Checks if this line is parallel to another line.
         * 
         * Two lines are considered parallel if they have the same slope (m).
         * this.m - epsilon_error <= other.m >= this.m + epsilon_error
         * 
         * @param other The other line to check for parallelism with.
         * @return True if the two lines are parallel, false otherwise.
         */
        bool is_parallel(const Line& other) const {
            return std::abs(this->m - other.m) < epsilon_error;
            // return this->m == other.m;
            
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
            return std::abs(this->m * other.m + 1) < epsilon_error;
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
            return !this->is_parallel(other);
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
         * Computes a line that is perpendicular to this line and passes through a given point.
         * 
         * The method first calculates the slope of the perpendicular line as -1 divided by the slope of this line.
         * It then calculates the intercept of the perpendicular line by subtracting the product of the slope and the x-coordinate of the point
         * from the y-coordinate of the point. The start point of the perpendicular line is set to the origin (0, 0), and the end point is set to the given point.
         * 
         * @param point The point that the perpendicular line should pass through.
         * @return A shared pointer to a new Line that is perpendicular to this line and passes through the given point.
         */
        std::shared_ptr<Line> get_perpendicular_line(const Point& point) const {
            if (this->m == 0) { // this line is horizontal, so the perpendicular line is vertical.
                return std::make_shared<Line>(point.clone(), 
                                              std::make_shared<Point>(point.get_x(), this->get_y_from_x(point.get_x())));
            }
            double new_m = -1 / this->m;
            double new_c = point.get_y() - new_m * point.get_x();
            std::shared_ptr<Point> new_start = point.clone();
            double new_x = (new_c - this->c) / (this->m - new_m);
            double new_y = new_m * new_x + new_c;
            std::shared_ptr<Point> new_end = std::make_shared<Point>(new_x, new_y);
            return std::make_shared<Line>(new_start, new_end);
        }

        /**
         * Evaluates the line equation at a given x-coordinate.
         * 
         * Given an x-coordinate, this method returns the corresponding y-coordinate
         * according to the line's equation in slope-intercept form (y = mx + c).
         * 
         * @param x The x-coordinate to evaluate at.
         * @return The y-coordinate at the given x-coordinate according to the line's equation.
         */
        double get_y_from_x(const double x) const {
            return this->m * x + this->c;
        }

        /**
        * Calculates the x-coordinate for a given y-coordinate based on the line's equation.
        * 
        * The function assumes the line is in slope-intercept form (y = mx + c).
        * If the slope (m) is zero, indicating a horizontal line, the function returns 0.0.
        * Otherwise, it calculates and returns the x-coordinate using the formula:
        * x = (y - c) / m, with a small epsilon added to handle floating-point precision.
        * 
        * @param y The y-coordinate for which to calculate the corresponding x-coordinate.
        * @return The calculated x-coordinate.
        */
        double get_x_from_y(const double y) const {
            if (this->m == 0) return 0.0;
            return (y - this->c) / (this->m + this->epsilon_error);
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