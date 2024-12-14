import Debug.Trace
import Data.List (sortOn)

moveFiles :: [Int] -> Int -> [Int] -> Int -> [Int]
moveFiles (x:y:arr) idx1 (z:j:rev) idx2
    | idx1 == idx2 = replicate z idx2
    -- | y == z = trace ("X: " ++ show x ++ " Y: " ++ show y ++ " idx1: " ++ show idx1 ++ " Z: " ++ show z ++ " J: " ++ show idx2) replicate x idx1 ++ replicate z idx2 ++ moveFiles arr (idx1 + 1) rev (idx2 - 1)
    | y <  z = replicate x idx1 ++ replicate y idx2 ++ moveFiles arr (idx1 + 1) ((z-y):y:rev) idx2
    | y >=  z = replicate x idx1 ++ replicate z idx2 ++ moveFiles (0:(y-z):arr) idx1 rev (idx2 - 1)
    | otherwise = []

-- trace ("X: " ++ show x ++ " Y: " ++ show y ++ " idx1: " ++ show idx1 ++ " Z: " ++ show z ++ " J: " ++ show idx2)
-- trace ("X: " ++ show x ++ " Y: " ++ show y ++ " idx1: " ++ show idx1 ++ " Z: " ++ show z ++ " J: " ++ show idx2)


hash :: [Int] -> Int
hash [] = 0
hash xs = hashHelper xs 0

hashHelper :: [Int] -> Int -> Int
hashHelper [] _ = 0
hashHelper (x:xs) idx = idx * x + hashHelper xs (idx + 1)

part1 :: [Int] -> Int
part1 xs = hash (moveFiles arr idx1 rev idx2)
    where
        arr = xs
        idx1 = 0
        rev = reverse xs
        idx2 = length xs `div` 2

-- part 2 is in main2.cpp

parseInput :: String -> [Int]
parseInput = map (\x -> read [x])

main :: IO()
main = do
    input <- readFile "test_input"
    let parsed = parseInput input
    putStrLn ("Part 1: " ++ show (part1 parsed))
    -- putStrLn ("Part 2: " ++ show (part2 parsed))