# Your code here!

echo "Paiza start"
touch paiza.txt
echo "Paiza" >> paiza.txt
echo "Paiza" >> paiza.txt

tar zcvf paiza.tar.gz paiza.txt 2>/dev/null >/dev/null

tar zxf paiza.tar.gz -O
