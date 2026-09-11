MyRenderer

A from-scratch Software Rasterizer written in C++17.

MyRenderer is a CPU-based rendering pipeline built without using OpenGL or Vulkan as the core rendering API. The project implements the fundamental stages of a real-time rendering pipeline, including transformation, clipping, rasterization, depth testing, perspective-correct interpolation, texture mapping, lighting, and shadow mapping.

The main goal of this project is to understand how a real-time rendering pipeline works internally by implementing its core components from scratch.

⸻

Features

Mathematics

* Vector2 / Vector3 / Vector4
* Matrix 2x2 / 3x3 / 4x4
* Dot Product
* Cross Product
* Normalization
* Matrix Inverse
* Matrix Transpose
* Matrix Transformations

Transform

* Model Transform
* View Transform
* Projection Transform
* lookAt
* Perspective Projection
* Orthographic Projection
* MVP Matrix

The main transformation pipeline is:

Model Space
    ↓
Model Matrix
    ↓
World Space
    ↓
View Matrix
    ↓
View Space
    ↓
Projection Matrix
    ↓
Clip Space

⸻

Rasterization

MyRenderer implements triangle rasterization completely on the CPU.

* Bounding Box Rasterization
* Barycentric Coordinates
* Triangle Coverage Test
* Depth Buffer / Z-Buffer
* Back-face Culling
* Viewport Transformation

The basic rasterization process is:

Triangle
   ↓
Bounding Box
   ↓
Pixel Coverage Test
   ↓
Barycentric Coordinates
   ↓
Depth Test
   ↓
Fragment

⸻

Clipping

MyRenderer implements Sutherland-Hodgman polygon clipping against the six planes of the view frustum.

Left
Right
Top
Bottom
Near
Far

The clipping pipeline follows:

Clip Space
    ↓
Frustum Clipping
    ↓
Perspective Divide
    ↓
NDC
    ↓
Viewport Transform
    ↓
Screen Space

A key rule of the pipeline is:

Clipping must happen before perspective division.

⸻

Perspective-Correct Interpolation

Per-vertex attributes are interpolated using perspective-correct interpolation.

Currently supported attributes include:

* Color
* Normal
* World Position
* UV
* Depth

The interpolation uses the reciprocal homogeneous coordinate:

invW = 1 / w

For an attribute A:

denominator =
    α * invW0 +
    β * invW1 +
    γ * invW2
A =
    (α * A0 * invW0 +
     β * A1 * invW1 +
     γ * A2 * invW2)
    / denominator

This allows attributes such as texture coordinates and normals to remain correct under perspective projection.

⸻

Lighting

MyRenderer implements a basic Blinn-Phong lighting model.

Ambient

Ambient = Material × LightColor × AmbientIntensity

Diffuse

Diffuse =
    Material × LightColor × Intensity × max(N · L, 0)

Specular

The Blinn-Phong half vector is used:

H = normalize(L + V)

Then:

Specular =
    LightColor × Intensity × pow(max(N · H, 0), Shininess)

The renderer supports:

* Ambient Lighting
* Diffuse Lighting
* Specular Highlights
* Per-vertex Normal Interpolation
* Material Parameters

⸻

Texture Mapping

MyRenderer supports texture mapping using UV coordinates.

Currently implemented:

* TGA Texture Loading
* UV Coordinates
* Perspective-Correct UV Interpolation
* Texture Sampling
* Diffuse Texture Mapping

Example model:

obj/african_head/african_head.obj

with:

obj/african_head/african_head_diffuse.tga

⸻

Shadow Mapping

MyRenderer also implements a first version of Shadow Mapping.

The shadow map is generated from the light’s point of view:

World Space
     ↓
Light View
     ↓
Light Projection
     ↓
Light NDC
     ↓
Shadow Map

During the main rendering pass, the fragment’s world position is transformed into light space:

Fragment World Position
        ↓
Light MVP
        ↓
Light NDC
        ↓
Shadow Map Coordinates
        ↓
Depth Comparison
        ↓
Shadow Test

The current implementation uses:

* Depth Shadow Map
* Orthographic Light Projection
* Depth Comparison
* Constant Shadow Bias

Fragments determined to be inside a shadow disable diffuse and specular lighting while preserving ambient lighting.

⸻

Rendering Pipeline

The current rendering pipeline is approximately:

                    ┌───────────────┐
                    │      OBJ      │
                    └───────┬───────┘
                            │
                            ▼
                     Model Transform
                            │
               ┌────────────┴────────────┐
               │                         │
               ▼                         ▼
          Light MVP                 Camera MVP
               │                         │
               ▼                         ▼
         Shadow Map                    Clipping
               │                         │
               │                         ▼
               │                  Perspective Divide
               │                         │
               │                         ▼
               │                     Viewport
               │                         │
               │                         ▼
               │                    Rasterization
               │                         │
               │                         ▼
               │                     Z-Buffer
               │                         │
               │                         ▼
               │              Perspective Interpolation
               │                         │
               │                         ▼
               │                  Fragment Processing
               │                         │
               │          ┌──────────────┼──────────────┐
               │          │              │              │
               │          ▼              ▼              ▼
               │       Texture        Normal        World Position
               │                         │              │
               │                         │              ▼
               │                         │         Shadow Test
               │                         │              │
               │                         └──────┬───────┘
               │                                ▼
               │                       Ambient + Diffuse
               │                       + Specular
               │                                │
               └────────────────────────────────┤
                                                ▼
                                           Framebuffer
                                                │
                                                ▼
                                            PPM / TGA

⸻

Project Structure

MyRenderer/
├── include/
│   ├── Framebuffer/
│   ├── DepthBuffer/
│   ├── Math/
│   ├── Triangle/
│   ├── Rasterizer/
│   ├── Transform/
│   ├── Render/
│   ├── Shader/
│   ├── Texture/
│   ├── Shadow/
│   └── objLoader/
│
├── src/
│   ├── Framebuffer/
│   ├── DepthBuffer/
│   ├── Math/
│   ├── Triangle/
│   ├── Rasterizer/
│   ├── Transform/
│   ├── Render/
│   ├── Shader/
│   ├── Texture/
│   ├── Shadow/
│   └── objLoader/
│
├── obj/
│   └── ...
│
├── main.cpp
├── CMakeLists.txt
└── README.md

⸻

Build

Requirements

* C++17 compatible compiler
* CMake
* macOS / Linux / Windows

The project currently uses CMake as its build system.

Build

mkdir build
cd build
cmake ..
make

Then run the renderer:

./MyRenderer

The exact executable name may depend on the CMake configuration.

⸻

Output

MyRenderer currently renders images offline rather than using a real-time window.

The renderer can output image data such as:

PPM
TGA

This design keeps the rendering pipeline independent from a graphics API or windowing system.

⸻

Example

One of the main demonstrations uses the classic African Head model:

OBJ
 ↓
Model / View / Projection
 ↓
Clipping
 ↓
Rasterization
 ↓
Depth Testing
 ↓
Texture Mapping
 ↓
Blinn-Phong Lighting
 ↓
Shadow Mapping
 ↓
PPM

The resulting image demonstrates:

* Textured geometry
* Diffuse lighting
* Specular highlights
* Depth testing
* Cast shadows

⸻

Design Goals

The primary goal of MyRenderer is not to replace GPU graphics APIs.

Instead, the project focuses on understanding the internal mechanisms behind a real-time renderer.

The project was developed around several questions:

* How does a triangle become pixels?
* How does perspective projection work?
* Why is clipping required before perspective division?
* How does a Z-buffer determine visible fragments?
* Why is perspective-correct interpolation necessary?
* How are normals transformed?
* How does texture mapping work?
* How does a shadow map determine whether a fragment is occluded?
* How do lighting calculations operate at the fragment level?

Implementing these systems from scratch makes the relationship between mathematical theory and an actual rendering pipeline much more concrete.

⸻

Current Limitations

This project is intentionally focused on the fundamentals of rasterization.

The current version does not aim to provide a production-ready rendering engine.

Known limitations include:

* CPU-only rasterization
* No GPU acceleration
* No real-time window / presentation system
* Basic shadow mapping
* No PCF shadow filtering
* Fixed shadow bias
* No advanced material system
* No PBR
* No mipmapping
* No perspective-aware clipping in the current shadow-map pass
* Limited asset loading functionality

These are possible directions for future development rather than requirements for the current version.

⸻

Future Improvements

Possible future directions include:

* PCF Shadow Mapping
* Improved Shadow Bias
* Normal Mapping
* Multiple Lights
* More Advanced Material System
* Mipmapping
* Frustum Culling
* SIMD Optimization
* Multithreaded Rasterization
* Real-time Window Presentation
* GPU Renderer Backend

⸻

Learning Sources

This project was developed alongside practical study of computer graphics and real-time rendering concepts, including:

* Rasterization
* Linear Algebra
* Computer Graphics
* Lighting Models
* Texture Mapping
* Shadow Mapping

The implementation is intentionally built from the underlying algorithms rather than relying on an existing rendering framework.

⸻

License

This project is intended primarily as a personal graphics programming and learning project.