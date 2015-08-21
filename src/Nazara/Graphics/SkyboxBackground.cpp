// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Graphics/SkyboxBackground.hpp>
#include <Nazara/Core/ErrorFlags.hpp>
#include <Nazara/Graphics/AbstractViewer.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <Nazara/Utility/IndexBuffer.hpp>
#include <Nazara/Utility/VertexBuffer.hpp>
#include <Nazara/Utility/VertexDeclaration.hpp>
#include <memory>
#include <Nazara/Graphics/Debug.hpp>

namespace
{
	static NzIndexBufferRef s_indexBuffer;
	static NzRenderStates s_renderStates;
	static NzShaderRef s_shader;
	static NzVertexBufferRef s_vertexBuffer;
}

NzSkyboxBackground::NzSkyboxBackground(NzTextureRef cubemapTexture)
{
	m_sampler.SetWrapMode(nzSamplerWrap_Clamp); // Nécessaire pour ne pas voir les côtés

	SetTexture(std::move(cubemapTexture));
}

void NzSkyboxBackground::Draw(const NzAbstractViewer* viewer) const
{
	NzMatrix4f skyboxMatrix(viewer->GetViewMatrix());
	skyboxMatrix.SetTranslation(NzVector3f::Zero());

	NzRenderer::SetIndexBuffer(s_indexBuffer);
	NzRenderer::SetMatrix(nzMatrixType_View, skyboxMatrix);
	NzRenderer::SetMatrix(nzMatrixType_World, NzMatrix4f::Scale(NzVector3f(viewer->GetZNear())));
	NzRenderer::SetRenderStates(s_renderStates);
	NzRenderer::SetShader(s_shader);
	NzRenderer::SetTexture(0, m_texture);
	NzRenderer::SetTextureSampler(0, m_sampler);
	NzRenderer::SetVertexBuffer(s_vertexBuffer);

	NzRenderer::DrawIndexedPrimitives(nzPrimitiveMode_TriangleList, 0, 36);

	NzRenderer::SetMatrix(nzMatrixType_View, viewer->GetViewMatrix());
}

nzBackgroundType NzSkyboxBackground::GetBackgroundType() const
{
	return nzBackgroundType_Skybox;
}

bool NzSkyboxBackground::Initialize()
{
	const nzUInt16 indices[6*6] =
	{
		0, 1, 2, 0, 2, 3,
		3, 2, 6, 3, 6, 7,
		7, 6, 5, 7, 5, 4,
		4, 5, 1, 4, 1, 0,
		0, 3, 7, 0, 7, 4,
		1, 6, 2, 1, 5, 6
	};

	const float vertices[8 * 3 * sizeof(float)] =
	{
		-1.0,  1.0,  1.0,
		-1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,
		 1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
	};

	///TODO: Replace by ShaderNode (probably after Vulkan)
	const char* fragmentShaderSource =
	"#version 140\n"

	"in vec3 vTexCoord;\n"

	"out vec4 RenderTarget0;\n"

	"uniform samplerCube Skybox;\n"
	"uniform float VertexDepth;\n"

	"void main()\n"
	"{\n"
	"	RenderTarget0 = texture(Skybox, vTexCoord);\n"
	"	gl_FragDepth = VertexDepth;\n"
	"}\n";

	const char* vertexShaderSource =
	"#version 140\n"

	"in vec3 VertexPosition;\n"

	"out vec3 vTexCoord;\n"

	"uniform mat4 WorldViewProjMatrix;\n"

	"void main()\n"
	"{\n"
	"    vec4 WVPVertex = WorldViewProjMatrix * vec4(VertexPosition, 1.0);\n"
	"    gl_Position = WVPVertex.xyww;\n"
	"    vTexCoord = vec3(VertexPosition.x, VertexPosition.y, -VertexPosition.z);\n"
	"}\n";

	try
	{
		NzErrorFlags flags(nzErrorFlag_ThrowException, true);

		// Index buffer
		NzIndexBufferRef indexBuffer = NzIndexBuffer::New(false, 36, nzDataStorage_Hardware, nzBufferUsage_Static);
		indexBuffer->Fill(indices, 0, 36);

		// Vertex buffer
		NzVertexBufferRef vertexBuffer = NzVertexBuffer::New(NzVertexDeclaration::Get(nzVertexLayout_XYZ), 8, nzDataStorage_Hardware, nzBufferUsage_Static);
		vertexBuffer->Fill(vertices, 0, 8);

		// Shader
		NzShaderRef shader = NzShader::New();
		shader->Create();
		shader->AttachStageFromSource(nzShaderStage_Fragment, fragmentShaderSource);
		shader->AttachStageFromSource(nzShaderStage_Vertex, vertexShaderSource);
		shader->Link();

		shader->SendInteger(shader->GetUniformLocation("Skybox"), 0);
		shader->SendFloat(shader->GetUniformLocation("VertexDepth"), 1.f);

		// Renderstates
		s_renderStates.depthFunc = nzRendererComparison_Equal;
		s_renderStates.faceCulling = nzFaceSide_Front;
		s_renderStates.parameters[nzRendererParameter_DepthBuffer] = true;
		s_renderStates.parameters[nzRendererParameter_DepthWrite] = false;
		s_renderStates.parameters[nzRendererParameter_FaceCulling] = true;

		// Exception-free zone
		s_indexBuffer = std::move(indexBuffer);
		s_shader = std::move(shader);
		s_vertexBuffer = std::move(vertexBuffer);
	}
	catch (const std::exception& e)
	{
		NazaraError("Failed to initialise: " + NzString(e.what()));
		return false;
	}

	return true;
}

void NzSkyboxBackground::Uninitialize()
{
	s_indexBuffer.Reset();
	s_shader.Reset();
	s_vertexBuffer.Reset();
}
