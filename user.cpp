
#include "user.h"

User::User(const std::string& login, const std::string& password, const std::string& displayName)
    : login_(login), password_(password), displayName_(displayName) {}

const std::string& User::getLogin() const {
    return login_;
}

const std::string& User::getDisplayName() const {
    return displayName_;
}

bool User::checkPassword(const std::string& pwd) const {
    return pwd == password_;
}

void User::receiveMessage(const Message& msg) {
    inbox_.push_back(msg);
}

std::vector<Message> User::getAndClearInbox() {
    std::vector<Message> tmp = inbox_;
    inbox_.clear();
    return tmp;
}
