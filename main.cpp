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
    std::shared_ptr<Rectangle> boundries = std::make_shared<Rectangle>(std::make_shared<Point>(-1.0 * width / 2 + 1, height / 2 - 1.0), std::make_shared<Point>(width / 2 - 1, -1.0 * height / 2 + 1));
    double rotation = 0.001;

    // Main loop
    while (window.isOpen()) {
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
        window.draw(*boundries->to_convex_shape(sf::Color::Transparent, sf::Color::White, 3.0));

        // Draw the shapes you want here
        



        window.display();
    }
   return 0;
}

// to run:
// cmake -S . -B build
// cmake --build build
// ./build/PhysicsSimulator