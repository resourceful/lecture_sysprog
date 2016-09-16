reset
set terminal pngcairo enhanced color font "Helvetica, 18" 
set output "iotest.png"
set grid
unset key
set style data linespoint

set xtics ("1" 1, "64" 2, "256" 3, "512" 4, "2048" 5, "4096" 6, "16384" 7, "32768" 8, "65536" 9, "81920" 10) rotate by -45
set xlabel "Buffer Size"
set ylabel "Time"

set title "I/O Efficiency (Buffer Size Vs Time)"
plot 'iotest.data' using 3:2 lt 1 dt 2 pt 3

set output "iotest2.png"
set yrange [0:1.8]
plot 'iotest.data' using 3:2 lt 1 dt 2 pt 3 
