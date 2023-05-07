// this file was automatically generated and should not be edited

/*
	Nazara Engine - Core module

	Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#pragma once

#ifndef NAZARA_GLOBAL_CORE_HPP
#define NAZARA_GLOBAL_CORE_HPP

#include <Nazara/Core/AbstractHash.hpp>
#include <Nazara/Core/AbstractLogger.hpp>
#include <Nazara/Core/Algorithm.hpp>
#include <Nazara/Core/AppFilesystemComponent.hpp>
#include <Nazara/Core/Application.hpp>
#include <Nazara/Core/ApplicationBase.hpp>
#include <Nazara/Core/ApplicationComponent.hpp>
#include <Nazara/Core/ApplicationComponentRegistry.hpp>
#include <Nazara/Core/ApplicationUpdater.hpp>
#include <Nazara/Core/ByteArray.hpp>
#include <Nazara/Core/ByteArrayPool.hpp>
#include <Nazara/Core/ByteStream.hpp>
#include <Nazara/Core/Clock.hpp>
#include <Nazara/Core/Color.hpp>
#include <Nazara/Core/Config.hpp>
#include <Nazara/Core/Core.hpp>
#include <Nazara/Core/DynLib.hpp>
#include <Nazara/Core/EmptyStream.hpp>
#include <Nazara/Core/EntityWorld.hpp>
#include <Nazara/Core/Enums.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Core/ErrorFlags.hpp>
#include <Nazara/Core/File.hpp>
#include <Nazara/Core/FileLogger.hpp>
#include <Nazara/Core/Functor.hpp>
#include <Nazara/Core/GuillotineBinPack.hpp>
#include <Nazara/Core/HandledObject.hpp>
#include <Nazara/Core/HardwareInfo.hpp>
#include <Nazara/Core/Initializer.hpp>
#include <Nazara/Core/Log.hpp>
#include <Nazara/Core/MemoryStream.hpp>
#include <Nazara/Core/MemoryView.hpp>
#include <Nazara/Core/ModuleBase.hpp>
#include <Nazara/Core/Modules.hpp>
#include <Nazara/Core/ObjectHandle.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/OwnedMemoryStream.hpp>
#include <Nazara/Core/ParameterList.hpp>
#include <Nazara/Core/Plugin.hpp>
#include <Nazara/Core/PluginInterface.hpp>
#include <Nazara/Core/PluginLoader.hpp>
#include <Nazara/Core/PoolByteStream.hpp>
#include <Nazara/Core/Primitive.hpp>
#include <Nazara/Core/PrimitiveList.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/Resource.hpp>
#include <Nazara/Core/ResourceLoader.hpp>
#include <Nazara/Core/ResourceManager.hpp>
#include <Nazara/Core/ResourceParameters.hpp>
#include <Nazara/Core/ResourceRegistry.hpp>
#include <Nazara/Core/ResourceSaver.hpp>
#include <Nazara/Core/SerializationContext.hpp>
#include <Nazara/Core/State.hpp>
#include <Nazara/Core/StateMachine.hpp>
#include <Nazara/Core/StdLogger.hpp>
#include <Nazara/Core/Stream.hpp>
#include <Nazara/Core/StringExt.hpp>
#include <Nazara/Core/TaskScheduler.hpp>
#include <Nazara/Core/Time.hpp>
#include <Nazara/Core/Unicode.hpp>
#include <Nazara/Core/Updatable.hpp>
#include <Nazara/Core/Uuid.hpp>
#include <Nazara/Core/VirtualDirectory.hpp>
#include <Nazara/Core/VirtualDirectoryFilesystemResolver.hpp>

#ifdef NAZARA_ENTT

#include <Nazara/Core/AppEntitySystemComponent.hpp>
#include <Nazara/Core/Components.hpp>
#include <Nazara/Core/EnttSystemGraph.hpp>
#include <Nazara/Core/EnttWorld.hpp>
#include <Nazara/Core/Systems.hpp>

#endif

#endif // NAZARA_GLOBAL_CORE_HPP
