import GHC.Conc (par, pseq)

part1 :: [Int] -> Int
part1 xs = blinkXDFS xs 25

parseInput :: String -> [Int]
parseInput s = map read (words s)

part2 :: [Int] -> Int
part2 xs = blinkXDFS xs 75

countDigitsHelper :: Int -> Int -> Int
countDigitsHelper 0 y = y
countDigitsHelper x y = countDigitsHelper (x `div` 10) (y +1)

countDigits :: Int -> Int
countDigits x = countDigitsHelper x 0

blinkDFS :: Int -> Int -> Int
blinkDFS _ 0 = 1
blinkDFS 0 depth = blinkDFS 1 (depth - 1)
blinkDFS x depth
    | let digit_count = countDigits x,
      even digit_count =
      let mask = 10 ^ (digit_count `div` 2)
          left = x `div` mask
          right = x `mod` mask
      in blinkDFS left (depth - 1) + blinkDFS right (depth - 1)
    | otherwise = blinkDFS (x * 2024) (depth - 1)

blinkXDFS :: [Int] -> Int -> Int
blinkXDFS xs y = foldr (\ x -> (+) (blinkDFS x y)) 0 xs

-- parallel blink for each number
pblinkXDFS :: [Int] -> Int -> Int
pblinkXDFS [] _ = 0
pblinkXDFS (x:xs) y = par n1 (pseq n2 (n1 + n2))
    where n1 = blinkDFS x y
          n2 = pblinkXDFS xs y

main :: IO()
main = do
    input <- readFile "input"
    let parsed = parseInput input
    putStrLn ("Part 1: " ++ show (part1 parsed))
    putStrLn ("Part 2: " ++ show (part2 parsed))