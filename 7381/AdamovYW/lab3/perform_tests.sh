echo "Test 1: a+(45-f(x)*(b-c))"
./program < Tests/test01.txt

echo "Test 2: aaa((c(()b)d)e)aaaa"
./program < Tests/test02.txt

echo "Test 3: a+c*(13*(10*(12+4)*(8-3)+1)*66+13/(1+1))"
./program < Tests/test03.txt

echo "Test 4: ((()()))()((()))(()(()))"
./program < Tests/test04.txt

echo "Test 5: a+b-c*3+d/5"
./program < Tests/test05.txt

echo "Test 6: ()()()((()))()()()"
./program < Tests/test06.txt

echo "Test 7: ((a+b)*c)+(a*((b+c)/13)"
./program < Tests/test07.txt

echo "Test 8: (a+b)*(a+e/(2+g)+8))"
./program < Tests/test08.txt
