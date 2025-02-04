#include "Triangle.h"

Triangle::Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3) : p1(p1), p2(p2), p3(p3) {}

std::shared_ptr<Point> Triangle::get_p1() const {
    return p1;
}

std::shared_ptr<Point> Triangle::get_p2() const {
    return p2;
}

std::shared_ptr<Point> Triangle::get_p3() const {
    return p3;
}

void Triangle::set_p1(std::shared_ptr<Point> p1) {
    this->p1 = p1;
}
void Triangle::set_p2(std::shared_ptr<Point> p2) {
    this->p2 = p2;
}

void Triangle::set_p3(std::shared_ptr<Point> p3) {
    this->p3 = p3;
}

double Triangle::calculate_perimeter() const {
    return p1->distance_to(p2) + p2->distance_to(p3) + p3->distance_to(p1);
}

double Triangle::calculate_area() const {
    return this->calculate_area(p1, p2, p3);
}

double Triangle::calculate_area(const std::shared_ptr<Point> a_, const std::shared_ptr<Point> b_, const std::shared_ptr<Point> c_) const {
    return abs(
        a_->get_x() * (b_->get_y() - c_->get_y()) +
        b_->get_x() * (c_->get_y() - a_->get_y()) +
        c_->get_x() * (a_->get_y() - b_->get_y())
    ) * 0.5;
}

std::vector<double> Triangle::angles() const {
    std::vector<double> angles{};
    angles.push_back(this->angles(p1, p2, p3));
    angles.push_back(this->angles(p2, p3, p1));
    angles.push_back(this->angles(p3, p1, p2));
    return angles;
}

double Triangle::angles(std::shared_ptr<Point> a_, std::shared_ptr<Point> b_, std::shared_ptr<Point> c_) const {
            double length_ab = a_->distance_to(b_);
            double length_bc = b_->distance_to(c_);
            double length_ac = a_->distance_to(c_);
            double cos_angle_a = (length_ab * length_ab + length_ac * length_ac - length_bc * length_bc) / 
                                 (2.0 * length_ab * length_ac + EPSILON_ERROR);

            if (cos_angle_a < -1.0) cos_angle_a = -1.0;
            if (cos_angle_a > 1.0) cos_angle_a = 1.0;

            return acos(cos_angle_a);
}

std::shared_ptr<Triangle> Triangle::clone() const {
    return std::make_shared<Triangle>(p1, p2, p3);
}

std::shared_ptr<Triangle> Triangle::move(const std::shared_ptr<Point> offset) {
    this->p1->add(offset);
    this->p2->add(offset);
    this->p3->add(offset);
    return shared_from_this();
}

std::shared_ptr<Triangle> Triangle::scale(const double factor) {
    this->p1->scale(factor);
    this->p2->scale(factor);
    this->p3->scale(factor);
    return shared_from_this();
}

std::shared_ptr<Triangle> Triangle::rotate(const std::shared_ptr<Point> center, const double angle) {
    this->p1->rotate(center, angle);
    this->p2->rotate(center, angle);
    this->p3->rotate(center, angle);
    return shared_from_this();
}

std::shared_ptr<Triangle> Triangle::rotate_origin(const double angle) {
    this->rotate(std::make_shared<Point>(0.0, 0.0), angle);
    return shared_from_this();
}

std::shared_ptr<Triangle> Triangle::rotate_center(const double angle) {
    this->rotate(this->centroid(), angle);
    return shared_from_this();
}

std::shared_ptr<Point> Triangle::center(std::shared_ptr<Point> a_, std::shared_ptr<Point> b_, std::shared_ptr<Point> c_) const {
    return std::make_shared<Point>((a_->get_x() + b_->get_x() + c_->get_x()) / 3.0, (a_->get_y() + b_->get_y() + c_->get_y()) / 3.0);
}

std::shared_ptr<Point> Triangle::centroid() const {
    return this->center(p1, p2, p3);
}

bool Triangle::is_equal(const std::shared_ptr<Triangle> other) const {
    return (this->p1->is_equal(other->get_p1())) && 
           (this->p2->is_equal(other->get_p2())) && 
           (this->p3->is_equal(other->get_p3()));
}

std::shared_ptr<sf::ConvexShape> Triangle::to_convex_shape(const sf::Color& color_fill, const sf::Color& color_outline, const double outline_thickness) const {
    std::shared_ptr<sf::ConvexShape> triangle = std::make_shared<sf::ConvexShape>(3);
    triangle->setPoint(0, *p1->to_vector2f());
    triangle->setPoint(1, *p2->to_vector2f());
    triangle->setPoint(2, *p3->to_vector2f());
    triangle->setFillColor(color_fill);
    triangle->setOutlineColor(color_outline);
    triangle->setOutlineThickness(outline_thickness);
    return triangle;
}

std::string Triangle::to_string() const {
    return "Triangle(" + p1->to_string() + ", " + p2->to_string() + ", " + p3->to_string() + ")";
}