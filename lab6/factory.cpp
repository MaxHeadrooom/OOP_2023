#include "factory.h"
#include "squirrel.h"
#include "orc.h"
#include "bear.h"

std::shared_ptr<NPC> factory(std::istream& in) 
{
    std::string type, name;
    int x, y;
    char c;
    in >> type >> name >> c >> x >> c >> y >> c;
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") 
    {
        res = std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Orc") 
    {
        res = std::make_shared<Orc>(x, y, name);
    }
    else if (type == "Bear") 
    {
        res = std::make_shared<Bear>(x, y, name);
    }
    else if (type != "") 
    {
        std::cerr << "Unknown type" << '\n';
    }
    return res;
}

std::shared_ptr<NPC> factory(const std::string& type, const std::string& name, const int& x, const int& y) 
{
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") 
    {
        res = std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Orc") 
    {
        res = std::make_shared<Orc>(x, y, name);
    }
    else if (type == "Bear") 
    {
        res = std::make_shared<Bear>(x, y, name);
    }
    else 
    {
        std::cerr << "Unknown type" << '\n';
    }
    return res;
}