declare -a arr=("-t" "-s" "-b" "-v" "-e" "-n")
gcc s21_cat.c -o s21_cat.o
gcc test_cat.c -o test_cat.o

for i in "${arr[@]}"
do
cat "$i" ss >> file1
./s21_cat.o "$i" ss >> file2
echo "$i (1 file)"
./test_cat.o
rm file1 file2
done

for i in "${arr[@]}"
do
cat "$i" dd ss >> file1
./s21_cat.o "$i" dd ss >> file2
echo "$i (2 files)"
./test_cat.o
rm file1 file2
done


