set terminal pngcairo size 1200,800 enhanced font 'Verdana,10'

# Execution Time
set output 'Q2_graph_time.png'
set title "Execution Time vs Duplicate Percentage"
set xlabel "Duplicate Percentage (%)"
set ylabel "Time (seconds)"
set grid
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.9
set xtics ("10%%" 0, "50%%" 1, "90%%" 2)

# "every 2::0" : rows 0, 2, 4 (Standard)
# "every 2::1" : rows 1, 3, 5 (Randomized)

plot 'data.txt' every 2::0 using 3:xtic(1) title "Standard QS" lc rgb "red", \
     'data.txt' every 2::1 using 3 title "Randomized QS" lc rgb "blue"

# Comparisons
set output 'Q2_graph_comparisons.png'
set title "Comparisons vs Duplicate Percentage"
set ylabel "Number of Comparisons"
plot 'data.txt' every 2::0 using 4:xtic(1) title "Standard QS" lc rgb "red", \
     'data.txt' every 2::1 using 4 title "Randomized QS" lc rgb "blue"

# Recursion Depth
set output 'Q2_graph_depth.png'
set title "Max Recursion Depth vs Duplicate Percentage"
set ylabel "Max Depth"
plot 'data.txt' every 2::0 using 5:xtic(1) title "Standard QS" lc rgb "red", \
     'data.txt' every 2::1 using 5 title "Randomized QS" lc rgb "blue"
