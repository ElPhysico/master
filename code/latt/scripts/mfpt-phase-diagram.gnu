set terminal pngcairo  background "#ffffff" enhanced font "Times,28" fontscale 1.0 size 1024, 768

set datafile missing "NaN"

set xlabel "p_m_i_n" rotate parallel
set ylabel "p_m_a_x" rotate parallel
set zlabel offset 4 "MFPT" rotate parallel

#set format z "%2.1f 10^{%L}"
#set format z "%2.1e"
set xtics 0.2
set ytics 0.2
unset ztics #offset 10 40000
set size square 0.95,1

set style fill solid 0.50 border
unset key
set isosamples 20, 20
set pm3d depthorder hidden3d 1
set hidden3d front offset 1 trianglepattern 3 undefined 1 altdiagonal bentover
set style data lines
set xyplane at 0
set cbrange [0 : 200000] noreverse nowriteback
set palette rgbformulae 31, -11, 32
#set palette cubehelix
#set palette negative
set grid
#set border 4095
set border 127+256+512

f(x,y) = 16540	#the mfpt of the optimal constant search persistency


#linear
set output "../png/fpt/ch/linMfpt-3D.png"
#set title "Linear search strategies in comparison to optimal constant search strategy p_o_p_t=0.97"
set view 60,135
splot "../data/ch/linearMfpt.dat" u 1:2:3 with pm3d lc rgb "black" ti "p(d) = p_m_a_x - (p_m_a_x - p_m_i_n) * d * sqrt2 / 200", f(x,y) with lines lc rgb "red" ti "Optimal constant MFPT"


#parabolic
set output "../png/fpt/ch/paraMfpt-3D.png"
#set title "Symmetric parabolic search strategies in comparison to optimal constant search strategy p_o_p_t=0.97"
set view 60,135
splot "../data/ch/parabolicMfpt.dat" u 1:2:3 with pm3d lc rgb "black" ti "p(d) = p_m_a_x - (p_m_a_x - p_m_i_n) * (d - 200 / 2sqrt2)^2 * (2sqrt2 / 200)^2", f(x,y) with lines lc rgb "red" ti "Optimal constant MFPT"






