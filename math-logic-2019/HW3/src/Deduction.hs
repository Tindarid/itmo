module Main where

import Grammar

data Result = Axiom | MP Expr Expr | Hyp

--main = mapM_ writeLine (generateMP (Var "A") (Var "B"))
main = mapM_ writeLine (generate10 (Var "A"))

writeLine (expr, result) = putStrLn $ show $ expr

deduction h [] = []
deduction h ((e, r):as) = (helper h (e, r)) ++ (deduction h as)
                          where helper hypo (expr, (MP a b)) = generate3 hypo expr a b
                                helper hypo (expr, Axiom)    = generate1 hypo expr 
                                helper hypo (expr, Hyp)     | hypo == expr = generate2 hypo expr
                                                            | otherwise    = generate1 hypo expr

generate1 hypo expr = [(f, Hyp), (s, Axiom), (t, MP s f)]
                      where s = Impl expr (Impl hypo expr)
                            f = expr
                            t = Impl hypo expr
generate2 hypo a     = [(f1, Axiom), (f2, Axiom), (f3, Axiom), (f4, Axiom), (f5, MP f3 f4)]
                       where f1 = Impl a (Impl a a)
                             f2 = Impl (Impl a (Impl a a)) (Impl (Impl a (Impl (Impl a a) a)) (Impl a a))
                             f3 = Impl (Impl a (Impl (Impl a a) a)) (Impl a a)
                             f4 = Impl a (Impl (Impl a a) a)
                             f5 = Impl hypo a
generate3 a i k j   = [(f1, Axiom), (f2, MP f1 f3), (f5, MP f2 f4)]
                       where f1 = Impl f3 f2
                             f2 = Impl f4 (Impl a i)
                             f3 = Impl a j
                             f4 = Impl a (Impl j i)
                             f5 = Impl a i

generateLemm1 a b = [
                     (f1, Hyp),
                     (f2, Hyp),
                     (f3, Axiom),
                     (f4, MP f3 f1),
                     (f5, Axiom),
                     (f6, MP f5 f2),
                     (f7, MP f6 f4)
                    ]
                    where f1 = Not b
                          f2 = Impl a b
                          f3 = Impl f1 f4
                          f4 = Impl a (Not b)
                          f5 = Impl f2 f6
                          f6 = Impl f4 f7
                          f7 = Not a

generateLemm2 a b = [
                     (f1, Axiom)] ++ 
                     f2 ++ 
                    [
                     (f3, MP f1 (Impl (Impl a b) (Not a))),
                     (f4, Axiom),
                     (f5, Hyp),
                     (f6, MP f4 f5),
                     (f7, MP f3 f6)
                    ]
                    where f1 = Impl (Impl (Impl a b) (Not a)) f3
                          f2 = deduction (Impl a b) (generateLemm1 a b)
                          f3 = Impl f6 f7
                          f4 = Impl f5 f6
                          f5 = Not (Not a)
                          f6 = Impl (Impl a b) f5
                          f7 = Not (Impl a b)

generateMP a b = [
                  (fa, Hyp),
                  (fimpl, Hyp),
                  (f3, Axiom)
                 ] ++ 
                  (deduction (Not b) (generateLemm2 a b)) ++ 
                 [
                  (f5, MP f3 f4),
                  (f6, Axiom),
                  (f7, MP f6 fimpl),
                  (fb, MP f5 f7)
                 ]
                 where impl = Impl a b
                       fa = Not (Not a)
                       fb = Not (Not b)
                       fimpl = Not (Not impl)
                       f3 = Impl f4 f5
                       f6 = Impl fimpl f7
                       f4 = Impl (Not b) (Not impl)
                       f5 = Impl (Impl (Not b) fimpl) fb
                       f7 = Impl (Not b) fimpl

generate10 a = [(f1, Axiom)] ++ (deduction fss (generateLemm1 a (Impl ffa a))) ++ 
               [(f3, Axiom)] ++ (deduction fss (generateLemm1 fa (Impl ffa a))) ++ 
               [
                (some, Axiom),
                (some2, MP some some3),
                (fsss, MP some2 some3)
               ]
               where f1 = Impl a (Impl ffa a)
                     ffa = Not fa
                     fa = Not a
                     f3 = Impl fa (Impl ffa a)
                     fss = Not fs
                     fsss = Not fss
                     fs = Impl ffa a
                     some = Impl some3 some2
                     some2 = Impl (Impl fss ffa) fsss
                     some3 = Impl fss fa
