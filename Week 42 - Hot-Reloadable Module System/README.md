# Week 42: Hot-Reloadable Module System

## Project Overview
Build a system that allows code modules to be reloaded at runtime without restarting the application.

## Learning Objectives
- File watching for changes
- Module state preservation
- Safe code reloading
- Minimize downtime
- Handle reload failures
- Transaction-like updates

## Features to Implement
- [ ] Watch module files for changes
- [ ] Unload old module version
- [ ] Load new module version
- [ ] Preserve state between reloads
- [ ] Rollback on failure
- [ ] Incremental reloading
- [ ] Dependency tracking
- [ ] API versioning
- [ ] Debug symbol reloading
- [ ] Minimal service disruption

## Usage Example
```cpp
HotReloadSystem reloader;

// Register module for hot-reload
reloader.registerModule("game_logic.dll", []() {
    // State preservation callback
    return saveGameState();
}, [](const State& state) {
    // State restoration callback
    restoreGameState(state);
});

// Start watching
reloader.startWatching();

// Manual reload
reloader.reloadModule("game_logic");
```

## File Watcher Integration
```cpp
class HotReloadSystem {
public:
    void startWatching() {
        watcher_.addWatch(modulePath_, 
                         FileWatcher::MODIFY);
        
        watcher_.setCallback([this](const FileEvent& event) {
            if (event.type == FileEvent::MODIFIED) {
                scheduleReload(event.path);
            }
        });
    }
    
    bool reloadModule(const std::string& name) {
        auto it = modules_.find(name);
        if (it == modules_.end()) return false;
        
        // Save state
        auto state = it->second.saveState();
        
        // Unload old version
        unloadModule(name);
        
        // Load new version
        if (!loadModule(name)) {
            // Rollback: reload old version
            loadModuleVersion(name, it->second.version);
            return false;
        }
        
        // Restore state
        it->second.restoreState(state);
        
        return true;
    }
    
private:
    void scheduleReload(const std::string& path) {
        // Debounce: wait for file to stabilize
        std::this_thread::sleep_for(
            std::chrono::milliseconds(100));
        reloadModule(pathToModuleName(path));
    }
};
```

## Module Interface
```cpp
class IReloadableModule {
public:
    virtual ~IReloadableModule() = default;
    
    // Called before unload
    virtual void* saveState() = 0;
    
    // Called after load
    virtual void restoreState(void* state) = 0;
    
    // Version for compatibility checking
    virtual int getVersion() const = 0;
};

// Example module
class GameLogic : public IReloadableModule {
    struct State {
        int score;
        std::vector<Entity> entities;
    };
    
    void* saveState() override {
        auto* state = new State{score_, entities_};
        return state;
    }
    
    void restoreState(void* data) override {
        auto* state = static_cast<State*>(data);
        score_ = state->score;
        entities_ = state->entities;
        delete state;
    }
    
private:
    int score_;
    std::vector<Entity> entities_;
};
```

## Build Integration
```cmake
# CMakeLists.txt for hot-reloadable module
add_library(game_logic SHARED game_logic.cpp)

# Set output directory for easy watching
set_target_properties(game_logic PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/modules"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/modules"
)

# Enable debug symbols for hot-reload
target_compile_options(game_logic PRIVATE
    $<$<CONFIG:Debug>:-g>
)
```

## Key Concepts
- File system watching
- Dynamic library versioning
- State serialization
- Memory management during reload
- Transaction-like reload process
- Graceful degradation on failure
- Symbol collision prevention

## Extensions
- Add dependency graph tracking
- Implement partial reloads
- Create module migration system
- Add reload testing framework
- Implement reload hooks
- Create distributed hot-reload
- Add rollback history
- Implement A/B module testing
