# Simulation Client

The client desktop app for the Blood Simulation project, available for Windows and Linux, made in C++ 20.

## Authors
 * Hubert Lawenda
 * Piotr Nieciecki
 * Filip Skrzeczkowski

## Prerequisites
Most of the project is self-contained as the libraries are shipped together with it.
The only thing you have to do beforehand is to install the **gstreamer-1.0 1.22.8** library:
 * Windows: visit https://gstreamer.freedesktop.org/
 * Linux: use your package manager

Additionally, in order to build the solution you may need to install OpenMP, if it's not already provided by your environment.

## Build
The primary method of building the solution is to use cmake.
Typically you'd want to create a directory named build at the level of CMakeLists.txt, enter it, and execute

`cmake ..`

`make`

In the case of Windows, there is a Visual Studio 2022 solution file provided.

## Usage

Upon launching the app two windows will appear - a native OpenGL window and a ImGui user interface window. The client app allows you to manage the configuration files of the simulation split into three categories:
 * general config
 * blood cell definitions
 * vein definition.
To load and save them use the GUI window's top menu bar.

You can also use the app to define the parameters. The general config constists of three tabs: simulation, physics and graphics that allow you to change various simulation parameters.
Use the blood cells editor to define blood cell types yourself - including vertices, springs betweeen them, colors and quantity.
The vein editor allows you to creae your own tree-like hierarchy of vein segments including both simple cylinders and bifurcations. Each segment can be bent and rotated.

When "Compile and run" is clicked the data you defined is going to be serialized to C++ headers that will have to be compiled into the server. If you so desire (click "Run locally"), it can be done automatically and the server will be automatically run and the data it renders will streamed back to the client.


## Keyboard controls
Both the vein editor and the aforementioned final simulation screen enable the user to move and rotate the camera.

 * W - move forward
 * S - move backward
 * A - move leftw
 * D - move right
 * Space - ascend
 * Shift - descend
 * Up arrow - rotate up (pitch axis)
 * Down arrow - rotate down (pitch axis)
 * Left arrow - rotate left (yaw axis)
 * Right arrow - rotate right (yaw axis)
 * V - switch between solid shader and edges-only
 * B - switch the visibility of blood cell springs (simulation only)
 * N - switch between the normal blood cell view and "blood cells as spheres connected by springs" (simulation only)
