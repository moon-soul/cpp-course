#include "player.hpp"
#include "weapon.hpp"
#include "player_class.hpp"

int main()
{
    Player player1("John");
    Player player2("Mary", new Sword, new BerserkClass);
    Player player3("Travis", new Pistol, new LuckymanClass);
    Player player4("Susan", new AssaultRifle, new DefenderClass);
    Player player5("Emily", new SniperRifle, new AttackerClass);

    player1.attack(player1, 0);
    player1.attack(player2, 0);
    player1.attack(player2, 10);
    player1.setWeapon(new Sword);
    player1.setPlayerClass(new DefenderClass);
    player1.attack(player2, 200);
    player1.attack(player2, 150);

    player2.attack(player1, 150);

    player5.attack(player1, 500);
    player5.attack(player3, 1000);

    player3.attack(player5, 1000);
    player3.attack(player5, 100);
    player3.attack(player4, 100);

    player4.attack(player3, 100);
    player4.attack(player2, 100);

    return 0;
}
