# STM32-Register-Drivers
STM32 register-level peripheral drivers (no HAL/LL).

.
└── F3-Series/
│    └── Nucleo-f302r8/
│        └── Drivers/
│            └── USART/
│                └── USART1/
│                    ├── Basic/          # Standard register-level init
│                    │   ├── usart1.c
│                    │   └── usart1.h
│                    │   └── README.txt
│                    └── Compile-Time/   # Zero-overhead static init
│                        ├── usart1.c
│                        └── usart1.h
│                        └── README.txt
