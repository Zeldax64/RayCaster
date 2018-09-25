# Simple Graphics API

A simple graphics API to render 3D scenes using software raytracing.

Objectives:

1. [x] Implement math cores to support API implementation: Vertex (Vertex3f) and Transformation Matrices (TMatrix);
2. [ ] Implement object abstract class: start with a simple cube using vertices, edges and faces lists (Triangle mesh) and a mathematical defined sphere;
3. [ ] Implement a scenery class to hold objects (list of objects?);
4. [ ] Implement Rayracing algorithm: implement eye, lookAt, and ray;
5. [ ] Render the scene and use OpenGL to colour the screen (another API can be used).

## How to run it

To build the project:

    $ make all

To build and run:

    $ make run

## TODO

#### Objective 2
  Implement a cube and a sphere by their mathematical definition without using meshes;

#### Objective 3
  Create a scenery class which hold all objects and can apply transformations on them.
