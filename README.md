<!-- HEADER BANNER -->
<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=200&section=header&text=Yutaro%20Kiyota&fontSize=40&fontAlignY=40&desc=Embedded%20Systems%20%7C%20Software%20Development%20%7C%20CS%20Student&descAlignY=60&animation=fadeIn"/>
</p>

# ✨ **Yutaro Kiyota**

Hi, I’m Yutaro! A passionate sophomore studying Computer Science at **Missouri University of Science & Technology**.

- 🌍 International student from Japan  
- ⚙️ Into Embedded Systems & Cybersecurity  
- 🎓 RA & Satellite Research Team Contributor  
- 🏃 Running & Fitness enthusiast  

---

### 🎓 **Education**
**Missouri University of Science & Technology**  
**Major**: Computer Science  
**Year**: Junior

---

### 📄 **Documents**
- [Resume](https://github.com/ykydh/Portfolio/blob/main/projects/Resume_.pdf)  
- [LinkedIn](https://www.linkedin.com/in/yutaro-kiyota-0b8ab7307/)

---

### 🛠️ **Skills**
<p align="center">
  <img src="https://skillicons.dev/icons?i=cpp,python,linux,git,vscode,sql" />
</p>

- C++ / Python / SQL  
- Data Structures / Algorithm  
- Technical Writing  
- Leadership & Communication  

---

### 🌐 **Languages**
- 🇯🇵 Japanese — Native  
- 🇺🇸 English — Fluent

---

### 🚀 **Programming Portfolio**

#### ♦ Black Jack  
A single-player Black Jack game with a twist:  
- Dynamic advice system with risk-reward balance  
- Different payouts depending on user decision-making  

**Links:** [Main](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Jack.cpp) | [Header](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Black5.h) | [Implementation](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/Black5.cpp)

---

#### ♦ Tree Map (Binary Search Tree)  
Recreating a simplified `std::map` using a BST.  
- Parses input character frequency into mapped ASCII  
- Demonstrates core map operations using templated nodes  

**Links:** [Main](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/main.cpp) | [TreeNode](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/TreeNode.h) | [MyMap.h](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/MyMap.h) | [MyMap.hpp](https://github.com/ykydh/Portfolio/blob/main/projects/Codes/MyMap.hpp)

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
### 📝 **Technical Writing Portfolio**
- [International Student Challenges: Mental & Academic Struggles](https://github.com/ykydh/Portfolio/blob/main/projects/Writing/StudentStruggles.pdf)  
- [Research Paper: Lightweight RTOS for Raspberry Pi Pico W](https://github.com/ykydh/Portfolio/blob/main/projects/Writing/PicoRTOSResearch.pdf)  
- [Data Analysis of MLB Pitching Stats](https://github.com/ykydh/Portfolio/blob/main/projects/Writing/BaseballAnalytics.pdf)

---
