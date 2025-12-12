
#ifndef MESSAGE_H
#define MESSAGE_H

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
    std::string to_;
    std::string text_;
    std::chrono::system_clock::time_point timestamp_;
};

#endif 
