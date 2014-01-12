// Copyright (C) 2014 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DEFERREDFINALPASS_HPP
#define NAZARA_DEFERREDFINALPASS_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Graphics/DeferredRenderPass.hpp>
#include <Nazara/Renderer/RenderStates.hpp>
#include <Nazara/Renderer/ShaderProgram.hpp>
#include <Nazara/Renderer/TextureSampler.hpp>

class NAZARA_API NzDeferredFinalPass : public NzDeferredRenderPass
{
	public:
		NzDeferredFinalPass();
		virtual ~NzDeferredFinalPass();

		bool Process(const NzScene* scene, unsigned int firstWorkTexture, unsigned secondWorkTexture) const;

	protected:
		NzRenderStates m_states;
		NzShaderProgramRef m_program;
		NzTextureSampler m_pointSampler;
};

#endif // NAZARA_DEFERREDFINALPASS_HPP
