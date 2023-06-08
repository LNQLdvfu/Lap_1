//
// Created by Lê Ngọc Quốc Lịch on 20/04/2023.
//

#ifndef UNTITLED_CARTOON_H
#define UNTITLED_CARTOON_H
#include <iostream>
#include "box.h"
#include <string>

class Cartoon :public Box
{
private:
    std::string material{"Cardboard"};
    double thickness{0.125};
    double density{0.2};
public:
    Cartoon(double lv, double hv, double wv, std::string_view mat):
    Box{lv,hv,wv}, material{mat}
    {
        std::cout<<"Cartoon(double, double double) is called\n";
    }

    explicit Cartoon(std::string mat) : material{mat} {
        std::cout<<"Carton(double) called.\n";
    }

    Cartoon(double side , std::string_view mat) : Box{side}, material{mat} {
        std::cout<<"Cartoon(double, string) called.\n";
    }

    Cartoon() {std::cout<<"Cartoon() called.\n";}

    Cartoon(const Cartoon& cartoon) : Box{cartoon}, material{cartoon.material}{
        std::cout<<"Copy of cartoon is call.\n";
    }

    Cartoon(double lv, double hv, double wv, double thickness, double density, std::string_view mat) : Cartoon{lv,hv,wv,mat} {
        this->density = density;
        this->thickness = thickness;
        std::cout<<"Cartoon(double, double, double, double, doubel , string) is called.\n ";
    }

    ~Cartoon() {
        std::cout<<"Cartoon destructor. Material = "<<material<<std::endl;
    }

    double getWeight() const {
        return 2.0*(length*width + width*height + height*length)*thickness*density;
    }

};

#endif //UNTITLED_CARTOON_H
