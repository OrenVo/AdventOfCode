package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

type Node struct {
	name      string
	leftName  string
	left      *Node
	rightName string
	right     *Node
}

// var stop bool = false

// func aproximateCount(count *int) {
// 	lastCount := *count
// 	for !stop {
// 		time.Sleep(1 * time.Second)
// 		fmt.Println("Count: ", *count)
// 		fmt.Println("Speed: ", *count-lastCount, "/s")
// 		lastCount = *count
// 	}
// }

func main() {

	in, err := io.ReadAll(os.Stdin)
	if err != nil {
		fmt.Println("Error reading input")
		os.Exit(1)
	}
	str := string(in)
	// split string into lines
	lines := strings.Split(str, "\n")
	directions := lines[0]
	lines = lines[1:]
	nodes := make([]Node, 0)
	for _, line := range lines {
		if line == "" {
			continue
		}
		parts := strings.Split(line, " = ")
		name := parts[0]
		dstLeft := strings.Split(parts[1], ", ")
		left := dstLeft[0][1:]
		right := dstLeft[1][:len(dstLeft[1])-1]
		nodes = append(nodes, Node{name, left, nil, right, nil})
	}

	for i, node := range nodes {
		for j, node2 := range nodes {
			if node2.name == node.leftName {
				nodes[i].left = &nodes[j]
			}
			if node2.name == node.rightName {
				nodes[i].right = &nodes[j]
			}
		}
	}
	var count int = 0
	// go aproximateCount(&count)
	var lastNode *Node = &nodes[0]
	for _, node := range nodes {
		if node.name == "AAA" {
			lastNode = &node
			break
		}
	}
	var direction_idx int = 0
	for {
		if lastNode.name == "ZZZ" {
			break
		}
		if string(directions[direction_idx]) == string("L") {
			lastNode = lastNode.left
		} else if string(directions[direction_idx]) == string("R") {
			lastNode = lastNode.right
		}
		count++
		direction_idx++
		if direction_idx >= len(directions) {
			direction_idx = 0
		}
	}
	stop = true
	fmt.Println("Part 1: ", count)

	// Part 2
	lastNodes := make([]*Node, 0)
	count2 := 0
	for i, node2 := range nodes {
		if node2.name[len(node2.name)-1] == 'A' {
			lastNodes = append(lastNodes, &nodes[i])
		}
	}
	idx2 := 0
	for {
		var end bool = true
		for _, lastNode := range lastNodes {
			name := lastNode.name
			if name[len(name)-1] != 'Z' {
				end = false
			}
		}
		if end {
			break
		}

		for i, lastNode := range lastNodes {
			if string(directions[idx2]) == string("L") {
				lastNodes[i] = lastNode.left
			} else if string(directions[idx2]) == string("R") {
				lastNodes[i] = lastNode.right
			}
		}

		count2++
		idx2++
		if idx2 >= len(directions) {
			idx2 = 0
		}
	}
	fmt.Println("Part 2: ", count2)
	os.Exit(0)
}
