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

std::string Line::print() const{
    return "Line (y = " + std::to_string(this->get_slope()) + " * x + " + std::to_string(this->get_intercept()) + "): " + this->start->print() + " -> " + this->end->print();
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


// TODO: implement this in the future after implementing Circle
std::shared_ptr<Line> Line::extend(const double factor){
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

        if (abs(this->m) <= EPSILON_ERROR) this->m = 0;
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
    // Handle vertical lines: A vertical line is perpendicular to a horizontal line.
    bool thisIsVertical = std::abs(std::abs(this->m) - ((1-EPSILON_ERROR) / (EPSILON_ERROR)) >= EPSILON_ERROR);
    bool otherIsVertical = std::abs(std::abs(other->get_slope()) - (1.0 / EPSILON_ERROR) >= EPSILON_ERROR);
    bool thisIsHorizontal = std::abs(this->m) <= Shape::EPSILON_ERROR;
    bool otherIsHorizontal = std::abs(other->get_slope()) <= Shape::EPSILON_ERROR;

    if (thisIsVertical && otherIsHorizontal) return true;
    if (thisIsHorizontal && otherIsVertical) return true;
    if (thisIsVertical || otherIsVertical) return false; // One vertical, one not, then not perpendicular

    return std::abs(this->m * other->get_slope() + 1) <= Shape::EPSILON_ERROR;
}

bool Line::is_intersecting(const std::shared_ptr<Line> other) const{
    return !this->is_parallel(other);
}

bool Line::between_bounds(const std::shared_ptr<Point> point) const{
    return ((point->get_x() >= this->start->get_x() && point->get_x() <= this->end->get_x()) && 
            (point->get_y() >= this->start->get_y() && point->get_y() <= this->end->get_y()) ||
            ((point->get_x() >= this->end->get_x() && point->get_x() <= this->start->get_x()) &&
             (point->get_y() >= this->end->get_y() && point->get_y() <= this->start->get_y())));
}

std::shared_ptr<Point> Line::intersection(const std::shared_ptr<Line> other) const{
    if (!this->is_intersecting(other)){
        throw std::runtime_error("Lines do not intersect");
        return this->start; 
    }
    double intersection_x = (other->get_intercept() - this->get_intercept()) / (this->get_slope() - other->get_slope() + EPSILON_ERROR);
    double intersection_y = this->get_slope() * intersection_x + this->get_intercept();
    return std::make_shared<Point>(intersection_x, intersection_y);
}

// std::shared_ptr<Line> Line::get_perpendicular_line(const std::shared_ptr<Point> point) const{
//     if (abs(this->get_slope()) <= EPSILON_ERROR) {
//         return std::make_shared<Line>(point->clone(), 
//                std::make_shared<Point>(point->get_x(), this->evaluate_y(point->get_x())));
//     } 
//     double new_m = -1.0 / this->get_slope();
//     double new_c = point->get_y() - new_m * point->get_x();
//     std::shared_ptr<Point> new_start = point->clone();
//     double new_x = (new_c - this->get_intercept()) / (this->get_slope() - new_m + EPSILON_ERROR);
//     double new_y = new_m * new_x + new_c;
//     std::shared_ptr<Point> new_end = std::make_shared<Point>(new_x, new_y);
//     return std::make_shared<Line>(new_start, new_end);
// }

std::shared_ptr<Line> Line::get_perpendicular_line(const std::shared_ptr<Point> point) const {
    // Handle horizontal line case correctly.
    if (std::abs(this->get_slope()) < Shape::EPSILON_ERROR) {
        return std::make_shared<Line>(point, std::make_shared<Point>(point->get_x() + 1, point->get_y())); // Vertical line
    } else if (std::abs(this->get_slope()) > 1.0 / Shape::EPSILON_ERROR){ //Handle vertical line
        return std::make_shared<Line>(point, std::make_shared<Point>(point->get_x(), point->get_y()+1)); // Horizontal line
    }

    double new_m = -1.0 / this->get_slope();
    double new_c = point->get_y() - new_m * point->get_x();
    std::shared_ptr<Point> new_start = point; // No need to clone here; it's already a shared pointer.
    std::shared_ptr<Point> new_end = std::make_shared<Point>(point->get_x() + 1, new_m * (point->get_x() + 1) + new_c);
    return std::make_shared<Line>(new_start, new_end);
}


double Line::evaluate_y(const double x) const{
    if (abs(this->get_slope()) <= EPSILON_ERROR) {
        return this->start->get_y();
    } else if (abs(abs(this->get_slope()) - ((1-EPSILON_ERROR) / EPSILON_ERROR)) >= EPSILON_ERROR) {
        return this->start->get_x();
    }
    return this->get_slope() * x + this->get_intercept();
}

double Line::evaluate_x(const double y) const{
    if (abs(this->get_slope()) < EPSILON_ERROR) return 0.0;
    return (y - this->get_intercept()) / (this->get_slope());
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
