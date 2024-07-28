/* 
 * File:   main.cpp
 * Author: Jazmine Garcia
 * Created on July 20, 2024, 10:58 PM
 * Purpose: Project 1 (BlackJack)
 */

// system libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int main() {
    // Set the random number seed 
    srand(static_cast<unsigned int>(time(0))); 

    // Constants
    const float INIT_MNY = 1000.0; // Default initial money to bet ($1000)
    const string SAVE_FLE = "blackjack_save.txt"; // Save file name

    // Declare Variables
    float money = INIT_MNY; // Player's initial money
    float bet; // Amount the player wants to bet
    string name; // Player's name
    char again; // Choice to play again, save or load game
    int games = 0; // Number of games played
    bool contPlay = true; // control the game loop/ asks if player wants to continue

    // Get player name
    cout << "Enter your name: ";
    cin >> name; 

    cout << "Welcome to Blackjack, " << name << "!" << endl;
    cout << "Starting money: $" << fixed << setprecision(2) << money << endl; // Display initial money $1000

    // Main game loop with do-while
    do {
        // Check if the player has no money left to bet
        if (money <= 0) {
            cout << "You have no money left to bet. Game over!" << endl;
            contPlay = false; // Exit the loop if no money left
            continue; 
        }

        // Get the player's bet amount
        cout << "You have $" << fixed << setprecision(2) << money << ". Enter your bet amount: $";
        cin >> bet; // Read the bet amount

        // Validate the bet amount
        if (bet <= 0 || bet > money) {
            cout << "Invalid bet amount. Please enter an amount between $0.01 and $" << fixed << setprecision(2) << money << "." << endl;
            continue; 
        }

        int betInt = static_cast<int>(bet); // Convert bet amount to integer (type casting)
        cout << "You have bet $" << betInt << "." << endl;
     
        // Variables for player and dealer hands
        int pCard1 = (rand() % 13) + 1; // Draw the first card for player
        int pCard2 = (rand() % 13) + 1; // Draw the second card for player
        int dCard1 = (rand() % 13) + 1; // Draw the first card for dealer
        int dCard2 = (rand() % 13) + 1; // Draw the second card for dealer
        
        // Convert face cards to value 10 and Ace to value 11
        pCard1 = (pCard1 > 10) ? 10 : pCard1;
        pCard2 = (pCard2 > 10) ? 10 : pCard2;
        dCard1 = (dCard1 > 10) ? 10 : dCard1;
        dCard2 = (dCard2 > 10) ? 10 : dCard2;

        pCard1 = (pCard1 == 1) ? 11 : pCard1;
        pCard2 = (pCard2 == 1) ? 11 : pCard2;
        dCard1 = (dCard1 == 1) ? 11 : dCard1;
        dCard2 = (dCard2 == 1) ? 11 : dCard2;

        int pTotal = pCard1 + pCard2; // Calculate total value of player's cards
        int dTotal = dCard1 + dCard2; // Calculate total value of dealer's cards
        bool bust = false; // check if the player busts

        // Display initial hands
        cout << "Your cards: " << pCard1 << " and " << pCard2 << " (Total: " << pTotal << ")" << endl;
        cout << "Dealer's face-up card: " << dCard1 << endl;

        char choice; // Player's choice to hit or stand
        bool decided = false; // Player's decision
        do {
            cout << "Do you want to (h)it or (s)tand? ";
            cin >> choice; 

            if (choice == 'h' || choice == 'H') {
                // If Player chooses to hit
                int newCard = (rand() % 13) + 1; // Draw a new card
                newCard = (newCard > 10) ? 10 : newCard; // Convert face cards to 10
                newCard = (newCard == 1) ? 11 : newCard; // Convert Ace to 11

                pTotal += newCard; // Add new card to player's total
                cout << "You drew a " << newCard << ". Your total is now " << pTotal << "." << endl;

                if (pTotal > 21) {
                    cout << "You busted!" << endl;
                    bust = true; 
                } else if (newCard == 11) {
                    cout << "You drew an Ace! If you bust, Ace will be counted as 1 instead of 11." << endl;
                    if (pTotal > 21) {
                        pTotal -= 10; // Decrement to show Ace value from 11 to 1
                        cout << "Ace adjusted. Your total is now " << pTotal << "." << endl;
                    }
                }
            } else if (choice == 's' || choice == 'S') {
                decided = true; 
            } else {
                cout << "Invalid choice. Please enter 'h' to hit or 's' to stand." << endl;
            }
        } while (!decided && !bust); 

        if (!bust) {
            // Dealer's turn
            cout << "Dealer's cards: " << dCard1 << " and " << dCard2 << " (Total: " << dTotal << ")" << endl;

            // Dealer draws cards until total is at least 17
            while (dTotal < 17) {
                int newCard = (rand() % 13) + 1; // Draw a new card for the dealer
                newCard = (newCard > 10) ? 10 : newCard; // Convert face cards to 10
                newCard = (newCard == 1) ? 11 : newCard; // Convert Ace to 11

                dTotal += newCard; // Add new card to dealer's total
                cout << "Dealer draws a " << newCard << ". Dealer's total is now " << dTotal << "." << endl;
            }

            //  If-statement Compare totals to determine the outcome
            if (dTotal > 21) {
                cout << "Dealer busted! You win!" << endl;
                money += bet; // increment to show winning money
            } else if (dTotal > pTotal) {
                cout << "Dealer wins with " << dTotal << ". You lose." << endl;
                money -= bet; // Dealer wins
            } else if (dTotal < pTotal) {
                cout << "You win with " << pTotal << ", dealer has " << dTotal << "." << endl;
                money += bet; 
            } else {
                cout << "It's a tie! Both you and the dealer have " << pTotal << "." << endl;
            }
        } else {
            // Dealer wins if player busts
            cout << "Dealer wins by default." << endl;
            money -= bet; // Decrement for money lost
        }

        // Display updated player money and number of games played
        cout << "You now have $" << fixed << setprecision(2) << money << "." << endl;
        games++; // Increment the number of games played
        cout << "Games played: " << games << "." << endl;

        // Prompt player to play again, save, or load game
        if (money > 0) {
            cout << "Do you want to (p)lay again, (s)ave game, or (l)oad game? (p/s/l): ";
            cin >> again; // Read user's choice

            if (again == 'p' || again == 'P') {
                contPlay = true;
            } else if (again == 's' || again == 'S') {
                // Save the game state
                ofstream outFile(SAVE_FLE);
                if (outFile) {
                    outFile << money << endl; // Save player's money
                    outFile << games << endl; // Save number of games played
                    outFile.close();
                    cout << "Game saved successfully." << endl;
                } else {
                    cout << "Error saving the game." << endl;
                }
                contPlay = false; 
            } else if (again == 'l' || again == 'L') {
                // Load the game 
                ifstream inFile(SAVE_FLE);
                if (inFile) {
                    inFile >> money; // Load player's money
                    inFile >> games; // Load number of games played
                    inFile.close();
                    cout << "Game loaded successfully." << endl;
                    cout << "You have $" << fixed << setprecision(2) << money << " and have played " << games << " games." << endl;
                } else {
                    cout << "No saved game found." << endl;
                }
                contPlay = true; 
            } else {
                cout << "Invalid choice. Exiting game." << endl;
                contPlay = false; // Exit the game loop if choice is invalid
            }
        } else {
            // Exit the game loop if player has no money left
            contPlay = false;
        }
    } while (contPlay); 

    // Exit Message 
    if (money <= 0) {
        cout << "You have no money left to bet. Thank you for playing, " << name << "!" << endl;
    } else {
        cout << "Thank you for playing, " << name << "! You leave with $" << fixed << setprecision(2) << money << "." << endl;
    }

    return 0; 
}