# Data Preprocessing – Quick Revision Note

## Definition
**Data preprocessing** is the process of cleaning, transforming, and organizing raw data  
to make it suitable for data analysis and machine learning.

Real-world data is often **incomplete, noisy, and inconsistent**, so preprocessing is required.

---

## Problems in Real-World Data (Dirty Data)

### 1. Incomplete Data
- Missing attribute values  
- Missing important records or fields  
- Example: Occupation = blank  

### 2. Noisy Data
- Contains errors or outliers  
- Example: Salary = -10 (invalid value)  

### 3. Inconsistent Data
- Conflicting or incorrect information  
- Examples:
  - Age = 42, but birthday shows different age  
  - Rating system changed (1,2,3 → A,B,C)  
  - Duplicate records with different values  

---

## Why Data Preprocessing is Required

### 1. Improving Data Quality
- Handle missing values (mean, median, prediction, or removal)  
- Remove noise and outliers  
- Improves accuracy and reliability  

### 2. Ensuring Consistency
- **Normalization / Standardization:** brings data to common scale  
- **Data Transformation:** converts data into consistent format  

### 3. Enhancing Model Performance
- Feature selection removes irrelevant features  
- Reduces dimensionality  
- Improves accuracy and reduces computation time  

### 4. Facilitating Data Understanding
- Data cleaning improves understanding  
- Makes visualization and analysis easier  

### 5. Reducing Computational Cost
- Reduces dataset size  
- Faster training  
- Less memory and CPU usage  

### 6. Improving Model Generalization
- Reduces overfitting  
- Improves performance on new/unseen data  
- Balances class distribution  

---

## Final Conclusion (Exam Line)
Data preprocessing converts raw data into clean, consistent, and usable form,  
which improves accuracy, performance, and reliability of machine learning models.

---

## Key Memory Line
**Raw data is dirty → preprocessing makes it clean, consistent, and useful.**