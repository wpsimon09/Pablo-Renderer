//
// Created by wpsimon09 on 30/12/23.
//

#include "Material.h"

bool Material::operator==(const Material &other) const {
    if(other.ID == this->ID) {
        return true;
    }else
        return false;
}
