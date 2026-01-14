# Week 44: Dependency Injection Container

## Project Overview
Implement an Inversion of Control (IoC) container for managing dependencies and object lifetimes.

## Learning Objectives
- Dependency Injection patterns
- Service locator pattern
- Lifetime management (singleton, transient, scoped)
- Automatic dependency resolution
- Interface-based programming
- RAII and smart pointers

## Features to Implement
- [ ] Service registration
- [ ] Dependency resolution
- [ ] Constructor injection
- [ ] Property/setter injection
- [ ] Lifetime management (singleton, transient, scoped)
- [ ] Circular dependency detection
- [ ] Factory registration
- [ ] Named registrations
- [ ] Decoration/interception
- [ ] Container hierarchies

## API Design
```cpp
class DIContainer {
public:
    // Register types
    template<typename Interface, typename Implementation>
    void registerSingleton() {
        registrations_[typeid(Interface)] = {
            []() { return new Implementation(); },
            Lifetime::Singleton,
            nullptr
        };
    }
    
    template<typename Interface, typename Implementation>
    void registerTransient() {
        registrations_[typeid(Interface)] = {
            []() { return new Implementation(); },
            Lifetime::Transient,
            nullptr
        };
    }
    
    // Register factory
    template<typename T>
    void registerFactory(
        std::function<T*()> factory) {
        registrations_[typeid(T)] = {
            factory, Lifetime::Singleton, nullptr
        };
    }
    
    // Resolve dependencies
    template<typename T>
    T* resolve() {
        auto& reg = registrations_[typeid(T)];
        
        if (reg.lifetime == Lifetime::Singleton) {
            if (!reg.instance) {
                reg.instance = reg.factory();
            }
            return static_cast<T*>(reg.instance);
        }
        
        return static_cast<T*>(reg.factory());
    }
    
private:
    enum class Lifetime { Singleton, Transient, Scoped };
    
    struct Registration {
        std::function<void*()> factory;
        Lifetime lifetime;
        void* instance;
    };
    
    std::map<std::type_index, Registration> 
        registrations_;
};
```

## Usage Example
```cpp
// Interfaces
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& msg) = 0;
};

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual void connect() = 0;
};

// Implementations
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& msg) override {
        std::cout << msg << std::endl;
    }
};

class PostgresDB : public IDatabase {
    ILogger* logger_;
public:
    PostgresDB(ILogger* logger) : logger_(logger) {}
    
    void connect() override {
        logger_->log("Connecting to PostgreSQL...");
    }
};

// Service with dependencies
class UserService {
    IDatabase* db_;
    ILogger* logger_;
    
public:
    UserService(IDatabase* db, ILogger* logger)
        : db_(db), logger_(logger) {}
    
    void createUser(const std::string& name) {
        logger_->log("Creating user: " + name);
        db_->connect();
    }
};

// Setup container
int main() {
    DIContainer container;
    
    // Register services
    container.registerSingleton<ILogger, ConsoleLogger>();
    container.registerSingleton<IDatabase, PostgresDB>();
    container.registerTransient<UserService>();
    
    // Resolve with automatic dependency injection
    auto* service = container.resolve<UserService>();
    service->createUser("Alice");
    
    return 0;
}
```

## Advanced Features
```cpp
// Named registrations
container.register<ILogger>("file", []() {
    return new FileLogger("app.log");
});

container.register<ILogger>("console", []() {
    return new ConsoleLogger();
});

// Resolve by name
auto* logger = container.resolve<ILogger>("file");

// Scoped lifetime
{
    auto scope = container.createScope();
    auto* service = scope.resolve<UserService>();
    // service destroyed when scope ends
}

// Decorator pattern
container.decorate<ILogger>([](ILogger* inner) {
    return new TimestampLogger(inner);
});
```

## Key Concepts
- Inversion of Control (IoC)
- Dependency Inversion Principle
- Service locator pattern
- Factory pattern
- RAII for lifetime management
- Type erasure
- Smart pointers for ownership

## Extensions
- Add property injection
- Implement method injection
- Create fluent registration API
- Add module/configuration support
- Implement interceptors/AOP
- Add validation framework
- Create diagnostic tools
- Implement child containers
