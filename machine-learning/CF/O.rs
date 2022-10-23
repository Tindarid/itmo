use std::io::{self, BufRead};

fn read_u64() -> usize {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    buffer.trim().parse().unwrap()
}

fn read_vec_i64(k: usize, n: usize) -> Vec<Vec<i64>> {
    let mut ans = vec![Vec::new(); k];
    for l in io::stdin().lock().lines().take(n).map(|l| l.unwrap()) {
        let mut iter = l.trim().split_whitespace();
        let x: usize = iter.next().unwrap().parse().unwrap();
        let y: i64 = iter.next().unwrap().parse().unwrap();
        ans[x - 1].push(y);
    }
    ans
}

fn main() {
    let k = read_u64();
    let n = read_u64();
    let classes = read_vec_i64(k, n);

    let e_y_from_x_sq: f64 = classes
        .iter()
        .map(|v| {
            if v.is_empty() {
                0.0
            } else {
                let sum = v.iter().sum::<i64>() as f64;
                sum * sum / (v.len() as f64) / (n as f64)
            }
        })
        .sum();

    let e_y_2: f64 = classes
        .iter()
        .map(|v| v.iter().map(|x| (x * x) as f64).sum::<f64>() as f64)
        .sum::<f64>()
        / (n as f64);

    println!("{:.10}", e_y_2 - e_y_from_x_sq);
}
