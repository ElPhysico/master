set terminal png size 1024, 768 enhanced font "Times,28"

#set title "Mean first-passage time"
set key off
set xlabel "p"
set ylabel "<#steps> / <#steps>_d_i_f_f"

#set yrange[0.6:0.8]
#set output "../png/fpt/sysL/fpt-L=10.png"
#plot	"../data/sysL/fpt-L=10.dat" using 1:4:5 ti "L = 10" with yerr
#set output "../png/fpt/sysL/fpt-L=20.png"
#plot	"../data/sysL/fpt-L=20.dat" using 1:4:5 ti "L = 20" with yerr
#set output "../png/fpt/sysL/fpt-L=50.png"
#plot	"../data/sysL/fpt-L=50.dat" using 1:4:5 ti "L = 50" with yerr
#set output "../png/fpt/sysL/fpt-L=100.png"
#plot	"../data/sysL/fpt-L=100.dat" using 1:4:5 ti "L = 100" with yerr
#set output "../png/fpt/sysL/fpt-L=200.png"
#plot	"../data/sysL/fpt-L=200.dat" using 1:4:5 ti "L = 200" with yerr
#set output "../png/fpt/sysL/fpt-L=500.png"
#plot	"../data/sysL/fpt-L=500.dat" using 1:4:5 ti "L = 500" with yerr
#set output "../png/fpt/sysL/fpt-L=1000.png"
#plot	"../data/sysL/fpt-L=1000.dat" using 1:4:5 ti "L = 1000" with yerr

#set size 2,2

set style line 500 ps 3 lw 3

set xtics 0.2
set ytics 2

set key left top Left title 'System size L' box 3
set output "../graphs/summercamp/fpt.png"
plot	"../data/L/fpt-L=10.dat" using 1:4:5 ls 500 pt 19 lc rgb "red" ti " 10", \
	"../data/L/fpt-L=20.dat" using 1:4:5 ls 500 pt 8 lc rgb "blue" ti " 20", \
	"../data/L/fpt-L=50.dat" using 1:4:5 ls 500 pt 4 lc rgb "green" ti " 50", \
	"../data/L/fpt-L=100.dat" using 1:4:5 ls 500 pt 7 lc rgb "brown" ti " 100", \
	"../data/L/fpt-L=200.dat" using 1:4:5 ls 500 pt 9 lc rgb "magenta" ti " 200", \
	"../data/L/fpt-L=500.dat" using 1:4:5 ls 500 pt 5 lc rgb "black" ti " 500", \
	"../data/L/fpt-L=1000.dat" using 1:4:5 ls 500 pt 26 lc rgb "gray" ti " 1000", \
