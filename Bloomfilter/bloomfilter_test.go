package bloomfilter

import (
	"testing"
)

func TestHashing(t *testing.T){
	filter := Bloomfilter{50, nil, 10}

	h := filter.hash("Hallo", 0)

	if h != 38 {
		t.Errorf("Excpected %d got %d\n", 10, h)
	}
}

func TestContains(t *testing.T){
	filter := Bloomfilter{5, []bool{false,false,true,true,true}, 3}

	r := filter.Contains("AB")
	if !r {
		t.Errorf("Excpected %t got %t\n", true, r)
	}

	r = filter.Contains("ABCD")
	if r {
		t.Errorf("Excpected %t got %t\n", false, r)
	}
}

func TestAdd(t *testing.T){
	filter := Bloomfilter{}
	filter.Init(100, 2)

	n1 := "steinelu"
	filter.Add(n1)

	if !filter.Contains(n1) {
		t.Errorf("Excpected %t got %t\n", true, false)
	}

	n2 := "other"

	if filter.Contains("other") {
		t.Errorf("Excpected %t got %t\n", false, true)
	}

	filter.Add(n2)
	if !filter.Contains(n2) {
		t.Errorf("Excpected %t got %t\n", true, false)
	}
}




