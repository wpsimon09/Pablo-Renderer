//
// Created by wpsimon09 on 11/07/24.
//

#ifndef PARAMETER_H
#define PARAMETER_H
#include <glm/common.hpp>


class Parameter {
public:
    explicit Parameter(float val,bool isCustomizable= true, float min = 0.0, float max = 1.0);

    float getMax(){return maxValue;}
    float getMin(){return minValue;}

    float &getValue(){return currentValue;}
    float getVlaue() const{return currentValue;}
private:
    float maxValue;
    float minValue;
    float currentValue;

    bool isCustomizable;
};



#endif //PARAMETER_H
