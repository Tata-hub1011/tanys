
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "message.h"

class User {
public:
    User() = default;
    User(const std::string& login, const std::string& password, const std::string& displayName);

    const std::string& getLogin() const;
    const std::string& getDisplayName() const;
    bool checkPassword(const std::string& pwd) const;

    void receiveMessage(const Message& msg);
    std::vector<Message> getAndClearInbox(); 

private:
    std::string login_;
    std::string password_; 
    std::string displayName_;
    std::vector<Message> inbox_;
};

#endif // USER_H

