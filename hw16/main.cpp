#include <iostream>

#include "player.hpp"
#include "rectangle.hpp"
#include "weapon.hpp"

int main()
{
    /* Task 1 - 3 */
    const Rectangle rectangle;
    const Rectangle rectangle1(6.6f, 10.0f);
    std::cout << "Rectangle #0"
              << "\nArea: " << rectangle.getArea()
              << "\nPerimeter: " << rectangle.getPerimeter()
              << '\n'
              << "\nRectangle #1"
              << "\nArea: " << rectangle1.getArea()
              << "\nPerimeter: " << rectangle1.getPerimeter()
              << '\n';

    /* Task 4 - 6 */
    Weapon lightsaber("Lightsaber", 80, 10);
    lightsaber.printInfo();
    Player player("John", ClassName::Assault);
    player.printInfo();
    player.setWeapon(&lightsaber);
    player.printInfo();
    Weapon* playerWeapon = player.getWeapon();
    playerWeapon->printInfo();

    /* Task 7 */
    Team team("Star");
    Team team1("Galaxy");

    /* Task 8 */
    Player player1("Jane", ClassName::Sniper);
    Player player2("Emily", ClassName::Medic);
    Player player3("David", ClassName::Medic);
    Player player4("Sarah", ClassName::Assault);
    Player player5("Michael", ClassName::Support);
    team.addPlayer(&player);
    team.addPlayer(&player1);
    team.addPlayer(&player2);
    team1.addPlayer(&player3);
    team1.addPlayer(&player4);
    team1.addPlayer(&player5);
    team.printInfo();
    team1.printInfo();
    team.removePlayer(&player2);
    team1.removePlayer(&player3);
    team.printInfo();
    team1.printInfo();
    player2.printInfo();
    player3.printInfo();

    return 0;
}
