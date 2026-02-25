#include <iostream>
#include <stdexcept>
#include <loggerxxi/logger.hpp>

void divide(int a, int b) {
    try {
        if (b == 0) {
            throw std::runtime_error("Division by zero!");
        }
        int result = a / b;
        LOG_INFO("Division result: " + std::to_string(result));
    } catch (const std::exception& e) {
        LOG_ERROR("Error during division: " + std::string(e.what()));
    }
}

int main() {
    // Setting the logging level to WARNING
    loggerxxi::Logger::getInstance().setLevel(loggerxxi::LogLevel::WARNING);

    LOG_INFO("Start");

    // Demonstration of error handling
    divide(10, 2);  // Successful
    divide(10, 0);  // Error

    LOG_INFO("End");

    return 0;
}
