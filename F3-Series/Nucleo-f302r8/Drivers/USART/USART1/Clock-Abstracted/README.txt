⚠️ Note:
Only one implementation (Clock-Abstracted or Low-Level) should be included in a project. Including both may lead to symbol conflicts and multiple definition errors.

⚠️ Note:
A simplified integer-based BRR calculation is used instead of the full fractional USARTDIV method. This reduces implementation complexity while maintaining acceptable baud rate accuracy for standard communication speeds. For production-grade or high-precision communication, the full STM32 fractional BRR calculation method should be used.

• This driver is designed using a compile-time configuration principle. Instead of increasing CPU load at runtime, all hardware parameters are determined at compile time.
• Unlike the low-level implementation, this driver includes a clock abstraction layer. Peripheral clock configurations are handled internally, reducing the need for user intervention.
• The user only needs to configure the parameters in the user settings section of the header file based on application requirements.
