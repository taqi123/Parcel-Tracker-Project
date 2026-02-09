# 📦 Smart Parcel Delivery & Tracking System (HELLO G)

## 📌 Project Overview
The **Smart Parcel Delivery & Tracking System** is a console-based C++ application developed as a **Data Structures semester project**.  
It simulates a real-world courier management system using core data structures such as **Linked Lists, Queues, Stacks**, and **File Handling**.

The project demonstrates how classical data structures can be combined to solve practical problems like parcel tracking, delivery scheduling, undoing operations, and persistent storage.

---

## 🎯 Objectives
- Apply **Data Structures concepts** to a real-world problem  
- Implement **Linked Lists** for dynamic parcel storage  
- Maintain **Tracking History** using a nested linked list  
- Simulate delivery scheduling using a **Queue**  
- Support undo operations using a **Stack**  
- Enable **file-based persistence** (save/load data)

---

## ⚙️ Features
- ➕ Add new parcel  
- 📄 View all parcels  
- 🔍 Search parcel (by ID, sender, receiver, status)  
- 🔄 Update parcel status  
- 🗑️ Delete parcel  
- 🕒 View parcel tracking history  
- 🚚 Manage delivery queue (FIFO)  
- ↩️ Undo last operation  
- 💾 Save & load data from files  

---

## 🧠 Data Structures Used
| Data Structure | Purpose |
|---------------|---------|
| Singly Linked List | Store parcel records |
| Nested Linked List | Track parcel history |
| Queue | Delivery scheduling |
| Stack | Undo functionality |
| Text Files | Data persistence |

---

## 🏗️ System Design
The system follows a modular design:
- **Parcel**: Represents a single delivery item  
- **TrackingEvent**: Stores individual tracking updates  
- **DeliveryManager**: Manages parcel linked list  
- **DeliveryQueue**: Handles delivery order  
- **UndoStack**: Stores reversible operations  
- **FileHandler**: Saves and loads system data  

UML diagrams (Use Case, Class, Activity, Sequence) are included in the documentation.

---

## 🛠️ Tools & Technologies
- **Language:** C++ (C++17)
- **IDE:** Visual Studio Code / CodeBlocks
- **Storage:** Text files (.txt)
- **Diagrams:** PlantUML / Draw.io

---

## 👥 Team Members
| Name | Responsibility |
|------|----------------|
| Asadullah | Parcel CRUD & linked list |
| Hafiz Taqi | Tracking history & status |
| Muhammad Faheem | Searching, sorting, queue |
| Hamza Farooq | File handling, undo, documentation |

---

## 🧪 Testing
The system was tested for:
- Correct parcel insertion and deletion  
- Accurate tracking history updates  
- Proper queue scheduling  
- Undo functionality  
- Successful save/load from files  

All major features worked as expected.

---

## 🚀 How to Run
1. Clone the repository  
2. Compile using a C++17 compatible compiler  
3. Run the executable in the terminal  
4. Use the menu to interact with the system  

---

## 📈 Future Enhancements
- GUI-based interface  
- Route optimization using graphs  
- Authentication system  
- Database integration  

---

## 📚 References
- C++ Documentation: https://cplusplus.com  
- Data Structures course material  
- Online tutorials on linked lists, stacks, and queues  

---

⭐ *This project was developed as part of a university Data Structures course and is suitable for academic evaluation and portfolio use.*  
