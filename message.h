
#pragma once

#include <string>
#include <chrono>

class Message {
public:
    Message() = default;
    Message(const std::string& from, const std::string& to, const std::string& text);

    const std::string& getFrom() const;
    const std::string& getTo() const;
    const std::string& getText() const;
    std::string getTimeString() const;

private:
    std::string from_;
    std::string to_; // логин получателя или "*" для broadcast
    std::string text_;
    std::chrono::system_clock::time_point timestamp_;
};

