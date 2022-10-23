from subprocess import Popen, PIPE
import random

def count(poly, x):
    poly.reverse()
    for i in poly:
       assert(i >= 0)
       assert(i <= 238)
    if (x == 0):
        return (poly[0] + 10 * 239) % 239
    assert (x == 1)
    ans = 0
    for i in poly:
       ans = (ans + i + 10 * 239) % 239
    return ans

def main():
    random.seed()

    test_cases = [
            #{
            # "number" : 2,
            # "str" : "x1 & x2 | !x1 & !x2",
            # "func" : (lambda x1,x2: x1 and x2 or (not x1) and (not x2))
            #},
            #{
            # "number" : 2,
            # "str" : "x1 | x2",
            # "func" : (lambda x1,x2: x1 or x2)
            #},
            #{
            # "number" : 3,
            # "str" : "x1 | x2 | x3",
            # "func" : (lambda x1,x2,x3: x1 or x2 or x3)
            #},
            #{
            # "number" : 3,
            # "str" : "x1 & x2 | x3",
            # "func" : (lambda x1,x2,x3: x1 and x2 or x3)
            #},
            #{
            # "number" : 3,
            # "str" : "x1 & (x2 | x3)",
            # "func" : (lambda x1,x2,x3: x1 and (x2 or x3))
            #},
            #{
            # "number" : 4,
            # "str" : "x1 & x4 | x3 & x4",
            # "func" : (lambda x1,x2,x3,x4: (x1 and x4) or (x3 and x4))
            #},
            #{
            # "number" : 7,
            # "str" : "x1 & x2 & x3 & x4 & x5 & x6 & x7",
            # "func" : (lambda x1,x2,x3,x4,x5,x6,x7: x1 and x2 and x3 and x4 and x5 and x6 and x7)
            #},
            {
             "number" : 5,
             "str" : "x1 | x5 | (x2 | x4 & x5) | !(x1 & x4) | x3",
             "func" : (lambda x1,x2,x3,x4,x5: x1 or x5 or (x2 or x4 and x5) or (not x1 and x4) or x3)
            },
    ]

    for test in test_cases:
        process = Popen([r'./A', 'arg1'], stdin=PIPE, stdout=PIPE)
        total = 100
        total_failed = 0
        for t in range(0, total):
            to_program = '{0}\n{1}\n{2}\n'.format(test["number"], test["str"], t % pow(2, test["number"]))
            ws = []
            for r in range(0, test["number"] - 1):
                rr = random.randint(0, 1)
                to_program += str(rr) + "\n"
                ws.append(rr)
            ws.append(random.randint(0, 1))

            process.stdin.write(to_program)
            print("src: " + to_program)

            failed = False
            last_w = t % pow(2, test["number"])

            poly = []
            for r in range(0, test["number"]):
                from_program = process.stdout.readline()
                print(from_program[:-1])
                from_program = process.stdout.readline()
                degree = int(from_program)
                from_program = process.stdout.readline()[:-1]
                poly = list(map(int, from_program.split()))
                print("poly: " + str(poly))

                fi = count(poly, 0)
                se = count(poly, 1)
                print("fi: " + str(fi))
                print("se: " + str(se))
                print("last_w: " + str(last_w))
                if (not failed and (((fi + se) % 239) != last_w)):
                    print("Faileddd")
                    failed = True
                last_w = count(poly, ws[r])
                print("next r is: " + str(ws[r]))
                print("k is: " + str(last_w))
                print("")
            last_ans = test["func"](*ws)

            if (int(last_ans) != int(last_w)):
                failed = True
                print("!Failed in last check!")
            if failed:
                total_failed = total_failed + 1
        print("failed: " + str(float(total_failed) / total))
        process.stdin.write("0\n")
        a = 0 
        while process.poll() == None:
            a = a + 1

if __name__ == "__main__":
    main()
