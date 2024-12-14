import Data.ByteString.Lazy (split)
import GHC.Conc (par, pseq)

blink :: [Int] -> [Int]
blink [] = []
blink (x:xs)
    | x == 0 = 1 : blink xs
    | even (length (show x)) =
      let (l_half, r_half) = splitAt (length (show x) `div` 2) (show x)
      in read l_half : read r_half : blink xs
    | otherwise = (x * 2024) : blink xs

blinkXTimes :: [Int] -> Int -> [Int]
blinkXTimes xs 0 = xs
blinkXTimes xs x = blinkXTimes (blink xs) (x - 1)

part1 :: [Int] -> Int
part1 xs = length (blinkXTimes xs 25)

parseInput :: String -> [Int]
parseInput s = map read (words s)

part2 :: [Int] -> Int
part2 [] = 0
part2 (x:xs) = par n1 (pseq n2 (n1 + n2))
    where n1 = length (blinkXTimes [x] 75)
          n2 = part2 xs

main :: IO()
main = do
    input <- readFile "input"
    let parsed = parseInput input
    putStrLn ("Part 1: " ++ show (part1 parsed))
    putStrLn ("Part 2: " ++ show (part2 parsed))