# Grass
This project demonstrates a grass rendering technique inspired by the visual style of Ghost of Tsushima. It features an efficient implementation of grass instancing, utilizing Level of Detail (LOD) to maintain high performance even with large numbers of instances.
## Features
- **Instanced Grass Rendering:** A 3x3 tile system with evenly spaced grass blades, each with slightly randomized offsets to avoid uniformity.
- **Wind System**: Convicing grass movement using Perlin noise to generate wind direction and lean angle. This adds dynamic and natural motion to the grass blades.
- **Level of Detail (LOD):** Different levels of detail are applied based on the camera's distance, with less detailed grass rendered further away to optimize performance.

<img width="466" alt="level of detail showcase" src="https://github.com/user-attachments/assets/9d63785a-5c10-46cb-af77-b0bc4fa8b37b">

## Implementation Details
- **Tiling System:** The scene is constructed from 3x3 tiles, each containing grass instances. Grass instances are drawn using instanced rendering, where each instance is slightly randomized in position and rotation to create a natural appearance.
- **Wind Effects:** Two instances of Perlin noise are sampled—one for the wind direction (used to rotate the grass on its Y-axis) and another for the wind lean angle (added to the random X-axis rotation). This results in a dynamic, wind-driven appearance for the grass.

## Libraries
GLEW, GLFW, OpenGL, glm

## How To Compile and Run
```
mkdir build-dir
cd build-dir
cmake ..
./playground
```

## Demo
Check out the demo video showing 416,025 grass instances running at 60 FPS on an M1 Mac with a resolution of 2560x1600 and vsync enabled. For a less compressed version of the demo, please visit the assets directory.


https://github.com/user-attachments/assets/55e30350-f08f-4ea3-bca9-04e64cbdad48

## References
https://www.youtube.com/watch?v=bp7REZBV4P4
