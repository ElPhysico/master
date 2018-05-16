set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Mean first passage time"
set key off
set xlabel "p"
set ylabel "<#steps> / <#steps>_0"

#set yrange[0.6:0.8]
set output "../png/fpt/sysL/fpt-L=10.png"
plot	"../data/sysL/fpt-L=10.dat" using 1:4:5 ti "L = 10" with yerr
set output "../png/fpt/sysL/fpt-L=20.png"
plot	"../data/sysL/fpt-L=20.dat" using 1:4:5 ti "L = 20" with yerr
set output "../png/fpt/sysL/fpt-L=50.png"
plot	"../data/sysL/fpt-L=50.dat" using 1:4:5 ti "L = 50" with yerr
set output "../png/fpt/sysL/fpt-L=100.png"
plot	"../data/sysL/fpt-L=100.dat" using 1:4:5 ti "L = 100" with yerr
set output "../png/fpt/sysL/fpt-L=200.png"
plot	"../data/sysL/fpt-L=200.dat" using 1:4:5 ti "L = 200" with yerr
set output "../png/fpt/sysL/fpt-L=500.png"
plot	"../data/sysL/fpt-L=500.dat" using 1:4:5 ti "L = 500" with yerr
set output "../png/fpt/sysL/fpt-L=1000.png"
plot	"../data/sysL/fpt-L=1000.dat" using 1:4:5 ti "L = 1000" with yerr

set key left top
set output "../png/fpt/sysL/fpt.png"
plot	"../data/sysL/fpt-L=10.dat" using 1:4:5 ti "L = 10" with yerr, \
	"../data/sysL/fpt-L=20.dat" using 1:4:5 ti "L = 20" with yerr, \
	"../data/sysL/fpt-L=50.dat" using 1:4:5 ti "L = 50" with yerr, \
	"../data/sysL/fpt-L=100.dat" using 1:4:5 ti "L = 100" with yerr, \
	"../data/sysL/fpt-L=200.dat" using 1:4:5 ti "L = 200" with yerr, \
	"../data/sysL/fpt-L=500.dat" using 1:4:5 ti "L = 500" with yerr, \
	"../data/sysL/fpt-L=1000.dat" using 1:4:5 ti "L = 1000" with yerr, \
