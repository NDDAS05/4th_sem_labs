set terminal png size 1024,768
set output "comparison.png"

set title "QuickSelect vs Median of Medians"
set xlabel "Input Size (n)"
set ylabel "Execution Time (seconds)"
set grid
set key left top

plot "results.txt" using 1:2 with linespoints title "QuickSelect", \
     "results.txt" using 1:3 with linespoints title "MedianOfMedians"
