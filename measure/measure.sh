#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
IMG=$DIR/img
REPORT=$DIR/report
###############################################################################

make

# measureName="01_n_vertexrepr_color"

# $DIR/$measureName".out" > $REPORT/$measureName".dat"
# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/$measureName.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/$measureName.dat' title \"Color - vertex repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile


# measureName="02_n_nbhoodrepr_color"

# $DIR/$measureName".out" > $REPORT/$measureName".dat"
# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/$measureName.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/$measureName.dat' title \"Color - nbhood repr\" with circles fill solid " \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile


# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/n_bothrepr_color.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/01_n_vertexrepr_color.dat' title \"Color - vertex repr\" with circles fill solid, '$REPORT/02_n_nbhoodrepr_color.dat' title \"Color - nbhood repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile


# measureName="03_n_vertexrepr_complement"

# $DIR/$measureName".out" > $REPORT/$measureName".dat"
# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/$measureName.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/$measureName.dat' title \"Complement - vertex repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile

# measureName="04_n_nbhoodrepr_complement"

# $DIR/$measureName".out" > $REPORT/$measureName".dat"
# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/$measureName.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/$measureName.dat' title \"Complement - vertex repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile

# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/n_bothrepr_complement.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/03_n_vertexrepr_complement.dat' title \"Complement - vertex repr\" with circles fill solid, '$REPORT/04_n_nbhoodrepr_complement.dat' title \"Complement - nbhood repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile


# measureName="05_n_vertexrepr_intersection"

# $DIR/$measureName".out" > $REPORT/$measureName".dat"
# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/$measureName.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/$measureName.dat' title \"Intersection - vertex repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile

# measureName="06_n_nbhoodrepr_intersection"

# $DIR/$measureName".out" > $REPORT/$measureName".dat"
# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/$measureName.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/$measureName.dat' title \"Intersection - nbhood repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile

# gpSrcFile=`mktemp`
# echo "set terminal pdf
#     set output '$IMG/n_bothrepr_intersection.pdf'
#     set xlabel 'vertex count'
#     set ylabel 'time [sec]'
#     set format y '%f'
#     set key box opaque
#     set key left top
#     set border back
#     set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#     plot '$REPORT/05_n_vertexrepr_intersection.dat' title \"Intersection - vertex repr\" with circles fill solid, '$REPORT/06_n_nbhoodrepr_intersection.dat' title \"Intersection - nbhood repr\" with circles fill solid" \
# > $gpSrcFile
# cat $gpSrcFile
# gnuplot $gpSrcFile
