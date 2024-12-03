package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
	"sync"
	"sync/atomic"
)

type Line struct {
	line   string
	counts []int
}

func (l Line) String() string {
	return fmt.Sprintf("%s %v", l.line, l.counts)
}

func generateVariations(chars []rune, size int, current string, result *[]string, l *Line) {
	if size == 0 {
		var str string = ""
		var varI int = 0
		for _, c := range l.line {
			if c == '?' {
				str += string(current[varI])
				varI++
			} else {
				str += string(c)
			}
		}
		if checkVariation(str, l.counts){
			*result = append(*result, current)
		}
		return
	}

	for _, char := range chars {
		generateVariations(chars, size-1, current+string(char), result, l)
	}
}

func getAllVariations(chars []rune, size int, l *Line) []string {
	var result []string
	generateVariations(chars, size, "", &result, l)
	return result
}

func checkVariation(variation string, counts []int) bool {
	var countIdx int = 0
	var counting bool = false
	var copyCounts []int = make([]int, len(counts))
	copy(copyCounts, counts)
	for _, c := range variation {
		if c == '#' {
			if counting && counts[countIdx] <= 0 {
				return false
			} else if !counting {
				counting = true
				copyCounts[countIdx]--
			} else {
				copyCounts[countIdx]--
			}
		} else {
			if counting && copyCounts[countIdx] != 0 {
				return false
			} else if counting && copyCounts[countIdx] == 0 {
				if countIdx < len(copyCounts) - 1 {
					countIdx++
				}
				counting = false
			} else {
				continue
			}
		}
	}
	for _, count := range copyCounts {
		if count != 0 {
			return false
		}
	}
	return true
}

func (l Line) CountPossibilities() int32 {
	var chars []rune = []rune{'.', '#'}
	var count int32 = 0
	// Create all variations and filter non valid ones
	var number int = strings.Count(l.line, "?")
	var variations []string = getAllVariations(chars, number, &l)
	count = int32(len(variations))
	return count
}

func part1(lines []Line) int32 {
	var cumSum atomic.Int32
	cumSum.Store(0)
	var wg sync.WaitGroup
	
	for i := 0; i < len(lines); i++ {
		var copyI int = i
		wg.Add(1)
		go func() {
			cumSum.Add(lines[copyI].CountPossibilities())
			wg.Done()
		}()
	}
	wg.Wait()
	return cumSum.Load()
}

func part2(lines []Line) int32 {
	
	var newLines []Line = make([]Line, len(lines)) 
	for i, line := range lines {
		l := line.line
		line.line += l
		line.line += l
		line.line += l
		line.line += l
		line.line += l
		c := line.counts
		line.counts = append(line.counts, c...)
		line.counts = append(line.counts, c...)
		line.counts = append(line.counts, c...)
		line.counts = append(line.counts, c...)
		line.counts = append(line.counts, c...)
		newLines[i] = line
	}
	var cumSum atomic.Int32
	cumSum.Store(0)
	var wg sync.WaitGroup

	for i := 0; i < len(newLines); i++ {
		var copyI int = i
		wg.Add(1)
		go func() {
			cumSum.Add(newLines[copyI].CountPossibilities())
			wg.Done()
		}()
	}
	wg.Wait()
	return cumSum.Load()
}

func parseLines(lines []string) []Line {
	var parsed []Line = make([]Line, 0)
	for _, line := range lines {
		splited := strings.Split(line, " ")
		ints := strings.Split(splited[1], ",")
		var counts []int = make([]int, 0)
		for _, i := range ints {
			number, _ := strconv.Atoi(i)
			counts = append(counts, number)
		}
		parsed = append(parsed, Line{splited[0], counts})
	}
	return parsed
}

func main() {

	in, err := io.ReadAll(os.Stdin)
	if err != nil {
		fmt.Println("Error reading input")
		os.Exit(1)
	}
	str := string(in)
	// split string into lines
	lines := strings.Split(str, "\n")
	// remove last line if empty
	if lines[len(lines)-1] == "" {
		lines = lines[:len(lines)-1]
	}
	parsed := parseLines(lines)
	fmt.Println("Part1: ", part1(parsed))
	fmt.Println("Part1: ", part2(parsed))
	
	
}
