use std::io;

fn get_line() -> String {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    buffer
}

type Matrix = Vec<Vec<f64>>;

fn get_bounds(matrix: &Matrix) -> (usize, usize) {
    (matrix.len(), matrix[0].len())
}

fn empty_matrix(r: usize, c: usize, dummy_value: f64) -> Matrix {
    vec![vec![dummy_value; c]; r]
}

#[derive(Clone)]
enum NodeType {
    Var(usize, usize),
    Tnh(usize),
    Rlu(usize, f64),
    Mul(usize, usize),
    Sum(Vec<usize>),
    Had(Vec<usize>),
}

#[derive(Clone)]
struct Node {
    data: Matrix,
    der_data: Matrix,
    t: NodeType,
}

impl Node {
    fn new(t: NodeType) -> Self {
        Node {
            t,
            der_data: Vec::new(),
            data: Vec::new(),
        }
    }

    fn calculate(&self, src: &Vec<Node>) -> Matrix {
        fn rlu(x: f64, a: f64) -> f64 {
            if x < 0.0 {
                a * x
            } else {
                x
            }
        }
        match &self.t {
            NodeType::Var(_, _) => unreachable!(),
            NodeType::Tnh(i) => src[*i]
                .data
                .iter()
                .map(|r| r.iter().map(|v| v.tanh()).collect::<Vec<f64>>())
                .collect::<Matrix>(),
            NodeType::Rlu(i, a) => src[*i]
                .data
                .iter()
                .map(|r| r.iter().map(|v| rlu(*v, *a)).collect::<Vec<f64>>())
                .collect::<Matrix>(),
            NodeType::Mul(i, j) => {
                let (a, b) = (&src[*i].data, &src[*j].data);
                let (r, m1) = get_bounds(a);
                let (m2, c) = get_bounds(b);
                assert_eq!(m1, m2);
                let mut data = empty_matrix(r, c, 0.0);

                for i in 0..r {
                    for j in 0..c {
                        for l in 0..m1 {
                            data[i][j] += a[i][l] * b[l][j];
                        }
                    }
                }

                data
            }
            NodeType::Sum(nodes) => {
                let (r, c) = get_bounds(&src[nodes[0]].data);
                let mut data = empty_matrix(r, c, 0.0);

                for &n in nodes {
                    let m = &src[n].data;
                    for i in 0..r {
                        for j in 0..c {
                            data[i][j] += m[i][j];
                        }
                    }
                }

                data
            }
            NodeType::Had(nodes) => {
                let (r, c) = get_bounds(&src[nodes[0]].data);
                let mut data = empty_matrix(r, c, 1.0);

                for &n in nodes {
                    let m = &src[n].data;
                    for i in 0..r {
                        for j in 0..c {
                            data[i][j] *= m[i][j];
                        }
                    }
                }

                data
            }
        }
    }

    fn calculate_der(&self, src: &mut Vec<Node>) {
        fn tanh_(f: f64) -> f64 {
            1.0 - f * f
        }
        fn rlu_(x: f64, a: f64) -> f64 {
            if x < 0.0 {
                a
            } else {
                1.0
            }
        }
        match &self.t {
            NodeType::Var(_, _) => unreachable!(),
            NodeType::Tnh(i) => {
                let target = &mut src[*i].der_data;
                let (r, c) = get_bounds(&target);

                for i in 0..r {
                    for j in 0..c {
                        target[i][j] += tanh_(self.data[i][j]) * self.der_data[i][j];
                    }
                }
            }
            NodeType::Rlu(i, a) => {
                let target = &mut src[*i].der_data;
                let (r, c) = get_bounds(&target);

                for i in 0..r {
                    for j in 0..c {
                        target[i][j] += rlu_(self.data[i][j], *a) * self.der_data[i][j];
                    }
                }
            }
            NodeType::Mul(i, j) => unsafe {
                let src_a = &mut *(src.get_unchecked_mut(*i) as *mut Node);
                let src_b = &mut *(src.get_unchecked_mut(*j) as *mut Node);
                let (a, b) = (&mut src_a.data, &mut src_b.data);
                let (d_a, d_b) = (&mut src_a.der_data, &mut src_b.der_data);

                let (r, m1) = get_bounds(&a);
                let (m2, c) = get_bounds(&b);
                assert_eq!(m1, m2);

                for i in 0..r {
                    for j in 0..c {
                        for l in 0..m1 {
                            d_a[i][l] += b[l][j] * self.der_data[i][j];
                            d_b[l][j] += a[i][l] * self.der_data[i][j];
                        }
                    }
                }
            },
            NodeType::Sum(nodes) => {
                let (r, c) = get_bounds(&src[nodes[0]].data);

                for &n in nodes {
                    let m = &mut src[n].der_data;
                    for i in 0..r {
                        for j in 0..c {
                            m[i][j] += self.der_data[i][j];
                        }
                    }
                }
            }
            NodeType::Had(nodes) => {
                let (r, c) = get_bounds(&self.data);

                for i in 0..r {
                    for j in 0..c {
                        for (ind1, &n) in nodes.iter().enumerate() {
                            let temp = nodes.iter().enumerate().fold(1.0, |acc, (ind2, &m)| {
                                if ind2 == ind1 {
                                    acc
                                } else {
                                    acc * src[m].data[i][j]
                                }
                            });
                            src[n].der_data[i][j] += self.der_data[i][j] * temp;
                        }
                    }
                }
            }
        }
    }

    fn parse_from_io() -> Self {
        let line = get_line();
        let mut it = line.trim().split_whitespace();
        let name = it.next().unwrap();

        let t = match name {
            "var" => {
                let r: usize = it.next().unwrap().parse().unwrap();
                let c: usize = it.next().unwrap().parse().unwrap();
                NodeType::Var(r, c)
            }
            "tnh" => {
                let i: usize = it.next().unwrap().parse().unwrap();
                NodeType::Tnh(i - 1)
            }
            "rlu" => {
                let a: usize = it.next().unwrap().parse().unwrap();
                let i: usize = it.next().unwrap().parse().unwrap();
                NodeType::Rlu(i - 1, 1.0 / a as f64)
            }
            "mul" => {
                let a: usize = it.next().unwrap().parse().unwrap();
                let b: usize = it.next().unwrap().parse().unwrap();
                NodeType::Mul(a - 1, b - 1)
            }
            "sum" => {
                let len: usize = it.next().unwrap().parse().unwrap();
                let u = it
                    .take(len)
                    .map(|x| x.parse::<usize>().unwrap() - 1)
                    .collect();
                NodeType::Sum(u)
            }
            "had" => {
                let len: usize = it.next().unwrap().parse().unwrap();
                let u = it
                    .take(len)
                    .map(|x| x.parse::<usize>().unwrap() - 1)
                    .collect();
                NodeType::Had(u)
            }
            _ => unreachable!(),
        };

        Node::new(t)
    }

    fn set_data(&mut self, data: Matrix) {
        self.data = data;
    }

    fn set_der_data(&mut self, data: Matrix) {
        self.der_data = data;
    }

    fn print_data(&self, is_der: bool) {
        let data: &Matrix = if is_der { &self.der_data } else { &self.data };
        for row in data {
            for cell in row {
                print!("{:.5} ", cell)
            }
            println!();
        }
    }

    fn fill_data_from_io(&mut self, is_der: bool) {
        let (r, c) = if !is_der {
            match self.t {
                NodeType::Var(r, c) => (r, c),
                _ => unreachable!(),
            }
        } else {
            get_bounds(&self.data)
        };

        let mut data: Matrix = Vec::new();
        for _ in 0..r {
            let line = get_line();
            let row = line
                .trim()
                .split_whitespace()
                .take(c)
                .map(|x| x.parse::<f64>().unwrap())
                .collect();
            data.push(row);
        }

        if is_der {
            self.set_der_data(data)
        } else {
            self.set_data(data)
        }
    }
}

struct Net {
    m: usize,
    k: usize,
    nodes: Vec<Node>,
}

impl Net {
    fn parse_from_io() -> Self {
        let src: Vec<usize> = get_line()
            .trim()
            .split_whitespace()
            .map(|x| x.parse::<usize>().unwrap())
            .collect();

        let (n, m, k) = (src[0], src[1], src[2]);
        let mut nodes: Vec<Node> = (0..n).map(|_| Node::parse_from_io()).collect();

        (0..m).for_each(|i| nodes[i].fill_data_from_io(false));

        Net { m, k, nodes }
    }

    fn init_der(&mut self) {
        let n = self.nodes.len();
        ((n - self.k)..n).for_each(|i| self.nodes[i].fill_data_from_io(true));
        (0..(n - self.k)).for_each(|i| {
            let (r, c) = get_bounds(&self.nodes[i].data);
            self.nodes[i].set_der_data(empty_matrix(r, c, 0.0));
        });
    }

    fn calculate(&mut self) {
        let n = self.nodes.len();
        for i in self.m..n {
            // this is because of Rust borrow checker :c
            let data = self.nodes[i].calculate(&self.nodes);
            self.nodes[i].set_data(data);
        }
    }

    fn calculate_der(&mut self) {
        let n = self.nodes.len();
        for i in (self.m..n).rev() {
            // this is because of Rust borrow checker :c
            let node = self.nodes[i].clone();
            node.calculate_der(&mut self.nodes);
        }
    }

    fn print(&self) {
        let n = self.nodes.len();
        for i in (n - self.k)..n {
            self.nodes[i].print_data(false);
        }
    }

    fn print_der(&self) {
        for i in 0..self.m {
            self.nodes[i].print_data(true);
        }
    }
}

fn main() {
    let mut net = Net::parse_from_io();

    net.calculate();
    net.print();

    net.init_der();
    net.calculate_der();
    net.print_der();
}
