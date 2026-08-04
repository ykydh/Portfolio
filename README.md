<!-- HEADER -->
<div align="center">

<h1>Yutaro Kiyota</h1>

<p>
  Computer Science student at <strong>Missouri University of Science & Technology</strong><br />
  Embedded systems, RTOS development, networking, and software engineering
</p>

<p>
  <a href="https://github.com/ykydh/Portfolio/blob/main/projects/resume2-16.pdf">
    <img src="https://img.shields.io/badge/Resume-111827?style=flat&logo=readthedocs&logoColor=white" alt="Resume" />
  </a>
  <a href="https://www.linkedin.com/in/yutaro-kiyota-0b8ab7307/">
    <img src="https://img.shields.io/badge/LinkedIn-0A66C2?style=flat&logo=linkedin&logoColor=white" alt="LinkedIn" />
  </a>
  <a href="mailto:ykydh@umsystem.edu">
    <img src="https://img.shields.io/badge/Email-D14836?style=flat&logo=gmail&logoColor=white" alt="Email" />
  </a>
</p>

<img
  src="https://skillicons.dev/icons?i=cpp,c,python,typescript,react,linux,git,vscode,mysql"
  alt="C++, C, Python, TypeScript, React, Linux, Git, VS Code, MySQL"
/>

</div>

---

## About Me

Hi, I’m **Yutaro Kiyota**, a Computer Science student at **Missouri University of Science & Technology**.

I enjoy developing software that interacts with real-world systems, including embedded devices, communication networks, and data-driven applications. My current focus is embedded systems, RTOS development, C/C++ programming, and software engineering.

I contribute to a CubeSat flight software research team, where I develop communication modules and operating system abstractions for satellite software. I also work as a Senior Resident Assistant, developing leadership, communication, and mentoring skills.

---

## Education

**Missouri University of Science & Technology**  
**Bachelor of Science in Computer Science**  
Expected Graduation: May 2027  

GPA: 3.97 / 4.0 | Dean’s List

---

## Skills

| Area | Tools and Topics |
|---|---|
| Programming | C++, C, Python, SQL, TypeScript |
| Embedded Systems | Zephyr RTOS, FreeRTOS, UART, I2C, GPIO, ADC, USB CDC ACM |
| Systems | Linux, TCP/IP, Networking, Multithreading |
| Software Development | FastAPI, React, Git, Database Design |
| Machine Learning | XGBoost, NLP, Data Processing |
| Professional | Leadership, Technical Communication |

---

## Experience

### CubeSat Flight Software Developer  
**Missouri University of Science & Technology Satellite Research Team**  
Aug 2023 – Present

- Developed and extended an Operating System Abstraction Layer (OSAL) over FreeRTOS to standardize file system and task-level interactions for CubeSat flight software.
- Designed and debugged multithreaded Ethernet communication modules supporting concurrent data transfer between satellite subsystems.
- Investigated and resolved flight software issues using GDB debugging tools and systematic software analysis.
- Collaborated with a multidisciplinary engineering team to develop reliable spacecraft software components.

---

### Senior Resident Assistant  
**Missouri University of Science & Technology Residential Life**  
Aug 2024 – May 2026

- Supported residents through mentorship, conflict resolution, and resource guidance.
- Organized community-building programs to improve engagement and foster an inclusive residential environment.
- Mentored and trained first-year resident assistants through individualized coaching and leadership development.

---

## Featured Projects

## Embedded Spatial Audio Calibration System

<table>
<tr>
<td width="52%" valign="top">

<p>
An embedded audio calibration and control system built on <strong>Zephyr RTOS</strong> using the <strong>Raspberry Pi Pico W</strong>. The system combines embedded hardware, device communication, and Python-based signal processing to measure speaker characteristics and perform multi-speaker audio synchronization.
</p>

<p>
Spatial audio systems provide immersive experiences, but Bluetooth speakers introduce different buffering and processing delays that cause playback synchronization issues. This project develops a calibration pipeline that measures speaker latency, maps speaker configurations, and applies timing compensation to improve multi-speaker alignment.
</p>

<p><strong>Highlights</strong></p>

<ul>
  <li>Developed embedded firmware using Zephyr RTOS with I2C OLED display, VL53L0X ToF sensor, ADC input, GPIO control, and USB CDC ACM communication</li>
  <li>Designed a JSON-based communication protocol between embedded firmware and a Python desktop application for device configuration, speaker registration, and calibration data logging</li>
  <li>Implemented speaker latency measurement using chirp signal detection and NumPy-based signal processing to calculate per-speaker delay compensation</li>
  <li>Designed custom hardware schematics using KiCad and integrated sensors and peripherals with the Raspberry Pi Pico W</li>
  <li>Configured Zephyr devicetree overlays, Kconfig options, and peripheral drivers for embedded hardware integration</li>
</ul>

<p><strong>Technologies</strong></p>

<p>
C, Zephyr RTOS, Raspberry Pi Pico W, Python, NumPy, UART, I2C, ADC, GPIO, USB CDC ACM, KiCad
</p>

</td>

<td width="48%" valign="top">

<img
  src="https://github.com/ykydh/Portfolio/blob/main/projects/Sensors.jpeg?raw=true"
  alt="Raspberry Pi Pico W spatial audio calibration hardware prototype"
  width="100%"
/>

<p align="center">
  <em>Raspberry Pi Pico W sensor module prototype</em>
</p>

<br />

<img
  src="https://github.com/ykydh/Portfolio/blob/main/projects/Schematic.png?raw=true"
  alt="KiCad circuit schematic for spatial audio calibration system"
  width="100%"
/>

<p align="center">
  <em>KiCad circuit schematic for embedded audio calibration hardware</em>
</p>

</td>
</tr>
</table>

### Engineering Challenges

The most challenging part of this project was configuring and debugging Zephyr RTOS device trees. Hardware documentation alone was sometimes insufficient, requiring investigation of Zephyr documentation, driver implementations, and system configuration files.

Integrating multiple peripherals also required understanding different driver architectures and hardware abstractions. Through this process, I developed stronger skills in RTOS configuration, embedded debugging, and hardware-software integration.

---

## Stock Prediction Platform

<table>
<tr>
<td width="52%" valign="top">

<p>
A full-stack machine learning application that combines financial data processing, natural language processing, and predictive modeling to estimate next-day stock price movement.
</p>

<p>
The system integrates a <strong>FastAPI backend</strong>, <strong>React frontend</strong>, SQL database, <strong>XGBoost regression</strong>, and <strong>FinBERT sentiment analysis</strong> to analyze historical market data and financial news.
</p>

<p><strong>Highlights</strong></p>

<ul>
  <li>Built an end-to-end ML pipeline using historical stock data and financial news sentiment features</li>
  <li>Implemented SQL database structures for storing market data, sentiment analysis results, and model outputs</li>
  <li>Developed REST APIs using FastAPI to provide prediction results and confidence metrics</li>
  <li>Created interactive React dashboards for visualization of stock trends and predictions</li>
</ul>

<p><strong>Technologies</strong></p>

<p>
Python, FastAPI, React, TypeScript, SQL, XGBoost, FinBERT, Machine Learning
</p>

</td>

<td width="48%" valign="top">

<img
  src="https://github.com/ykydh/Portfolio/blob/main/projects/displays/Pics/Screenshot%202026-05-23%20at%2015.15.00.png?raw=true"
  alt="Stock prediction dashboard"
  width="100%"
/>

</td>
</tr>
</table>

---

## TCP Ethernet File Transfer System

<table>
<tr>
<td width="52%" valign="top">

<p>
A C++ client-server file transfer system built using TCP sockets and custom packet handling. The application supports reliable transmission of text messages and binary files through a structured communication protocol.
</p>

<p><strong>Highlights</strong></p>

<ul>
  <li>Developed a TCP client-server architecture using Berkeley sockets</li>
  <li>Implemented custom packet framing with size-prefixed headers for reliable data reconstruction</li>
  <li>Designed modular socket classes for connection management and data exchange</li>
  <li>Applied buffering, serialization, and error handling techniques for reliable communication</li>
</ul>

<p><strong>Technologies</strong></p>

<p>
C++, TCP/IP, Socket Programming, Networking
</p>

</td>

<td width="48%" valign="top">

<img
  src="https://github.com/ykydh/Portfolio/blob/main/projects/displays/Pics/message.jpeg?raw=true"
  alt="TCP message transfer"
  width="100%"
/>

</td>
</tr>
</table>

---

## Additional Projects

### C++ Data Structures Implementation

<p>
Implemented fundamental data structures and algorithms in C++ to strengthen understanding of memory management, templates, and object-oriented programming.
</p>

<ul>
  <li>Developed a custom binary search tree-based map implementation similar to <code>std::map</code></li>
  <li>Implemented templated classes with separate header and implementation files</li>
  <li>Applied dynamic memory allocation and pointer-based data structures</li>
</ul>

<p>
<a href="https://github.com/ykydh/Portfolio/blob/main/projects/Codes/map/main.cpp">Source Code</a>
</p>

---

### Blackjack Game (C++)

<p>
A single-player Blackjack game developed in C++ featuring game logic, decision-based recommendations, and modular software design.
</p>

<ul>
  <li>Designed object-oriented classes separating game logic and user interaction</li>
  <li>Implemented dynamic advice generation based on player decisions</li>
  <li>Applied modular header/source file organization</li>
</ul>

<p>
<a href="https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Black/Jack.cpp">Source Code</a>
</p>

---

### Neural Network Implementation in C++

<p>
A machine learning learning project focused on implementing neural network fundamentals from scratch without external ML frameworks.
</p>

<ul>
  <li>Implemented dataset generation and vector-based data processing</li>
  <li>Developed activation functions including ReLU and Softmax</li>
  <li>Explored the mathematical foundations behind machine learning models</li>
</ul>

---

## Technical Writing Portfolio

Developed technical documents through a usability engineering project focused on evaluating and improving the Microsoft To Do application.

The project included:

- User research planning and experiment design
- Usability testing methodology
- Data analysis and recommendation reporting
- Technical documentation and visual communication

<p align="center">

<a href="https://github.com/ykydh/Portfolio/blob/main/projects/Proposal.pdf">
  <img
    src="https://github.com/ykydh/Portfolio/blob/main/projects/displays/Proposal/Proposal-2.png?raw=true"
    alt="Proposal preview"
    width="30%"
  />
</a>

<a href="https://github.com/ykydh/Portfolio/blob/main/projects/Usability%20Test.pdf">
  <img
    src="https://github.com/ykydh/Portfolio/blob/main/projects/displays/Usability%20Test/Usability%20Test-01.png?raw=true"
    alt="Usability test preview"
    width="30%"
  />
</a>

<a href="https://github.com/ykydh/Portfolio/blob/main/projects/Recommendation.pdf">
  <img
    src="https://github.com/ykydh/Portfolio/blob/main/projects/displays/Recommendation/Recommendation-02.png?raw=true"
    alt="Recommendation report preview"
    width="30%"
  />
</a>

</p>

---

## What I Bring

- Experience developing software across the full stack, from embedded firmware to cloud-connected applications.
- Hands-on experience with RTOS development, hardware integration, networking, and debugging.
- Ability to communicate technical concepts through documentation, teamwork, and leadership experience.
- Strong interest in embedded systems, aerospace software, and practical engineering solutions.

---

## Connect

<div align="center">

<a href="https://www.linkedin.com/in/yutaro-kiyota-0b8ab7307/">
  <img src="https://img.shields.io/badge/LinkedIn-0A66C2?style=flat&logo=linkedin&logoColor=white" alt="LinkedIn" />
</a>

<a href="mailto:ykydh@umsystem.edu">
  <img src="https://img.shields.io/badge/Email-D14836?style=flat&logo=gmail&logoColor=white" alt="Email" />
</a>

</div>
