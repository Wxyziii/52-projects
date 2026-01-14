# Week 41: Plugin System

## Project Overview
Implement a dynamic plugin system that allows loading and unloading of functionality at runtime.

## Learning Objectives
- Dynamic library loading
- Symbol resolution
- Plugin interface design
- Version management
- ABI compatibility
- Hot-swapping plugins

## Features to Implement
- [ ] Plugin interface definition
- [ ] Dynamic library loading (.dll/.so)
- [ ] Plugin discovery and enumeration
- [ ] Load/unload at runtime
- [ ] Version checking
- [ ] Dependency resolution
- [ ] Plugin metadata
- [ ] Sandbox/isolation (optional)
- [ ] Plugin communication API
- [ ] Hot-reload support

## Plugin Interface
```cpp
// plugin_interface.h
#define PLUGIN_API_VERSION 1

class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual const char* getName() const = 0;
    virtual const char* getVersion() const = 0;
    virtual int getAPIVersion() const = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual void execute() = 0;
};

// Plugin export macros
#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
    EXPORT IPlugin* createPlugin();
    EXPORT void destroyPlugin(IPlugin* plugin);
}
```

## Plugin Implementation
```cpp
// my_plugin.cpp
class MyPlugin : public IPlugin {
public:
    const char* getName() const override {
        return "MyPlugin";
    }
    
    const char* getVersion() const override {
        return "1.0.0";
    }
    
    int getAPIVersion() const override {
        return PLUGIN_API_VERSION;
    }
    
    bool initialize() override {
        std::cout << "Plugin initialized!\n";
        return true;
    }
    
    void execute() override {
        std::cout << "Plugin executing...\n";
    }
    
    void shutdown() override {
        std::cout << "Plugin shutdown\n";
    }
};

extern "C" {
    EXPORT IPlugin* createPlugin() {
        return new MyPlugin();
    }
    
    EXPORT void destroyPlugin(IPlugin* plugin) {
        delete plugin;
    }
}
```

## Plugin Manager
```cpp
class PluginManager {
public:
    bool loadPlugin(const std::string& path) {
        void* handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) return false;
        
        auto createFunc = (IPlugin*(*)())
            dlsym(handle, "createPlugin");
        auto destroyFunc = (void(*)(IPlugin*))
            dlsym(handle, "destroyPlugin");
            
        IPlugin* plugin = createFunc();
        
        if (plugin->getAPIVersion() != PLUGIN_API_VERSION) {
            destroyFunc(plugin);
            dlclose(handle);
            return false;
        }
        
        plugin->initialize();
        plugins_[plugin->getName()] = {
            handle, plugin, destroyFunc
        };
        
        return true;
    }
    
    void unloadPlugin(const std::string& name) {
        auto it = plugins_.find(name);
        if (it != plugins_.end()) {
            it->second.plugin->shutdown();
            it->second.destroyFunc(it->second.plugin);
            dlclose(it->second.handle);
            plugins_.erase(it);
        }
    }
    
    IPlugin* getPlugin(const std::string& name) {
        auto it = plugins_.find(name);
        return it != plugins_.end() ? 
               it->second.plugin : nullptr;
    }
    
private:
    struct PluginInfo {
        void* handle;
        IPlugin* plugin;
        void(*destroyFunc)(IPlugin*);
    };
    
    std::map<std::string, PluginInfo> plugins_;
};
```

## Key Concepts
- dlopen/LoadLibrary for dynamic loading
- dlsym/GetProcAddress for symbol lookup
- Plugin discovery (scanning directories)
- Version compatibility
- ABI stability
- RAII for automatic cleanup
- Function pointers and vtables

## Extensions
- Add plugin dependencies
- Implement plugin signing
- Create plugin marketplace
- Add sandbox security
- Implement plugin updates
- Create scripting bindings
- Add plugin communication bus
- Implement plugin priorities
