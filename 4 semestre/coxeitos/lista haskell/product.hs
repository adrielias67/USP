prod :: [Int] -> Int
prod [] = 1
prod (x:xs) =  x * prod xs


main :: IO ()
main = do
    let myList = [2, 3]
    let p = prod myList
    putStrLn "Original List:"
    print myList
    putStrLn "Product:"
    print p
