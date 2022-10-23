use std::io::{self, BufRead};

struct Object {
    attrs: Vec<i32>,
    class: usize,
}

enum Vertex {
    Leaf {
        id: usize,
        class: usize,
    },
    Node {
        id: usize,
        f_ind: usize,
        b: f64,
        left: Box<Vertex>,
        right: Box<Vertex>,
    },
}

struct DecisionTree {
    root: Vertex,
    nodes: usize,
}

fn cnt(cnt: &[u64], total: &usize) -> f64 {
    cnt.iter()
        .map(|x| *x as f64)
        .map(|x| x * (1.0 - x / *total as f64))
        .sum::<f64>()
}

fn change_cnt(
    from: &mut Vec<u64>,
    to: &mut Vec<u64>,
    cl: usize,
    total1: &mut usize,
    total2: &mut usize,
) {
    from[cl] -= 1;
    *total1 -= 1;
    to[cl] += 1;
    *total2 += 1;
}

fn best_gini(objects: &mut [Object], k: usize, m: usize) -> Option<(usize, f64)> {
    let total = objects.len();
    let mut cnt_all: Vec<u64> = vec![0; k];
    for p in objects.iter() {
        cnt_all[p.class] += 1;
    }
    let mut best = cnt(&cnt_all, &total);
    let mut best_ans: Option<(usize, f64)> = None;

    for i in 0..m {
        objects.sort_by(|a, b| a.attrs[i].cmp(&b.attrs[i]));

        let mut total1 = total;
        let mut total2 = 0;
        let mut cnt1: Vec<u64> = vec![0; k];
        let mut cnt2: Vec<u64> = vec![0; k];
        for p in objects.iter() {
            cnt1[p.class] += 1;
        }

        let mut cur = 0;
        for j in 0..total {
            if objects[j].attrs[i] == objects[cur].attrs[i] {
                change_cnt(
                    &mut cnt1,
                    &mut cnt2,
                    objects[j].class,
                    &mut total1,
                    &mut total2,
                );
                continue;
            }
            let score = cnt(&cnt1, &total1) + cnt(&cnt2, &total2);
            change_cnt(
                &mut cnt1,
                &mut cnt2,
                objects[j].class,
                &mut total1,
                &mut total2,
            );

            if score <= best {
                best_ans = Some((
                    i,
                    (objects[j].attrs[i] + objects[cur].attrs[i]) as f64 / 2.0,
                ));
                best = score;
            }
            cur = j;
        }
    }

    best_ans
}

fn mode(objects: &[Object], k: usize) -> usize {
    let mut cnt: Vec<u64> = vec![0; k];
    for i in objects.iter() {
        cnt[i.class] += 1;
    }
    cnt.iter()
        .enumerate()
        .max_by(|(_, a), (_, b)| a.cmp(b))
        .unwrap()
        .0
}

impl Vertex {
    fn new(mut objects: Vec<Object>, k: usize, h: u16, id: usize) -> (Self, usize) {
        let max = objects.iter().map(|x| x.class).max().unwrap();
        let min = objects.iter().map(|x| x.class).min().unwrap();
        if min == max {
            return (Self::Leaf { id, class: min }, id + 1);
        }

        if h == 0 {
            return (
                Self::Leaf {
                    id,
                    class: mode(&objects, k),
                },
                id + 1,
            );
        }

        let m = objects[0].attrs.len();
        let ans = best_gini(&mut objects, k, m);
        if ans == None {
            return (
                Self::Leaf {
                    id,
                    class: mode(&objects, k),
                },
                id + 1,
            );
        }
        let (f_ind, b) = ans.unwrap();

        let (left, right): (Vec<_>, Vec<_>) = objects
            .into_iter()
            .partition(|e| (e.attrs[f_ind] as f64) < b);
        let was_id = id;
        let (left, id) = Vertex::new(left, k, h - 1, id + 1);
        let (right, id) = Vertex::new(right, k, h - 1, id);

        (
            Self::Node {
                id: was_id,
                f_ind,
                b,
                left: Box::new(left),
                right: Box::new(right),
            },
            id,
        )
    }

    fn get_id(&self) -> usize {
        match self {
            Vertex::Leaf { id, class: _ }
            | Vertex::Node {
                id,
                f_ind: _,
                b: _,
                left: _,
                right: _,
            } => id + 1,
        }
    }

    fn print(&self) {
        match self {
            Vertex::Leaf { id: _, class } => {
                println!("C {}", class + 1);
            }
            Vertex::Node {
                id: _,
                f_ind,
                b,
                left,
                right,
            } => {
                println!(
                    "Q {} {:.10} {} {}",
                    f_ind + 1,
                    b,
                    left.get_id(),
                    right.get_id()
                );
                left.print();
                right.print();
            }
        }
    }
}

impl DecisionTree {
    fn new(objects: Vec<Object>, k: usize, h: u16) -> Self {
        let (root, nodes) = Vertex::new(objects, k, h, 0);
        Self { root, nodes }
    }

    fn print(&self) {
        println!("{}", self.nodes);
        self.root.print();
    }
}

fn input() -> (Vec<Object>, usize, u16) {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();

    let mut iter = buffer.trim().split_whitespace();
    let _: usize = iter.next().unwrap().parse().unwrap();
    let k: usize = iter.next().unwrap().parse().unwrap();
    let h: u16 = iter.next().unwrap().parse().unwrap();

    buffer.clear();
    io::stdin().read_line(&mut buffer).unwrap();
    let n: usize = buffer.trim().parse().unwrap();
    let mut objects: Vec<Object> = Vec::new();

    for l in io::stdin().lock().lines().take(n).map(|l| l.unwrap()) {
        let mut attrs: Vec<i32> = l
            .trim()
            .split_whitespace()
            .map(|x| x.parse::<i32>().unwrap())
            .collect::<_>();
        let class = (attrs.pop().unwrap() - 1) as usize;
        objects.push(Object { attrs, class });
    }

    (objects, k, h)
}

fn main() {
    let (objects, k, h) = input();
    let t = DecisionTree::new(objects, k, h);

    t.print();
}
