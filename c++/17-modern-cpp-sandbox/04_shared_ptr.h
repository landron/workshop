#pragma once

// Simple demo of shared_ptr/weak_ptr interactions.
// The weak reference counter is illustrative only and not a true std::weak_ptr lifetime counter.

#include <map>
#include <memory>
#include <string_view>

#include "gtest/gtest.h"

// A minimal Tile object with an illustrative weak reference counter.
class Tile final {
public:
    enum class Type { Grass, Water, Mountain };

    Tile(Type type) noexcept : type(type), weak_count(0) {}
    ~Tile() noexcept {
        // std::println("Destroying Tile(type={}, weak_count={})", to_string(type), weak_count);
    }

    // Demonstration-only weak reference tracking.
    // This count is incremented on requests, not by actual std::weak_ptr lifetime.
    // A proper solution would wrap std::weak_ptr and update counts when objects copy/move/destroy.
    void inc_weak_reference() noexcept {
        ++weak_count;
    }
    bool dec_weak_reference() noexcept {
        if (weak_count > 0) {
            --weak_count;
            return true;
        }
        return false;
    }

    [[nodiscard]] size_t get_weak_count() const noexcept {
        return weak_count;
    }

    static constexpr std::string_view to_string(Type t) noexcept {
        switch (t) {
            case Type::Grass: return "Grass";
            case Type::Water: return "Water";
            case Type::Mountain: return "Mountain";
            default: return "Unknown";
        }
    }

private:
    const Type type;
    size_t weak_count;
};

// Registry caches shared Tile instances and returns weak_ptr handles to them.
class Registry final {
public:
    // "Rule of Zero"
    // Registry() = default;
    // ~Registry() = default;

    [[nodiscard]] std::weak_ptr<Tile> get_tile(size_t x, size_t y) {
        auto key = std::pair{x, y};
        auto it = std::as_const(tiles).find(key);
        if (it != tiles.end()) {
            it->second->inc_weak_reference();
            return it->second;
        }
        // For demonstration, we create a new tile based on coordinates
        auto type = static_cast<Tile::Type>((x + y) % 3); // Just a simple way to assign types
        auto tile = std::make_shared<Tile>(type);
        tile->inc_weak_reference();
        tiles[key] = tile;
        return tile;
    }

private:
    std::map<std::pair<size_t, size_t>, std::shared_ptr<Tile>> tiles;
};

// A Layer holds weak references to tiles and releases them when the layer is destroyed.
class Layer final {
public:
    enum class Type { Weather, Navigation, Terrain };

    Layer(Type type, Registry& registry) noexcept 
        : type(type), registry(registry) {}
    ~Layer() noexcept {
        for (const auto& [key, tile] : tiles) {
            auto ptr = tile.lock();
            if (ptr) {
                ptr->dec_weak_reference();
            }
        }
    }

    void load_tile(size_t x, size_t y) {
        auto key = std::pair{x, y};
        if (!tiles.contains(key)) {
            tiles.emplace(key, registry.get_tile(x, y));
        }
    }

private:
    const Type type;
    Registry& registry;

    std::map<std::pair<size_t, size_t>, std::weak_ptr<Tile>> tiles;
};

TEST(SharedPtrTest, GetTileReturnsValidWeakPtr) {
    Registry registry;
    auto first_weak = registry.get_tile(1, 2);
    auto first_shared = first_weak.lock();

    EXPECT_TRUE(static_cast<bool>(first_shared));
    EXPECT_EQ(first_shared.get(), registry.get_tile(1, 2).lock().get());
}

TEST(SharedPtrTest, DifferentCoordsReturnDifferentTiles) {
    Registry registry;
    auto tile_a = registry.get_tile(0, 0).lock();
    auto tile_b = registry.get_tile(1, 0).lock();

    EXPECT_TRUE(static_cast<bool>(tile_a));
    EXPECT_TRUE(static_cast<bool>(tile_b));
    EXPECT_NE(tile_a.get(), tile_b.get());
}

TEST(SharedPtrTest, WeakCountTracksRequests) {
    Registry registry;
    auto tile = registry.get_tile(3, 4).lock();

    ASSERT_TRUE(static_cast<bool>(tile));
    EXPECT_EQ(tile->get_weak_count(), 1u);

    registry.get_tile(3, 4);
    EXPECT_EQ(tile->get_weak_count(), 2u);
}

TEST(SharedPtrTest, RealUse) {
    auto registry = std::make_unique<Registry>();
    auto terrain = std::make_unique<Layer>(Layer::Type::Terrain, *registry);
    auto weather = std::make_unique<Layer>(Layer::Type::Weather, *registry);
    auto nav = std::make_unique<Layer>(Layer::Type::Navigation, *registry);

    terrain->load_tile(25, 24);
    weather->load_tile(25, 24);
    nav->load_tile(25, 24);

    auto tile = registry->get_tile(25, 24);
    EXPECT_EQ(tile.lock()->get_weak_count(), 4u) << "Three layers (+get_tile) have requested the tile";
    EXPECT_EQ(tile.use_count(), 1) << "Only the registry holds a shared_ptr to the tile";

    weather.reset();
    nav.reset();
    EXPECT_EQ(tile.lock()->get_weak_count(), 2u) << "Only the terrain layer and get_tile";
    EXPECT_EQ(tile.use_count(), 1) << "Only the registry holds a shared_ptr to the tile";

    registry.reset();
    ASSERT_EQ(tile.use_count(), 0);
    ASSERT_TRUE(tile.expired());
}
