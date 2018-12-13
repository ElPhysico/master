set terminal png size 1024, 768 enhanced font "Times,33"

#set title "Optimal persistency"
set key bottom right
set xlabel "System size L"
set ylabel "p_o_p_t"

#set yrange[0.5:1]
#set logscale y

f(x)=a/x + b
a=-1
b=0.1
fit f(x) "../data/L/p_opt.dat" via a,b

set style line 500 ps 3 lw 3

set xtics 200
set ytics 0.1

set output "../graphs/summercamp/p_opt.png"
plot	f(x) ti "f(x) = -2.85 / x + 0.98" ls 500 lc rgb "red", "../data/L/p_opt.dat" using 1:2 ls 500 pt 19 lc rgb "red" ti ""

