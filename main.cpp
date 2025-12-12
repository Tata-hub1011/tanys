
#include <iostream>
#include "Chat.h"

int main()
{
    Chat chat;
    chat.register_user("ivan", "909", "Ivan");
    chat.register_user("anna", "345", "Anna");

    chat.send_private_message("ivan", "anna", "Привет, Анна!");
    chat.send_global_message("anna", "Всем привет!");

    auto inbox = chat.get_inbox_for("anna");
    for (const auto& m : inbox)
    {
        std::cout << "От: " << m.get_from() << " Тo: " << m.get_to() << " Текст: " << m.get_text() << "\n";
    }

    return 0;
}

