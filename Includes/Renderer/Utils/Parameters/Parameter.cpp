//
// Created by wpsimon09 on 11/07/24.
//

#include "Parameter.h"

Parameter::Parameter(float val,bool isCustomizable, float min, float max) {
    this->currentValue = val;
    this->minValue = min;
    this->maxValue = max;
    this->isCustomizable = isCustomizable;
}
