# Qt Car Workshop Manager

## 🚗 Overview

This repository contains two Qt-based applications that work together:

### 🛠 QtCarWorkshopManager
An application that simulates a **single automotive workshop**:
- Generates a random workshop location (city + address) on startup.
- Dynamically generate clients' cars and repair issues
- Dynamically adds and updates cars in a scrollable UI.
- View and fix car issues
- Scrollable client list with real-time interaction
- Tracks total revenue (`takings`) and types of issues fixed.
- Sends current workshop state over TCP after each repair.
- Creates simple reports in PDF about all repairs

### 📊 QtMultipleWorkshopsManager
A second application that acts as a **central monitor** for multiple workshops:
- Runs a TCP server and listens for incoming workshop data.
- Parses received messages with `city`, `address`, `takings`, and issues.
- Dynamically adds or updates workshop widgets in a scrollable UI.
- Visually displays each workshop's location, income, and repair history (e.g. `3x Dead Battery – 1200 $`).

### 🔌 Communication
Data is exchanged in a simple TCP format:
city=Krakow
address=Szeroka 184
takings=3160
issue=Loose tie rod:1400
issue=Dead battery:400

---

## 💻 Tech Stack

- **Language:** C++
- **Framework:** Qt 5 / Qt 6 (Widgets)
- **PDF Generation:** Qt PDF module or HTML-to-PDF workaround

---

## 📸 UI Sketch

The initial UI mockup for the workshop view:

![image](https://github.com/user-attachments/assets/e75cceea-3f11-40b3-a19f-4ea8442ac197)


---

## 🚀 Getting Started

### Prerequisites

- Qt 5.15+ or Qt 6.x
- CMake or Qt Creator

### Build Instructions

```bash
git clone https://github.com/yourusername/WorkshopManagerQt.git
cd WorkshopManagerQt
open with Qt Creator or build with CMake
```

---

## Screenshots of the app:

![image](https://github.com/user-attachments/assets/7947d2d5-7e8e-41cc-830e-5c0ef9ae7755)

generated report:

![image](https://github.com/user-attachments/assets/46a4673b-290e-48aa-92c3-487201718372)

apps working together, sharing information with TCP:

![image](https://github.com/user-attachments/assets/a60bfc77-d0a5-4f94-b388-cc54ee857b1f)
