set terminal png size 500,500
set pm3d map
unset colorbox
set yrange [] reverse
set output 'roots.png'
splot "output.txt" u 2:1:3
