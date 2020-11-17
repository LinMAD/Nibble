> Nibble

Everything starts from small and evolve to something big.
The project mirrors my passion to learn computer graphics, C++, and art with programming. More like demoscene making or "games" maybe.

The current goal of this project to create a flexible and comfortable demo scene engine to make things like from my Instagram *[nibble_hex](https://www.instagram.com/nibble_hex/)* ^_^

---

## Past result showcase
![OpenGL](Extras/CurrentRender.gif)

Implemented with C++, OpenGL and with other libraries GLEW, GLFW, GLM, Assimp.3.0 - [Old project branch](https://github.com/LinMAD/Nibble/tree/old_master)
- Shadows Maps
- Omni-directional Shadows
- Directional light
- Spotlights
- Point lights
- Mesh renderers
- Materials
- Model importing from .obj

### Development work environment info
* Window 10 x64
* Microsoft Visual Studio Community 2019 (Solution contains linking, build events, and rest configuration)
* To build include engine and dependencies sources like in (lib\src;lib\vendor\spdlog\include;)

## License
Project under MIT, so I don't mind if someone will use this code for any purpose. 
Because it's fair enough, during researches and implementation I looking for manuals, books and other projects to solve my problems.

## Brainstorm and ...
![just_do_it](https://i.pinimg.com/originals/ab/28/a3/ab28a35ba61c3310ed6341b09dbbafab.jpg)

### Research more about that
- Debug support system? Or it's ok with logger and break points?
- Memory system layer (Like I saw in the Snowdrop from Massive entertainment)
- Entity components system layer?
- Physics system layer?
- Scene managment (Better with UI but for now component will work)?
- How to write an automated tests for graphics?
- What else?

### TODO List for refactoring to have a flexible and clean work base (Not final)
Research and refactor old codebase to have a nice structure like that list:
- ~~Entry point~~
- ~~Logger~~
- ~~Base Event bus system for user I/O~~
	- ~~Event listeners~~
	- ~~Client layer stack: Client app can create layers to work with I\O and Events~~
- Files (I/O), VFS (Virutal file system) support
- Graphic related layers
    - ~~GUI Overlay~~
	- Graphic renderer layer
		- API Abstraction for (OpenGL, Vulcan or DirectX)
		- Shaders compilation
- ???

##### Singletons
- `Logger` can be accessed like `LOGGER_CLIENT_INFO("msg")`
- `EventBus` just to add event use `EVENT_BUS_ADD_EVENT(Event)`

##### Vendor note
Dependencies are forked and have minor modifications to use precompiled headers in `imgui` and `glad`. 
All modified files included in the project and managed by MSBuild.
