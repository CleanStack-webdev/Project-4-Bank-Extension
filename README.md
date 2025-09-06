# 🏦 Bank Management System with Transactions  

A console-based C++ application that simulates a simple **bank client management system with transactions support**.  
The program allows adding, listing, updating, deleting, and searching client records stored in a text file, **plus performing deposit, withdraw, and balance inquiry operations**.  

It uses a **menu-driven interface** where each option corresponds to a specific operation on the clients' database.  

---

## ✨ Features  
- 📋 Display all clients in a formatted table  
- ➕ Add new clients with unique account numbers  
- 🗑️ Delete existing clients after confirmation  
- ✏️ Update client information (PinCode, Name, Phone, Balance)  
- 🔍 Search for a client by account number and display details  
- 💾 Persistent storage of client data in a text file (`Clients.txt`)  
- 💳 **Transactions Menu:**  
  - 💵 Deposit money into an account  
  - 💸 Withdraw money with balance validation  
  - 📊 Show total balances of all clients  

---

## 🛠️ Technologies  
- **C++**  
- Standard libraries:  
  - `<iostream>` (input/output)  
  - `<fstream>` (file handling)  
  - `<vector>` (dynamic storage)  
  - `<string>` (text processing)  
  - `<iomanip>` (formatted output)  

---

## ⚙️ How It Works  
1. The program starts by displaying the **Main Menu** with available options.  
2. User selects one of the following operations:  
   - **1:** Show Client List  
   - **2:** Add New Client  
   - **3:** Delete Client  
   - **4:** Update Client Info  
   - **5:** Find Client  
   - **6:** Transactions  
   - **7:** Exit Program  
3. Inside the **Transactions Menu**, the user can:  
   - **1:** Deposit  
   - **2:** Withdraw  
   - **3:** Show Total Balances  
   - **4:** Return to Main Menu  
4. Each client is stored as a record in `Clients.txt` using the format:  
```
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
```
5. The system ensures **unique account numbers** when adding new clients.  
6. Data is automatically saved to file after any update, deletion, or transaction.  

---

## 📂 Project Structure  
```
Bank-Management-Transactions/
│── main.cpp # Main source code
│── Clients.txt # File that stores client records
│── README.md # Project documentation
```

---

## 🎯 Learning Outcomes  
This project demonstrates fundamental concepts of **C++ programming**, such as:  
- Structs for data representation  
- Enums for menu navigation  
- Functions for modular design  
- File I/O operations  
- Input validation and user interaction  
- Implementing **transactional operations (deposit, withdraw, balance inquiry)**  

---
