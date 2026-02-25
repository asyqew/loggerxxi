#include <iostream>
#include <loggerxxi/logger.hpp>

int main() {
    // Setting the logging level to DEBUG
    loggerxxi::Logger::getInstance().setLevel(loggerxxi::LogLevel::DEBUG);

    // Demonstrating all logging levels
    LOG_DEBUG("This is a DEBUG level message");
    LOG_INFO("This is a INFO level message");
    LOG_WARNING("This is a WARNING level message");
    LOG_ERROR("This is a ERROR level message");

    // Example of logging in a loop
    for(int i = 0; i < 3; ++i) {
        LOG_INFO("Loop iteration: " + std::to_string(i));
    }

    return 0;
}