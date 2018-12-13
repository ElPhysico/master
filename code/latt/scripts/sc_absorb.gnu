set terminal png size 1024, 768 enhanced font "Times,28"

set xlabel "p"
set ylabel "<#steps> / <#steps>_d_i_f_f"

set style line 500 ps 3 lw 3

set xtics 0.2
set ytics 0.4

set key right top Left title 'Alpha' box 3
set output "../graphs/summercamp/fpt-absorb.png"
plot	"../data/alpha/L=200/fpt-alpha=0.1.dat" using 1:4 ls 500 pt 19 lc rgb "red" ti " 0.1", \
	"../data/alpha/L=200/fpt-alpha=0.2.dat" using 1:4 ls 500 pt 8 lc rgb "blue" ti " 0.2", \
	"../data/alpha/L=200/fpt-alpha=0.3.dat" using 1:4 ls 500 pt 4 lc rgb "green" ti " 0.3", \
	"../data/alpha/L=200/fpt-alpha=0.4.dat" using 1:4 ls 500 pt 7 lc rgb "brown" ti " 0.4", \
	"../data/alpha/L=200/fpt-alpha=0.5.dat" using 1:4 ls 500 pt 9 lc rgb "magenta" ti " 0.5", \
	"../data/alpha/L=200/fpt-alpha=0.6.dat" using 1:4 ls 500 pt 5 lc rgb "black" ti " 0.6", \
	"../data/alpha/L=200/fpt-alpha=0.7.dat" using 1:4 ls 500 pt 26 lc rgb "gray" ti " 0.7", \
	"../data/alpha/L=200/fpt-alpha=0.8.dat" using 1:4 ls 500 pt 22 lc rgb "pink" ti " 0.8", \
	"../data/alpha/L=200/fpt-alpha=0.9.dat" using 1:4 ls 500 pt 10 lc rgb "navy" ti " 0.9", \
	"../data/alpha/L=200/fpt-alpha=1.dat" using 1:4 ls 500 pt 24 lc rgb "#4B0082" ti " 1.0", \
