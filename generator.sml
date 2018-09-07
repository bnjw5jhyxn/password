datatype charType = LOWERCASE | CAPITAL | DIGIT
datatype commandLineState = ST | NUM | LEN | CAP | DIG
fun update (l, i, f) =
   if i = 0
      then f (hd l) :: tl l
   else hd l :: update (tl l, i - 1, f)
fun delete (l, i) =
   if i = 0
      then tl l
   else hd l :: delete (tl l, i - 1)
fun repeat (n, f) =
   let
      fun tailRepeat i =
         if i >= n
            then ()
         else
            let
               val () = f i
            in
               tailRepeat (i + 1)
            end
   in
      tailRepeat 0
   end
fun randomWords n =
   let
      fun tailRandom (m, l) =
         if m > 0
            then
               let
                  val () = MLton.Random.srand (valOf (MLton.Random.useed ()))
               in
                  tailRandom (m - 6,
                              MLton.Random.rand ()
                              :: MLton.Random.rand ()
                              :: MLton.Random.rand ()
                              :: MLton.Random.rand ()
                              :: MLton.Random.rand ()
                              :: MLton.Random.rand ()
                              :: l)
               end
         else l
   in
      tailRandom (n, nil)
   end
fun getTypes (l, c, d, r) =
   let
      fun tailTypes (e, f, s, t, i) =
         if e > 0
            then
              let
                val j = Word.toIntX (hd s) mod (length i)
              in
                tailTypes (e - 1,
                           f,
                           tl s,
                           update (t,
                                   List.nth (i, j),
                                   fn _ => CAPITAL),
                           delete (i, j))
              end
         else if f > 0
            then
              let
                val j = Word.toIntX (hd s) mod (length i)
              in
                tailTypes (e,
                           f - 1,
                           tl s,
                           update (t,
                                   List.nth (i, j),
                                   fn _ => DIGIT),
                           delete (i, j))
              end
         else (t, s)
   in
      tailTypes (c,
                 d,
                 r,
                 List.tabulate (l, fn _ => LOWERCASE),
                 List.tabulate (l, fn x => x))
   end
fun computeChar (t, r) =
   case t of
      LOWERCASE => chr (Word.toIntX r mod 26 + ord #"a")
    | CAPITAL => chr (Word.toIntX r mod 26 + ord #"A")
    | DIGIT => chr (Word.toIntX r mod 10 + ord #"0")
fun password (l, c, d) =
   implode (ListPair.map computeChar (getTypes (l,
                                                c,
                                                d,
                                                randomWords (l + c + d))))
   ^ "\n"
fun params args =
   let
      fun tailParams (a, n, l, c, d, s) =
         if null a
            then (n, l, c, d)
         else
            case (hd a, s) of
               ("-n", ST) => tailParams (tl a, n, l, c, d, NUM)
             | ("-l", ST) => tailParams (tl a, n, l, c, d, LEN)
             | ("-c", ST) => tailParams (tl a, n, l, c, d, CAP)
             | ("-d", ST) => tailParams (tl a, n, l, c, d, DIG)
             | (_, ST) => tailParams (tl a, n, l, c, d, ST)
             | (i, NUM) => tailParams (tl a,
                                       getOpt (Int.fromString i, n),
                                       l,
                                       c,
                                       d,
                                       ST)
             | (i, LEN) => tailParams (tl a,
                                       n,
                                       getOpt (Int.fromString i, l),
                                       c,
                                       d,
                                       ST)
             | (i, CAP) => tailParams (tl a,
                                       n,
                                       l,
                                       getOpt (Int.fromString i, c),
                                       d,
                                       ST)
             | (i, DIG) => tailParams (tl a,
                                       n,
                                       l,
                                       c,
                                       getOpt (Int.fromString i, d),
                                       ST)
   in
      tailParams (args, 1, 16, 1, 1, ST)
   end
val (n, l, c, d) = params (CommandLine.arguments ())
val () = repeat (n, fn _ => print (password (l, c, d)))
