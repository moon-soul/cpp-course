# 2D Solar System Simulator

## Genre
Arcade Simulator

## Overview
The 2D Solar System Simulator is an interactive, visually engaging arcade simulator set in space. It enables exploration of a virtual solar system, navigating through celestial bodies and an optionally included spacecraft within a two-dimensional environment. The simulator is designed to provide educational insights into the mechanics of solar systems while also providing an enjoyable and immersive experience. The simulation maintains 1:1 scale ratios for celestial bodies, distances between them, and their orbital periods, mirroring real-life astronomical measurements to provide an accurate representation of the solar system's dynamics.

## Main Flow
Upon launching the simulator, a dynamically generated solar system is presented, complete with planets, moons, and the sun. The simulation starts with the solar system in motion, planets orbiting the sun, and moons orbiting their respective planets.

### Start
- The simulator initializes with a view of the entire solar system centered on the sun.
- Celestial bodies (planets, moons) are loaded with their initial positions and trajectories.
- The main space ambient sound theme begins to play, adding to the immersive experience of the simulation.
- A spacecraft can optionally be spawned, subject to the gravitational forces of nearby celestial bodies.

### Simulation Process
- To interact with the simulation, zoom in/out and focus on specific celestial bodies. If present, the spacecraft will be affected by the gravitational pull of nearby planets and moons.
- The simulation runs in real-time, with the ability to pause, speed up, or slow down the simulation speed.

## Mechanics
- **Orbital Dynamics**: Planets and moons follow simplified circular orbits around their attractors, which streamline the complex physics of real-world orbital mechanics for accessibility and ease of simulation.
- **Spacecraft Orbital Mechanics**: The spacecraft's movement is determined by the gravitational influence of nearby celestial bodies, simulating an orbital navigation experience within the constraints of the simulation's environment.
- **Zoom and Focus**: The camera system allows to zoom in/out and focus on specific entities, providing detailed views of planets, moons, and the spacecraft.
- **Time Control**: The simulation speed can be adjusted, to experience faster or slower orbital movements and spacecraft navigation.

## Technical Systems

### Class Diagram
![Class Diagram](/solar_system/docs/class_diagram.png)

### Main Modules
- **Celestial Body**: Manages the appearance, position, and simplified circular orbital mechanics of planets and moons, including their initial positions and trajectories.
- **Spacecraft**: Implements a simplified approach to orbital mechanics, where the gravitational influence of nearby celestial bodies is approximated using a constant scaling value for the force calculation. This method simplifies the simulation of spacecraft movement, focusing on accessibility and stability of the simulation over physical accuracy.
- **Camera**: Handles the viewport, allowing to zoom and focus on different parts of the solar system with smooth transitions.
- **Solar System**: The core module integrating all entities (celestial bodies, spacecraft) and managing the simulation flow, including the initialization, real-time progression, and user interactions.

### Algorithms
- **Orbital Calculation**: Utilizes basic physics principles to calculate the trajectories of celestial bodies and the spacecraft. For celestial bodies, simplified circular orbits are assumed, while for the spacecraft, a simplified gravitational model scales the gravitational force without directly using the gravitational constant or masses.
- **Orbits Rendering**: Visualizes the orbits of celestial bodies as simple circular paths. This approach provides a clear representation of the orbital trajectories, enhancing the educational value and visual appeal of the simulation.
- **Trail Rendering**: Implements a dynamic visualization of the spacecraft's path, displaying a fading trail effect that updates in real time as the spacecraft moves through the solar system.

### Camera and Controls
- **Camera**: Dynamically adjusts based on user interactions, with smooth transitions and the ability to lock onto specific entities, including celestial bodies and the spacecraft.
- **Controls**:
  - **Focusing**: Numbers 1 to 8 on the keyboard allow to focus on the respective planet in the solar system. Pressing 0 focuses on the Moon, C focuses on the center (the Sun), and V focuses on the spacecraft, if present.
  - **Camera Movement**: The arrow keys allow for manual movement of the camera across the solar system, providing a way to freely explore the space.
  - **Zoom**: The mouse wheel is used to zoom in and out, providing the ability to adjust the view from close-up details to a wide-angle perspective.
  - **Time Control**: The simulation speed can be paused by pressing the spacebar, and adjusted by using the = (increase speed) and - (decrease speed) keys, enabling a tailored viewing experience of the solar system dynamics.
  - **Spacecraft Management**: Spacecraft can be spawned at the current mouse position by left-clicking, and despawned by right-clicking, providing dynamic interaction with the simulation's navigational component.

## Compilation
The following commands are used to compile the 2D Solar System Simulator:

```
clang++ *.cpp -o solar_system -std=c++20 -Wall -Wextra -pedantic -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

## Dependencies
The project relies on the Simple and Fast Multimedia Library (SFML) to handle graphical rendering, window management, system interactions, and audio playback. To compile and run the simulator, SFML must be installed and correctly configured on the system.

### SFML Installation
SFML is available for various operating systems, including Windows, macOS, and Linux. Installation instructions and precompiled libraries can be found on the [SFML website](https://www.sfml-dev.org/download.php).

Ensure that SFML is installed and linked correctly when compiling the simulator, as specified in the Compilation section of this document.

## License
The project is licensed under the MIT License - see the LICENSE file for details.

## Demo
[![Demo](https://img.youtube.com/vi/o8k9qp7oz10/0.jpg)](https://www.youtube.com/watch?v=o8k9qp7oz10)
