#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

enum colours {
    WHITE = 0,
    BLUE,
    RED,
    GREY
};

class car {
protected:
    unsigned int plate;
    bool parking_sensors = false;
    colours colour = WHITE;
public:
    car(unsigned int pl, bool p_s = false, colours col = WHITE) :
            plate(pl), parking_sensors(p_s), colour(col) {};
    car(const car &c) : plate(c.plate + 1), parking_sensors(c.parking_sensors) {};
    unsigned int weeks_to_deliver(std::unordered_map<std::string, unsigned int> &stock) const;
    virtual unsigned int compute_cost() const;
};

//• car.cpp
unsigned int car::weeks_to_deliver(std::unordered_map<std::string, unsigned int> &stock) const
{
    unsigned int ret = 2;
    if (stock.at("pistons") < 3)
    {
        ret = ret + 3 - stock.at("pistons");
        stock.at("pistons") = 0;
    }
    else
    {
        stock.at("pistons") = stock.at("pistons") - 3;
    }
    unsigned int c_num = 5;
    if (this->parking_sensors)
    {
        c_num = c_num + 2;
    }
    if (stock.at("chips") < c_num)
    {
        ret = ret + (c_num - stock.at("chips")) * 5;
    }
    else
    {
        stock.at("chips") = stock.at("chips") - c_num;
    }
    return ret;
}
unsigned int car::compute_cost() const
{
    unsigned int cost = 15000;
    if (this->parking_sensors)
    {
        cost = cost + 500;
    }
    if (this->colour != WHITE)
    {
        cost = cost + 1000;
    }
    return cost;
}


// • station_wagon.h
class station_wagon : public car {
public:
    station_wagon(unsigned int pl, colours col = BLUE) :
            car(pl, true, col) {};
    unsigned int weeks_to_deliver(std::unordered_map<std::string, unsigned int> &stock) const;
    unsigned int compute_cost() const override;
};

//• station_wagon.cpp
unsigned int station_wagon::weeks_to_deliver(std::unordered_map<std::string, unsigned int> &stock) const
{
    unsigned int ret = 3;
    if (stock.at("pistons") < 4)
    {
        ret += 4 - stock.at("pistons");
    }
    if (stock.at("chips") < 6)
    {
        ret += (6 - stock.at("chips")) * 5;
        stock.at("chips") = 0;
    }
    else
    {
        stock.at("chips") -= 6;
    }
    return ret;
}
unsigned int station_wagon::compute_cost() const
{
    unsigned int cost = 18500;
    if (this->colour != BLUE)
    {
        cost = cost + 1500;
    }
    return cost;
}

// • main.cpp
void place_order(const car &item, std::unordered_map<std::string, unsigned int> &stock)
{
    unsigned int weeks = item.weeks_to_deliver(stock);
    unsigned int cost = item.compute_cost();
    std::cout << "The car will arrive in " << weeks << " weeks, cost is " << cost << std::endl;
}

int main()
{
std::unordered_map<std::string, unsigned int> parts_in_stock;
parts_in_stock.insert(std::make_pair<std::string, unsigned int>("pistons", 6));
parts_in_stock.insert(std::make_pair<std::string, unsigned int>("chips", 20));
car c1(001, false, GREY);
station_wagon s1(002, RED);
place_order(c1, parts_in_stock);
place_order(s1, parts_in_stock);

car c2(s1);
place_order(c2, parts_in_stock);

station_wagon s2(993, WHITE);
unsigned int estimate = s2.weeks_to_deliver(parts_in_stock);
std::cout << "Estimated delivery in " << estimate << " weeks" << std::endl;

return 0;
}
