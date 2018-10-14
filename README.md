# Simple Graphics API

A simple graphics API to render 3D scenes using software raytracing.

Objectives:

1. [x] Implement math cores to support API implementation: Vertex (Vertex3f) and Transformation Matrices (TMatrix);
2. [ ] Implement object abstract class: start with a simple cube using vertices, edges and faces lists (Triangle mesh) and a mathematical defined sphere;
3. [X] Implement a scenery class to hold objects (list of objects?);
4. [X] Implement Rayracing algorithm: implement eye, lookAt, and ray;
5. [X] Render the scene and use OpenGL to colour the screen (another API can be used).

## How to run it

To build the project:

    $ make all

To build and run:

    $ make run

## Dependencies


1. freeglut: To create a window and paint it;
2. DevIL: To load images and handle images:

To install DevIL:

    $ sudo apt-get install libdevil-dev
