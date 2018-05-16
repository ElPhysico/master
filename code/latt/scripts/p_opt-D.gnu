set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Optimal persistency"
set key off
set xlabel "Detection radius D"
set ylabel "p_o_p_t"

set yrange[0.95:1]
set output "../png/fpt/detecR/p_opt.png"
plot	"../data/detecR/p_opt.dat" using 1:2

