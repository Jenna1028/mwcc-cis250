#sample source file
echo "This is my lab05 test file." > source.txt

#test copying file
echo "Test 1: copying a file"
./copy2 source.txt target.txt

#display file
echo "Contents of target.txt:"
cat target.txt

#compare source and destination
echo "Test 2: Comparing files"
if diff -q source.txt target.txt; then
	echo "Files are identical"
else
	echo "Files are different"
fi

#test missing statements
echo "Test 3: missing arguments"
./copy2

#test too many arguments
echo "Test 4: too many arguments"
./copy2 source.txt target.txt extra.txt

#test nonexistent source file
echo "Test 5: Nonexistent source file"
./copy2 missing.txt target.txt
