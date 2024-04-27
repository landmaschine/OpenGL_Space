#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

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
        virtual void update(float dt) {};
        virtual void draw() {};

        virtual ~Component() {};
};

class Entity {
    public:
        void update(float dt) {
            for(auto& c : components) c->update(dt);
        }

        void draw() {
            for(auto& c : components) c->draw();
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

class Manager {
    public:
        void draw() { for(auto& e : entities) e->draw(); }

        void update(float dt) {
            entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
                [](const std::unique_ptr<Entity> &mEntity) {
                    return !mEntity->isActive();
                }), 
                std::end(entities));

                for(auto& e : entities) e->update(dt);
            }
        
        Entity& addEntity() {
            Entity* e = new Entity;
            std::unique_ptr<Entity> uPtr{ e };
            entities.emplace_back(std::move(uPtr));
            return *e;
        }
        
    private:
        std::vector<std::unique_ptr<Entity>> entities;
};