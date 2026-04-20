### DATA NORMALIZATION
# QUICK REVISION NOTE

### Definition:
Normalization is the process of scaling data values to a common range 
(such as 0 to 1 or -1 to 1) so that all features have equal importance.

--------------------------------------------------
## ADVANTAGES OF NORMALIZATION

1. Improves ML performance

   * Ensures all features have equal scale
   * Prevents large values from dominating small values

2. Better handling of outliers
   * Reduces the influence of extreme values

3. Improves interpretability
   * Makes it easier to compare features on the same scale

4. Better generalization
   * Makes models less sensitive to scale differences
   * Improves prediction accuracy on new data

--------------------------------------------------
## DISADVANTAGES OF NORMALIZATION

1. Loss of original information
   * Original units and scale are lost

2. Harder to detect outliers
   * Outliers are scaled along with normal values

3. Reduced interpretability (in real-world units)
   * Results may not directly reflect real-world meaning

4. Additional computational cost
   * Requires extra processing time

--------------------------------------------------
## CONCLUSION

Normalization improves model performance and consistency, 
but may cause loss of original scale information and increase computation.

--------------------------------------------------
> KEY MEMORY LINE:
**"Normalization improves performance, but loses original scale."**