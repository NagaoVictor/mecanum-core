Mecanum Core

Mecanum Core is a low-level control system written in C for the Freenove 4WD Smart Car Kit for Raspberry Pi, running on a Raspberry Pi 5 with Linux.

The main goal of this project is to study and apply in practice the concepts presented in The Linux Programming Interface, including device control through ioctl(), I²C communication, TCP/IP sockets, multithreading with POSIX threads, and build automation with Makefile.

The project replaces the original Python implementation with a fully native C architecture, providing direct access to memory, pointers, and hardware resources. This approach offers a deeper understanding of how Linux interacts with devices at the operating system level.

Features
Low-level motor control over I²C using the PCA9685 PWM controller
Remote client-server communication using TCP/IP sockets
Real-time keyboard input capture
Concurrent processing with POSIX Threads (pthread)
Remote access and management through OpenSSH
Automated compilation with GNU Make
Educational Purpose

This project was designed as a modular and extensible foundation for studying:

Linux systems programming
Embedded software development
Robotics and motor control
Network programming
Multithreaded applications in C

The same architecture can be adapted to other projects such as robotic arms, drones, autonomous vehicles, and sensor-based systems.

This project is intended for educational purposes and serves as a practical reference for developers interested in low-level Linux programming, embedded systems, and robotics.

<p align="center">

&#x20; <img src="assets/demo1.gif" width="500">

</p>

