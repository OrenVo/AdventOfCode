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
mulMulInstruction (Mul a b) = a * b


part1 :: String -> Int
part1 input = case findMulInstructions input of
    Left err -> error $ show err
    Right results -> trace (show (filter (\(Mul a b) -> a /= 0 || b /= 0) results)) (sum $ map (\(Mul a b) -> a * b) (filter (\(Mul a b) -> a /= 0 || b /= 0) results))

findMulInstructionsDo :: String -> Either ParseError [MulInstruction]
findMulInstructionsDo = parse (many (try mulParserOrDo <|> consumeOne)) "" -- TODO - parse untile dont then skip until do

mulParserOrDo :: Parser MulInstruction
mulParserOrDo = do
    return Do

doParser :: Parser MulInstruction
doParser = do
    return Do

dontParser :: Parser MulInstruction
dontParser = do
    return Dont


part2 :: String -> Int
part2 input = case findMulInstructionsDo input of
    Left err -> error $ show err
    Right results -> trace (show (filter (\(Mul a b) -> a /= 0 || b /= 0) (Do : results))) (sum $ map (\(Mul a b) -> a * b) (filter (\(Mul a b) -> a /= 0 || b /= 0) (Do : results)))


main :: IO()
main = do
    input <- readFile "input"
    let result1 = part1 input
    let result2 = part2 input
    print result1
    print result2
