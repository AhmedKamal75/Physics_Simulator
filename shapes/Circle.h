#ifndef RECTANGLE_H
#define RECTANGLE_H


#include "Line.h"

class Circle : public Shape, public std::enable_shared_from_this<Circle> {
    private:
        std::shared_ptr<Point> center;
        double radius;

    public:
        Circle(std::shared_ptr<Point> center, double radius);
        std::shared_ptr<Point> getCenter() const;
        double getRadius() const;
        void setCenter(std::shared_ptr<Point> center);
        void setRadius(double radius);
        double area() const;
        double circumference() const;
        double diameter() const;
        bool contains(const std::shared_ptr<Point> point) const;
        bool is_intersecting(const std::shared_ptr<Circle> other) const;
        void move (const double dx, const double dy);
        void scale (const double factor);
        std::shared_ptr<Line> solve_with(const std::shared_ptr<Line> line) const;
        bool is_tangent(const std::shared_ptr<Circle> other) const;
        bool is_disjoint(const std::shared_ptr<Circle> other) const;
        bool is_equal(const std::shared_ptr<Circle> other) const;
        std::shared_ptr<sf::CircleShape> to_circle_shape(const sf::Color& color) const;
        std::string to_string() const;
        std::shared_ptr<Circle> clone() const;
};


#endif // RECTANGLE_H