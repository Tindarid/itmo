use std::io;

fn main() {
    let (m, values) = {
        let mut buffer = String::new();
        io::stdin().read_line(&mut buffer).unwrap();
        let m: usize = buffer.trim().parse().unwrap();
        let total = 1 << m;
        let mut values: Vec<usize> = vec![0; total];
        for i in 0..total {
            buffer.truncate(0);
            io::stdin().read_line(&mut buffer).unwrap();
            values[i] = buffer.trim().parse().unwrap();
        }
        (m, values)
    };

    let total = 1 << (m - 1);

    println!("2");
    println!("{} 1", total);

    let mut temp: Vec<f32> = vec![0.0; m + 1];
    for i in 0..total {
        for j in 1..m {
            let mask = 1 << (j - 1);
            temp[j] = if i & mask == mask { 1.0 } else { -1.0 }
        }
        let (w, b) = match (values[2 * i], values[2 * i + 1]) {
            (0, 0) => (0, -0.5),
            (0, 1) => (1, -0.5),
            (1, 0) => (-1, 0.5),
            (1, 1) => (0, 0.5),
            _ => unreachable!(),
        };
        temp[0] = w as f32;
        temp[m] = b - i.count_ones() as f32;
        println!(
            "{}",
            temp.iter()
                .fold(String::new(), |a, v| a + &v.to_string() + " ")
        );
    }

    println!(
        "{}{}",
        (0..total).fold(String::new(), |a, _| a + "1 "),
        -0.5
    );
}
