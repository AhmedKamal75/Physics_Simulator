#ifndef CIRCLE_H
#define CIRCLE_H


#include "Line.h"

class Circle : public Shape, public std::enable_shared_from_this<Circle> {
    private:
        std::shared_ptr<Point> center{}; // position
        std::shared_ptr<Point> velocity{};
        std::shared_ptr<Point> acceleration{};
        double radius;
        double mass;



    public:
        Circle(std::shared_ptr<Point> center, double radius);
        std::shared_ptr<Point> getCenter() const;
        double getRadius() const;
        std::shared_ptr<Point> getVelocity() const;
        std::shared_ptr<Point> getAcceleration() const;
        double getMass() const;
        std::shared_ptr<Circle> setCenter(std::shared_ptr<Point> center);
        std::shared_ptr<Circle> setCenterX(double x);
        std::shared_ptr<Circle> setCenterY(double y);
        std::shared_ptr<Circle> setRadius(double radius);
        std::shared_ptr<Circle> setVelocity(const double x, const double y);
        std::shared_ptr<Circle> setAcceleration(const double x, const double y);
        std::shared_ptr<Circle> setVelocity(std::shared_ptr<Point> velocity);
        std::shared_ptr<Circle> setAcceleration(std::shared_ptr<Point> acceleration);
        std::shared_ptr<Circle> setMass(double mass);
        void update_physics(const double delta_time);
        double area() const;
        double circumference() const;
        double diameter() const;
        bool contains(const std::shared_ptr<Point> point) const;
        bool is_intersecting(const std::shared_ptr<Circle> other) const;
        void move (const double dx, const double dy);
        void extend (const double factor);
        std::shared_ptr<Line> solve_with(const std::shared_ptr<Line> line) const;
        bool is_tangent(const std::shared_ptr<Circle> other) const;
        bool is_disjoint(const std::shared_ptr<Circle> other) const;
        bool is_equal(const std::shared_ptr<Circle> other) const;
        std::shared_ptr<sf::CircleShape> to_circle_shape(const sf::Color& color) const;
        std::string to_string() const;
        std::shared_ptr<Circle> clone() const;
};


#endif // CIRCLE_H