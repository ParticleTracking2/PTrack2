C=$#
if [ $C -ne 11 ] 
then
    echo "Must run as ./gen_tests.sh PREFIX FOLDER fD A B MINL MAXL DL DN NC seed"
    echo ""
    echo "Parameters:"
    echo "PREFIX:         the prefix for the output file"
    echo "FOLDER:         the folder where the output file will be saved"
    echo "fD:             particle diameter (float)"
    echo "A, B:           parameters for Beta distribution"
    echo "MINL,MAXL,DL:   min max range for image size L at steps DL"
    echo "DN:             step for increasing number of particles"
    echo "NC:             number of clusters"
    echo "seed:           PRNG seed"
    echo ""
    echo "example:"
    echo "./gentests.sh set1 myfolder/  0.7 50 50 4000 4000 100 3000 4 49"
    exit
fi
D=10
PREFIX=$1
folder=${2}
fD=$3
A=$4
B=$5
MINL=$6
MAXL=$7
DL=$8
DN=$9
NC=${10}
seed=${11}
MINN=10
for i in `seq $MINL $DL $MAXL`;
do
    MAXN=$(echo "2 * $i * $i/ (3.14159265359 * ($D/2.0)*($D/2))" | bc -l)
    MAXN=$(echo "4 * $MAXN / 1" | bc)
    seed=$(($seed))
    echo "max N = $MAXN   seed = $seed"
    for j in `seq $MINN $DN $MAXN`;
    do
        eval "octave -qf runGenerateImage.m $PREFIX $folder $fD $i $j $A $B $NC $seed"
        L=$(echo "$i * 1.0" | bc);
        PACKD=$(echo "$N * 3.14159265359 * ($D/2.0)*($D/2.0) / ($L * $L)" | bc -l)
    done
done 
