//
// Created by Lê Ngọc Quốc Lịch on 21/04/2023.
//
#include <iostream>
#include <string>
#include <string_view>

class Content {
protected:
    std::string name{"Cereal"};
    double volume{};
    double density{0.03};
public:
    Content(std::string_view name, double density, double volume) : name{name}, density{density}, volume{volume} {
        std::cout<<"Content(string, double, double is call.\n";
    }

    Content(std::string_view name) : name{name} {
        std::cout<<"Content(string) is called.\n"
    }

    Content(){std::cout<<"Content() is called.\n"};

    ~Content() {std::cout<<"Destruc Content called.\n"};

    double getwight(){
        return volume * density;
    }

};