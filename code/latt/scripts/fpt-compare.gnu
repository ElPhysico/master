set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Mean first passage time L=20, alpha=0.1"
set key off
set xlabel "p"
set ylabel "<#steps> / <#steps>_0"


set key left top
set output "../png/fpt/comp-center-L=20.png"
plot	"../data/alpha/tarCen/L=20/fpt-alpha=0.1.dat" using 1:4:5 ti "Centered target" with yerr, \
	"../data/alpha/L=20/fpt-alpha=0.1.dat" using 1:4:5 ti "Random target" with yerr, \
