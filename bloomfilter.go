package bloomfilter

import "math"

type Bloomfilter struct{
	size 	int // large prime number
	bucket	[]bool
	k 		int
}

func (filter* Bloomfilter) Init(size int, k int){
	filter.bucket = make([]bool, size)
	filter.k = k
	filter.size = size
}

func (filter* Bloomfilter) Add(str string) {
	for _, pos := range filter.Hash(str){
		filter.bucket[pos] = true
	}
}

func (filter Bloomfilter) Contains(str string) bool{
	pos := filter.Hash(str)
	for _, b := range pos{
		if !filter.bucket[b] {
			return false
		}
	}
	return true
}

func (filter Bloomfilter) Hash (str string) []int {
	positions := []int{}
	for k := 0; k < filter.k; k++ {
		positions = append(positions, filter.hash(str, k))
	}
	return positions
}

// Polynomial rolling hash function
func (filter Bloomfilter) hash (str string, k int) int {
	pos := 0
	for i, rune := range str {
		i_ := float64(i)
		r := float64(rune)
		k_ := float64(k)
		b := filter.p() + math.Pow(k_, i_ + 1.0)
		pos = (pos + int(r * b)) % filter.size
	}
	return pos
}

func (Bloomfilter) p() float64 {
	return 53.
}