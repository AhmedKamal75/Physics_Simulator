#include "Line.h"

Line::Line(std::shared_ptr<Point> start, std::shared_ptr<Point> end) : start(start), end(end) {
    calculate_slope_intercept();
}

std::shared_ptr<Point> Line::get_start() const {
    return this->start;
}
std::shared_ptr<Point> Line::get_end() const {
    return this->end;
}

double Line::get_slope() const {
    return this->m;
}

double Line::get_intercept() const{
    return this->c;
}

std::shared_ptr<Line> Line::set_start(std::shared_ptr<Point> start){
    this->start = start;
    calculate_slope_intercept();
    return shared_from_this();
}

std::shared_ptr<Line> Line::set_end(std::shared_ptr<Point> end){
    this->end = end;
    calculate_slope_intercept();
    return shared_from_this();
}

double Line::length() const{
    return this->start->distance_to(this->end);
}

std::string Line::to_string() const{
    return "Line (y = " + std::to_string(this->get_slope()) + " * x + " + std::to_string(this->get_intercept()) + "): " + this->start->to_string() + " -> " + this->end->to_string();
}

std::shared_ptr<Line> Line::clone() const{
    return std::make_shared<Line>(this->start->clone(), this->end->clone());
}

std::shared_ptr<Line> Line::set(const std::shared_ptr<Point> start, const std::shared_ptr<Point> end){
    this->start = start;
    this->end = end;
    calculate_slope_intercept();
    return shared_from_this();
}

std::shared_ptr<Line> Line::set(const std::shared_ptr<Line> other){
    this->start = other->get_start();
    this->end = other->get_end();
    calculate_slope_intercept();
    return shared_from_this();
}

std::shared_ptr<Line> Line::move(const std::shared_ptr<Point> offset){
    this->start->move(offset->get_x(), offset->get_y());
    this->end->move(offset->get_x(), offset->get_y());
    calculate_slope_intercept();
    return shared_from_this();
}

std::shared_ptr<Line> Line::scale(const double factor){
    this->start->scale(factor);
    this->end->scale(factor);
    calculate_slope_intercept();
    return shared_from_this();
}

std::shared_ptr<Line> Line::extend(const double factor) {
    // Compute the midpoint M of the current line.
    auto mid = this->start->mid_point_to(this->end);

    // Compute the new endpoints by scaling the vector from M to each endpoint.
    double new_start_x = mid->get_x() + factor * (this->start->get_x() - mid->get_x());
    double new_start_y = mid->get_y() + factor * (this->start->get_y() - mid->get_y());
    double new_end_x   = mid->get_x() + factor * (this->end->get_x() - mid->get_x());
    double new_end_y   = mid->get_y() + factor * (this->end->get_y() - mid->get_y());

    this->start->set(new_start_x, new_start_y);
    this->end->set(new_end_x, new_end_y);
    calculate_slope_intercept();

    return shared_from_this();
}

std::shared_ptr<Line> Line::rotate_around(const std::shared_ptr<Point> center, const double angle){
    this->start->rotate(center, angle);
    this->end->rotate(center, angle);
    calculate_slope_intercept();
    return shared_from_this();
}

std::shared_ptr<Line> Line::rotate_origin(const double angle){
    return this->rotate_around(std::make_shared<Point>(), angle);
}

std::shared_ptr<Line> Line::rotate_center(const double angle){
    return this->rotate_around(this->start->mid_point_to(this->end), angle);
}

void Line::calculate_slope_intercept(){
    double dx = this->end->get_x() - this->start->get_x();
    if (dx == 0){
        this->m = 1.0 / EPSILON_ERROR;
        this->c = 0;
    } else {
        this->m = (this->end->get_y() - this->start->get_y()) / dx;
        this->c = this->start->get_y() - this->m * this->start->get_x();
    }
}

bool Line::on_extended_line(const std::shared_ptr<Point> point) const{
    double dx = end->get_x() - start->get_x();
    double dy = end->get_y() - start->get_y();

    if (std::abs(dx) < EPSILON_ERROR) {
        return std::abs(point->get_x() - start->get_x()) < EPSILON_ERROR;
    } else if (std::abs(dy) <= EPSILON_ERROR) {
        return std::abs(point->get_y() - start->get_y()) < EPSILON_ERROR;
    } else {
        return std::abs(this->m * point->get_x() + this->c - point->get_y()) < EPSILON_ERROR;
    }
}

bool Line::is_parallel(const std::shared_ptr<Line> other) const {
    // Handle vertical lines: Two vertical lines are parallel.
    bool thisIsVertical = std::abs(this->m) > 1.0 / Shape::EPSILON_ERROR;
    bool otherIsVertical = std::abs(other->get_slope()) > 1.0 / Shape::EPSILON_ERROR;

    if (thisIsVertical && otherIsVertical) return true;
    if (thisIsVertical || otherIsVertical) return false; // One vertical, one not, then not parallel


    return std::abs(this->m - other->get_slope()) < Shape::EPSILON_ERROR; 
}


bool Line::is_perpendicular(const std::shared_ptr<Line> other) const {
    bool thisHorizontal = std::abs(this->get_slope()) < EPSILON_ERROR;
    bool otherHorizontal = std::abs(other->get_slope()) < EPSILON_ERROR;
    bool thisVertical = std::abs(this->get_slope()) > 1.0/EPSILON_ERROR;
    bool otherVertical = std::abs(other->get_slope()) > 1.0/EPSILON_ERROR;

    // A horizontal line is perpendicular to a vertical line.
    if ((thisHorizontal && otherVertical) || (thisVertical && otherHorizontal))
        return true;
    // For non-special cases, check if the product of slopes is approximately -1.
    if (!thisVertical && !otherVertical && !thisHorizontal && !otherHorizontal)
        return std::abs(this->get_slope() * other->get_slope() + 1) < EPSILON_ERROR;
    
    return false;
}


bool Line::is_intersecting(const std::shared_ptr<Line> other) const{
    return !this->is_parallel(other);
}

bool Line::between_bounds(const std::shared_ptr<Point> point) const {
    double min_x = std::min(this->start->get_x(), this->end->get_x());
    double max_x = std::max(this->start->get_x(), this->end->get_x());
    double min_y = std::min(this->start->get_y(), this->end->get_y());
    double max_y = std::max(this->start->get_y(), this->end->get_y());
    
    return (point->get_x() >= min_x && point->get_x() <= max_x &&
            point->get_y() >= min_y && point->get_y() <= max_y);
}


std::shared_ptr<Point> Line::intersection(const std::shared_ptr<Line> other) const {
    if (std::abs(this->get_slope() - other->get_slope()) < EPSILON_ERROR) {
        throw std::runtime_error("Lines are parallel or coincident; no unique intersection exists");
    }
    double intersection_x = (other->get_intercept() - this->get_intercept()) / (this->get_slope() - other->get_slope());
    double intersection_y = this->get_slope() * intersection_x + this->get_intercept();
    return std::make_shared<Point>(intersection_x, intersection_y);
}



std::shared_ptr<Line> Line::get_perpendicular_line(const std::shared_ptr<Point> point) const {
    // Retrieve the slope of the current line.
    double slope = this->get_slope();    

    // Case 1: The current line is (nearly) horizontal.
    // A horizontal line (slope ≈ 0) has a perpendicular that is vertical.
    // A vertical line is defined by a constant x coordinate.
    if (std::abs(slope) < EPSILON_ERROR) {
        // Create a vertical line through 'point'. 
        // We choose an arbitrary offset in y (here, +1) to define the second point.
        return std::make_shared<Line>(
            point,
            std::make_shared<Point>(point->get_x(), point->get_y() + 1)
        );
    }
    
    // Case 2: The current line is (nearly) vertical.
    // A vertical line (undefined or infinite slope) has a perpendicular that is horizontal.
    // A horizontal line is defined by a constant y coordinate.
    if (std::abs(slope) >= (1.0 - EPSILON_ERROR) / EPSILON_ERROR) {
        // Create a horizontal line through 'point'.
        // We choose an arbitrary offset in x (here, +1) to define the second point.
        return std::make_shared<Line>(
            point,
            std::make_shared<Point>(point->get_x() + 1, point->get_y())
        );
    }
    
    // Case 3: General case.
    // The slope of the perpendicular line is given by -1 / slope.
    double perpendicular_slope = -1.0 / slope;
    double perpendicular_intercept = point->get_y() - perpendicular_slope * point->get_x();
    
    // To construct the line, we need a second point. 
    // We choose the intersection point.
    double newX = (perpendicular_intercept - this->get_intercept()) / (this->get_slope() - perpendicular_slope);
    double newY = perpendicular_slope * newX + perpendicular_intercept;
    
    return std::make_shared<Line>(
        point,
        std::make_shared<Point>(newX, newY)
    );
}





double Line::evaluate_y(const double x) const{
    if (abs(this->get_slope()) <= EPSILON_ERROR) {
        return this->start->get_y();
    } else if (abs(abs(this->get_slope()) - ((1-EPSILON_ERROR) / EPSILON_ERROR)) >= EPSILON_ERROR) {
        return this->start->get_x();
    }
    return this->get_slope() * x + this->get_intercept();
}

double Line::evaluate_x(const double y) const {
    // For a horizontal line, evaluating x for an arbitrary y is undefined.
    if (std::abs(this->end->get_y() - this->start->get_y()) < EPSILON_ERROR) {
        throw std::runtime_error("Cannot evaluate x for a horizontal line");
    }
    return (y - this->get_intercept()) / this->get_slope();
}

bool Line::is_equal(const std::shared_ptr<Line> other) const{
    return abs(this->get_slope() - other->get_slope()) < EPSILON_ERROR &&
           abs(this->get_intercept() - other->get_intercept()) < EPSILON_ERROR;
}

std::shared_ptr<sf::VertexArray> Line::to_vertex_array() const{
    std::shared_ptr<sf::VertexArray> line = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
    line->operator[](0).position = *this->start->to_vector2f();
    line->operator[](1).position = *this->end->to_vector2f();
    return line;

}
