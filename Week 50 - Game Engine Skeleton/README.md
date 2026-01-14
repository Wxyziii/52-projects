# Week 50: Game Engine Skeleton

## Project Overview
Build a basic game engine framework with Entity Component System (ECS), rendering, physics, and input handling.

## Learning Objectives
- Game engine architecture
- Entity Component System (ECS)
- Rendering pipeline
- Physics simulation
- Input handling
- Resource management
- Scene graph

## Features to Implement
- [ ] Entity Component System (ECS)
- [ ] 2D/3D rendering (OpenGL/DirectX)
- [ ] Scene management
- [ ] Camera system
- [ ] Input handling (keyboard, mouse, gamepad)
- [ ] Physics engine integration
- [ ] Audio system
- [ ] Resource manager (textures, models, sounds)
- [ ] Animation system
- [ ] Particle system
- [ ] Scripting integration
- [ ] Level editor (optional)

## Architecture
```
┌─────────────────────────────────────┐
│         Game Engine                 │
├─────────────────────────────────────┤
│ Application Layer                   │
│ - Game Loop                         │
│ - Scene Manager                     │
├─────────────────────────────────────┤
│ Core Systems                        │
│ - ECS                              │
│ - Resource Manager                  │
│ - Input Manager                     │
│ - Time Manager                      │
├─────────────────────────────────────┤
│ Rendering                           │
│ - Renderer                          │
│ - Shader Manager                    │
│ - Camera                            │
├─────────────────────────────────────┤
│ Physics                             │
│ - Collision Detection               │
│ - Rigid Body Dynamics               │
├─────────────────────────────────────┤
│ Audio                               │
│ - Sound Manager                     │
│ - 3D Audio                          │
├─────────────────────────────────────┤
│ Platform Layer                      │
│ - Window Management                 │
│ - Graphics API (OpenGL/DX)          │
└─────────────────────────────────────┘
```

## ECS Implementation
```cpp
// Entity Component System
class Entity {
    uint32_t id_;
    std::bitset<64> componentMask_;
public:
    uint32_t getId() const { return id_; }
    
    template<typename T>
    bool hasComponent() const {
        return componentMask_[ComponentType<T>::id];
    }
};

class World {
    std::vector<Entity> entities_;
    ComponentManager componentManager_;
    SystemManager systemManager_;
    
public:
    Entity createEntity() {
        Entity entity;
        entity.id_ = nextEntityId_++;
        entities_.push_back(entity);
        return entity;
    }
    
    template<typename T, typename... Args>
    void addComponent(Entity& entity, Args&&... args) {
        componentManager_.add<T>(
            entity.getId(), 
            std::forward<Args>(args)...);
        entity.componentMask_[ComponentType<T>::id] = true;
    }
    
    template<typename T>
    T* getComponent(Entity& entity) {
        return componentManager_.get<T>(entity.getId());
    }
    
    void update(float deltaTime) {
        systemManager_.update(deltaTime);
    }
};

// Components
struct Transform {
    glm::vec3 position{0.0f};
    glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 scale{1.0f};
};

struct MeshRenderer {
    Mesh* mesh;
    Material* material;
};

struct RigidBody {
    glm::vec3 velocity{0.0f};
    glm::vec3 acceleration{0.0f};
    float mass = 1.0f;
};

// Systems
class RenderSystem : public System {
public:
    void update(float deltaTime) override {
        auto view = world_->view<Transform, MeshRenderer>();
        
        for (auto entity : view) {
            auto* transform = 
                world_->getComponent<Transform>(entity);
            auto* renderer = 
                world_->getComponent<MeshRenderer>(entity);
            
            drawMesh(renderer->mesh, 
                    renderer->material, 
                    transform);
        }
    }
};

class PhysicsSystem : public System {
public:
    void update(float deltaTime) override {
        auto view = world_->view<Transform, RigidBody>();
        
        for (auto entity : view) {
            auto* transform = 
                world_->getComponent<Transform>(entity);
            auto* body = 
                world_->getComponent<RigidBody>(entity);
            
            // Apply physics
            body->velocity += body->acceleration * deltaTime;
            transform->position += body->velocity * deltaTime;
        }
    }
};
```

## Game Loop
```cpp
class GameEngine {
    Window window_;
    Renderer renderer_;
    World world_;
    float fixedTimeStep_ = 1.0f / 60.0f;
    
public:
    void run() {
        initialize();
        
        float accumulator = 0.0f;
        auto lastTime = std::chrono::high_resolution_clock::now();
        
        while (window_.isOpen()) {
            auto currentTime = 
                std::chrono::high_resolution_clock::now();
            float deltaTime = 
                std::chrono::duration<float>(
                    currentTime - lastTime).count();
            lastTime = currentTime;
            
            accumulator += deltaTime;
            
            // Process input
            processInput();
            
            // Fixed timestep updates (physics)
            while (accumulator >= fixedTimeStep_) {
                fixedUpdate(fixedTimeStep_);
                accumulator -= fixedTimeStep_;
            }
            
            // Variable timestep update (rendering)
            update(deltaTime);
            
            // Render
            render();
        }
        
        shutdown();
    }
    
    void fixedUpdate(float deltaTime) {
        world_.getSystem<PhysicsSystem>()->update(deltaTime);
    }
    
    void update(float deltaTime) {
        world_.update(deltaTime);
    }
    
    void render() {
        renderer_.clear();
        world_.getSystem<RenderSystem>()->update(0.0f);
        renderer_.present();
    }
};
```

## Example Game
```cpp
class MyGame : public GameEngine {
public:
    void initialize() override {
        // Create player entity
        auto player = world_.createEntity();
        world_.addComponent<Transform>(player);
        world_.addComponent<MeshRenderer>(player,
            resources_.getMesh("player.obj"),
            resources_.getMaterial("player_mat"));
        world_.addComponent<RigidBody>(player);
        world_.addComponent<PlayerController>(player);
        
        // Create camera
        auto camera = world_.createEntity();
        world_.addComponent<Transform>(camera,
            glm::vec3(0, 5, -10));
        world_.addComponent<Camera>(camera);
        
        // Add systems
        world_.addSystem<PhysicsSystem>();
        world_.addSystem<RenderSystem>();
        world_.addSystem<InputSystem>();
    }
};
```

## Key Concepts
- Entity Component System pattern
- Data-oriented design
- Game loop architecture
- Fixed timestep vs variable timestep
- Scene graph traversal
- Resource management
- OpenGL/DirectX rendering
- Event system

## Extensions
- Add networking (multiplayer)
- Implement spatial partitioning
- Create visual scripting
- Add post-processing effects
- Implement LOD system
- Create asset pipeline
- Add VR support
- Implement save/load system
