#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "shapes/Shape.h"
#include "shapes/Point.h"
#include "shapes/Line.h"
#include "shapes/Triangle.h"
#include "shapes/Rectangle.h"
#include "shapes/Circle.h"

// Function to handle collision between two balls
void handle_ball_collision(std::shared_ptr<Circle> a, std::shared_ptr<Circle> b) {
    auto dx = b->getCenter()->get_x() - a->getCenter()->get_x();
    auto dy = b->getCenter()->get_y() - a->getCenter()->get_y();
    double distance = std::sqrt(dx * dx + dy * dy);
    double min_dist = a->getRadius() + b->getRadius();

    if (distance < min_dist && distance > 0.0) { // Ensure actual overlap and avoid division by zero
        double overlap = 0.5 * (min_dist - distance);

        // Displace balls to prevent overlap
        a->setCenterX(a->getCenter()->get_x() - overlap * (dx / distance));
        a->setCenterY(a->getCenter()->get_y() - overlap * (dy / distance));
        b->setCenterX(b->getCenter()->get_x() + overlap * (dx / distance));
        b->setCenterY(b->getCenter()->get_y() + overlap * (dy / distance));

        // Simple elastic collision response (equal mass assumption)
        auto va = a->getVelocity();
        auto vb = b->getVelocity();

        double nx = dx / distance;
        double ny = dy / distance;

        double p = 2 * (va->get_x() * nx + va->get_y() * ny - vb->get_x() * nx - vb->get_y() * ny) / 2;

        a->setVelocity(va->get_x() - p * nx, va->get_y() - p * ny);
        b->setVelocity(vb->get_x() + p * nx, vb->get_y() + p * ny);
    }
}

/**
 * @brief The main function of this program. It sets up a window of size 1200x900 and a view that is centered at the origin.
 * It then creates a few shapes and draws them to the window in a loop until the window is closed.
 * The loop polls for events and if the window is closed, it closes the window.
 * It then clears the window to black, draws the x and y axes, and draws the shapes to the window.
 * It also rotates the line by 0.001 degrees each frame.
 * It then displays the window on screen.
 */
int main() {
    float width = 1200;
    float height = 900;
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "SFML window");
    sf::View view(sf::FloatRect(-width / 2, height / 2, width, -height));
    window.setView(view);

    std::shared_ptr<Line> x_axis = std::make_shared<Line>(std::make_shared<Point>(-width / 2, 0), std::make_shared<Point>(width / 2, 0));
    std::shared_ptr<Line> y_axis = std::make_shared<Line>(std::make_shared<Point>(0, height / 2), std::make_shared<Point>(0, -height / 2));
    std::shared_ptr<Rectangle> boundaries = std::make_shared<Rectangle>(
        std::make_shared<Point>(-width / 2 + 1, height / 2 - 1),
        std::make_shared<Point>(width / 2 - 1, -height / 2 + 1)
    );

    sf::Clock clock;
    // Friction coefficient
    double diminishing_factor = 0.1;
    // Gravitational constant (adjust this value for visible gravitational effects)
    const double G = 5000;

    std::vector<std::shared_ptr<Circle>> balls;
    int num_balls = 100;

    for (int i = 0; i < num_balls; ++i) {
        int x = rand() % (int)width - width / 2;
        int y = rand() % (int)height - height / 2;
        int radius = rand() % 5 + 5;
        int max_speed = 500;
        int min_speed = -500;
        // int speed_x = rand() % (max_speed - min_speed + 1) + min_speed;
        // int speed_y = rand() % (max_speed - min_speed + 1) + min_speed;
        int speed_x = 0;
        int speed_y = 0;
        int max_acc = 5000;
        int min_acc = -5000;
        // int acc_x = rand() % (max_acc - min_acc + 1) + min_acc;
        // int acc_y = rand() % (max_acc - min_acc + 1) + min_acc;
        int acc_x = 0;
        // int acc_y = -5000;
        // For this simulation we use gravitational interaction between balls, so a constant acceleration is no longer added.
        int acc_y = 0;
        int max_mass = 1000;
        int min_mass = 100;
        // int mass = rand() % (max_mass - min_mass + 1) + min_mass;
        int mass = 1;

        // Create the ball with its radius (you might want to use the 'radius' variable here if needed)
        balls.push_back(std::make_shared<Circle>(std::make_shared<Point>(x, y), radius));
        balls[i]->setVelocity(std::make_shared<Point>(speed_x, speed_y))
                 ->setAcceleration(acc_x, acc_y)
                 ->setMass(mass);
    }


    while (window.isOpen()) {
        float delta_time = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Compute gravitational acceleration for each ball due to every other ball.
        // For ball i, the acceleration from ball j is: a = G * mass_j / (r^2) in the direction of ball j,
        // or more precisely: a = G * mass_j * (r_vector) / |r|^3.
        for (auto& ball : balls) {
            double net_ax = 0.0;
            double net_ay = 0.0;
            for (auto& other : balls) {
                if (ball == other) continue;
                double dx = other->getCenter()->get_x() - ball->getCenter()->get_x();
                double dy = other->getCenter()->get_y() - ball->getCenter()->get_y();
                double distance = std::sqrt(dx * dx + dy * dy);
                // Avoid division by zero (or extremely small distances) which can lead to huge forces.
                if (distance < 1.0) distance = 1.0;
                net_ax += G * other->getMass() * dx / (distance * distance * distance);
                net_ay += G * other->getMass() * dy / (distance * distance * distance);
            }
            ball->setAcceleration(net_ax, net_ay);
        }

        // Update physics and handle boundary collisions
        for (auto& ball : balls) {
            ball->update_physics(delta_time);

            float left = boundaries->get_left_boundry();
            float right = boundaries->get_right_boundry();
            float top = boundaries->get_top_boundry();
            float bottom = boundaries->get_bottom_boundry();

            float x = ball->getCenter()->get_x();
            float y = ball->getCenter()->get_y();
            float r = ball->getRadius();

            if (x - r < left) {
                ball->setCenterX(left + r);
                ball->setVelocity(-diminishing_factor * ball->getVelocity()->get_x(), ball->getVelocity()->get_y());
            }
            if (x + r > right) {
                ball->setCenterX(right - r);
                ball->setVelocity(-diminishing_factor * ball->getVelocity()->get_x(), ball->getVelocity()->get_y());
            }
            if (y + r > top) {
                ball->setCenterY(top - r);
                ball->setVelocity(ball->getVelocity()->get_x(), -diminishing_factor * ball->getVelocity()->get_y());
            }
            if (y - r < bottom) {
                ball->setCenterY(bottom + r);
                ball->setVelocity(ball->getVelocity()->get_x(), -diminishing_factor * ball->getVelocity()->get_y());
            }
        }

        // Handle collisions between balls
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                handle_ball_collision(balls[i], balls[j]);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(*x_axis->to_vertex_array());
        window.draw(*y_axis->to_vertex_array());
        window.draw(*boundaries->to_convex_shape(sf::Color::Transparent, sf::Color::White, 3.0));

        // Draw balls
        for (const auto& ball : balls) {
            window.draw(*ball->to_circle_shape(sf::Color::White));
        }

        window.display();
    }

    return 0;
}

// to run:
// cmake -S . -B build
// cmake --build build
// ./build/PhysicsSimulator