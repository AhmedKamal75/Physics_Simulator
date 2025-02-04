// This project uses the CMake build system.
#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "shapes/Shape.h"
#include "shapes/Point.h"
#include "shapes/Line.h"
#include "shapes/Triangle.h"
#include "shapes/Rectangle.h"
#include "shapes/Circle.h"

/**
 * @brief The main function of this program. It sets up a window of size 1200x900 and a view that is centered at the origin.
 * It then creates a few shapes and draws them to the window in a loop until the window is closed.
 * The loop polls for events and if the window is closed, it closes the window.
 * It then clears the window to black, draws the x and y axes, and draws the shapes to the window.
 * It also rotates the line by 0.001 degrees each frame.
 * It then displays the window on screen.
 */
int main() {
    // Create a window
    float width = 1200;
    float height = 900;
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "SFML window");
    sf::View view(sf::FloatRect(-1 * width / 2, height / 2, width, -height)); // Corrected
    window.setView(view);


    std::shared_ptr<Line> x_axis = std::make_shared<Line>(std::make_shared<Point>(-1.0 * width / 2, 0), std::make_shared<Point>(width / 2.0, 0.0));
    std::shared_ptr<Line> y_axis = std::make_shared<Line>(std::make_shared<Point>(0.0, height / 2.0), std::make_shared<Point>(0.0, -1.0 * height / 2.0));
    std::shared_ptr<Rectangle> boundaries = std::make_shared<Rectangle>(std::make_shared<Point>(-1.0 * width / 2 + 1, height / 2 - 1.0), std::make_shared<Point>(width / 2 - 1, -1.0 * height / 2 + 1));
    double deminishing_factor = 0.999;

    sf::Clock clock;

    std::shared_ptr<Circle> ball = std::make_shared<Circle>(std::make_shared<Point>(50, 50), 50); 
    ball->setVelocity(std::make_shared<Point>(500,-400))->setAcceleration(std::make_shared<Point>(0, -5000));

    // Main loop
    while (window.isOpen()) {
        float delta_time = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        // Draw the x and y axes
        window.draw(*x_axis->to_vertex_array());
        window.draw(*y_axis->to_vertex_array());
        window.draw(*boundaries->to_convex_shape(sf::Color::Transparent, sf::Color::White, 3.0));

        // Draw the shapes you want here
        ball->update_physics(delta_time);

        // Assuming the coordinate system is set so that positive y is up:
        float left   = boundaries->get_left_boundry();
        float right  = boundaries->get_right_boundry();
        float top    = boundaries->get_top_boundry();
        float bottom = boundaries->get_bottom_boundry();

        float circle_x = ball->getCenter()->get_x();
        float circle_y = ball->getCenter()->get_y();
        float circle_radius = ball->getRadius();

        // Left boundary: if the left edge of the circle is beyond the left boundary
        if (circle_x - circle_radius < left) {
            ball->setCenterX(left + circle_radius);
            ball->setVelocity(-deminishing_factor * ball->getVelocity()->get_x(), ball->getVelocity()->get_y());
        }

        // Right boundary: if the right edge of the circle is beyond the right boundary
        if (circle_x + circle_radius > right) {
            ball->setCenterX(right - circle_radius);
            ball->setVelocity(-deminishing_factor * ball->getVelocity()->get_x(), ball->getVelocity()->get_y());
        }

        // Top boundary: if the top edge of the circle is beyond the top boundary
        if (circle_y + circle_radius > top) {
            ball->setCenterY(top - circle_radius);
            ball->setVelocity(ball->getVelocity()->get_x(), -deminishing_factor * ball->getVelocity()->get_y());
        }

        // Bottom boundary: if the bottom edge of the circle is beyond the bottom boundary
        if (circle_y - circle_radius < bottom) {
            ball->setCenterY(bottom + circle_radius);
            ball->setVelocity(ball->getVelocity()->get_x(), -deminishing_factor * ball->getVelocity()->get_y());
        }


        window.draw(*ball->to_circle_shape(sf::Color::White));


        window.display();
    }
   return 0;
}

// to run:
// cmake -S . -B build
// cmake --build build
// ./build/PhysicsSimulator