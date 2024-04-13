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

assert 0 0
assert 42 42
assert 21 "5+20-4"
assert 32 " 15 + 24 - 7 "
assert 47 "5+6*7"
assert 35 "10/2+6*5"
assert 50 "10*(3+2)"
assert 4 "(3+5)/2"
assert 4 "-5 + +11 + -2"

echo OK

