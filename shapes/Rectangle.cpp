#include "Rectangle.h"


Rectangle::Rectangle(std::shared_ptr<Point> upper_left, std::shared_ptr<Point> lower_right) : upper_left(upper_left), lower_right(lower_right) {
    this->lower_left = std::make_shared<Point>(upper_left->get_x(), lower_right->get_y());
    this->upper_right = std::make_shared<Point>(lower_right->get_x(),upper_left->get_y());
}

Rectangle::Rectangle(std::shared_ptr<Point> upper_left, std::shared_ptr<Point> upper_right, std::shared_ptr<Point> lower_right, std::shared_ptr<Point> lower_left) : upper_left(upper_left), upper_right(upper_right), lower_right(lower_right), lower_left(lower_left) {}

Rectangle::Rectangle(const std::shared_ptr<Rectangle> other) {
    this->upper_left = other->get_upper_left();
    this->upper_right = other->get_upper_right();
    this->lower_right = other->get_lower_right();
    this->lower_left = other->get_lower_left();
}


std::shared_ptr<Point> Rectangle::get_upper_left() const {
    return upper_left;
}

std::shared_ptr<Point> Rectangle::get_lower_right() const {
    return lower_right;
}

std::shared_ptr<Point> Rectangle::get_upper_right() const {
    return upper_right;
}

std::shared_ptr<Point> Rectangle::get_lower_left() const {
    return lower_left;
}

double Rectangle::area() const {
    return upper_left->distance_to(upper_right) * upper_left->distance_to(lower_left);
}

double Rectangle::perimeter() const {
    return 2.0 * (upper_left->distance_to(upper_right) + upper_left->distance_to(lower_left));
}

std::shared_ptr<Rectangle> Rectangle::clone() const {
    return std::make_shared<Rectangle>(upper_left, lower_right);
}

std::shared_ptr<Rectangle> Rectangle::move(const std::shared_ptr<Point> offset) {
    this->upper_left->add(offset);
    this->lower_right->add(offset);
    this->upper_right->add(offset);
    this->lower_left->add(offset);
    return shared_from_this();
}

std::shared_ptr<Rectangle> Rectangle::scale(const double factor) {
    this->upper_left->scale(factor);
    this->lower_right->scale(factor);
    this->upper_right->scale(factor);
    this->lower_left->scale(factor);
    return shared_from_this();
}

std::shared_ptr<Rectangle> Rectangle::extend(const double factor) {
    // Compute the centroid of the rectangle.
    double cx = (upper_left->get_x() + upper_right->get_x() +
                 lower_left->get_x() + lower_right->get_x()) / 4.0;
    double cy = (upper_left->get_y() + upper_right->get_y() +
                 lower_left->get_y() + lower_right->get_y()) / 4.0;
    auto centroid = std::make_shared<Point>(cx, cy);

    // Compute new positions for each vertex.
    auto new_upper_left = std::make_shared<Point>(
        cx + factor * (upper_left->get_x() - cx),
        cy + factor * (upper_left->get_y() - cy)
    );
    auto new_upper_right = std::make_shared<Point>(
        cx + factor * (upper_right->get_x() - cx),
        cy + factor * (upper_right->get_y() - cy)
    );
    auto new_lower_left = std::make_shared<Point>(
        cx + factor * (lower_left->get_x() - cx),
        cy + factor * (lower_left->get_y() - cy)
    );
    auto new_lower_right = std::make_shared<Point>(
        cx + factor * (lower_right->get_x() - cx),
        cy + factor * (lower_right->get_y() - cy)
    );

    // Optionally, if you want to ensure the points are ordered consistently,
    // you can sort the four new points by their angle with respect to the centroid.
    // For example:
    
    std::vector<std::shared_ptr<Point>> vertices = { new_upper_left, new_upper_right, new_lower_right, new_lower_left };
    std::sort(vertices.begin(), vertices.end(), [&](const std::shared_ptr<Point>& a, const std::shared_ptr<Point>& b) {
        return std::atan2(a->get_y() - cy, a->get_x() - cx) < std::atan2(b->get_y() - cy, b->get_x() - cx);
    });
    // Then assign back in order:
    this->upper_left->set(vertices[0]);
    this->upper_right->set(vertices[1]);
    this->lower_right->set(vertices[2]);
    this->lower_left->set(vertices[3]);
    return shared_from_this();
}

std::shared_ptr<Rectangle> Rectangle::rotate(const std::shared_ptr<Point> center, const double angle) {
    this->upper_left->rotate(center, angle);
    return shared_from_this();
}

std::shared_ptr<Rectangle> Rectangle::rotate_origin(const double angle) {
    this->rotate(std::make_shared<Point>(), angle);
    return shared_from_this();
}

std::shared_ptr<Rectangle> Rectangle::rotate_center(const double angle) {
    this->rotate(this->centroid(), angle);
    return shared_from_this();
}

#include <vector>
#include <algorithm>
#include <cmath>

bool Rectangle::is_equal(const std::shared_ptr<Rectangle> other) const {
    // Gather vertices for both rectangles.
    std::vector<std::shared_ptr<Point>> vertices1 = {upper_left, upper_right, lower_right, lower_left};
    std::vector<std::shared_ptr<Point>> vertices2 = {other->get_upper_left(), other->get_upper_right(),
                                                     other->get_lower_right(), other->get_lower_left()};

    // Compute the centroids for both rectangles.
    auto centroid1 = this->centroid();
    auto centroid2 = other->centroid();

    // Lambda to compute angle relative to centroid.
    auto angleFromCentroid = [](const std::shared_ptr<Point>& pt, const std::shared_ptr<Point>& centroid) -> double {
        return std::atan2(pt->get_y() - centroid->get_y(), pt->get_x() - centroid->get_x());
    };

    // Sort the vertices by angle from the centroid.
    std::sort(vertices1.begin(), vertices1.end(),
              [&](const std::shared_ptr<Point>& a, const std::shared_ptr<Point>& b) {
                  return angleFromCentroid(a, centroid1) < angleFromCentroid(b, centroid1);
              });
    std::sort(vertices2.begin(), vertices2.end(),
              [&](const std::shared_ptr<Point>& a, const std::shared_ptr<Point>& b) {
                  return angleFromCentroid(a, centroid2) < angleFromCentroid(b, centroid2);
              });

    // Compare corresponding vertices.
    for (int i = 0; i < 4; i++) {
        if (!vertices1[i]->is_equal(vertices2[i])) { 
            return false;
        }
    }
    return true;
}


bool Rectangle::contains(const std::shared_ptr<Point> point) const {
    // Helper lambda to compute the signed cross product (isLeft test)
    auto cross = [](const std::shared_ptr<Point>& a,
                    const std::shared_ptr<Point>& b,
                    const std::shared_ptr<Point>& c) -> double {
        return (b->get_x() - a->get_x()) * (c->get_y() - a->get_y()) -
               (b->get_y() - a->get_y()) * (c->get_x() - a->get_x());
    };

    // Using the four vertices in order
    double d1 = cross(upper_left, upper_right, point);
    double d2 = cross(upper_right, lower_right, point);
    double d3 = cross(lower_right, lower_left, point);
    double d4 = cross(lower_left, upper_left, point);

    // If the signs of all cross products are either non-negative or non-positive,
    // the point is inside or on the edge.
    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0) || (d4 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0) || (d4 > 0);

    return !(hasNeg && hasPos);
}

bool Rectangle::between_bounds(const std::shared_ptr<Point> point) const {
    // Determine the axis-aligned bounding box of the rectangle
    double min_x = std::min({upper_left->get_x(), upper_right->get_x(), lower_left->get_x(), lower_right->get_x()});
    double max_x = std::max({upper_left->get_x(), upper_right->get_x(), lower_left->get_x(), lower_right->get_x()});
    double min_y = std::min({upper_left->get_y(), upper_right->get_y(), lower_left->get_y(), lower_right->get_y()});
    double max_y = std::max({upper_left->get_y(), upper_right->get_y(), lower_left->get_y(), lower_right->get_y()});

    return (point->get_x() >= min_x && point->get_x() <= max_x &&
            point->get_y() >= min_y && point->get_y() <= max_y);
}

std::string Rectangle::to_string() const {
    return "Rectangle[" + upper_left->to_string() + ", " + upper_right->to_string() + ", " + lower_right->to_string() + ", " + lower_left->to_string() + "]";
}

std::shared_ptr<Point> Rectangle::centroid() const {
    return this->upper_left->mid_point_to(this->lower_right);
}

std::shared_ptr<sf::ConvexShape> Rectangle::to_convex_shape(const sf::Color& color_fill, const sf::Color& color_outline, const double outline_thickness) const {
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
