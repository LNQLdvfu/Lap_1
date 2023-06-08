//
// Created by Lê Ngọc Quốc Lịch on 24/04/2023.
//

#ifndef POLYMORPHISM_CARTON_H
#define POLYMORPHISM_CARTON_H
#include <string_view>
#include <string>
#include "box.h"

class carton : public box
{
private:
    std::string material;
public:
    carton(double lv, double hv, double wv, std::string_view mat) : box{lv, hv, wv}, material{mat}{}
    double volume() const  override{
        const double vol {(length - 0.5)*(width - 0.5)*(height - 0.5)};
        return vol > 0.0? vol : 0.0;
    }
};
#endif //POLYMORPHISM_CARTON_H
