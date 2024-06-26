assert() {
	expected="$1"
	input="$2"

	./ccomp "$input" > tmp.s
	cc -o tmp tmp.s
	./tmp
	actual="$?"

	if [ "$actual" = "$expected" ]; then
		echo "$input => $actual"
	else
		echo "$input => $expected expected, but got $actual"
		exit 1
	fi
}

assert 0 '0;'
assert 42 '42;'
assert 21 "5+20-4;"
assert 32 " 15 + 24 - 7 ;"
assert 47 "5+6*7;"
assert 35 "10/2+6*5;"
assert 50 "10*(3+2);"
assert 4 "(3+5)/2;"
assert 4 "-5 + +11 + -2;"
assert 0 '0==1;'
assert 1 '42==42;'
assert 1 '0!=1;'
assert 0 '42!=42;'

assert 1 '0<1;'
assert 0 '1<1;'
assert 0 '2<1;'
assert 1 '0<=1;'
assert 1 '1<=1;'
assert 0 '2<=1;'

assert 1 '1>0;'
assert 0 '1>1;'
assert 0 '1>2;'
assert 1 '1>=0;'
assert 1 '1>=1;'
assert 0 '1>=2;'
 
assert 3 '1; 2; 3;'
assert 3 "a = 3; a;"
assert 14 "a = 3; b = 5 * 6 - 8; a + b / 2;"

assert 21 "foo = 3; bar = 7; foo * bar;"
assert 41 "qu1ck_brown_f0x = 2; jump5 = 3; oVER = 5; the_LAZY_D0G = 7; qu1ck_brown_f0x * jump5 + oVER * the_LAZY_D0G;"

assert 40 "return 40; 1;"

assert 30 "if (1) return 30; return 20;"
assert 20 "if (0) return 30; else return 20; return 10;"

assert 10 "while (0) return 20; return 10;"
assert 20 "while (1) return 20; return 10;"
assert 2 "b = 10; while (b > 2) b = b - 1; return b;"

assert 1 "for (; ; ) return 0; return 1;"
assert 1 "for (1; ; ) return 0; return 1;"
assert 0 "for (; 1; ) return 0; return 1;"
assert 1 "for (; ; 1) return 0; return 1;"
assert 0 "for (1; 1; ) return 0; return 1;"
assert 0 "for (; 1; 1) return 0; return 1;"
assert 1 "for (1; ; 1) return 0; return 1;"
assert 0 "for (1; 1; 1) return 0; return 1;"

assert 32 "b = 1; for (a = 0; a < 5; a = a + 1) b = b * 2; return b;"
assert 1 "b = 1; for (a = 0; ; ) b = b + 2; return b;"
assert 1 "b = 1; for (; 0; ) b = b + 2; return b;"
assert 1 "b = 1; for (; ; a = a + 1) b = b + 2; return b;"

echo OK

