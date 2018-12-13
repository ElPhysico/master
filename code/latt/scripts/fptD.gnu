set terminal png size 1024, 768 enhanced font "Times,28"


#set title "Mean first passage time"
set key off
set xlabel "p"
set ylabel "<#steps> / <#steps>_d_i_f_f"


#set yrange[0.6:0.8]
#set output "../png/fpt/detecR/fpt-D=1.png"
#plot	"../data/detecR/fpt-D=1.dat" using 1:4:5 ti "D = 1" with yerr

#set output "../png/fpt/detecR/fpt-D=2.png"
#plot	"../data/detecR/fpt-D=2.dat" using 1:4:5 ti "D = 2" with yerr

#set output "../png/fpt/detecR/fpt-D=3.png"
#plot	"../data/detecR/fpt-D=3.dat" using 1:4:5 ti "D = 3" with yerr

#set output "../png/fpt/detecR/fpt-D=4.png"
#plot	"../data/detecR/fpt-D=4.dat" using 1:4:5 ti "D = 4" with yerr

#set output "../png/fpt/detecR/fpt-D=5.png"
#plot	"../data/detecR/fpt-D=5.dat" using 1:4:5 ti "D = 5" with yerr

#set output "../png/fpt/detecR/fpt-D=10.png"
#plot	"../data/detecR/fpt-D=10.dat" using 1:4:5 ti "D = 10" with yerr

#set output "../png/fpt/detecR/fpt-D=15.png"
#plot	"../data/detecR/fpt-D=15.dat" using 1:4:5 ti "D = 15" with yerr

#set output "../png/fpt/detecR/fpt-D=20.png"
#plot	"../data/detecR/fpt-D=20.dat" using 1:4:5 ti "D = 20" with yerr


set style line 500 ps 3 lw 3

set xtics 0.2
set ytics 0.4

set key right top Left title 'Det. range D' box 3
set output "../graphs/summercamp/fpt-D.png"
#plot	"../data/D/fpt-D=1.dat" using 1:4:5 ti "D = 1" with yerr, \
	"../data/D/fpt-D=2.dat" using 1:4:5 ti "D = 2" with yerr, \
	"../data/D/fpt-D=3.dat" using 1:4:5 ti "D = 3" with yerr, \
	"../data/D/fpt-D=4.dat" using 1:4:5 ti "D = 4" with yerr, \
	"../data/D/fpt-D=5.dat" using 1:4:5 ti "D = 5" with yerr, \
	"../data/D/fpt-D=10.dat" using 1:4:5 ti "D = 10" with yerr, \
	"../data/D/fpt-D=15.dat" using 1:4:5 ti "D = 15" with yerr, \
	"../data/D/fpt-D=20.dat" using 1:4:5 ti "D = 20" with yerr, \

plot	"../data/D/fpt-D=1.dat" using 1:4 ls 500 pt 19 lc rgb "red" ti " 1", \
	"../data/D/fpt-D=2.dat" using 1:4 ls 500 pt 8 lc rgb "blue" ti " 2", \
	"../data/D/fpt-D=3.dat" using 1:4 ls 500 pt 4 lc rgb "green" ti " 3", \
	"../data/D/fpt-D=4.dat" using 1:4 ls 500 pt 7 lc rgb "brown" ti " 4", \
	"../data/D/fpt-D=5.dat" using 1:4 ls 500 pt 9 lc rgb "magenta" ti " 5", \
	"../data/D/fpt-D=10.dat" using 1:4 ls 500 pt 5 lc rgb "black" ti " 10", \
	"../data/D/fpt-D=15.dat" using 1:4 ls 500 pt 26 lc rgb "gray" ti " 15", \
	"../data/D/fpt-D=20.dat" using 1:4 ls 500 pt 22 lc rgb "pink" ti " 20", \

