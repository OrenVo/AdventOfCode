package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

type universe [][]byte

func (u universe) String() string {
	var str string = ""
	for _, row := range u {
		str += string(row) + "\n"
	}
	return str
}

func createUniverse(in []string) (universe, universe) {
	var u universe = make(universe, len(in))
	for i := 0; i < len(in); i++ {
		u[i] = make([]byte, len(in[i]))
		for j := 0; j < len(in[i]); j++ {
			u[i][j] = in[i][j]
		}
	}

	var nonExpandedU universe = make(universe, len(u))
	for i := range u {
		nonExpandedU[i] = make([]byte, len(u[i]))
		copy(nonExpandedU[i], u[i])
	}

	fmt.Println(u)
	var expandRows []int = make([]int, 0)
	var expandCols []int = make([]int, 0)
	for i := 0; i < len(u); i++ {
		var expand bool = true
		for j := 0; j < len(u[i]); j++ {
			if u[i][j] == '#' {
				expand = false
				break
			}
		}
		if expand {
			expandRows = append(expandRows, i)
		}
	}
	for i := 0; i < len(u[0]); i++ {
		var expand bool = true
		for j := 0; j < len(u); j++ {
			if u[j][i] == '#' {
				expand = false
				break
			}
		}
		if expand {
			expandCols = append(expandCols, i)
		}
	}
	var offset_row int = 0
	for _, row := range expandRows {
		u = append(u[:row+1+offset_row], u[row+offset_row:]...)
		offset_row++
	}
	var offset_col int = 0
	for _, col := range expandCols {
		for i, row := range u {
			u[i] = append(row[:col+1+offset_col], row[col+offset_col:]...)
		}
		offset_col++
	}
	return nonExpandedU, u
}

func part1(u universe) int {
	var galaxyPositions [][2]int = make([][2]int, 0)
	for i := 0; i < len(u); i++ {
		for j := 0; j < len(u[i]); j++ {
			if u[i][j] == '#' {
				galaxyPositions = append(galaxyPositions, [2]int{i, j})
			}
		}
	}
	var sum int = 0
	for i, posA := range galaxyPositions {
		for _, posB := range galaxyPositions[i+1:] {
			var a int = (posA[0] - posB[0])
			if a < 0 {
				a *= -1
			}
			var b int = (posA[1] - posB[1])
			if b < 0 {
				b *= -1
			}
			sum += a + b
		}
	}

	return sum
}

func expandUniversePart2(u *universe) ([]int, []int) {
	var expandRows []int = make([]int, 0)
	var expandCols []int = make([]int, 0)
	for i := 0; i < len(*u); i++ {
		var expand bool = true
		for j := 0; j < len((*u)[i]); j++ {
			if (*u)[i][j] == '#' {
				expand = false
				break
			}
		}
		if expand {
			expandRows = append(expandRows, i)
		}
	}
	for i := 0; i < len((*u)[0]); i++ {
		var expand bool = true
		for j := 0; j < len(*u); j++ {
			if (*u)[j][i] == '#' {
				expand = false
				break
			}
		}
		if expand {
			expandCols = append(expandCols, i)
		}
	}
	return expandRows, expandCols
	// var offset_row int = 0
	// const expandSize int = 1000000
	// for _, row := range expandRows {
	// 	for i := 0; i < expandSize; i++ {
	// 		*u = append((*u)[:row+1+offset_row], (*u)[row+offset_row:]...)
	// 		offset_row++
	// 	}
	// }
	// var new_coll []byte = make([]byte, expandSize)
	// for i, _ := range new_coll {
	// 	new_coll[i] = '.'
	// }
	// var offset_col int = 0
	// for _, col := range expandCols {
	// 	for i, row := range *u {
	// 		var add []byte = make([]byte, expandSize)
	// 		copy(add, new_coll)
	// 		(*u)[i] = append(append(row[:col+offset_col], add...), row[col+offset_col:]...)
	// 	}
	// 	offset_col += expandSize
	// }
}

/* part2 not finished */
func part2(u universe) int {
	rows, cols := expandUniversePart2(&u)

	var galaxyPositions [][2]int = make([][2]int, 0)
	for i := 0; i < len(u); i++ {
		for j := 0; j < len(u[i]); j++ {
			if u[i][j] == '#' {
				galaxyPositions = append(galaxyPositions, [2]int{i, j})
			}
		}
	}
	fmt.Println("Galaxy positions: ", galaxyPositions)
	fmt.Println("Rows: ", rows)
	fmt.Println("Cols: ", cols)
	var sum int = 0
	for i, posA := range galaxyPositions {
		for _, posB := range galaxyPositions[i+1:] {
			fmt.Println("PosA: ", posA[0], " ", posA[1])
			fmt.Println("PosB: ", posB[0], " ", posB[1])
			var posAX, posAY, posBX, posBY int = posA[0], posA[1], posB[0], posB[1]
			for _, row := range rows {
				if posB[0] > row && row > posA[0] {
					fmt.Println("Expanding row: ", row, " posBX: ", posB[0], " posAX: ", posA[0])
					posBX += 1000000
					posBX++
				}
			}
			for _, col := range cols {
				if posB[1] > col && col > posA[1] {
					fmt.Println("Expanding col: ", col, " posBY: ", posB[1], " posAY: ", posA[1])
					posBY += 1000000
					posBY++
				}
			}
			var a int = (posAX - posBX)
			if a < 0 {
				a *= -1
			}
			var b int = (posAY - posBY)
			if b < 0 {
				b *= -1
			}
			fmt.Println("A: ", a, " B: ", b, " Sum: ", a+b)
			sum += a + b
		}
	}

	return sum
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
	var u, expandedU universe = createUniverse(lines)
	fmt.Println("Part 1:", part1(expandedU))
	fmt.Println("Part 2:", part2(u))
}
