package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)


func part1(input []string) int {
	for i := 0; i < len(input); i++ {
		for j := 0; j < len(input[i]); j++ {
			if j < len(input) {
				
			}
		}
	}
	return 0
}

func part2(input []string) int {
	
	return 0
}

func main() {
	in, err := io.ReadAll(os.Stdin)
	if err != nil {
		fmt.Println("Error reading input")
		os.Exit(0)
	}
	str := string(in)
	// split string into lines
	lines := strings.Split(str, "\n")
	// remove last line if empty
	if lines[len(lines)-1] == "" {
		lines = lines[:len(lines)-1]
	}
	fmt.Println("Part 1: ", part1(lines))
	fmt.Println("Part 2: ", part2(lines))
}