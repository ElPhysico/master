set terminal png size 800, 800
set output "../graphs/startingDistanceDistribution.png"

set title "Starting distance distribution"

set style data histogram
set style histogram cluster gap 0
set style fill solid border -1
set boxwidth 1

#set xrange[50:]
#set yrange[0:0.06]

set xlabel "Starting distance to target"
set ylabel "Relative weight"

everyhundredth(col) = (int(column(col))%10 ==0)?stringcolumn(1):""

set xtics rotate by 90 right 
set key top left

plot	"../data/TESTING/startDis.dat" using 2:xticlabels(everyhundredth(0)) ti ""
