set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'complexity_graph.png'

set title "Comparison Counts: Naive vs Divide & Conquer"
set xlabel "Input Size (n)"
set ylabel "Comparisons"
set grid
set key left top box


# Column 1 is X (Size), Col 2 is Naive, Col 3 is D&C
plot "comparison_data.txt" using 1:2 with lines lw 2 title "Naive (2n)", \
     "comparison_data.txt" using 1:3 with lines lw 2 title "Divide & Conquer (1.5n)"