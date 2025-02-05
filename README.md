# Physics Simulator 🌌⚛️

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![SFML](https://img.shields.io/badge/SFML-2.5.1-blue.svg)](https://www.sfml-dev.org/)
[![CMake](https://img.shields.io/badge/CMake-3.12+-064f8c.svg)](https://cmake.org/)

A 2D physics simulator implementing gravitational interactions and collision dynamics using SFML and modern C++.


## Features 🚀

### Core Physics
- **Gravitational Interaction** between multiple bodies with adjustable constant (G)
- **Elastic Collision System** for both ball-ball and ball-boundary interactions
- **Real-time Physics Updates** with fixed time step simulation
- **Friction Modeling** using velocity diminishing factor after collisions
- **Boundary Conditions** with configurable rectangular constraints

### Visualization
- 🎨 SFML-based rendering system
- 📏 Axis visualization with dynamic scaling
- ⚪ Circle/ball rendering with position and velocity vectors
- 🟦 Boundary visualization with collision highlights

### Architecture
- **Object-Oriented Design** with polymorphic shape classes
- **Component-based Structure** for easy extension
- **CMake Build System** for cross-platform compatibility
- **Modular Physics Components** (velocity, acceleration, collision)

## Supported Shapes 🔷
| Class       | Description                          | Key Features                              |
|-------------|--------------------------------------|-------------------------------------------|
| `Point`     | 2D coordinate point                  | Vector operations, distance calculations |
| `Line`      | Line segment                         | Slope/intercept, intersection detection  |
| `Circle`    | Circular body with physics           | Mass, velocity, collision response       |
| `Rectangle` | Axis-aligned bounding box            | Boundary checks, area/perimeter          |
| `Triangle`  | Triangular polygon                   | Centroid calculation, rendering          |

## Installation ⚙️

### Prerequisites
- C++17 compatible compiler (g++ 9+/clang 10+/MSVC 2019+)
- CMake 3.12+
- SFML 2.5.1+

### Build Instructions
```bash
git clone https://github.com/yourusername/PhysicsSimulator.git
cd PhysicsSimulator
mkdir build
cmake -S . -B build
cmake --build build
```

### Running
```bash
cd build
./PhysicsSimulator  # Linux/macOS
./PhysicsSimulator.exe  # Windows
```

## Configuration 🛠️
Adjust simulation parameters in `main.cpp`:
```cpp
// Physics parameters
const double G = 6.674e-11;    // Gravitational constant
const double diminishing_factor = 0.95;  // Collision energy retention
int acc_y = -5000;    // Acceleration due to gravity
int acc_x = 0;
// Simulation bounds
const float width = 1200;
const float height = 900;
```

## Future Roadmap 🗺️
- [ ] Support for polygonal shapes
- [ ] Better collision handling
- [ ] User interaction system
- [ ] Air resistance modeling
- [ ] Multi-threaded physics
- [ ] Scenario presets

## Contributing 🤝
We welcome contributions:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License 📄
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
