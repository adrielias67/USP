cut_first :: Int -> [a] -> [a]
cut_first 0 xs = []
cut_first n [] = []
cut_first n (x:xs) = x : cut_first (n-1) xs


main :: IO ()
main = do
    let myList = [1, 2, 3, 4, 5, 6, 7]
    let cutResult = cut_first 10 myList
    putStrLn "Original List:"
    print myList
    putStrLn "Cut List:"
    print cutResult