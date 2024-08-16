mod scanner;
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

    let mut scanner = scanner::Scanner::new(args[1].clone());

    let tokens = scanner.scan();

    if scanner.has_error {
        for err in scanner.errors {
            eprintln!("{err}");
        }
    } else {
        for token in tokens {
            println!("{:?}", token);
        }
    }
}
