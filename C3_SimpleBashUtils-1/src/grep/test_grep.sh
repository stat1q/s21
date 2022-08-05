declare -a arr=("-i" "-v" "-l" "-c" "-n" "-h" "-o" "-s" "-ivcnh")
gcc s21_grep.c -o s21_grep.o
gcc test_grep.c -o test_grep.o
for i in "${arr[@]}"
do
grep "$i" kom tt >> file1
./s21_grep.o "$i" kom tt >> file2
echo "$i"
./test_grep.o
rm file1 file2
done

grep -e hello -e world tt >> file1
./s21_grep.o -e hello -e world tt >> file2
echo -e
./test_grep.o
rm file1 file2

grep -f ff -f gg tt >> file1
./s21_grep.o -f ff -f gg tt >> file2
echo -f
./test_grep.o
rm file1 file2
