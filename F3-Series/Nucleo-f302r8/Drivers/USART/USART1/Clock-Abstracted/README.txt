⚠️ Note:
Only one implementation (Clock-Abstracted or Low-Level) should be included in a project. Including both may lead to symbol conflicts and multiple definition errors.

• This driver is designed using a compile-time configuration principle. Instead of increasing CPU load at runtime, all hardware parameters are determined at compile time.
• Unlike the low-level implementation, this driver includes a clock abstraction layer. Peripheral clock configurations are handled internally, reducing the need for user intervention.
• The user only needs to configure the variables in the user settings section of the .h file according to their requirements.
