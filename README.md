# Loggerxxi
**Loggerxxi** - A simple, header-only C++ 17 logging library with support for multiple log levels and timestamped messages.

- Header-only design for easy integration
- Multiple log levels: DEBUG, INFO, WARNING, ERROR
- Timestamped log entries
- Colored console output for better readability
- Level-based filtering

## Installation

Simply include the `logger.hpp` file in your project:
```cpp
#include <loggerxxi/logger.hpp>
```

Or add the library as a submodule or dependency in your `CMakeLists.txt`:
```cmake
add_subdirectory(path/to/loggerxxi)
target_link_libraries(your_project PRIVATE loggerxxi)
```

## Usage
Basic Example:
```cpp
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
```

## API Reference
Log Levels:
- DEBUG: Detailed debug information
- INFO: General information
- WARNING: Potential issues
- ERROR: Critical errors

Logging Methods:
- setLevel(LogLevel level): Set the minimum log level to display
- getLevel(): Get the current log level
- debug(const std::string& message)
- info(const std::string& message)
- warning(const std::string& message)
- error(const std::string& message)

Macros:
- LOG_DEBUG
- LOG_INFO
- LOG_WARNING
- LOG_ERROR

## Examples
The repository includes example projects demonstrating basic and advanced usage:
- `examples/01_hello.cpp`: Basic logging demonstration
- `examples/02_advanced.cpp`: Error handling and logging in functions
