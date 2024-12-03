import Text.Parsec
import Text.Parsec.String (Parser)
import Debug.Trace
import Data.Binary.Get (skip)

data MulInstruction =
    Do    |
    Dont  |
    Mul { a :: Int , b :: Int }

instance Show MulInstruction where
  show :: MulInstruction -> String
  show Do = "Do()"
  show Dont = "Don't()"
  show (Mul a b) = "Mul(" ++ show a ++ "," ++ show b ++ ")"



number :: Parser Int
number = read <$> (try (count 3 digit) <|> try (count 2 digit) <|> count 1 digit)

skipGarbage :: Parser ()
skipGarbage = many (noneOf "m") >> return ()

consumeOne :: Parser MulInstruction
consumeOne = do
    anyChar
    many (noneOf "md")
    return (Mul 0 0)

findMulInstructions :: String -> Either ParseError [MulInstruction]
findMulInstructions = parse (many (try mulParser <|> consumeOne)) ""

mulParser :: Parser MulInstruction
mulParser = do
    string "mul("
    x <- number
    char ','
    y <- number
    char ')'
    return (Mul x y)


mulMulInstruction :: MulInstruction -> Int
mulMulInstruction Do = 0
mulMulInstruction Dont = 0
mulMulInstruction (Mul a b) = a * b


findMulInstructionsDo :: String -> Either ParseError [MulInstruction]
findMulInstructionsDo = parse (many (try mulParserOrDo <|> consumeOne)) "" -- TODO - parse untile dont then skip until do

mulParserOrDo :: Parser MulInstruction
mulParserOrDo = try mulParser <|> try doParser <|> try dontParser

doParser :: Parser MulInstruction
doParser = do
    string "do()"
    return Do

dontParser :: Parser MulInstruction
dontParser = do
    string "don't()"
    return Dont

advancedFilter :: [MulInstruction] -> [MulInstruction]
advancedFilter = go True
  where
    go _ [] = []
    go keep (Do:xs) = go True xs
    go keep (Dont:xs) = go False xs
    go keep (Mul 0 0:xs) = go keep xs
    go keep (Mul a b:xs) = if keep then Mul a b : go keep xs else go keep xs

part1 :: String -> Int
part1 input = case findMulInstructions input of
    Left err -> error $ show err
    -- trace (show (filter (\(Mul a b) -> a /= 0 || b /= 0) results))
    Right results -> sum $ map (\(Mul a b) -> a * b) (filter (\(Mul a b) -> a /= 0 || b /= 0) results)

filterZero :: MulInstruction -> Bool
filterZero (Mul 0 0) = False
filterZero _ = True

part2 :: String -> Int
part2 input = case findMulInstructionsDo input of
    Left err -> error $ show err
    -- trace (show (filter filterZero results))
    Right results -> (sum $ map (\(Mul a b) -> a * b) (advancedFilter results))


main :: IO()
main = do
    input <- readFile "input"
    putStrLn ("Part 1: " ++ show (part1 input))
    putStrLn ("Part 2: " ++ show (part2 input))
