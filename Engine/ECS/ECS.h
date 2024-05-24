#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Engine/Camera/Camera.h"

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
    public: 
        Entity* entity;

        virtual void init() {};
        virtual void update() {};

        virtual ~Component() {};
};

class Entity {
    public:
        void update() {
            for(auto& c : components) c->update();
        }

        bool isActive() const {return active;}
        void destroy() {active = false;}

        template <typename T> bool hasComponent() const {
            return componentBitSet[getComponentTypeID<T>()];
        }

        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mAgrs) {
            T* c(new T(std::forward<TArgs>(mAgrs)...));
            c->entity = this;
            std::shared_ptr<Component> uPtr{ c };
            components.emplace_back(std::move(uPtr));

            componentArray[getComponentTypeID<T>()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;

            c->init();
            return *c;
        }

        template<typename T> T& getComponent() const {
            if(!hasComponent<T>()) throw std::runtime_error("Entity has no such component!");

            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }

    private:
        bool active = true;
        std::vector<std::shared_ptr<Component>> components;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
};

class Entities {
    public:
        std::vector<std::unique_ptr<Entity>> entities;
};

class System {
    public:
        virtual void update(float dt, std::vector<std::unique_ptr<Entity>>& entities) {}
        virtual void render(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities) {}
        virtual ~System() {}
};

class SystemManager {
    public:
        SystemManager(Entities& entities) : m_entities(entities) {}

        void update(float dt) {
            for(auto& s : systems) s->update(dt, m_entities.entities);
        }

        void render(Icamer2D& cam) {
            for(auto& s : systems) s->render(cam, m_entities.entities);
        }

        template<typename T, typename... TArgs>
        void addSystem(TArgs&&... mArgs) {
            T* s = new T(std::forward<TArgs>(mArgs)...);
            std::unique_ptr<System> uPtr{ s };
            systems.emplace_back(std::move(uPtr));
        }

    private:
        std::vector<std::unique_ptr<System>> systems;
        Entities& m_entities;
};

class EntityManager {
    public:
        EntityManager(Entities& entities) : m_entities(entities) {}

        void update() {
            m_entities.entities.erase(std::remove_if(std::begin(m_entities.entities), std::end(m_entities.entities), 
                [](const std::unique_ptr<Entity> &mEntity) {
                    return !mEntity->isActive();
                }), 
                std::end(m_entities.entities));
                for(auto& e : m_entities.entities) e->update();
            }
        
        Entity& addEntity() {
            Entity* e = new Entity;
            std::unique_ptr<Entity> uPtr{ e };
            m_entities.entities.emplace_back(std::move(uPtr));
            return *e;
        }

        Entities& m_entities;
    private:
};
