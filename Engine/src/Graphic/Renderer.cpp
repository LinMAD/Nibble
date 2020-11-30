#include "pch.h"
#include "Renderer.h"
#include "Graphic/OpenGL/GLRenderer.h"

Nibble::Renderer::Type Nibble::Renderer::s_RendererType = Nibble::Renderer::Type::OpenGL;

std::unique_ptr<Nibble::Renderer> Nibble::Renderer::s_RendererImpl = std::make_unique<Nibble::GLRenderer>();
