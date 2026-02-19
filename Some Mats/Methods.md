# Methods

Based on the sources provided, here is the breakdown of the methods, strategies, and processes mentioned in each document.

### **Source 1: DS1.pdf**
*   **Data Collection Methods:** Web scraping, accessing APIs, querying databases/spreadsheets.
*   **Data Preparation Strategies:**
    *   **Imputation:** Estimating or replacing missing values using statistical methods.
    *   **Outlier Treatment:** Using statistical tests and visualization to identify and handle extreme values.
    *   **Normalization:** Transforming variables to a common scale/range.
    *   **Integrity Checks:** Validations to identify inconsistencies or duplications.
*   **Modeling Techniques:**
    *   **Algorithms:** Linear Regression, Decision Trees, Neural Networks.
    *   **Feature Selection:** Choosing relevant variables to simplify models and reduce overfitting.
    *   **Hyperparameter Tuning:** Grid Search, Random Search, Bayesian Optimization.
*   **Evaluation Methods:** Statistical analysis (Accuracy, Precision, Recall, F1 score) and Data Visualization.
*   **Deployment Methods:** Creating APIs, building interactive dashboards (Tableau, Power BI).

### **Source 2: DS2.pdf**
*   **Data Preprocessing Overview:** Data cleaning (noise removal), Data integration, Data selection, Data transformation.
*   **Classification (Predictive) Methods:**
    *   **Feature Extraction:** Measuring properties (e.g., length, lightness).
    *   **Decision Boundary:** Creating rules (e.g., `If length > 12 then Sea Bass`) to separate classes.
    *   **Cross-Validation:** 3-fold cross-validation to estimate accuracy.
*   **Clustering (Descriptive) Methods:**
    *   **Similarity Measure:** Euclidean Distance.
    *   **Outlier Analysis:** Discarding data that does not comply with general behavior.
*   **Association Rule Mining:** Finding dependency rules (e.g., "If Diaper, then Beer").
*   **Regression:** Linear Regression ($y = mx + c$) for predicting continuous values.

### **Source 3: DS3.pdf**
*   **Data Cleaning (Missing Values):**
    *   **Basic:** Mean/Median/Mode imputation, Arbitrary value imputation, Constant value imputation.
    *   **Statistical:** K-Nearest Neighbors (KNN) imputation, Regression imputation.
    *   **Machine Learning:** Decision Tree/Random Forest imputation, Deep Learning (Autoencoders).
*   **Data Cleaning (Noisy Data):**
    *   **Binning:** Equal-width partitioning, Equal-depth partitioning, Smoothing by bin means/boundaries.
    *   **Regression Smoothing:** Fitting data to functions (Linear, Polynomial, LOESS).
    *   **Clustering:** Grouping to replace points with centroids.
*   **Data Integration:**
    *   **Correlation Analysis:** Pearson Correlation Coefficient (linear), Spearman’s Rank Correlation (ordinal/non-linear).
*   **Data Transformation (Normalization):**
    *   Min-Max Normalization.
    *   Z-Score Normalization.
    *   Decimal Scaling.
    *   Robust Scaling (using IQR).
    *   Max Abs Scaling.
    *   Log Transformation.
    *   Unit Vector (L2) Normalization.
*   **Handling Inconsistency:** Standardizing formats (dates, units), Spell-checking (Levenshtein distance), Deduplication.

### **Source 4: DS4.pdf**
*   **Data Reduction Strategies:**
    *   **Data Cube Aggregation:** Multidimensional aggregation at multiple levels.
    *   **Dimensionality Reduction:** Principal Component Analysis (PCA), Factor Analysis (FA), Linear Discriminant Analysis (LDA), Singular Value Decomposition (SVD).
    *   **Feature Selection:** Step-wise forward selection, Step-wise backward elimination, Decision-tree induction.
    *   **Data Compression:**
        *   *Lossless:* Run Length Encoding (RLE), Huffman Coding, Lempel-Ziv.
        *   *Lossy:* JPEG, MPEG, MP3, Discrete Cosine Transform (DCT), Wavelet transform.
    *   **Numerosity Reduction:**
        *   *Parametric:* Regression, Log-linear models.
        *   *Non-parametric:* Histograms, Clustering, Sampling (SRSWOR, SRSWR, Stratified, Cluster).
*   **Discretization & Concept Hierarchy:**
    *   **Entropy-Based Discretization:** Supervised method using Information Gain (top-down split).
    *   **Segmentation by Natural Partitioning:** The **3-4-5 rule** for segmenting numeric data into natural intervals.