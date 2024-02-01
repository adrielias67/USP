cut_last :: Int -> [a] -> [a]
cut_last 0 xs = xs
cut_last n [] = []
cut_last n (x:xs) = cut_last (n-1) xs


main :: IO ()
main = do
    let myList = [1, 2, 3, 4, 5, 6, 7]
    let cutResult = cut_last 10 myList
    putStrLn "Original List:"
    print myList
    putStrLn "Cut List:"
    print cutResult