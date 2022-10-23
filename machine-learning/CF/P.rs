use std::collections::HashMap;
use std::io::{self, BufRead};

fn input() -> (usize, usize, usize, HashMap<(usize, usize), usize>) {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let mut iter = buffer.trim().split_whitespace();
    let k1: usize = iter.next().unwrap().parse().unwrap();
    let k2: usize = iter.next().unwrap().parse().unwrap();

    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let n: usize = buffer.trim().parse().unwrap();

    let mut count = HashMap::new();
    for l in io::stdin().lock().lines().take(n).map(|a| a.unwrap()) {
        let mut iter = l.trim().split_whitespace();
        let a: usize = iter.next().unwrap().parse().unwrap();
        let b: usize = iter.next().unwrap().parse().unwrap();
        let k = (a - 1, b - 1);
        match count.get_mut(&k) {
            Some(c) => *c += 1,
            None => {
                count.insert(k, 1);
            }
        }
    }

    (k1, k2, n, count)
}

fn main() {
    let (k1, k2, n, count) = input();
    let mut rows: Vec<u64> = vec![0; k1];
    let mut cells: Vec<u64> = vec![0; k2];

    for ((row, cell), c) in &count {
        rows[*row] += *c as u64;
        cells[*cell] += *c as u64;
    }

    let n = n as f64;
    let mut hi = rows.iter().sum::<u64>() as f64 * cells.iter().sum::<u64>() as f64;
    hi /= n;

    for ((r, c), cc) in count {
        let e = rows[r] as f64 * cells[c] as f64 / n;
        hi -= e;
        let a = cc as f64 - e;
        hi += a * a / e;
    }

    println!("{}", hi);
}
