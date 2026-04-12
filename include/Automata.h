#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>
enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};
class Automata {
 private:
    int cash;
    int selectedPrice;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
 public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    std::string getMenu();
    STATES getState();
    bool choice(int drinkIndex);
    void cancel();
    void cook();
    void finish();
    int getCash() const;
    int getSelectedPrice() const;
    void setStateForTest(STATES newState);
};
#endif
