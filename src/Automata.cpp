// Copyright 2026 AnastasiaLos
#include "Automata.h"
#include <iostream>
#include <sstream>
#include <string>

Automata::Automata() : cash(0), selectedPrice(0), state(STATES::OFF) {
    menu = {"Чай", "Кофе", "Молоко", "Горячий шоколад", "Капучино"};
    prices = {50, 80, 60, 100, 120};
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        std::cout << "Автомат включен. Состояние: ОЖИДАНИЕ\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        state = STATES::OFF;
        cash = 0;
        std::cout << "Автомат выключен\n";
    }
}

void Automata::coin(int amount) {
    if (amount <= 0) return;
    if (state == STATES::WAIT) {
        cash = amount;
        state = STATES::ACCEPT;
        std::cout << "Внесено " << amount << " руб.\n";
    } else if (state == STATES::ACCEPT) {
        cash += amount;
        std::cout << "Добавлено " << amount << " руб. Всего: " << cash << "\n";
    }
}

std::string Automata::getMenu() {
    std::stringstream ss;
    ss << "===== МЕНЮ =====\n";
    for (size_t i = 0; i < menu.size(); i++) {
        ss << i + 1 << ". " << menu[i] << " - " 
           << prices[i] << " руб.\n";
    }
    ss << "================\n";
    return ss.str();
}

STATES Automata::getState() {
    return state;
}

bool Automata::choice(int drinkIndex) {
    if (state != STATES::ACCEPT) return false;
    if (drinkIndex < 1 || drinkIndex > static_cast<int>(menu.size())) 
        return false;
    selectedPrice = prices[drinkIndex - 1];
    std::cout << "Выбран: " << menu[drinkIndex - 1] 
              << " - " << selectedPrice << " руб.\n";
    state = STATES::CHECK;
    if (cash >= selectedPrice) {
        cook();
        return true;
    } else {
        std::cout << "Недостаточно средств\n";
        cancel();
        return false;
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPT || state == STATES::CHECK) {
        std::cout << "Возврат " << cash << " руб.\n";
        cash = 0;
        state = STATES::WAIT;
    }
}

void Automata::cook() {
    if (state == STATES::CHECK && cash >= selectedPrice) {
        state = STATES::COOK;
        std::cout << "Приготовление...\n";
        for (int i = 3; i > 0; i--) {
            std::cout << i << "...\n";
        }
        finish();
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        int change = cash - selectedPrice;
        if (change > 0) {
            std::cout << "Сдача: " << change << " руб.\n";
        }
        std::cout << "Напиток выдан. Спасибо!\n";
        cash = 0;
        selectedPrice = 0;
        state = STATES::WAIT;
    }
}

int Automata::getCash() const { return cash; }
int Automata::getSelectedPrice() const { return selectedPrice; }
void Automata::setStateForTest(STATES newState) { state = newState; }
