+ This driver is engineered using the compile-time configuration principle. Instead of increasing CPU load during execution (runtime), all hardware parameters are determined at compile time.

+ Unlike the low-level implementation, this driver includes a clock abstraction layer. The required peripheral clock configurations are handled internally, reducing the need for user intervention.

+ The user only needs to configure the variables in the user settings section within the .h file according to their needs.
