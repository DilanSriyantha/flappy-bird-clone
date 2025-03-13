# DynamiteEngine
<div align="center">
  <img src="https://raw.githubusercontent.com/DilanSriyantha/DilanSriyantha/main/made_with_dynamite_engine_flappy_bird.gif" alt="Banner" width="400">
</div> 

Dynamite Engine is a lightweight and efficient 2D game engine built with C++ and SDL2. It provides an Entity-Component-System (ECS) architecture, 2D collision detection, sprite animation, and UI components, making it easy to develop high-performance 2D games.

## Features

- **Entity-Component-System (ECS)** for modular game object management.
- **2D Rendering** using SDL2 for optimized performance.
- **Collision Detection** with AABB and pixel-based techniques.
- **Audio Management** for sound effects and background music.
- **Texture and Asset Management** for efficient resource handling.
- **UI Components** for buttons, text, and other elements.
- **Input Handling** for keyboard and mouse events.

## Getting Started
### Prerequisites
Ensure you have the following installed:
- C++ 17 or later
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- MSVC Redistributables (x86 & x64)

### Installation
1. **Clone the Repository**
   ```sh
   git clone https://github.com/DilanSriyantha/flappy-bird-clone
   cd flappy-bird-clone
   ```
2. **Open in Visual Studio 2022**
   - Open ```DynamiteEngine.sln``` in **Microsoft Visual Studio 2022**.
   - Ensure all dependencies are correctly linked.
3. **Build the Project**
   - Select **Release** or **Debug** mode.
   - Click **Build Solution** (```Ctrl + Shift + B```)
4. **Run the Engine**
   - Execute the built application.
  
## Usage
Once you have cloned the repository and opened it in Visual Studio, take a look at ```Scene01.cpp``` file. Follow the same structure to create scenes on your own. The syntax and the system shares common similarities with Unity Engine as a matter of fact.

## License 
This project is licensed under the **MIT-License** - see the [LICENSE](https://github.com/DilanSriyantha/flappy-bird-clone/tree/main?tab=MIT-1-ov-file) file for details.
