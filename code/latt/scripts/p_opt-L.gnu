set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Optimal persistency"
set key off
set xlabel "System size L"
set ylabel "p_o_p_t"

#set yrange[0.5:1]
#set logscale y
set output "../png/fpt/sysL/p_opt.png"
plot	"../data/sysL/p_opt.dat" using 1:2

