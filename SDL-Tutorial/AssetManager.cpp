#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) {
	manager = man;
}

AssetManager::~AssetManager() {
}

void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

void AssetManager::CreateProjectile(Vector2D pos, int range, Vector2D vel, float speed, std::string id) {
	auto& projectile(manager->AddEntity());
	projectile.AddComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.AddComponent<SpriteComponent>(id, false);
	projectile.AddComponent<ProjectileComponent>(range, speed, vel);
	projectile.AddComponent<ColliderComponent>("projectile");
	projectile.AddGroup(Game::groupProjectiles);

}