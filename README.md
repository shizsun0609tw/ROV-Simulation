# ROV-Simulation

This is a C/C++ project to simulate ROV(Remotely Operated Vehicle) motion in deep-sea.<br/>
This project is written by OPENGL 4.3.

Demo Video: https://www.youtube.com/watch?v=nWtugU7TSyg

### Operation:
* Change Control Mode: Key1(EYE), Key2(ROV), Key3(LIGHT)
* Change Display Mode: M
* Mode EYE
  * Move: W, A, S, D				
  * Zoom: Q, E
  * On/Off: V
* Mode ROV
  * Move: W, A, S, D, Q, E
  * Roll: R, Shift + R
  * Yaw: Y, Shift + Y				
  * Pitch: P, Shift + P
* Mode Light
  * Select: S(SpotLight), P(PointLight), D(DirectionalLight)
  * On/Off: KP_0				
  * Color: R, G, B

### System:
* Render: OpenGL 4.3
* Library: glew, glfw, glm
* Header: Definition.h
* Class: WindowManagement, Scene, ROV, Billboard, Light, draw, 
          shader, texture, BMPfile, JellyFish, Eye, Icosphere
* Shader: shader.vert, shader.frag

### Settings:
* If you want to use Visual Studio to execute, you need to change enviroment to Debug/x64 and set Project/Attribute/Debug/environment "PATH=$(ProjectDir)\bin\"
