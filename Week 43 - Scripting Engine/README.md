# Week 43: Scripting Engine

## Project Overview
Embed a scripting language (Lua, Python, or custom) into a C++ application for runtime extensibility.

## Learning Objectives
- Script language integration
- C++ to script bindings
- Script execution and sandboxing
- Error handling across boundaries
- Performance considerations
- Resource management

## Features to Implement
- [ ] Lua/Python interpreter embedding
- [ ] C++ function exposure to scripts
- [ ] Script function calling from C++
- [ ] Variable sharing (bidirectional)
- [ ] Script loading and execution
- [ ] Error handling and reporting
- [ ] Sandbox/security restrictions
- [ ] Hot-reloading scripts
- [ ] Debugging support
- [ ] Performance profiling

## Lua Integration Example
```cpp
class ScriptEngine {
    lua_State* L;
    
public:
    ScriptEngine() {
        L = luaL_newstate();
        luaL_openlibs(L);
        registerFunctions();
    }
    
    void registerFunctions() {
        // Expose C++ function to Lua
        lua_register(L, "print_cpp", [](lua_State* L) {
            const char* msg = lua_tostring(L, 1);
            std::cout << "C++: " << msg << std::endl;
            return 0;
        });
    }
    
    void executeFile(const std::string& path) {
        if (luaL_dofile(L, path.c_str()) != LUA_OK) {
            std::cerr << "Error: " 
                     << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
        }
    }
    
    void executeString(const std::string& code) {
        if (luaL_dostring(L, code.c_str()) != LUA_OK) {
            handleError();
        }
    }
    
    template<typename T>
    T getGlobal(const std::string& name) {
        lua_getglobal(L, name.c_str());
        T value = lua_to<T>(L, -1);
        lua_pop(L, 1);
        return value;
    }
    
    template<typename... Args>
    void callFunction(const std::string& name, 
                     Args... args) {
        lua_getglobal(L, name.c_str());
        pushArgs(args...);
        lua_call(L, sizeof...(args), 0);
    }
};
```

## Script Example (Lua)
```lua
-- game_logic.lua
player = {
    x = 0,
    y = 0,
    health = 100
}

function update(deltaTime)
    player.x = player.x + 1
    print_cpp("Player moved to: " .. player.x)
end

function onDamage(amount)
    player.health = player.health - amount
    if player.health <= 0 then
        print_cpp("Game Over!")
        return true
    end
    return false
end
```

## C++ Usage
```cpp
int main() {
    ScriptEngine engine;
    
    // Load script
    engine.executeFile("game_logic.lua");
    
    // Call Lua function
    engine.callFunction("update", 0.016);
    
    // Get Lua variable
    int health = engine.getGlobal<int>("player.health");
    
    // Call with return value
    bool gameOver = engine.callFunction<bool>(
        "onDamage", 50);
    
    return 0;
}
```

## Key Concepts
- Foreign Function Interface (FFI)
- Stack-based VM interaction
- Type marshalling
- Garbage collection integration
- Error handling across boundaries
- Resource lifetime management
- Sandboxing and security

## Extensions
- Add script debugging interface
- Implement coroutines
- Create visual script editor
- Add JIT compilation
- Implement script profiler
- Create custom DSL
- Add script versioning
- Implement script signing
