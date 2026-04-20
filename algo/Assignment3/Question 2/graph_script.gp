set terminal pngcairo size 1200,800 enhanced font 'Verdana,10'

set style line 1 lc rgb '#E41A1C' lt 1 lw 3 pt 7 ps 1.5   # Red points
set style line 2 lc rgb '#377EB8' lt 1 lw 3 pt 5 ps 1.5   # Blue points

set grid
set xrange [0:100] # Set X-axis range from 0 to 100%
set xtics 10       # Mark every 10 units on X-axis

#Graph 1: Execution Time
set output 'line_time.png'
set title "Execution Time vs Duplicate Percentage"
set xlabel "Duplicate Percentage (%)"
set ylabel "Time (seconds)"
set key top left

plot 'data.txt' every 2::0 using 1:3 with linespoints ls 1 title "Standard QS", \
     'data.txt' every 2::1 using 1:3 with linespoints ls 2 title "Randomized QS"

#Graph 2: Comparisons
set output 'line_comparisons.png'
set title "Comparisons vs Duplicate Percentage"
set ylabel "Number of Comparisons"
set key top left

plot 'data.txt' every 2::0 using 1:4 with linespoints ls 1 title "Standard QS", \
     'data.txt' every 2::1 using 1:4 with linespoints ls 2 title "Randomized QS"

#Graph 3: Recursion Depth
set output 'line_depth.png'
set title "Max Recursion Depth vs Duplicate Percentage"
set ylabel "Max Depth"
set key top left

plot 'data.txt' every 2::0 using 1:5 with linespoints ls 1 title "Standard QS", \
     'data.txt' every 2::1 using 1:5 with linespoints ls 2 title "Randomized QS"
