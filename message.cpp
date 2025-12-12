
#include "message.h"
#include <ctime>
#include <sstream>
#include <iomanip>

Message::Message(const std::string& from, const std::string& to, const std::string& text)
    : from_(from), to_(to), text_(text), timestamp_(std::chrono::system_clock::now()) {}

const std::string& Message::getFrom() const { return from_; }
const std::string& Message::getTo() const { return to_; }
const std::string& Message::getText() const { return text_; }

std::string Message::getTimeString() const {
    std::time_t t = std::chrono::system_clock::to_time_t(timestamp_);
    std::tm tm{};
#if defined(_MSC_VER)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

