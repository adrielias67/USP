greatest :: [Int] -> Int
greatest [] = 0
greatest (x:xs) = 
    if x > greatest xs
        then x
        else greatest xs


main :: IO ()
main = do
    let myList = [2, 3, 4, 5, 6, 7]
    let p = greatest myList
    putStrLn "Original List:"
    print myList
    putStrLn "Product:"
    print p