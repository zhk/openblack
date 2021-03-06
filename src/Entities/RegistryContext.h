/*****************************************************************************
 * Copyright (c) 2018-2020 openblack developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/openblack/openblack
 *
 * openblack is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "AllMeshes.h"
#include "Graphics/DebugLines.h"

#include <bgfx/bgfx.h>
#include <entt/entity/fwd.hpp>
#include <glm/fwd.hpp>

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace openblack::entities
{
struct RenderContext
{
	RenderContext()
	    : instanceUniformBuffer(BGFX_INVALID_HANDLE) {};
	~RenderContext()
	{
		if (bgfx::isValid(instanceUniformBuffer))
		{
			bgfx::destroy(instanceUniformBuffer);
		}
	}
	std::unique_ptr<graphics::DebugLines> streams;
	std::unique_ptr<graphics::DebugLines> boundingBox;

	struct InstancedDrawDesc
	{
		InstancedDrawDesc(uint32_t offset, uint32_t count)
		    : offset(offset)
		    , count(count)
		{
		}
		uint32_t offset;
		uint32_t count;
	};

	/// A list of cpu-side uniforms which is refilled at every \ref PrepareDraw.
	/// This vector will resize to the number of instances it manages
	/// but in practice, it should only grow its reserved memory.
	/// If debug bounding boxes are enabled, it will double in size to fit all
	/// bounding boxes in the second half of the list.
	std::vector<glm::mat4> instanceUniforms;
	/// Stores information for rendering which is prepared at \ref PrepareDraw.
	std::map<MeshId, const InstancedDrawDesc> instancedDrawDescs;
	/// Not an actual vertex buffer, but a dynamic general purpose buffer which
	/// stores uniform data as a GPU-side copy of \ref _instanceUniforms and
	/// which is populated in \ref PrepareDraw and consumed in \ref DrawModels.
	/// This buffer will resize if the size of \ref _instanceUniforms exceeds
	/// its allocated size. It will never shrink.
	/// The values stored are a list of uniforms (model matrix) needed for both
	/// the instances of entities and their bounding boxes.
	bgfx::DynamicVertexBufferHandle instanceUniformBuffer;

	bool dirty {true};
	bool hasBoundingBoxes {false};
};

using TownId = int;
using StreamId = int;

struct RegistryContext
{
	RenderContext renderContext;
	std::unordered_map<StreamId, entt::entity> streams;
	std::unordered_map<TownId, entt::entity> towns;
};
} // namespace openblack::entities
