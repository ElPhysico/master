set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Mean first passage time"
#set key off
set xlabel "p"
set ylabel "<#steps> / <#steps>_0"


#set yrange[0.6:0.8]
set output "../png/fpt/detecR/fpt-D=1.png"
plot	"../data/detecR/fpt-D=1.dat" using 1:4:5 ti "D = 1" with yerr

set output "../png/fpt/detecR/fpt-D=2.png"
plot	"../data/detecR/fpt-D=2.dat" using 1:4:5 ti "D = 2" with yerr

set output "../png/fpt/detecR/fpt-D=3.png"
plot	"../data/detecR/fpt-D=3.dat" using 1:4:5 ti "D = 3" with yerr

set output "../png/fpt/detecR/fpt-D=4.png"
plot	"../data/detecR/fpt-D=4.dat" using 1:4:5 ti "D = 4" with yerr

set output "../png/fpt/detecR/fpt-D=5.png"
plot	"../data/detecR/fpt-D=5.dat" using 1:4:5 ti "D = 5" with yerr

set output "../png/fpt/detecR/fpt-D=10.png"
plot	"../data/detecR/fpt-D=10.dat" using 1:4:5 ti "D = 10" with yerr

set output "../png/fpt/detecR/fpt-D=15.png"
plot	"../data/detecR/fpt-D=15.dat" using 1:4:5 ti "D = 15" with yerr

set output "../png/fpt/detecR/fpt-D=20.png"
plot	"../data/detecR/fpt-D=20.dat" using 1:4:5 ti "D = 20" with yerr

#set key left top
set output "../png/fpt/detecR/fpt.png"
plot	"../data/detecR/fpt-D=1.dat" using 1:4:5 ti "D = 1" with yerr, \
	"../data/detecR/fpt-D=2.dat" using 1:4:5 ti "D = 2" with yerr, \
	"../data/detecR/fpt-D=3.dat" using 1:4:5 ti "D = 3" with yerr, \
	"../data/detecR/fpt-D=4.dat" using 1:4:5 ti "D = 4" with yerr, \
	"../data/detecR/fpt-D=5.dat" using 1:4:5 ti "D = 5" with yerr, \
	"../data/detecR/fpt-D=10.dat" using 1:4:5 ti "D = 10" with yerr, \
	"../data/detecR/fpt-D=15.dat" using 1:4:5 ti "D = 15" with yerr, \
	"../data/detecR/fpt-D=20.dat" using 1:4:5 ti "D = 20" with yerr, \

