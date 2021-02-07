#pragma once

#include <bitset>

#include "Component.hpp"

namespace Iris
{
    using EntityId = std::uint32_t;
    const EntityId MAX_ENTITIES = 5000;
    using Signature = std::bitset<MAX_COMPONENTS>;
}