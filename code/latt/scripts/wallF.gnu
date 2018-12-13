set terminal png size 1024, 768 enhanced font "Times,28"


#set title "Wall frequency"
set xlabel "p"
set ylabel "<#wall hits>"

#set yrange[0.6:0.8]
#set output "../png/fpt/wallFreq/WF-alpha=0.1.png"
#plot	"../data/wallFreq/WF-alpha=0.1.dat" using 1:2 ti "L = 200"
#set output "../png/fpt/wallFreq/WF-alpha=0.5.png"
#plot	"../data/wallFreq/WF-alpha=0.5.dat" using 1:2 ti "L = 200"
#set output "../png/fpt/wallFreq/WF-alpha=1.png"
#plot	"../data/wallFreq/WF-alpha=1.dat" using 1:2 ti "L = 200"



set ylabel "<#wall hits>/<#steps>"

set yrange[0.0045:0.0055]
#set output "../png/fpt/wallFreq/WF-alpha=0.1-rel.png"
#plot	"../data/wallFreq/WF-alpha=0.1.dat" using 1:3 ti "L = 200"
#set output "../png/fpt/wallFreq/WF-alpha=0.5-rel.png"
#plot	"../data/wallFreq/WF-alpha=0.5.dat" using 1:3 ti "L = 200"
#set output "../png/fpt/wallFreq/WF-alpha=1-rel.png"
#plot	"../data/wallFreq/WF-alpha=1.dat" using 1:3 ti "L = 200"

set style line 500 ps 3 lw 3

set xtics 0.2
set ytics 0.0002

set key left top Left title 'Alpha' box 3

set output "../graphs/summercamp/wallhits.png"
plot	"../data/wallFreq/WF-alpha=0.1.dat" using 1:3 ls 500 pt 19 lc rgb "red" ti " 0.1", \
	"../data/wallFreq/WF-alpha=0.5.dat" using 1:3 ls 500 pt 8 lc rgb "blue" ti " 0.5", \
	"../data/wallFreq/WF-alpha=1.dat" using 1:3 ls 500 pt 4 lc rgb "green" ti " 1.0", \
