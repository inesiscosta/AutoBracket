use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let first_line = lines.next().unwrap().unwrap();
    let mut parts = first_line.split_whitespace();
    let _n: usize = parts.next().unwrap().parse().unwrap();
    let _m: usize = parts.next().unwrap().parse().unwrap();

    let mut operation_table = vec![vec![0; _n]; _n];
    for i in 0.._n {
        let line = lines.next().unwrap().unwrap();
        let mut parts = line.split_whitespace();
        for j in 0.._n {
            operation_table[i][j] = parts.next().unwrap().parse().unwrap();
        }
    }

    let mut sequence = vec![0; _m];
    let line = lines.next().unwrap().unwrap();
    let mut parts = line.split_whitespace();
    for i in 0.._m {
        sequence[i] = parts.next().unwrap().parse().unwrap();
    }

    let desired_result: i32 = lines.next().unwrap().unwrap().parse().unwrap();

    let mut results_table = vec![vec![Vec::new(); _m]; _m];
    for i in 0.._m {
        results_table[i][i].push((sequence[i], sequence[i].to_string()));
    }

    for length in 2..=_m {
        for i in (0..=_m - length).rev() {
            let j = i + length - 1;
            for k in (i..j).rev() {
                let mut temp_results = Vec::new();
                for left in &results_table[i][k] {
                    for right in &results_table[k + 1][j] {
                        let combined_val = operation_table[left.0 as usize - 1][right.0 as usize - 1];
                        let combined_expr = format!("({} {})", left.1, right.1);
                        temp_results.push((combined_val, combined_expr.clone()));
                        if combined_val == desired_result && length == _m {
                            println!("1\n{}", combined_expr);
                            return;
                        }
                    }
                }
                results_table[i][j].extend(temp_results);
            }
        }
    }
    println!("0");
}