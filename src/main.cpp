// Copyright 2026 AnastasiaLos
#include "Automata.h"
#include <iostream>
int main() {
    Automata coffeeMachine;
    std::cout << coffeeMachine.getMenu();
    coffeeMachine.on();
    coffeeMachine.coin(100);
    coffeeMachine.choice(2);
    return 0;
}
