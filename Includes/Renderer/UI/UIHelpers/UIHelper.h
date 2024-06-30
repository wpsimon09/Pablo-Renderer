//
// Created by wpsimon09 on 30/06/24.
//

#ifndef UIHELPER_H
#define UIHELPER_H
#include <memory>

#include "Renderer/Material/Material.h"


class UIHelper {
public:
    static void displayExistingMaterials(std::shared_ptr<Material> &_selectedID, MATERIAL mat = ALL);

    static void displayExistingTextures(MATERIAL_TEXTURE_TYPE filter = UNDEFINED);

    template<typename T>
    static void displayItemsInGrid(std::vector<T> items);
};




#endif //UIHELPER_H
