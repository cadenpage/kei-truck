# Kei Truck
Kei Truck is an embedded robotics teleoperation project focused on low-latency wireless vehicle control with ESP-NOW.  
The current baseline validates ESP32 motor control and peer-to-peer command transfer, and the next phase adds MediaPipe hand-tracking teleoperation so the car steers from live camera input.
![Kei Truck](imgs/kei_truck.png)

---

## Demo

![ESP-NOW Touchscreen Controller Demo](imgs/kei_controller_demo.gif)

Current demo: a touchscreen ESP32 controller sends ESP-NOW commands to the car-side ESP32.

---

## Abstract
This repository documents an end-to-end control pipeline for a small robotic car platform: embedded motor driving, ESP-NOW wireless communication, and a planned vision teleoperation layer. The project is being developed in stages, starting with deterministic firmware behavior and expanding toward camera-based gesture steering.

---

## System Architecture
Kei Truck is organized into three connected layers:

1. Vehicle control firmware (`kei-truck/src/main.cpp`): dual-motor control through direction pins and PWM channels with high-level drive primitives (forward, reverse, left, right, stop).

2. Wireless command transport (`kei-truck/tmp/master.cpp`, `kei-truck/tmp/slave.cpp`, `kei-truck/tmp/get_mac.cpp`): ESP-NOW master/slave prototypes for low-latency command exchange, peer setup, MAC discovery, and serial-driven command tests.

3. Vision teleoperation layer (planned): MediaPipe hand tracking maps gesture/hand pose to steering and throttle commands, then a camera host sends parsed control intents to the ESP32 transmitter.

---

## Hardware
- Vehicle controller: Seeed XIAO ESP32S3.
- Drive stage: dual DC motor setup with H-bridge style direction + enable PWM control.
- Wireless interface: ESP-NOW over ESP32 Wi-Fi radio in station mode.
- Demo controller: touchscreen ESP32 transmitter (shown in GIF).
- Planned perception interface: camera + host machine for MediaPipe inference.

---

## Software Stack
- PlatformIO project environment (`kei-truck/platformio.ini`).
- Arduino framework on ESP32 (`espressif32`, `seeed_xiao_esp32s3` target).
- ESP-NOW + Wi-Fi station mode for controller-to-vehicle messaging.
- C++ motor control primitives and communication test programs.
- Planned: MediaPipe-based gesture-to-command mapping pipeline.

---

## Key Concepts
- Low-latency teleoperation using ESP-NOW rather than traditional AP/router networking.
- Separation of concerns between motor control firmware and control-input generation.
- Incremental robotics workflow: validate embedded transport and actuation first, then integrate perception.
- Safety-oriented control behavior through explicit stop/coast command paths.

---

## Challenges
- Maintaining reliable command delivery and predictable behavior under wireless interference.
- Translating noisy hand-tracking signals into smooth, stable steering commands.
- Keeping end-to-end latency low enough for natural manual driving.
- Defining safe fallback behavior for dropped packets or invalid gesture states.

---

## Future Work
- Integrate MediaPipe teleoperation and tune gesture-to-drive mapping.
- Add bidirectional telemetry (link quality, battery, and runtime status).
- Implement control smoothing/rate limiting for safer steering transitions.
- Split firmware into clearer modules for comms, control, and safety state management.
- Add repeatable test scenarios and benchmark command latency.

---

## Additional Documentation
- Project notes and setup guides will be added as the repository grows.
