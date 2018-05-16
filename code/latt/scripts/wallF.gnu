set terminal png size 1000, 800 #enhanced font "Helvetica,12"


set title "Wall frequency"
set xlabel "p"
set ylabel "<#wall hits>"

#set yrange[0.6:0.8]
set output "../png/fpt/wallFreq/WF-alpha=0.1.png"
plot	"../data/wallFreq/WF-alpha=0.1.dat" using 1:2 ti "L = 200"
set output "../png/fpt/wallFreq/WF-alpha=0.5.png"
plot	"../data/wallFreq/WF-alpha=0.5.dat" using 1:2 ti "L = 200"
set output "../png/fpt/wallFreq/WF-alpha=1.png"
plot	"../data/wallFreq/WF-alpha=1.dat" using 1:2 ti "L = 200"



set ylabel "<#wall hits>/<#steps>"

set yrange[0:0.01]
set output "../png/fpt/wallFreq/WF-alpha=0.1-rel.png"
plot	"../data/wallFreq/WF-alpha=0.1.dat" using 1:3 ti "L = 200"
set output "../png/fpt/wallFreq/WF-alpha=0.5-rel.png"
plot	"../data/wallFreq/WF-alpha=0.5.dat" using 1:3 ti "L = 200"
set output "../png/fpt/wallFreq/WF-alpha=1-rel.png"
plot	"../data/wallFreq/WF-alpha=1.dat" using 1:3 ti "L = 200"
