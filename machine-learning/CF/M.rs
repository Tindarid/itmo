use std::io::{self, BufRead};

fn get_ranks(a: Vec<i32>) -> Vec<usize> {
    let mut temp: Vec<(usize, &i32)> = a.iter().enumerate().collect();
    temp.sort_by(|(_, a), (_, b)| a.cmp(b));

    let mut ans = vec![0; a.len()];
    for (rank, (ind, _)) in temp.iter().enumerate() {
        ans[*ind] = rank;
    }
    ans
}

fn main() {
    let mut buffer = String::new();

    io::stdin().read_line(&mut buffer).unwrap();
    let n: u64 = buffer.trim().parse().unwrap();

    let mut x: Vec<i32> = Vec::new();
    let mut y: Vec<i32> = Vec::new();

    for line in io::stdin()
        .lock()
        .lines()
        .take(n as usize)
        .map(|l| l.unwrap())
    {
        let mut iter = line.trim().split_whitespace().map(|a| a.parse().unwrap());
        x.push(iter.next().unwrap());
        y.push(iter.next().unwrap());
    }

    let x = get_ranks(x);
    let y = get_ranks(y);
    let d: i64 = x
        .iter()
        .zip(y.iter())
        .map(|(&a, &b)| ((a as i64) - (b as i64)).pow(2))
        .sum();
    let ans = 1.0 - (d as f64) * 6.0 / (n * (n - 1) * (n + 1)) as f64;
    println!("{:.10}", ans)
}
