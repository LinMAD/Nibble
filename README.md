> Nibble

 A space to play with OpenGL\Shaders, 2D, 3D rendering etc
---

## Showcase
![OpenGL](Extras/CurrentRender.gif)

As well I have instagram related to this hobby *[nibble_hex]( https://www.instagram.com/nibble_hex/)*.

Implemented:
- Shadows
- Directional light
- Spot lights
- Point lights
- Mesh renderers
- Materials

### TODO of refactoring to more or less clean project
Refactor draft OpenGL app to have:
- Entry point
- Debug support system
- Build system
- Files (I/O), VFS (Virutal file system) support
- Graphic related layers
	- Applicaiton layer
		- User input
		- Events
	- Graphic renderer layer
		- API Abstraction for (OpenGL, Vulcan or DirectX)
	- Memory system layer
	- Entity components system layer
	- Physics system layer
