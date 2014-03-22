opengl-engine
=============

A series of classes utilizing OpenGL for graphics, including particle system effects, L-systems, skyboxes, etc.

Installation
------------
Navigate to the build/ subdirectory and execute ``cmake ..`` for an out-of-source build, then call ``make``. CMake must be installed, and OpenGL and GLUT are required dependencies for this project.

The sample program displays a textured grass floor, a skybox, plants procedurally generated using L-systems, and a particle water fountain. Right click to change fountain settings and press escape to quit.

Source description
------------------

* Camera.h: Defines a camera, which consists of 3 unit dimensional vectors and a 3D position. Contains methods for camera movement, rotation, etc.

* Color.h: Useful template classes for RGB and RGBA colors.

* Debug.h: Contains assert macros for debugging, including a compile-time assert.

* Error.h: Defines an ERR_CODE enum, used for general error handling.

* GLIncludes.h: Platform-dependent OpenGL/GLUT includes, put in a header file for convenience.

* Image.h: Contains functionality for loading TGA (either compressed or uncompressed) and RAW images.

* LSystem.h: Implementation of [Lindenmayer systems](http://en.wikipedia.org/wiki/L-system), which recursively use a set of grammar rules to generate an object.

* Logger.h: Defines a Logger singleton which writes messages to the user and/or a file (gameengine.txt by default).

* Math.h: Contains the constant pi and trigonometric functions in degrees.

* Model.h: Allows for the loading and rendering of MODEL files (a custom 3D format).

* ParticleSystem.h: A base particle system class and subclasses Fountain, Fireworks, and Snow with configurable parameters.

* Point.h: Template classes for 2D and 3D points.

* Quaternion.h: Implements quaternion rotation and various mathematical operations on quaternions.

* Singleton.h: Useful base class for singletons (inspired by "Game Programming Gems", section 1.3 by Scott Bilas).

* Skybox.h: Textured skybox class, which gives the appearance of a faraway background.

* Texture.h: Creates a texture manager which handles allocation, processing, and deletion of OpenGL textures through a texture handle class.

* Utils.h: General purpose methods.

* Vector.h: Template classes for 2D and 3D vectors.
