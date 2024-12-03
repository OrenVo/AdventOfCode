package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

// N	       N       N
// |   W - E   L E   W J   W 7    F E
// S					     S    S

type Node struct {
	position [2]int
	value    int
	prev     *Node
	next     *Node
	symbol   byte
}

func findLoop(in []string, start [2]int, symbol string) (int, *Node) {
	var startingNode *Node = &Node{start, 0, nil, nil, symbol[0]}
	var pos [2]int = [2]int{0, 0}
	var step string = ""
	var prevStep string = ""
	switch symbol {
	case "|":
		fallthrough
	case "7":
		fallthrough
	case "F":
		step = "S"
		pos = [2]int{start[0] + 1, start[1]}
		break
	case "J":
		fallthrough
	case "L":
		step = "N"
		pos = [2]int{start[0] - 1, start[1]}
		break
	case "-":
		step = "W"
		pos = [2]int{start[0], start[1] - 1}
	}
	prevStep = step
	var end bool = false
	prevNode := startingNode
	node := &Node{pos, 1, prevNode, nil, in[pos[0]][pos[1]]}
	prevNode.next = node
	for !end {
		if pos[0] < 0 || pos[0] >= len(in) || pos[1] < 0 || pos[1] >= len(in[pos[0]]) {
			return -1, nil
		}
		switch in[pos[0]][pos[1]] {
		case '|':
			if prevStep == "N" {
				step = "N"
			} else if prevStep == "S" {
				step = "S"
			} else {
				return -1, nil
			}
			break
		case '7':
			if prevStep == "N" {
				step = "W"
			} else if prevStep == "E" {
				step = "S"
			} else {
				return -1, nil
			}
			break
		case 'F':
			if prevStep == "W" {
				step = "S"
			} else if prevStep == "N" {
				step = "E"
			} else {
				return -1, nil
			}
			break
		case 'J':
			if prevStep == "S" {
				step = "W"
			} else if prevStep == "E" {
				step = "N"
			} else {
				return -1, nil
			}
			break
		case 'L':
			if prevStep == "W" {
				step = "N"
			} else if prevStep == "S" {
				step = "E"
			} else {
				return -1, nil
			}
			break
		case '-':
			if prevStep == "W" {
				step = "W"
			} else if prevStep == "E" {
				step = "E"
			} else {
				return -1, nil
			}
			break
		default:
			return -1, nil
		}
		// N	       N       N
		// |   W - E   L E   W J   W 7    F E
		// S					     S    S
		prevStep = step
		switch step {
		case "N":
			pos = [2]int{pos[0] - 1, pos[1]}
			break
		case "S":
			pos = [2]int{pos[0] + 1, pos[1]}
			break
		case "W":
			pos = [2]int{pos[0], pos[1] - 1}
			break
		case "E":
			pos = [2]int{pos[0], pos[1] + 1}
			break
		default:
			return -1, nil
		}
		prevNode = node
		if pos == start {
			end = true
			startingNode.prev = node
			node.next = startingNode
			break
		}
		node = &Node{pos, prevNode.value + 1, prevNode, nil, in[pos[0]][pos[1]]}
		prevNode.next = node
	}

	return startingNode.prev.value / 2, startingNode
}

func part1(in []string) ([6]int, *Node) {
	var startingPoint [2]int
	for i, line := range in {
		for j, char := range line {
			if char == 'S' {
				startingPoint = [2]int{i, j}
			}
		}
	}
	var top, bottom, left, right bool = false, false, false, false
	if startingPoint[0]-1 >= 0 {
		switch in[startingPoint[0]-1][startingPoint[1]] {
		case '|':
			fallthrough
		case '7':
			fallthrough
		case 'F':
			top = true
			break
		default:
			break
		}
	}
	if startingPoint[0]+1 < len(in) {
		switch in[startingPoint[0]+1][startingPoint[1]] {
		case '|':
			fallthrough
		case 'J':
			fallthrough
		case 'L':
			bottom = true
			break
		default:
			break
		}
	}
	if startingPoint[1]-1 >= 0 {
		switch in[startingPoint[0]][startingPoint[1]-1] {
		case '-':
			fallthrough
		case 'L':
			fallthrough
		case 'F':
			left = true
			break
		default:
			break
		}

	}
	if startingPoint[1]+1 < len(in[startingPoint[0]]) {
		switch in[startingPoint[0]][startingPoint[1]+1] {
		case '-':
			fallthrough
		case 'J':
			fallthrough
		case '7':
			right = true
			break
		default:
			break
		}
	}
	var values [6]int
	var node *Node
	if left && right {
		val, node1 := findLoop(in, startingPoint, "-")
		values[0] = val
		if node1 != nil {
			node = node1
		}
	}
	if top && bottom {
		val, node2 := findLoop(in, startingPoint, "|")
		values[1] = val
		if node2 != nil {
			node = node2
		}
	}
	if top && left {
		val, node3 := findLoop(in, startingPoint, "J")
		values[2] = val
		if node3 != nil {
			node = node3
		}
	}
	if top && right {
		val, node4 := findLoop(in, startingPoint, "L")
		values[3] = val
		if node4 != nil {
			node = node4
		}
	}
	if bottom && left {
		val, node5 := findLoop(in, startingPoint, "7")
		values[4] = val
		if node5 != nil {
			node = node5
		}
	}
	if bottom && right {
		val, node6 := findLoop(in, startingPoint, "F")
		values[5] = val
		if node6 != nil {
			node = node6
		}
	}

	return values, node
}

func isPosNode(pos [2]int, node *Node) bool {
	if node == nil {
		return false
	}
	var walk *Node = node
	if pos[0] == walk.position[0] && pos[1] == walk.position[1] {
		return true
	}
	walk = walk.next
	for walk != nil || walk != node {
		if pos[0] == walk.position[0] && pos[1] == walk.position[1] {
			return true
		}
		walk = walk.next
	}
	return false
}

func findBorders(pos [2]int, in []string, node *Node) bool {
	// TOP
	var bordersFound bool = true
	for i := pos[0] - 1; i >= 0; i-- {
		if in[i][pos[1]] == '.' {
			continue
		} else if isPosNode([2]int{i, pos[1]}, node) {
			bordersFound = false
			break
		}
	}
	if bordersFound {
		return true
	}
	// BOTTOM
	bordersFound = true
	for i := pos[0] + 1; i < len(in); i++ {
		if in[i][pos[1]] == '.' {
			continue
		} else if isPosNode([2]int{i, pos[1]}, node) {
			bordersFound = false
			break
		}
	}
	if bordersFound {
		return true
	}
	// LEFT
	bordersFound = true
	for i := pos[1] - 1; i >= 0; i-- {
		if in[pos[0]][i] == '.' {
			continue
		} else if isPosNode([2]int{pos[0], i}, node) {
			bordersFound = false
			break
		}
	}
	if bordersFound {
		return true
	}
	// RIGHT
	bordersFound = true
	for i := pos[1] + 1; i < len(in[pos[0]]); i++ {
		if in[pos[0]][i] == '.' {
			continue
		} else if isPosNode([2]int{pos[0], i}, node) {
			return false
		}
	}
	return true
}

func checkIfInsideBorders(pos [2]int, in []string, node *Node) bool {
	if in[pos[0]][pos[1]] == '.' {
		return findBorders(pos, in, node)
	} else if isPosNode(pos, node) {
		return false
	} else {
		return findBorders(pos, in, node)
	}
	return false
}

func createMap(in []string, node *Node) [][]byte {
	var mapOfWorld [][]byte = make([][]byte, len(in))
	for i, line := range in {
		mapOfWorld[i] = make([]byte, len(line))
	}
	for i, line := range in {
		for j, _ := range line {
			mapOfWorld[i][j] = 'I'
		}
	}
	var walk *Node = node
	for walk != nil {
		mapOfWorld[walk.position[0]][walk.position[1]] = walk.symbol
		fmt.Println("adding symbol", string(walk.symbol))
		walk = walk.next
		if walk == node {
			break
		}
	}
	return mapOfWorld
}

func followBorders(mapOfWorld *[][]byte, direction_out string, pos [2]int) {
	// TODO follow borders and fill if some values are found on the outside of borders
	
}

func floodFill(mapOfWorld *[][]byte, fill byte, start [2]int) {
	localMap := *mapOfWorld
	if localMap[start[0]][start[1]] == fill {
		return
	}

	var queue [][2]int = make([][2]int, 0)
	queue = append(queue, start)
	for len(queue) != 0 {
		var pos [2]int = queue[0]
		queue = queue[1:]
		if pos[0] < 0 || pos[0] >= len(localMap) || pos[1] < 0 || pos[1] >= len(localMap[pos[0]]) {
			continue
		} else if localMap[pos[0]][pos[1]] == '|' || localMap[pos[0]][pos[1]] == '-' || localMap[pos[0]][pos[1]] == 'J' ||
			localMap[pos[0]][pos[1]] == '7' || localMap[pos[0]][pos[1]] == 'F' || localMap[pos[0]][pos[1]] == 'L' {
			continue
		} else if localMap[pos[0]][pos[1]] == fill {
			continue
		} else {
			localMap[pos[0]][pos[1]] = fill
			queue = append(queue, [2]int{pos[0] - 1, pos[1]})
			queue = append(queue, [2]int{pos[0] - 1, pos[1] + 1})
			queue = append(queue, [2]int{pos[0] - 1, pos[1] - 1})
			queue = append(queue, [2]int{pos[0] + 1, pos[1] + 1})
			queue = append(queue, [2]int{pos[0] + 1, pos[1] - 1})
			queue = append(queue, [2]int{pos[0] + 1, pos[1]})
			queue = append(queue, [2]int{pos[0], pos[1] - 1})
			queue = append(queue, [2]int{pos[0], pos[1] + 1})
		}
	}
	*mapOfWorld = localMap
}

func part2(in []string, node *Node) int {
	var mapOfWorld [][]byte = createMap(in, node)
	for _, line := range in {
		fmt.Println(line)
	}
	fmt.Println()
	for _, line := range mapOfWorld {
		for _, val := range line {
			fmt.Print(string(val))
		}
		fmt.Println()
	}
	fmt.Println()

	// starting point
	var startingPoints [][2]int = make([][2]int, 0)

	for i, val := range mapOfWorld[0] {
		if val == 'I' && i != 0 && i != len(mapOfWorld[0])-1 {
			startingPoints = append(startingPoints, [2]int{0, i})
		}
	}
	for i, val := range mapOfWorld[len(mapOfWorld)-1] {
		if val == 'I' && i != 0 && i != len(mapOfWorld[0])-1 {
			startingPoints = append(startingPoints, [2]int{len(mapOfWorld) - 1, i})
		}
	}
	for i, line := range mapOfWorld {
		if line[0] == 'I' {
			startingPoints = append(startingPoints, [2]int{i, 0})
		}
		if line[len(line)-1] == 'I' {
			startingPoints = append(startingPoints, [2]int{i, len(line) - 1})
		}
	}
	for _, val := range startingPoints {
		floodFill(&mapOfWorld, '0', val)
	}
	for _, line := range mapOfWorld {
		for _, val := range line {
			fmt.Print(string(val))
		}
		fmt.Println()
	}
	var sum int = 0
	for _, line := range mapOfWorld {
		for _, val := range line {
			if val == 'I' {
				sum++
			}
		}
	}

	return sum
	// var sum atomic.Int64
	// sum.Store(0)
	// var wg sync.WaitGroup
	// for i, line := range in {
	// 	for j, _ := range line {
	// 		wg.Add(1)
	// 		if !checkIfInsideBorders([2]int{i, j}, in, node) {
	// 			sum.Add(1)
	// 		}
	// 		wg.Done()
	// 	}
	// }
	// wg.Wait()
	// return sum.Load()
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
	res, nodes := part1(lines)
	fmt.Println("Part 1:", res)
	fmt.Println("Part 2:", part2(lines, nodes))
}
