set terminal pngcairo size 1200,500 enhanced font 'Arial,10'
set output 'Q3_sorting_analysis_results.png'

set style fill solid 0.7 border -1
set boxwidth 0.4
set grid ytics lc rgb "#bbbbbb" lw 1

set xtics ("Merge Sort" 0, "Quick Sort" 1) scale 0

set multiplot layout 1,3 title "Algorithm Performance Analysis (N=100,000 | 80% Sorted)" font ",14"

set title "Execution Time (Lower is Better)" font ",11"
set ylabel "Time (seconds)"
set yrange [0:*]
# Plot column 1 (Type) vs Column 4 (Time)
plot 'Q3_comparison_data.txt' using 1:4 notitle with boxes lc rgb "#e74c3c"

set title "Number of Comparisons (Lower is Better)" font ",11"
set ylabel "Comparisons (Millions)"
set format y "%.1f M"
# Plot column 1 (Type) vs Column 2 (Comp), scaled by 1 million
plot 'Q3_comparison_data.txt' using 1:($2/1000000.0) notitle with boxes lc rgb "#3498db"

set title "Max Recursion Depth (Lower is Better)" font ",11"
set ylabel "Stack Depth"
set format y "%.0f"
# Plot column 1 (Type) vs Column 3 (Depth)
plot 'Q3_comparison_data.txt' using 1:3 notitle with boxes lc rgb "#2ecc71"

unset multiplot
