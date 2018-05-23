set terminal png size 800, 800
set output "../graphs/prep/angleDistribution.png"

set title "Random angle distribution for different persistencies"

set style data histogram
set style histogram cluster gap 0
set style fill solid border -1
set boxwidth 1

#set xrange[50:]
set yrange[0:0.06]

set xlabel "Angle"
set ylabel "Relative weight"

everyhundredth(col) = (int(column(col))%10 ==0)?stringcolumn(1):""

set xtics rotate by 90 right 
set key top left

plot	"../data/prep/ranAngDist-p=-1.dat" using 2:xticlabels(everyhundredth(0)) ti "p=-1", \
	"../data/prep/ranAngDist-p=0.dat" using 2:xticlabels(everyhundredth(0)) ti "p=0", \
	"../data/prep/ranAngDist-p=0.3.dat" using 2:xticlabels(everyhundredth(0)) ti "p=0.3", \
	"../data/prep/ranAngDist-p=0.7.dat" using 2:xticlabels(everyhundredth(0)) ti "p=0.7", \
	"../data/prep/ranAngDist-p=1.dat" using 2:xticlabels(everyhundredth(0)) ti "p=1", \
