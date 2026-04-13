// Copyright 2026 AnastasiaLos
#include <gtest/gtest.h>
#include "Automata.h"
TEST(AutomataTest, InitialStateIsOff) {
    Automata a;
    EXPECT_EQ(a.getState(), STATES::OFF);
    EXPECT_EQ(a.getCash(), 0);
}
TEST(AutomataTest, OnChangesStateToWait) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}
TEST(AutomataTest, OffFromWaitChangesStateToOff) {
    Automata a;
    a.on();
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
    EXPECT_EQ(a.getCash(), 0);
}
TEST(AutomataTest, CoinFromWaitMovesToAccept) {
    Automata a;
    a.on();
    a.coin(100);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
    EXPECT_EQ(a.getCash(), 100);
}
TEST(AutomataTest, CoinFromAcceptAddsMoney) {
    Automata a;
    a.on();
    a.coin(50);
    a.coin(30);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
    EXPECT_EQ(a.getCash(), 80);
}
TEST(AutomataTest, ChoiceWithoutMoneyDoesNothing) {
    Automata a;
    a.on();
    bool result = a.choice(1);
    EXPECT_FALSE(result);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}
TEST(AutomataTest, ChoiceWithEnoughMoneyStartsCooking) {
    Automata a;
    a.on();
    a.coin(100);
    bool result = a.choice(2);  // Кофе 80 руб.
    EXPECT_TRUE(result);
    // После choice должен быть CHECK, потом COOK, потом WAIT
    EXPECT_EQ(a.getState(), STATES::WAIT);
}
TEST(AutomataTest, CancelFromAcceptReturnsMoney) {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
    EXPECT_EQ(a.getCash(), 0);
}
TEST(AutomataTest, CancelFromCheckReturnsMoney) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(2);  // Выбрали кофе
    // После choice состояние стало CHECK
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
    EXPECT_EQ(a.getCash(), 0);
}
TEST(AutomataTest, GetMenuReturnsNonEmptyString) {
    Automata a;
    std::string menu = a.getMenu();
    EXPECT_FALSE(menu.empty());
    EXPECT_NE(menu.find("Чай"), std::string::npos);
    EXPECT_NE(menu.find("Кофе"), std::string::npos);
}
TEST(AutomataTest, ChoiceInvalidIndexReturnsFalse) {
    Automata a;
    a.on();
    a.coin(100);
    bool result = a.choice(99);  // Несуществующий напиток
    EXPECT_FALSE(result);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}
TEST(AutomataTest, FinishAfterCookResetsCash) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(2);
    // После приготовления cash должен обнулиться
    EXPECT_EQ(a.getCash(), 0);
}
TEST(AutomataTest, OffFromAcceptNotAllowed) {
    Automata a;
    a.on();
    a.coin(100);
    a.off();  // Не должно выключиться
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}
TEST(AutomataTest, CoinNegativeAmountIgnored) {
    Automata a;
    a.on();
    a.coin(-10);
    EXPECT_EQ(a.getCash(), 0);
    EXPECT_EQ(a.getState(), STATES::WAIT);
}
TEST(AutomataTest, ChoiceWithoutOnDoesNothing) {
    Automata a;
    bool result = a.choice(1);
    EXPECT_FALSE(result);
    EXPECT_EQ(a.getState(), STATES::OFF);
}
