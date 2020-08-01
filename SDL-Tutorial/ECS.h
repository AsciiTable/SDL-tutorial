#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

/**Basically, he's got a Manager which holds entities, which are anything drawn in your game.
Each entity has components, which give it functionality. 
Each component has it's own class, so templates and other fancy stuff are required in order to get and add components.
You can implement this same system in a simpler way yourself if the video confuses you, it'll help you understand.
Templates Tutorial video: https://www.youtube.com/watch?v=I-hZkUa9mIs&feature=youtu.be 
ECS Bad, What to use instead: https://www.youtube.com/watch?v=JxI3Eu5DPwE */

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID() { // Review Tutorial #7 @ 2:27
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept {
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>; // checks for components
using ComponentArray = std::array<Component*, maxComponents>; // array of component pointers

class Component {
public:
	Entity* entity;
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual ~Component() {}
};

class Entity {
public:
	void Update() {
		for (auto& c : components)
			c->Update();
	}
	void Draw() {
		for (auto& c : components)
			c->Draw();
	}
	bool IsActive() const {
		return active;
	}
	void Destroy() {
		active = false;
	}
	template <typename T> bool HasComponent() const {
		return componentBitSet[GetComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init(); 
		return *c;
	}
	template<typename T> T& GetComponent() const {
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};

class Manager {
public:
	void Update() {
		for (auto& e : entities)
			e->Update();
	}
	void Draw() {
		for (auto& e : entities)
			e->Draw();
	}
	void Refresh() { // removes entity if it's not active
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity) {
			return !mEntity->IsActive();
		}),std::end(entities));
	}

	Entity& AddEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
private:
	std::vector<std::unique_ptr<Entity>> entities;
};

