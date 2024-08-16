use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        panic!("Expected exactly two arguments found {}", args.len());
    }

    if args[1] == "--help" {
        println!("Usage:\n\tmath_repl \"EXPRESSION\"");
        return;
    }

    for ch in args[1].chars() {
        println!("{ch}");
    }
}
