> Nibble

Everything starts from small and evolve to something big.
The project mirrors my passion to learn computer graphics, C++, and art with programming. More like demoscene making or "games" maybe.

The current goal of this project to create a flexible and comfortable demo scene engine to make.
Like from my Instagram *[nibble_hex](https://www.instagram.com/nibble_hex/)* ^_^

---

## First version - render result and functionality
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

##### How to build
Build system used `MSBuild`, so solution files already preconfigured you need only open it and execute solution build. 
Then you will find inside `Nibble\bin` {release/debug}-x64 prepared files.

##### Engine main loop idea
![engine_work](Extras/core_process_idea.png)

##### Singletons
- `Logger` can be accessed like `LOGGER_CLIENT_INFO("msg")`
- `EventBus` just to add event use `EVENT_BUS_ADD_EVENT(Event)`
- `Engine` allows to have one instance

##### Vendor note
Dependencies are forked and have minor modifications to use precompiled headers in `imgui` and `glad`. 
All modified files included in the project and managed by MSBuild.

##### Development work environment info
```
OS: Windows 10 Home 64-bit
CPU: Intel(R) Core(TM) i7-6700HQ CPU @ 2.60GHz (8 CPUs), ~2.6GHz
GPU 1: Intel(R) HD Graphics 530
GPU 2: NVIDIA GeForce GTX 1060
IDE: Microsoft Visual Studio Community 2019 Version 16.8
```

---

## TODO Section
![just_do_it](https://i.pinimg.com/originals/ab/28/a3/ab28a35ba61c3310ed6341b09dbbafab.jpg)

### Research more about that
- Debug support system? Or it's ok with logger and breakpoints?
- Memory system layer (Like I saw in the Snowdrop from Massive entertainment)
- Entity components system layer?
- Physics system layer?
- How to write automated tests for graphics?
- What else?

### List for refactoring to have a flexible and clean work base (Not final)
Research and refactor old codebase to have a nice structure like that list:
- ~~Entry point~~
- ~~Logger~~
- ~~Base Event bus system for user I/O~~
	- ~~Event listeners~~
	- ~~Client layer stack: Client app can create layers to work with I\O and Events~~
- Files (I/O), VFS (Virtual file system) support
- Graphic related layers
	- ~~GUI Overlay~~
	- Graphic renderer layer
		- API Abstraction for now just OpenGL but I like Linux so Vulkan could be nice to touch
		- Shaders compilation
- Engine input handlers like Arx liberatits has

---

