
#include <iostream>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include "user.h"
#include "message.h"

using UserPtr = std::shared_ptr<User>;

void printMenu(bool loggedIn, const std::string& currentUser) {
    std::cout << "\n=== Simple Chat ===\n";
    if (!loggedIn) {
        std::cout << "1) Register\n";
        std::cout << "2) Login\n";
        std::cout << "0) Exit\n";
    } else {
        std::cout << "Logged in as: " << currentUser << "\n";
        std::cout << "1) Send message to user\n";
        std::cout << "2) Send broadcast (to all)\n";
        std::cout << "3) Check inbox\n";
        std::cout << "4) Logout\n";
        std::cout << "0) Exit\n";
    }
    std::cout << "Choose: ";
}

void printInbox(const std::vector<Message>& msgs) {
    if (msgs.empty()) {
        std::cout << "Inbox is empty.\n";
        return;
    }
    for (const auto& m : msgs) {
        std::cout << "[" << m.getTimeString() << "] " << m.getFrom();
        if (m.getTo() == "*") std::cout << " -> (broadcast)";
        else std::cout << " -> " << m.getTo();
        std::cout << ": " << m.getText() << "\n";
    }
}

int main() {
    std::unordered_map<std::string, UserPtr> users; // login -> User
    bool running = true;
    bool loggedIn = false;
    std::string currentLogin;

    while (running) {
        printMenu(loggedIn, currentLogin);
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (!loggedIn) {
            if (choice == 1) {
                std::string login, pwd, name;
                std::cout << "Enter login: ";
                std::getline(std::cin, login);
                if (login.empty()) { std::cout << "Login cannot be empty.\n"; continue; }
                if (users.find(login) != users.end()) {
                    std::cout << "User with this login already exists.\n";
                    continue;
                }
                std::cout << "Enter password: ";
                std::getline(std::cin, pwd);
                std::cout << "Enter display name: ";
                std::getline(std::cin, name);
                users[login] = std::make_shared<User>(login, pwd, name);
                std::cout << "Registered successfully.\n";
            } else if (choice == 2) {
                std::string login, pwd;
                std::cout << "Login: ";
                std::getline(std::cin, login);
                std::cout << "Password: ";
                std::getline(std::cin, pwd);
                auto it = users.find(login);
                if (it == users.end()) {
                    std::cout << "No such user.\n";
                } else {
                    if (it->second->checkPassword(pwd)) {
                        loggedIn = true;
                        currentLogin = login;
                        std::cout << "Logged in as " << it->second->getDisplayName() << "\n";
                    } else {
                        std::cout << "Wrong password.\n";
                    }
                }
            } else if (choice == 0) {
                running = false;
            } else {
                std::cout << "Unknown choice.\n";
            }
        } else { // logged in
            if (choice == 1) {
                std::string to, text;
                std::cout << "To (login): ";
                std::getline(std::cin, to);
                if (users.find(to) == users.end()) {
                    std::cout << "No such user.\n";
                    continue;
                }
                std::cout << "Message: ";
                std::getline(std::cin, text);
                Message msg(currentLogin, to, text);
                users[to]->receiveMessage(msg);
                std::cout << "Sent to " << to << "\n";
            } else if (choice == 2) {
                std::string text;
                std::cout << "Broadcast message: ";
                std::getline(std::cin, text);
                Message msg(currentLogin, "*", text);
                for (auto& kv : users) {
                    // send to all, including sender
                    kv.second->receiveMessage(msg);
                }
                std::cout << "Broadcast sent to all.\n";
            } else if (choice == 3) {
                auto msgs = users[currentLogin]->getAndClearInbox();
                printInbox(msgs);
            } else if (choice == 4) {
                loggedIn = false;
                currentLogin.clear();
                std::cout << "Logged out.\n";
            } else if (choice == 0) {
                running = false;
            } else {
                std::cout << "Unknown choice.\n";
            }
        }
    }

    std::cout << "Bye!\n";
    return 0;
}
