cut_greater :: Ord a => a -> [a] -> [a]
cut_greater n [] = []
cut_greater n (x:xs) =
    if x > n
        then x : cut_greater n xs
        else cut_greater n xs


main :: IO ()
main = do
    let myList = [1, 2, 3, 4, 5, 6, 7]
    let cutResult = cut_greater 2 myList
    putStrLn "Original List:"
    print myList
    putStrLn "Cut List:"
    print cutResult