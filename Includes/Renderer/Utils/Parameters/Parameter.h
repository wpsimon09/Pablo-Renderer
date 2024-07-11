//
// Created by wpsimon09 on 11/07/24.
//

#ifndef PARAMETER_H
#define PARAMETER_H
#include <glm/common.hpp>

template <typename T>
class Parameter {
public:
    Parameter()
      : maxValue(static_cast<T>(1.0)), minValue(static_cast<T>(0.0)), currentValue(T()), isCustomizable(true) {}

    explicit Parameter(T val,bool isCustomizable= true, T min = static_cast<T>(0.0), T max = static_cast<T>(1.0))
    : maxValue(max), minValue(min), currentValue(val), isCustomizable(isCustomizable) {}
    T getMax() const {return maxValue;}
    T getMin() const {return minValue;}

    T &getValue(){return currentValue;}
    T getValueConst() const {return currentValue;}

    bool canBeChanged() {return this->isCustomizable;}
private:
    T maxValue;
    T minValue;
    T currentValue;

    bool isCustomizable;
};



#endif //PARAMETER_H
