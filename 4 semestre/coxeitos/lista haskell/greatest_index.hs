greatest_i_rec :: [Int] -> Int -> Int
greatest_i_rec [] _ = 0
greatest_i_rec (x:xs) i = 
    if x > greatest_i_rec xs (i+1)
        then i
        else greatest_i_rec xs (i+1)


greatest_i :: [Int] -> Int
greatest_i xs = greatest_i_rec xs 1


main :: IO ()
main = do
    let myList = [2, 3, 4, 57, 6, 7]
    let i = greatest_i myList
    putStrLn "Original List:"
    print myList
    putStrLn "Product:"
    print i