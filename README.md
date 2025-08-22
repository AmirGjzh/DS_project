# DebtTracker

A high-performance **financial tracking system** written in C++ for managing debts and credits between individuals.  
It uses a **self-balancing map (AVL-like)** and a **segment tree** to efficiently calculate balances, debtors, creditors, and settlements.

---

## ✨ Features
- **Track Loans**: Record and update loans between individuals.  
- **Net Capital Analysis**: Identify who has the highest or lowest net capital.  
- **Debtor & Creditor Counts**: See how many people someone owes or is owed by.  
- **Settle Debts**: Calculate the exact amount required to settle debts between two people.  
- **Efficient Data Structures**: Uses a custom AVL-like map and segment tree for fast queries.  

---

## ⚙️ Commands
The program reads a number of queries `q`, followed by `q` commands.  
Each command has the following format:

1. **Loan**  
   ```
   1 s1 s2 x
   ```
   - Person `s1` loans `x` dollars to person `s2`.  

2. **Max Net Capital**  
   ```
   2
   ```
   - Prints the person with the **highest net capital**.  
   - If no valid person exists, prints `-1`.  

3. **Min Net Capital**  
   ```
   3
   ```
   - Prints the person with the **lowest net capital**.  
   - If no valid person exists, prints `-1`.  

4. **Count Debtors**  
   ```
   4 s
   ```
   - Prints how many people owe money to person `s`.  

5. **Count Creditors**  
   ```
   5 s
   ```
   - Prints how many people person `s` owes money to.  

6. **Settle Debt**  
   ```
   6 s1 s2
   ```
   - Prints the exact amount `s1` must pay `s2` to settle their debt.  
   - Amounts are formatted with two decimal places.  

---
