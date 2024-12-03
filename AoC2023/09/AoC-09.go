package main

import (
	"fmt"
	"io"
	"os"
	"strings"
	"sync"
	"sync/atomic"
)

func estimateNextValue(values []int64, sum *atomic.Int64, wg *sync.WaitGroup) {
	var end bool = false
	var diff_arr [][]int64 = make([][]int64, 0)
	diff_arr = append(diff_arr, values)
	var diffs []int64 = diff_arr[0]
	for !end {
		prev := diffs[0]
		var new_diffs []int64 = make([]int64, 0)
		for i := 1; i < len(diffs); i++ {
			new_diffs = append(new_diffs, diffs[i]-prev)
			prev = diffs[i]
		}
		end = true
		for _, diff := range new_diffs {
			if diff != 0 {
				end = false
			}
		}
		diff_arr = append(diff_arr, new_diffs)
		diffs = new_diffs
	}
	var diff int64 = 0
	for i := len(diff_arr) - 2; i >= 0; i-- {
		diff = diff_arr[i][len(diff_arr[i])-1] + diff
		diff_arr[i] = append(diff_arr[i], diff)
	}
	sum.Add(diff_arr[0][len(diff_arr[0])-1])
	wg.Done()
}

func part1(in [][]int64) int64 {
	var sum atomic.Int64
	sum.Store(0)
	var wg sync.WaitGroup
	for _, values := range in {
		wg.Add(1)
		go estimateNextValue(values, &sum, &wg)

	}
	wg.Wait()
	return sum.Load()
}

func estimatePrevValue(values []int64, sum *atomic.Int64, wg *sync.WaitGroup) {
	var end bool = false
	var diff_arr [][]int64 = make([][]int64, 0)
	diff_arr = append(diff_arr, values)
	var diffs []int64 = diff_arr[0]
	for !end {
		prev := diffs[0]
		var new_diffs []int64 = make([]int64, 0)
		for i := 1; i < len(diffs); i++ {
			new_diffs = append(new_diffs, diffs[i]-prev)
			prev = diffs[i]
		}
		end = true
		for _, diff := range new_diffs {
			if diff != 0 {
				end = false
			}
		}
		diff_arr = append(diff_arr, new_diffs)
		diffs = new_diffs
	}
	var diff int64 = 0
	for i := len(diff_arr) - 2; i >= 0; i-- {
		diff = diff_arr[i][0] - diff
		// diff_arr[i] = append([]int64{diff},diff_arr[i]...)
		diff_arr[i] = append(diff_arr[i], 0)
		copy(diff_arr[i][1:], diff_arr[i])
		diff_arr[i][0] = diff
	}
	sum.Add(diff_arr[0][0])
	wg.Done()
}

func part2(in [][]int64) int64 {
	var sum atomic.Int64
	sum.Store(0)
	var wg sync.WaitGroup
	for _, values := range in {
		wg.Add(1)
		go estimatePrevValue(values, &sum, &wg)

	}
	wg.Wait()
	return sum.Load()
}

func main() {
	fmt.Println("Advent of Code - Day 09")
	in, err := io.ReadAll(os.Stdin)
	if err != nil {
		fmt.Println("Error reading input")
		os.Exit(1)
	}
	str := string(in)
	// split string into lines
	lines := strings.Split(str, "\n")
	input := make([][]int64, 0)
	for _, line := range lines {
		var arr_str []string = strings.Split(line, " ")
		var arr_int []int64
		for _, str := range arr_str {
			var out int64
			n, err := fmt.Sscan(str, &out)
			if err != nil {
				fmt.Println("Error converting string:", str, " to int: ", err, " ", n)
			}
			arr_int = append(arr_int, out)
		}
		input = append(input, arr_int)
	}

	fmt.Println("Part 1: ", part1(input))
	fmt.Println("Part 2: ", part2(input))

}
