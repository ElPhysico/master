set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Mean first passage time for L=20"
#set key off
set xlabel "p"
set ylabel "<#steps> / <#steps>_0"


#set yrange[0.6:0.8]
set output "../png/fpt/alpha/L=20/fpt-A=0.1.png"
plot	"../data/alpha/L=20/fpt-alpha=0.1.dat" using 1:4:5 ti "Alpha = 0.1" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.2.png"
plot	"../data/alpha/L=20/fpt-alpha=0.2.dat" using 1:4:5 ti "Alpha = 0.2" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.3.png"
plot	"../data/alpha/L=20/fpt-alpha=0.3.dat" using 1:4:5 ti "Alpha = 0.3" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.4.png"
plot	"../data/alpha/L=20/fpt-alpha=0.4.dat" using 1:4:5 ti "Alpha = 0.4" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.5.png"
plot	"../data/alpha/L=20/fpt-alpha=0.5.dat" using 1:4:5 ti "Alpha = 0.5" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.6.png"
plot	"../data/alpha/L=20/fpt-alpha=0.6.dat" using 1:4:5 ti "Alpha = 0.6" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.7.png"
plot	"../data/alpha/L=20/fpt-alpha=0.7.dat" using 1:4:5 ti "Alpha = 0.7" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.8.png"
plot	"../data/alpha/L=20/fpt-alpha=0.8.dat" using 1:4:5 ti "Alpha = 0.8" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=0.9.png"
plot	"../data/alpha/L=20/fpt-alpha=0.9.dat" using 1:4:5 ti "Alpha = 0.9" with yerr

set output "../png/fpt/alpha/L=20/fpt-A=1.png"
plot	"../data/alpha/L=20/fpt-alpha=1.dat" using 1:4:5 ti "Alpha = 1" with yerr

#set key left top
set output "../png/fpt/alpha/L=20/fpt.png"
plot	"../data/alpha/L=20/fpt-alpha=0.1.dat" using 1:4:5 ti "Alpha = 0.1" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.2.dat" using 1:4:5 ti "Alpha = 0.2" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.3.dat" using 1:4:5 ti "Alpha = 0.3" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.4.dat" using 1:4:5 ti "Alpha = 0.4" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.5.dat" using 1:4:5 ti "Alpha = 0.5" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.6.dat" using 1:4:5 ti "Alpha = 0.6" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.7.dat" using 1:4:5 ti "Alpha = 0.7" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.8.dat" using 1:4:5 ti "Alpha = 0.8" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.9.dat" using 1:4:5 ti "Alpha = 0.9" with yerr, \
	"../data/alpha/L=20/fpt-alpha=1.dat" using 1:4:5 ti "Alpha = 1" with yerr, \


set output "../png/fpt/alpha/L=20/fpt2.png"
plot	"../data/alpha/L=20/fpt-alpha=0.1.dat" using 1:2:3 ti "Alpha = 0.1" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.2.dat" using 1:2:3 ti "Alpha = 0.2" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.3.dat" using 1:2:3 ti "Alpha = 0.3" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.4.dat" using 1:2:3 ti "Alpha = 0.4" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.5.dat" using 1:2:3 ti "Alpha = 0.5" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.6.dat" using 1:2:3 ti "Alpha = 0.6" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.7.dat" using 1:2:3 ti "Alpha = 0.7" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.8.dat" using 1:2:3 ti "Alpha = 0.8" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.9.dat" using 1:2:3 ti "Alpha = 0.9" with yerr, \
	"../data/alpha/L=20/fpt-alpha=1.dat" using 1:2:3 ti "Alpha = 1" with yerr, \






######### L = 200 #############
set title "Mean first passage time for L=200"

#set yrange[0.6:0.8]
set output "../png/fpt/alpha/L=200/fpt-A=0.1.png"
plot	"../data/alpha/L=200/fpt-alpha=0.1.dat" using 1:4:5 ti "Alpha = 0.1" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.2.png"
plot	"../data/alpha/L=200/fpt-alpha=0.2.dat" using 1:4:5 ti "Alpha = 0.2" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.3.png"
plot	"../data/alpha/L=200/fpt-alpha=0.3.dat" using 1:4:5 ti "Alpha = 0.3" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.4.png"
plot	"../data/alpha/L=200/fpt-alpha=0.4.dat" using 1:4:5 ti "Alpha = 0.4" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.5.png"
plot	"../data/alpha/L=200/fpt-alpha=0.5.dat" using 1:4:5 ti "Alpha = 0.5" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.6.png"
plot	"../data/alpha/L=200/fpt-alpha=0.6.dat" using 1:4:5 ti "Alpha = 0.6" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.7.png"
plot	"../data/alpha/L=200/fpt-alpha=0.7.dat" using 1:4:5 ti "Alpha = 0.7" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.8.png"
plot	"../data/alpha/L=200/fpt-alpha=0.8.dat" using 1:4:5 ti "Alpha = 0.8" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=0.9.png"
plot	"../data/alpha/L=200/fpt-alpha=0.9.dat" using 1:4:5 ti "Alpha = 0.9" with yerr

set output "../png/fpt/alpha/L=200/fpt-A=1.png"
plot	"../data/alpha/L=200/fpt-alpha=1.dat" using 1:4:5 ti "Alpha = 1" with yerr

#set key left top
set output "../png/fpt/alpha/L=200/fpt.png"
plot	"../data/alpha/L=200/fpt-alpha=0.1.dat" using 1:4:5 ti "Alpha = 0.1" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.2.dat" using 1:4:5 ti "Alpha = 0.2" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.3.dat" using 1:4:5 ti "Alpha = 0.3" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.4.dat" using 1:4:5 ti "Alpha = 0.4" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.5.dat" using 1:4:5 ti "Alpha = 0.5" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.6.dat" using 1:4:5 ti "Alpha = 0.6" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.7.dat" using 1:4:5 ti "Alpha = 0.7" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.8.dat" using 1:4:5 ti "Alpha = 0.8" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.9.dat" using 1:4:5 ti "Alpha = 0.9" with yerr, \
	"../data/alpha/L=200/fpt-alpha=1.dat" using 1:4:5 ti "Alpha = 1" with yerr, \


set output "../png/fpt/alpha/L=200/fpt2.png"
plot	"../data/alpha/L=200/fpt-alpha=0.1.dat" using 1:2:3 ti "Alpha = 0.1" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.2.dat" using 1:2:3 ti "Alpha = 0.2" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.3.dat" using 1:2:3 ti "Alpha = 0.3" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.4.dat" using 1:2:3 ti "Alpha = 0.4" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.5.dat" using 1:2:3 ti "Alpha = 0.5" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.6.dat" using 1:2:3 ti "Alpha = 0.6" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.7.dat" using 1:2:3 ti "Alpha = 0.7" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.8.dat" using 1:2:3 ti "Alpha = 0.8" with yerr, \
	"../data/alpha/L=200/fpt-alpha=0.9.dat" using 1:2:3 ti "Alpha = 0.9" with yerr, \
	"../data/alpha/L=200/fpt-alpha=1.dat" using 1:2:3 ti "Alpha = 1" with yerr, \

