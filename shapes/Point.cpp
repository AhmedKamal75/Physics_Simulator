#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::get_x() const {return x;}
double Point::get_y() const {return y;}

void Point::set_x(double x) {this->x = x;}
void Point::set_y(double y) {this->y = y;}

double Point::distance_to(const std::shared_ptr<Point> other) const {
    return sqrt(pow(x - other->get_x(), 2) + pow(y - other->get_y(), 2));
}

std::shared_ptr<Point> Point::clone() const {
    return std::make_shared<Point>(x, y);
}

std::shared_ptr<Point> Point::set(const double x, const double y) {
    this->x = x;
    this->y = y;
    return shared_from_this();
}

std::shared_ptr<Point> Point::set(const std::shared_ptr<Point> other) {
    this->x = other->get_x();
    this->y = other->get_y();
    return shared_from_this();
}

std::shared_ptr<Point> Point::move(const double dx, const double dy) {
    this->x += dx;
    this->y += dy;
    return shared_from_this();
}

std::shared_ptr<Point> Point::add(const std::shared_ptr<Point> other) {
    this->x += other->get_x();
    this->y += other->get_y();
    return shared_from_this();
}

std::shared_ptr<Point> Point::subtract(const std::shared_ptr<Point> other) {
    this->x -= other->get_x();
    this->y -= other->get_y();
    return shared_from_this();
}

std::shared_ptr<Point> Point::multiply(const double factor){
    this->x *= factor;
    this->y *= factor;
    return shared_from_this();
}

std::shared_ptr<Point> Point::divide(const double factor) {
    this->x /= factor;
    this->y /= factor;
    return shared_from_this();
}

double Point::dot(const std::shared_ptr<Point> other) const {
    return this->x * other->get_x() + this->y * other->get_y();
}

double Point::magnitude() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}

double Point::angle() const {
    return atan2(y, x);
}

std::shared_ptr<Point> Point::reflect_over_x() const {
    return std::make_shared<Point>(x, -y);
}

std::shared_ptr<Point> Point::reflect_over_y() const {
    return std::make_shared<Point>(-x, y);
}

std::shared_ptr<Point> Point::reflect_over_origin() const {
    return std::make_shared<Point>(-x, -y);
}

std::shared_ptr<Point> Point::scale(const double factor) {
    this->x *= factor;
    this->y *= factor;
    return shared_from_this();
}

std::shared_ptr<Point> Point::normalize() {
    this->set(this->divide(this->magnitude()));
    return shared_from_this();
}

std::shared_ptr<Point> Point::rotate(const std::shared_ptr<Point> center, const double angle) {
    double translated_x = x - center->get_x();
    double translated_y = y - center->get_y();

    double new_x = translated_x * cos(angle) - translated_y * sin(angle);
    double new_y = translated_x * sin(angle) + translated_y * cos(angle);

    this->set(new_x + center->get_x(), new_y + center->get_y());

    return shared_from_this();
}

std::shared_ptr<Point> Point::rotate_origin(const double angle) {
    return this->rotate(std::make_shared<Point>(), angle);
}

std::shared_ptr<Point> Point::mid_point_to(const std::shared_ptr<Point> other) const {
    return std::make_shared<Point>((this->get_x() + other->get_x()) / 2.0, (this->get_y() + other->get_y()) / 2.0);
}

std::shared_ptr<sf::Vector2f> Point::to_vector2f() const {
    return std::make_shared<sf::Vector2f>(static_cast<float>(x), static_cast<float>(y));
}

std::shared_ptr<sf::CircleShape> Point::point_to_circle_shape(const sf::Color& color, const double radius) const {
    std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>(radius);
    circle->setPosition(*this->clone()->move(-radius, -radius)->to_vector2f());
    circle->setFillColor(color);
    return circle;
}

std::string Point::to_string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

bool Point::is_equal(const std::shared_ptr<Point> other) const {
    return abs(x - other->get_x()) < Shape::EPSILON_ERROR && abs(y - other->get_y()) < Shape::EPSILON_ERROR;
}

