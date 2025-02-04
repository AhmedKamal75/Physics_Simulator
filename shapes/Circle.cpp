#include "Circle.h"


Circle::Circle(std::shared_ptr<Point> center, double radius) : center(center), radius(radius) {
    this->velocity = std::make_shared<Point>();
    this->acceleration = std::make_shared<Point>();
    this->mass = 1.0;
}

std::shared_ptr<Point> Circle::getCenter() const {
    return center;
}

double Circle::getRadius() const {
    return radius;
}

std::shared_ptr<Circle> Circle::setCenter(std::shared_ptr<Point> center) {
    this->center = center;
    return shared_from_this();
}

std::shared_ptr<Circle> Circle::setCenterX(double x) {
    this->center->set_x(x);
    return shared_from_this();
}

std::shared_ptr<Circle> Circle::setCenterY(double y) {
    this->center->set_y(y);
    return shared_from_this();
}


std::shared_ptr<Circle> Circle::setRadius(double radius) {
    this->radius = radius;
    return shared_from_this();
}

std::shared_ptr<Point> Circle::getVelocity() const {
    return velocity;
}

std::shared_ptr<Point> Circle::getAcceleration() const {
    return acceleration;
}

double Circle::getMass() const{
    return mass;
}

std::shared_ptr<Circle> Circle::setVelocity(std::shared_ptr<Point> velocity) {
    this->velocity = velocity;
    return shared_from_this();
}

std::shared_ptr<Circle> Circle::setAcceleration(std::shared_ptr<Point> acceleration) {
    this->acceleration = acceleration;
    return shared_from_this();
}

std::shared_ptr<Circle> Circle::setVelocity(const double x, const double y) {
    this->velocity->set_x(x);
    this->velocity->set_y(y);
    return shared_from_this();
}

std::shared_ptr<Circle> Circle::setAcceleration(const double x, const double y) {
    this->acceleration->set_x(x);
    this->acceleration->set_y(y);
    return shared_from_this();
}

std::shared_ptr<Circle> Circle::setMass(double mass) {
    this->mass = mass;
    return shared_from_this();
}

void Circle::update_physics(const double delta_time){
    if (velocity != nullptr && acceleration != nullptr) {
        velocity->set_x(velocity->get_x() + acceleration->get_x() * delta_time);
        velocity->set_y(velocity->get_y() + acceleration->get_y() * delta_time);

        center->set_x(center->get_x() + velocity->get_x() * delta_time);
        center->set_y(center->get_y() + velocity->get_y() * delta_time);


        // velocity->add(acceleration->clone()->multiply(delta_time));
        // center->add(velocity->clone()->multiply(delta_time));
    }
}


double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::circumference() const {
    return 2 * M_PI * radius;
}

double Circle::diameter() const {
    return 2 * radius;
}

bool Circle::contains(const std::shared_ptr<Point> point) const {
    return center->distance_to(point) <= radius;
}

bool Circle::is_intersecting(const std::shared_ptr<Circle> other) const {
    return center->distance_to(other->getCenter()) <= radius + other->getRadius();
}

void Circle::move(const double dx, const double dy) {
    this->center->move(dx, dy);
}

void Circle::extend(const double factor) {
    this->radius *= factor;
}

std::shared_ptr<Line> Circle::solve_with(const std::shared_ptr<Line> line) const {
    double m = line->get_slope();
    double c = line->get_intercept();

    double a = this->center->get_x();
    double b = this->center->get_y();
    double r = radius;

    std::vector<double> roots = solve_quadratic(
        1 + m * m, 
        -2 * a + 2 * m * (c - b), 
        a * a + (c - b) * (c - b) - r * r
    );

    if (roots.size() == 1) {
        return std::make_shared<Line>(
            std::make_shared<Point>(roots[0], m * roots[0] + c),
            std::make_shared<Point>(roots[0], m * roots[0] + c)
        );
    } else if (roots.size() == 2) { 
        return std::make_shared<Line>( 
            std::make_shared<Point>(roots[0], m * roots[0] + c),
            std::make_shared<Point>(roots[1], m * roots[1] + c)
        );
    }
    return std::make_shared<Line>(std::make_shared<Point>(), std::make_shared<Point>()); // should never happen

}

bool Circle::is_tangent(const std::shared_ptr<Circle> other) const {
    return abs(this->center->distance_to(other->getCenter()) - this->radius + other->getRadius()) <= Shape::EPSILON_ERROR;
}

bool Circle::is_disjoint(const std::shared_ptr<Circle> other) const {
    return this->center->distance_to(other->getCenter()) > this->radius + other->getRadius();
}

bool Circle::is_equal(const std::shared_ptr<Circle> other) const {
    return this->center->is_equal(other->getCenter()) && this->radius == other->getRadius();
}

std::shared_ptr<sf::CircleShape> Circle::to_circle_shape(const sf::Color& color) const {
    std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>(radius);
    std::shared_ptr<Point> bottom_left = std::make_shared<Point>(center->get_x() - radius, center->get_y() - radius);
    circle->setPosition(*bottom_left->to_vector2f());
    circle->setFillColor(color);
    return circle;
}

std::string Circle::to_string() const {
    return "Circle[" + this->center->to_string() + ", " + std::to_string(this->radius) + "]";
}

std::shared_ptr<Circle> Circle::clone() const {
    return std::make_shared<Circle>(this->center, this->radius);
}
