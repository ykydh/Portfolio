<!-- HEADER BANNER -->
<p align="center">
  <img 
    src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=200&section=header&text=Yutaro%20Kiyota&fontSize=40&fontAlignY=40&desc=Embedded%20Systems%20%7C%20Software%20Development%20%7C%20CS%20Student&descAlignY=60&animation=fadeIn"
    width="100%" 
  />

  <img src="https://skillicons.dev/icons?i=cpp,python,html,linux,git,vscode,mysql" />
</p>

# **Yutaro Kiyota**

Hi, I’m Yutaro! A passionate junior studying Computer Science at **Missouri University of Science & Technology**.
 
- Into Embedded Systems & Software Development  
- Senior Resident Assistant & Satellite Research Team Contributor  
- Running & Fitness enthusiast  

---

### 📄 **Documents**
- [Resume](https://github.com/ykydh/Portfolio/blob/main/projects/resume8-1.pdf)  
- [LinkedIn](https://www.linkedin.com/in/yutaro-kiyota-0b8ab7307/)

---

### 🛠️ **Skills**

- C++ / Python / SQL  
- Data Structures / Algorithm  
- Technical Writing  
- Leadership & Communication
  
---

### 🎓 **Education**
***Missouri University of Science & Technology***
</p>
Major: Computer Science
</p>
Year: Junior
</p>

---
### 🌐 **Languages**
- 🇯🇵 Japanese — Native  
- 🇺🇸 English — Fluent

---

### **Programming Portfolio**

#### ♦ TCP ethernet file transfer scheme
A C++ client-server file transfer system over TCP sockets.

This project is a TCP-based client-server application written in C++.<br />
It allows clients to send either message or binary files (eg.images) to a server.<br />
The system handles data packetization, transmission over sockets and reassembly into the original file or message.<br />
- Implemented using Berkeley sockets(socket, bind, listen, accept, connect, recv, send).
- Supprt two modes
  - Message Mode: Send plain text message between client and server.
  - File Mode: Send arbitrary binary files (e.g., .jpg, .pdf)
- Specification
  - Split data into 4096-byte packet
  - Prepends header with total data size to keep track of transferred data size.

![TCP message transfer](https://github.com/ykydh/Portfolio/blob/main/projects/displays/Pics/message.jpeg)

#### ♦ Tree Map (Binary Search Tree)  
Recreating a simplified `std::map` using a BST.  
- Parses input character frequency into mapped ASCII  
- Demonstrates core map operations using templated nodes  

**Links:** [Main](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/map/main.cpp) | [TreeNode](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/map/TreeNode.h) | [MyMap.h](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/map/MyMap.h) | [MyMap.hpp](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/map/MyMap.hpp)

---

#### ♦ Black Jack  
A single-player Black Jack game with a twist:  
- Dynamic advice system with risk-reward balance  
- Different payouts depending on user decision-making  

**Links:** [Main](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Black/Jack.cpp) | [Header](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Black/Black5.h) | [Implementation](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Black/Black5.cpp)

---

#### ♦ Ongoing: Machine Learning in C++  
- Implements spiral dataset generation  
- Activation functions: ReLU & Softmax  

```cpp
std::pair<std::vector<std::vector<double>>, std::vector<int>>
create_data(int points, int classes) {
  std::vector<std::vector<double>> X(points * classes, std::vector<double>(2));
  std::vector<int> y(points * classes);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> noise(0, 0.2);

  for (int class_number = 0; class_number < classes; ++class_number) {
    for (int i = 0; i < points; ++i) {
      int index = points * class_number + i;
      double r = static_cast<double>(i) / points;
      double t = class_number * 4 + 4.0 * i / points + noise(gen);
      X[index][0] = r * sin(t * 2.5);
      X[index][1] = r * cos(t * 2.5);
      y[index] = class_number;
    }
  }
  return std::make_pair(X, y);
}
```

---
## 📝 **Technical Writing Portfolio**

The following documents detail a usability experiment conducted on the Microsoft To Do application:

- **The Proposal** outlines the experiment’s methodology, its expected benefits, the required personnel and equipment, a proposed schedule, and the informed consent form.
- **The Usability Testing** includes a detailed test plan with clearly defined user tasks, a system for calculating error rates, a structured test log for observation recording, and thoughtfully designed pre- and post-screening questionnaires to gather feedback.
- **The Recommendation Report** provides an in-depth summary of findings and analysis, evaluating the usability and effectiveness of Microsoft To Do. It concludes with actionable recommendations to improve its intuitiveness and user-friendliness.

### 🔍 **What I Learned from This Project**

- **Effective Audience Analysis**  
  I developed the ability to assess target audiences and tailor messages to resonate with their specific expectations and needs.

- **Clarity and Precision in Writing**  
  I learned to structure documents for maximum clarity and engagement, using formatting and language that make content accessible and persuasive.

- **Data Analysis and Prioritization**  
  I gained experience identifying patterns in user behavior and prioritizing issues based on impact and urgency.

- **Visual Communication**  
  I became proficient in using charts, graphs, and tables to present information in a way that is both accurate and visually impactful, choosing representations that support clear decision-making.

<ins>*Click on the images below to view each document in full.*</ins>

---

## 📄 **Proposal**
[![Proposal Preview](https://github.com/ykydh/Portfolio/blob/main/projects/displays/Proposal/Proposal-2.png)](https://github.com/ykydh/Portfolio/blob/main/projects/Proposal.pdf)

---

## 🧪 **Usability Testing**
[![Usability Test Preview](https://github.com/ykydh/Portfolio/blob/main/projects/displays/Usability%20Test/Usability%20Test-01.png)](https://github.com/ykydh/Portfolio/blob/main/projects/Usability%20Test.pdf)

---

## 📊 **Recommendation Report**
[![Recommendation Report Preview](https://github.com/ykydh/Portfolio/blob/main/projects/displays/Recommendation/Recommendation-02.png)](https://github.com/ykydh/Portfolio/blob/main/projects/Recommendation.pdf)

---

## 🤝 Connect with Me

<p align="center">
  <a href="https://www.linkedin.com/in/ykydh-0b8ab7307/" target="blank"><img align="center" src="https://img.shields.io/badge/LinkedIn-0077B5?style=flat&logo=linkedin&logoColor=white" alt="LinkedIn" /></a>
  <a href="mailto:ykydh@umsystem.edu"><img align="center" src="https://img.shields.io/badge/Gmail-D14836?style=flat&logo=gmail&logoColor=white" alt="Gmail" /></a>
</p>
