#ifndef BLACKBOARD_HPP
#define BLACKBOARD_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <typeindex>
#include <iostream>
#include <typeinfo>

using environment_key_t = std::string;

class Blackboard {
public:
    class BaseValue {
    public:
        virtual ~BaseValue() = default;
    };

    template<typename T>
    class Value : public BaseValue {
    public:
        Value(const T& value) : value_(value) {}
        T value_;
    };

    template<typename T>
    void setInEnvironment(const environment_key_t &key, const T& value) {
        environment_[key] = std::make_shared<Value<T>>(value);
    }

    template<typename T>
    T getInEnvironment(const environment_key_t& key, const T& defaultValue = T()) const {
        auto it = environment_.find(key);
        if (it != environment_.end()) {
            auto basePtr = it->second;
            auto derivedPtr = std::dynamic_pointer_cast<Value<T>>(basePtr);
            if (derivedPtr) {
                return derivedPtr->value_;
            } else {
                std::cerr << "Bad cast for key: " << key << "\n";
                return defaultValue;
            }
        }
        return defaultValue;
    }

private:
    std::unordered_map<environment_key_t, std::shared_ptr<BaseValue>> environment_;  // State of the environmental variables
};

#endif // BLACKBOARD_HPP
